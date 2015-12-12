cmake_minimum_required(VERSION 2.6)

project(unittests CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CXX_FLAG_LIST
 -g
 -Wall
 -Wextra
 -Wold-style-cast
 -Wpointer-arith
 -Wno-unused-parameter
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
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../build/bin)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/..")
include_directories("${PROJECT_SOURCE_DIR}/../third_party/googletest/include")

add_executable(unittests
oss/oss_exception_unittest.cc
oss/status_unittest.cc
oss/oss_client_unittest.cc
http/http_engine_output_unittest.cc
http/http_engine_input_unittest.cc
http/http_engine_unittest.cc
http/curl_warppers_unittest.cc
http/http_configuration_unittest.cc
base/nullable_unittest.cc
base/string_piece_unittest.cc
utils/string_utils_unittest.cc
utils/apr_utils_unittest.cc
utils/sign_utils_unittest.cc
utils/utils_unittest.cc
utils/http_utils_unittest.cc
message/set_bucket_website_request_unittest.cc
message/get_bucket_logging_result_unittest.cc
message/get_bucket_cors_result_unittest.cc
message/set_bucket_logging_request_unittest.cc
message/set_bucket_cors_request_unittest.cc
message/option_object_request_unittest.cc
message/list_parts_request_unittest.cc
message/get_bucket_website_result_unittest.cc
message/upload_part_copy_result_unittest.cc
message/object_content_unittest.cc
message/complete_multipart_upload_result_unittest.cc
message/delete_multiple_objects_result_unittest.cc
message/list_buckets_result_unittest.cc
message/copy_object_request_unittest.cc
message/get_bucket_acl_result_unittest.cc
message/complete_multipart_upload_request_unittest.cc
message/list_objects_result_unittest.cc
message/upload_part_unittest.cc
message/list_multipart_uploads_request_unittest.cc
message/bucket_cors_unittest.cc
message/upload_part_request_unittest.cc
message/get_bucket_location_result_unittest.cc
message/get_object_request_unittest.cc
message/initiate_multipart_upload_result_unittest.cc
message/copy_object_result_unittest.cc
message/lifecycle_rule_unittest.cc
message/append_object_request_unittest.cc
message/set_bucket_referer_request_unittest.cc
message/multipart_upload_unitetest.cc
message/bucket_unittest.cc
message/upload_part_result_unittest.cc
message/object_metadata_unittest.cc
message/upload_part_copy_reques_unittest.cc
message/list_buckets_request_unittest.cc
message/delete_multiple_objects_request_unittest.cc
message/set_bucket_lifecycle_request_unittest.cc
message/get_bucket_referer_result_unittest.cc
message/append_object_result_unittest.cc
message/option_object_result_unittest.cc
message/get_bucket_lifecycle_result_unittest.cc
message/list_parts_result_unittest.cc
message/part_etag_unittest.cc
message/list_objects_request_unittest.cc
message/list_multipart_uploads_result_unittest.cc
message/initiate_multipart_upload_request_unittest.cc
)

target_link_libraries(unittests
${PROJECT_BINARY_DIR}/../build/lib/libosssdkcpp.a
${PROJECT_BINARY_DIR}/../third_party/googletest/libgtest.a
${PROJECT_BINARY_DIR}/../third_party/googletest/libgtest_main.a
libtinyxml.a
curl
libaprutil-1.a
libapr-1.a
pthread
)
