include(ExternalProject)

set(CPPREST_LIB ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libcpprest.so)
set(CPPREST_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/external/include)
#find_package(PkgConfig)
set(CMAKE_PREFIX_PATH "/usr/lib/cmake" "/usr/lib/x86_64-linux_gnu/cmake")
ExternalProject_Add(cpprest
        PREFIX cpprest
        GIT_REPOSITORY https://github.com/Microsoft/cpprestsdk.git
        GIT_TAG v2.10.2
        EXCLUDE_FROM_ALL 0
        SOURCE_SUBDIR Release
        EXCLUDE_FROM_ALL 0
        CMAKE_CACHE_ARGS "-DBUILD_SAMPLES:BOOL=OFF"
        CMAKE_CACHE_ARGS "-DCPPREST_EXCLUDE_WEBSOCKETS:BOOL=OFF"
        CMAKE_CACHE_ARGS "-DBUILD_TESTS:BOOL=OFF"
        CMAKE_CACHE_ARGS "-DOPENSSL_CRYPTO_LIBRARY:FILEPATH=${OPENSSL_CRYPTO_LIBRARY}"
        CMAKE_CACHE_ARGS "-DOPENSSL_INCLUDE_DIR:PATH=${OPENSSL_INCLUDE_DIR}"
        CMAKE_CACHE_ARGS "-DOPENSSL_SSL_LIBRARY:FILEPATH=${OPENSSL_SSL_LIBRARY}"
        CMAKE_CACHE_ARGS "-DBUILD_SHARED_LIBS:BOOL=ON"
        CMAKE_CACHE_ARGS "-DCMAKE_CXX_FLAGS:STRING=-fPIC -Wno-error=format-truncation="
        CMAKE_CACHE_ARGS "-DCMAKE_BUILD_TYPE:STRING=Release"
        CMAKE_CACHE_ARGS "-DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_SOURCE_DIR}/external"
        BUILD_BYPRODUCTS ${CPPREST_LIB}

        )
