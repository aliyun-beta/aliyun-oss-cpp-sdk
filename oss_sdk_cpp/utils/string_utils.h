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

#ifndef OSS_SDK_CPP_UTILS_STRING_UTILS_H_
#define OSS_SDK_CPP_UTILS_STRING_UTILS_H_

#include <string>
#include <list>

#include "oss_sdk_cpp/base/string_piece.h"

namespace oss {

bool StartsWith(oss::StringPiece str,
                oss::StringPiece search_for,
                bool case_sensitivity = false);

bool EndsWith(oss::StringPiece str,
              oss::StringPiece search_for,
              bool case_sensitivity = false);

std::string ToLower(oss::StringPiece str);

std::string ToUpper(oss::StringPiece str);

bool StringToBool(const std::string& str);

bool TrimString(const std::string& input,
                oss::StringPiece trim_chars,
                std::string* output);

bool TrimWhiteSpaces(const std::string& input,
                     std::string* output);

#ifndef _MSC_VER
int strnicmp(const char* string1, const char* string2, size_t count);

int stricmp(const char* string1, const char* string2);
#endif

enum TrimPositions {
  TRIM_NONE = 0,
  TRIM_LEADING = 1 << 0,
  TRIM_TRAILING = 1 << 1,
  TRIM_ALL = TRIM_LEADING | TRIM_TRAILING,
};

std::string JoinStringList(const std::list<std::string>& strings,
                           const std::string& separator);

void ReplaceSubstring(std::string* ocean,
                      const std::string& needle,
                      const std::string& replacements);

}  // namespace oss

#endif  // OSS_SDK_CPP_UTILS_STRING_UTILS_H_
