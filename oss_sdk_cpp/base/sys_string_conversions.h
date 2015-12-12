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

#ifndef OSS_SDK_CPP_BASE_SYS_STRING_CONVERSIONS_H_
#define OSS_SDK_CPP_BASE_SYS_STRING_CONVERSIONS_H_

#include <string>

namespace oss {

class StringPiece;

// Converts between wide and UTF-8 representations of a string. On error, the
// result is system-dependent.
std::string SysWideToUTF8(const std::wstring& wide);
std::wstring SysUTF8ToWide(const StringPiece& utf8);

// Converts between wide and the system multi-byte representations of a string.
// DANGER: This will lose information and can change (on Windows, this can
// change between reboots).
std::string SysWideToNativeMB(const std::wstring& wide);
std::wstring SysNativeMBToWide(const StringPiece& native_mb);

// Windows-specific ------------------------------------------------------------

#ifdef _WIN32

// Converts between 8-bit and wide strings, using the given code page. The
// code page identifier is one accepted by the Windows function
// MultiByteToWideChar().
std::wstring SysMultiByteToWide(const StringPiece& mb,
                                int code_page);
std::string SysWideToMultiByte(const std::wstring& wide,
                               int code_page);

#endif

}  // namespace oss

#endif  // OSS_SDK_CPP_BASE_SYS_STRING_CONVERSIONS_H_
