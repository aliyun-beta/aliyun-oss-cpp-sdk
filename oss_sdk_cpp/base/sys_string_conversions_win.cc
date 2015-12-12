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

#include <windows.h>

#include "oss_sdk_cpp/base/sys_string_conversions.h"
#include "oss_sdk_cpp/base/string_piece.h"

namespace oss {

// Do not assert in this function since it is used by the asssertion code!
std::string SysWideToUTF8(const std::wstring& wide) {
  return SysWideToMultiByte(wide, CP_UTF8);
}

// Do not assert in this function since it is used by the asssertion code!
std::wstring SysUTF8ToWide(const StringPiece& utf8) {
  return SysMultiByteToWide(utf8, CP_UTF8);
}

std::string SysWideToNativeMB(const std::wstring& wide) {
  return SysWideToMultiByte(wide, CP_ACP);
}

std::wstring SysNativeMBToWide(const StringPiece& native_mb) {
  return SysMultiByteToWide(native_mb, CP_ACP);
}

// Do not assert in this function since it is used by the asssertion code!
std::wstring SysMultiByteToWide(const StringPiece& mb, int code_page) {
  if (mb.empty())
    return std::wstring();

  int mb_length = static_cast<int>(mb.length());
  // Compute the length of the buffer.
  int charcount = MultiByteToWideChar(code_page, 0,
                                      mb.data(), mb_length, NULL, 0);
  if (charcount == 0)
    return std::wstring();

  std::wstring wide;
  wide.resize(charcount);
  MultiByteToWideChar(code_page, 0, mb.data(), mb_length, &wide[0], charcount);

  return wide;
}

// Do not assert in this function since it is used by the asssertion code!
std::string SysWideToMultiByte(const std::wstring& wide, int code_page) {
  int wide_length = static_cast<int>(wide.length());
  if (wide_length == 0)
    return std::string();

  // Compute the length of the buffer we'll need.
  int charcount = WideCharToMultiByte(code_page, 0, wide.data(), wide_length,
                                      NULL, 0, NULL, NULL);
  if (charcount == 0)
    return std::string();

  std::string mb;
  mb.resize(charcount);
  WideCharToMultiByte(code_page, 0, wide.data(), wide_length,
                      &mb[0], charcount, NULL, NULL);

  return mb;
}

}  // namespace oss
