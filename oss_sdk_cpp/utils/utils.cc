/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "oss_sdk_cpp/build_config.h"

#if defined(OS_WIN)
#include <windows.h>
#elif defined(OS_MACOSX)
#include <mach-o/dyld.h>
#endif  // OS_WIN

#include <fstream>

#include "oss_sdk_cpp/base/string_piece.h"
#include "oss_sdk_cpp/base/sys_string_conversions.h"

#include "oss_sdk_cpp/utils/utils.h"

namespace oss {

std::string ReadWholeFile(const std::string& path) {
  std::ifstream stream;
  OpenStream(&stream, path, std::ios::in | std::ios::binary);
  std::string content((std::istreambuf_iterator<char>(stream)),
                      std::istreambuf_iterator<char>());
  return content;
}

int64_t GetFileSize(const std::string& file_path) {
  std::ifstream stream;
  OpenStream(&stream, file_path, std::ios::in | std::ios::binary);
  if (!stream)
    return -1;
  stream.seekg(0, std::ios::end);

  return static_cast<int64_t>(stream.tellg());
}

void OpenStream(std::ifstream* stream,
                const std::string& file_path,
                std::ios_base::openmode mode) {
#if defined(OS_WIN)
  std::wstring wide_file_path = oss::SysUTF8ToWide(file_path);
  stream->open(wide_file_path, mode);
#else
  stream->open(file_path, mode);
#endif
}

void RemoveStream(const std::string& file_path) {
#if defined(OS_WIN)
  std::wstring wide_file_path = oss::SysUTF8ToWide(file_path);
  _wremove(wide_file_path.c_str());
#else
  remove(file_path.c_str());
#endif
}

void OpenStream(std::ofstream* stream,
                const std::string& file_path,
                std::ios_base::openmode mode) {
#if defined(OS_WIN)
  std::wstring wide_file_path = oss::SysUTF8ToWide(file_path);
  stream->open(wide_file_path, mode);
#else
  stream->open(file_path, mode);

#endif
}

std::string GetExecutableDirectory() {
  char path[1024] = "";

#if defined(OS_WIN)

  GetModuleFileNameA(NULL, path, sizeof(path));

#elif defined(OS_MACOSX)

  char nspath[1024] = "";
  uint32_t size = sizeof(nspath);
  if (_NSGetExecutablePath(nspath, &size) != 0)
    return "";

  if (realpath(nspath, path) == NULL)
    return "";

#else

  ssize_t count = readlink("/proc/self/exe", path, sizeof(path));
  (void)count;

#endif
  std::string str_path = path;
  std::string::size_type pos = std::string(str_path).find_last_of("\\/");
  str_path = std::string(str_path).substr(0, pos);

#if defined(OS_WIN)
  std::wstring wpath = oss::SysNativeMBToWide(str_path);
  str_path = oss::SysWideToUTF8(wpath);
#endif
  return str_path;
}

void NormalizeFilePath(std::string* path) {
  std::string& path_ref = *path;
  for (std::string::size_type i = 0; i < path_ref.size(); ++i) {
#if defined(OS_WIN)
    if (path_ref[i] == '/') {
      path_ref[i] = '\\';
    }
#else
    if (path_ref[i] == '\\') {
      path_ref[i] = '/';
    }
#endif
  }
}

std::string HexToString(const std::string& input) {
  static char const alphabet[] = "0123456789abcdef";

  std::string result;
  result.resize(input.size() * 2);

  for (unsigned i = 0, j = 0; i < input.size(); i++, j += 2) {
    uint8_t byte = static_cast<uint8_t>(input[i]);
    result[j] = alphabet[(byte >> 4) & 0xf];
    result[j + 1] = alphabet[byte & 0xf];
  }

  return result;
}

struct tm* GmTime(time_t t, struct tm* tm_result) {
#if defined(OS_WIN)
  gmtime_s(tm_result, &t);
  return tm_result;
#else
  return gmtime_r(&t, tm_result);
#endif
}

}  // namespace oss
