cmake_minimum_required(VERSION 2.6)

project(osssdkcpp CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CXX_FLAG_LIST
 -g
 -Wall
 -Wextra
 -Wno-unused-parameter 
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 -std=c++0x
 -fprofile-arcs 
 -ftest-coverage
 )
#convert list to string. 
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAG_LIST}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../build/lib)

find_package(APR REQUIRED)
include_directories("${APR_INCLUDE_DIR}")
include_directories("${APRUTIL_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/..")

add_library(osssdkcpp STATIC
http/http_headers.cc
http/http_engine_output.cc
http/http_engine.cc
http/http_engine_input.cc
http/curl_warppers.cc
http/http_configuration.cc
base/base.cc
base/string_piece.cc
utils/apr_utils.cc
utils/string_utils.cc
utils/sign_utils.cc
utils/http_utils.cc
utils/xml_utils.cc
utils/utils.cc
message/lifecycle_rule.cc
message/option_object_request.cc
message/bucket_cors.cc
message/object_content.cc
message/upload_part.cc
message/multipart_upload.cc
message/part_etag.cc
message/bucket.cc
message/list_multipart_uploads_result.cc
message/upload_part_copy_request.cc
message/copy_object_request.cc
message/list_parts_request.cc
message/list_buckets_result.cc
message/upload_part_request.cc
message/upload_part_result.cc
message/initiate_multipart_upload_result.cc
message/get_bucket_referer_result.cc
message/get_object_request.cc
message/set_bucket_cors_request.cc
message/list_multipart_uploads_request.cc
message/get_bucket_location_result.cc
message/initiate_multipart_upload_request.cc
message/upload_part_copy_result.cc
message/get_bucket_lifecycle_result.cc
message/option_object_result.cc
message/copy_object_result.cc
message/complete_multipart_upload_request.cc
message/list_buckets_request.cc
message/set_bucket_referer_request.cc
message/list_objects_request.cc
message/get_bucket_website_result.cc
message/list_objects_result.cc
message/get_bucket_cors_result.cc
message/object_metadata.cc
message/list_parts_result.cc
message/get_bucket_logging_result.cc
message/delete_multiple_objects_request.cc
message/get_bucket_acl_result.cc
message/set_bucket_logging_request.cc
message/complete_multipart_upload_result.cc
message/set_bucket_lifecycle_request.cc
message/append_object_request.cc
message/append_object_result.cc
message/delete_multiple_objects_result.cc
message/set_bucket_website_request.cc
oss/oss_client_configuration.cc
oss/oss_client.cc
oss/oss.cc
oss/oss_status.cc
oss/oss_exception.cc
oss/oss_error_code.cc
)