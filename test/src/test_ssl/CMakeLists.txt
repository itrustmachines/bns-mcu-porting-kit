project(bns_client_test_ssl_get)

file(GLOB SSL_UTIL_SOURCES LIST_DIRECTORIES false *.c)

set(SSL_UTIL_SOURCES ${SSL_UTIL_SOURCES})
include_directories(${CURL_INCLUDES})
include_directories(${CJSON_INCLUDE_DIRS})

set(TEST_SSL_UTIL_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CJSON_INCLUDE_DIRS})
set(TEST_SSL_UTIL_DIR ${TEST_SSL_UTIL_DIR} PARENT_SCOPE)

if (${MINGW})
    if (NOT ${VCPKG_TARGET_TRIPLET} MATCHES "static")
        if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
            get_target_property(_curl_location_debug CURL::libcurl IMPORTED_LOCATION_DEBUG)
            message(${_curl_location_debug})
            file(COPY ${_curl_location_debug} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
            get_target_property(_zlib_location_debug ZLIB::ZLIB IMPORTED_LOCATION_DEBUG)
            get_filename_component(_zlib_location_debug ${_zlib_location_debug} DIRECTORY)
            set(_zlib_location_debug ${_zlib_location_debug}/../bin/zlibd1.dll)
            message(${_zlib_location_debug})
            file(COPY ${_zlib_location_debug} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
        else ()
            get_target_property(_curl_location_release CURL::libcurl IMPORTED_LOCATION_RELEASE)
            message(${_curl_location_release})
            file(COPY ${_curl_location_release} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
            get_target_property(_zlib_location_release ZLIB::ZLIB IMPORTED_LOCATION_RELEASE)
            get_filename_component(_zlib_location_release ${_zlib_location_release} DIRECTORY)
            set(_zlib_location_release ${_zlib_location_release}/../bin/zlib1.dll)
            message(${_zlib_location_release})
            file(COPY ${_zlib_location_release} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
        endif ()
    endif ()
endif ()

include_directories(${BNS_CLIENT_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SSL_UTIL_SOURCES})

if (${VCPKG_PROJECT})
    target_link_libraries(${PROJECT_NAME} PRIVATE bns-client-lib CURL::libcurl ZLIB::ZLIB)
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE bns-client-lib curl pthread)
endif ()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})