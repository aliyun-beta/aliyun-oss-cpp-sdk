cmake_minimum_required(VERSION 2.6)

project(samples CXX)

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

add_executable(samples
samples.cc
normal_samples.cc
exp_oss_client.cc
exp_samples.cc
)

target_link_libraries(samples
${PROJECT_BINARY_DIR}/../build/lib/libosssdkcpp.a
libtinyxml.a
curl
libaprutil-1.a
libapr-1.a
pthread
)