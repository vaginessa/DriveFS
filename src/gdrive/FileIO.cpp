//
// Created by eric on 04/02/18.
//

#include <gdrive/FileIO.h>
#include <thread>
#include <cpprest/http_client.h>
#include <easylogging++.h>
#include <experimental/filesystem>
using namespace web::http::client;          // HTTP client features
using Object = DriveFS::_Object;
namespace fs = std::experimental::filesystem;

inline uint64_t getChunkStart(uint64_t start, uint64_t buffer_size){
    uint64_t chunkNumber = start / buffer_size;
    return chunkNumber * buffer_size;
}

inline uint64_t getChunkNumber(uint64_t start, uint64_t buffer_size){
    return  start / buffer_size;

}

namespace DriveFS{
    size_t FileIO::write_buffer_size = BLOCK_DOWNLOAD_SIZE;
    FileIO::FileIO(GDriveObject object, int flag, Account *account):
            m_account(account),
            m_file(std::move(object)),
            b_is_uploading(false),
            b_is_cached(false),
            b_needs_uploading(false),
            m_readable( (flag & 0x8000) || (flag & O_RDONLY) || (flag & O_RDWR)),
            m_writeable((flag & O_WRONLY) || (flag & O_RDWR)),
            write_buffer(nullptr),
            write_buffer2(nullptr),
            first_write_to_buffer(0),
            last_write_to_buffer(0),
            m_event(1)
    {
        setFileName();
        assert(m_readable || m_writeable || flag == 0);

    }

    FileIO::~FileIO(){
        if(write_buffer != nullptr){
            delete write_buffer;
        }
        if(write_buffer2 != nullptr){
            delete write_buffer2;
        }
    }

    std::vector<unsigned char>* FileIO::read(const size_t &size, const off_t &off) {
        if(b_is_cached && stream && stream.is_open()){
            auto buf = new std::vector<unsigned char>(size);
            stream.seekg(off);
            stream.read( (char *) buf->data(), size);
            return buf;
        }
        try {
            return getFromCache(size, off);
        }catch(std::exception &e){
            LOG(ERROR) << e.what();
            m_file->m_event.signal();
            return getFromCache(size, off);
        }

    }

    void FileIO::download(DownloadItem cache, std::string cacheName, uint64_t start, uint64_t end,  uint_fast8_t backoff) {
        LOG(INFO) << "Downloading " << m_file->getName() <<"\t" << start;
        http_client client = m_account->getClient();
        uri_builder builder( std::string("files/") +  m_file->getId());
        builder.append_query("alt", "media");
//        builder.append_query("acknowledgeAbuse", "true");
        builder.append_query("supportsTeamDrives", "true");

        http_request req;
        auto &headers = req.headers();
        std::stringstream range;
        range << "bytes="
              << std::to_string(start)
              << "-"
              << std::to_string(end);
        headers.add("Range", range.str());

        req.set_method(methods::GET);
        req.set_request_uri(builder.to_uri());

        LOG(DEBUG) << req.headers()["Range"];
        http_response  resp = client.request(req).get();
        if(resp.status_code() != 206 && resp.status_code() != 200){
            LOG(ERROR) << "Failed to get file fragment : " << resp.reason_phrase();
            LOG(ERROR) << resp.extract_json(true).get();
            const unsigned int sleep_time = std::pow(2, backoff);
            LOG(INFO) << "Sleeping for " << sleep_time << " seconds before retrying";
            sleep(sleep_time);
            if (backoff <= 5) {
                download(cache, std::move(cacheName), start, end, backoff + 1);
            }
            return;
        }

        cache->buffer = new std::vector<unsigned char>(resp.extract_vector().get());
        cache->event.signal();
    }

    void FileIO::create_write_buffer(){
        if(write_buffer == nullptr){
            write_buffer = new std::vector<unsigned char>((int)(write_buffer_size), 0);
        }
    }
    void FileIO::create_write_buffer2(){
        create_write_buffer();
        if(write_buffer2 == nullptr){
            write_buffer2 = new std::vector<unsigned char>((int)(write_buffer_size), 0);
        }
    }

