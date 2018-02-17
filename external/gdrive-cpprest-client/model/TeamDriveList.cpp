/**
 * Drive
 * Manages files in Drive including uploading, downloading, searching, detecting changes, and updating sharing permissions.
 *
 * OpenAPI spec version: v3
 * 
 *
 * NOTE: This class is auto generated by the swagger code generator 2.2.3.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */



#include "TeamDriveList.h"

namespace io {
namespace swagger {
namespace client {
namespace model {

TeamDriveList::TeamDriveList()
{
    m_Kind = U("");
    m_KindIsSet = false;
    m_NextPageToken = U("");
    m_NextPageTokenIsSet = false;
    m_TeamDrivesIsSet = false;
}

TeamDriveList::~TeamDriveList()
{
}

void TeamDriveList::validate()
{
    // TODO: implement validation
}

web::json::value TeamDriveList::toJson() const
{
    web::json::value val = web::json::value::object();

    if(m_KindIsSet)
    {
        val[U("kind")] = ModelBase::toJson(m_Kind);
    }
    if(m_NextPageTokenIsSet)
    {
        val[U("nextPageToken")] = ModelBase::toJson(m_NextPageToken);
    }
    {
        std::vector<web::json::value> jsonArray;
        for( auto& item : m_TeamDrives )
        {
            jsonArray.push_back(ModelBase::toJson(item));
        }
        if(jsonArray.size() > 0)
        {
            val[U("teamDrives")] = web::json::value::array(jsonArray);
        }
    }

    return val;
}

void TeamDriveList::fromJson(web::json::value& val)
{
    if(val.has_field(U("kind")))
    {
        setKind(ModelBase::stringFromJson(val[U("kind")]));
    }
    if(val.has_field(U("nextPageToken")))
    {
        setNextPageToken(ModelBase::stringFromJson(val[U("nextPageToken")]));
    }
    {
        m_TeamDrives.clear();
        std::vector<web::json::value> jsonArray;
        if(val.has_field(U("teamDrives")))
        {
        for( auto& item : val[U("teamDrives")].as_array() )
        {
            if(item.is_null())
            {
                m_TeamDrives.push_back( std::shared_ptr<TeamDrive>(nullptr) );
            }
            else
            {
                std::shared_ptr<TeamDrive> newItem(new TeamDrive());
                newItem->fromJson(item);
                m_TeamDrives.push_back( newItem );
            }
        }
        }
    }
}

void TeamDriveList::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix[namePrefix.size() - 1] != U('.'))
    {
        namePrefix += U(".");
    }

    if(m_KindIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + U("kind"), m_Kind));
        
    }
    if(m_NextPageTokenIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + U("nextPageToken"), m_NextPageToken));
        
    }
    {
        std::vector<web::json::value> jsonArray;
        for( auto& item : m_TeamDrives )
        {
            jsonArray.push_back(ModelBase::toJson(item));
        }
        
        if(jsonArray.size() > 0)
        {
            multipart->add(ModelBase::toHttpContent(namePrefix + U("teamDrives"), web::json::value::array(jsonArray), U("application/json")));
        }
    }
}

void TeamDriveList::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix[namePrefix.size() - 1] != U('.'))
    {
        namePrefix += U(".");
    }

    if(multipart->hasContent(U("kind")))
    {
        setKind(ModelBase::stringFromHttpContent(multipart->getContent(U("kind"))));
    }
    if(multipart->hasContent(U("nextPageToken")))
    {
        setNextPageToken(ModelBase::stringFromHttpContent(multipart->getContent(U("nextPageToken"))));
    }
    {
        m_TeamDrives.clear();
        if(multipart->hasContent(U("teamDrives")))
        {

        web::json::value jsonArray = web::json::value::parse(ModelBase::stringFromHttpContent(multipart->getContent(U("teamDrives"))));
        for( auto& item : jsonArray.as_array() )
        {
            if(item.is_null())
            {
                m_TeamDrives.push_back( std::shared_ptr<TeamDrive>(nullptr) );
            }
            else
            {
                std::shared_ptr<TeamDrive> newItem(new TeamDrive());
                newItem->fromJson(item);
                m_TeamDrives.push_back( newItem );
            }
        }
        }
    }
}

utility::string_t TeamDriveList::getKind() const
{
    return m_Kind;
}


void TeamDriveList::setKind(utility::string_t value)
{
    m_Kind = value;
    m_KindIsSet = true;
}
bool TeamDriveList::kindIsSet() const
{
    return m_KindIsSet;
}

void TeamDriveList::unsetKind()
{
    m_KindIsSet = false;
}

utility::string_t TeamDriveList::getNextPageToken() const
{
    return m_NextPageToken;
}


void TeamDriveList::setNextPageToken(utility::string_t value)
{
    m_NextPageToken = value;
    m_NextPageTokenIsSet = true;
}
bool TeamDriveList::nextPageTokenIsSet() const
{
    return m_NextPageTokenIsSet;
}

void TeamDriveList::unsetNextPageToken()
{
    m_NextPageTokenIsSet = false;
}

std::vector<std::shared_ptr<TeamDrive>>& TeamDriveList::getTeamDrives()
{
    return m_TeamDrives;
}

void TeamDriveList::setTeamDrives(std::vector<std::shared_ptr<TeamDrive>> value)
{
    m_TeamDrives = value;
    m_TeamDrivesIsSet = true;
}
bool TeamDriveList::teamDrivesIsSet() const
{
    return m_TeamDrivesIsSet;
}

void TeamDriveList::unsetTeamDrives()
{
    m_TeamDrivesIsSet = false;
}

}
}
}
}