    std::vector<unsigned char> * FileIO::getFromCache( const size_t &_size, const off_t &off ){

        const uint64_t chunkNumber = getChunkNumber(off, write_buffer_size);
        const uint64_t chunkStart = getChunkStart(off, write_buffer_size);
        const auto fileSize = m_file->getFileSize();
        const size_t size = _size + off > fileSize ? fileSize-off-1: _size;
        const bool spillOver = chunkStart != getChunkStart(off+size, write_buffer_size);
        std::stringstream ss;
        ss << m_file->getId();
        ss<< "\t";
        ss << chunkStart;
        std::string cacheName = ss.str();
        std::vector<uint64_t> chunksToDownload;
        uint64_t spillOverPrecopy=0;

        DownloadItem item;
//        LOG(INFO) << "Calling wait " << std::to_string( (uintptr_t ) &this->m_file->m_event);
        m_file->m_event.wait();
//        LOG(INFO) << "Calling signal " << std::to_string( (uintptr_t ) &this->m_file->m_event);
        m_file->m_event.signal();
        auto buffer = new std::vector<unsigned char>(size, 0);
        if ( (item = m_file->m_buffers->at(chunkNumber).lock()) ) {

            if(item->buffer==nullptr || item->buffer->empty()){
                item->event.wait();
                item->event.signal();
            }

            if(item->isInvalid){
                LOG(TRACE) << "cache was invalid for " << m_file->getName();
                chunksToDownload.push_back(chunkNumber);
            }else {
                const uint64_t start = off % write_buffer_size;
                const uint64_t size2 = spillOver ? item->buffer->size() - start: size;
                spillOverPrecopy = size2;
                assert((start+size2) <= item->buffer->size());
                memcpy(buffer->data(), item->buffer->data()+start, size2);
//                m_file->cache.updateAccessTime(m_file, chunkNumber, item);
            }


        }else{
            chunksToDownload.push_back(chunkNumber);

        }

        if(spillOver) {

            const uint64_t chunkStart2 = chunkStart + write_buffer_size;
            const uint64_t chunkNumber2 = chunkNumber+1;

            ss.str(std::string());
            ss <<m_file->getId();
            ss << "\t";
            ss << chunkStart2;
            cacheName = ss.str();
            DownloadItem item;

            if ( (item=m_file->m_buffers->at(chunkNumber2).lock()) ) {
                if(item) {
                    if( item->buffer == nullptr || item->buffer->empty() ){
                        item->event.wait();
                        item->event.signal();
                    }

                    if(item->isInvalid){
                        LOG(TRACE) << "cache was invalid for " << m_file->getName();
                        chunksToDownload.push_back(chunkNumber2);
                    }else{
                        uint64_t size2 = (off + size) % write_buffer_size;
                        assert((spillOverPrecopy+size2) <= buffer->size());
                        memcpy( buffer->data() + spillOverPrecopy, item->buffer->data(), size2);
//                        m_file->cache.updateAccessTime(m_file, chunkNumber2, item);
                    }

                }else{
                    chunksToDownload.push_back(chunkNumber2);
                }

            } else {
                chunksToDownload.push_back(chunkNumber2);
            }

        }


        bool done = chunksToDownload.empty();
        int off2 = off % write_buffer_size;
        if( off2 >= BLOCKREADAHEADSTART && off2 <= BLOCKREADAHEADFINISH ){
            uint64_t start = chunkStart;
            start += spillOver ? 2*write_buffer_size : write_buffer_size;
            uint64_t temp = 0;
            for(uint64_t i = 0; i < NUM_BLOCK_READ_AHEAD; i++){
                temp = start + i*write_buffer_size;
                if (temp >= fileSize){
                    break;
                }
                chunksToDownload.push_back(temp/write_buffer_size);
            }
        }

        if(!chunksToDownload.empty()){
            m_file->m_event.wait();
            m_file->create_heap_handles(write_buffer_size);
            for (auto _chunkNumber: chunksToDownload) {
                auto start = _chunkNumber*write_buffer_size;
                ss.str(std::string());
                ss << m_file->getId();
                ss << "\t";
                ss << start;
                cacheName = ss.str();
                DownloadItem item = m_file->m_buffers->at(_chunkNumber).lock();
                if ( !(item) || item->isInvalid){
                    DownloadItem cache = std::make_shared<__no_collision_download__>();
                    cache->last_access = time(NULL);
                    cache->name = cacheName;

                    auto chunkSize = (_chunkNumber +1)*write_buffer_size >= m_file->getFileSize() ?
                                     m_file->getFileSize() - chunkNumber*write_buffer_size : write_buffer_size;
                     Object::cache.insert(m_file, _chunkNumber, chunkSize, cache);
//                    void FileIO::download(DownloadItem cache, std::string cacheName, uint64_t start, uint64_t end,  uint_fast8_t backoff) {
                    (*m_file->m_buffers)[_chunkNumber] = cache;

                    cache->future = std::async(std::launch::async, &FileIO::download, this,  cache, cacheName,
                                           start, start + write_buffer_size - 1, 0);

                }
            }
            m_file->m_event.signal();

//        mtxDownloadInsert.unlock();
        }

        if(done){
            return buffer;
        }else{
            delete buffer;
            return getFromCache( size, off);
        }

    }

    void FileIO::setFileName(){
        fs::path file_location(CACHEPATH);
        file_location /= m_file->getId();
        f_name = file_location.string();
    }

    void FileIO::open(){

        if(m_writeable){
            clearFileFromCache();
            b_is_cached = true;
            m_file->attribute.st_size = 0;
            stream.open(f_name, std::ios_base::out);
            create_write_buffer();
            create_write_buffer2();
        }
        else if(m_readable) {
//            if (m_file->isUploaded()) {
//                //file is not cached on the hdd
//                b_is_cached = false;
//                return;
//            }

            stream.open(f_name.c_str());
        }

        return;

    }

    void FileIO::clearFileFromCache(){
        auto buffers = m_file->m_buffers;
        if(buffers != nullptr) {
            for (auto weak: *buffers) {
                weak.reset();
            }
        }
    }

    void FileIO::upload(){
        m_account->upsertFileToDatabase(m_file);
        std::string uploadUrl = m_account->getUploadUrlForFile(m_file);

        // make sure that the file is no longer setting attribute
        m_file->m_event.wait();
        m_file->m_event.signal();
        bool status = m_account->upload(uploadUrl, f_name + ".released", m_file->getFileSize());
    }

    void FileIO::release(){

        if(last_write_to_buffer >0 && stream && stream.is_open()){
            stream.write((char *) write_buffer->data(),last_write_to_buffer);
            last_write_to_buffer = 0;
            stream.close();
        }

        if(b_needs_uploading){

            fs::path released;
            if(f_name.empty()) {
                released = fs::path(m_file->getId());
            }else{
                released = fs::path(f_name);
            }
            released += ".released";
            try {
                fs::rename(f_name, released);
            }catch(std::exception &e){
                LOG(ERROR) << e.what() << std::endl << m_file->getName() << "\t" << m_file->getId();
            }
        }



    }

    bool FileIO::validateCachedFileForUpload(bool deleteCachedFile){
        auto path = fs::path(f_name + ".released");
        if(fs::exists(path)){
            if( fs::file_size(path) == m_file->getFileSize()) {
                return true;
            }
        }
        path = fs::path(f_name);
        if(deleteCachedFile){
            if(fs::exists(path)){
                fs::remove(path);
            }
        }
        return false;
    }
    bool FileIO::resumeFileUploadFromUrl(std::string url){
        auto start = m_account->getResumableUploadPoint(url, m_file->getFileSize());
        LOG(INFO) << "Resuming upload of: " << m_file->getName();
        if(start){
            LOG(INFO) << "Starting from: " << start.value() << " / " << m_file->getFileSize() << "  " << (int) ((double) start.value() / (double) m_file->getFileSize() * 100.0) << "%";
            m_account->upload(url, f_name + ".released", m_file->getFileSize(), start.value());
        }else{
            LOG(INFO) << "Starting from: 0";
            upload();
        }
    }
}