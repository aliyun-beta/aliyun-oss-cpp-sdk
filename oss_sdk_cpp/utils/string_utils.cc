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

#include <stdlib.h>
#include <string>

#include "oss_sdk_cpp/utils/string_utils.h"
#include "oss_sdk_cpp/base/string_piece.h"

namespace oss {

inline char ToLowerASCII(char c) {
  return (c >= 'A' && c <= 'Z') ? (c + ('a' - 'A')) : c;
}

inline char ToUpperASCII(char c) {
  return (c >= 'a' && c <= 'z') ? (c + ('A' - 'a')) : c;
}

#ifndef _MSC_VER
int strnicmp(const char* string1, const char* string2, size_t count) {
  return strncasecmp(string1, string2, count);
}

int stricmp(const char* string1, const char* string2) {
  return strcasecmp(string1, string2);
}
#endif

struct CaseInsensitiveCompareASCII {
 public:
  bool operator()(char x, char y) const {
    return ToLowerASCII(x) == ToLowerASCII(y);
  }
};

bool StartsWith(oss::StringPiece str,
                oss::StringPiece search_for,
                bool case_sensitivity) {
  if (search_for.size() > str.size())
    return false;

  oss::StringPiece source = str.substr(0, search_for.size());
  if (case_sensitivity) {
    return source == search_for;
  } else {
    return std::equal(
             search_for.begin(), search_for.end(),
             source.begin(),
             CaseInsensitiveCompareASCII());
  }
}

bool EndsWith(oss::StringPiece str,
              oss::StringPiece search_for,
              bool case_sensitivity) {
  if (search_for.size() > str.size())
    return false;

  oss::StringPiece source = str.substr(str.size() - search_for.size(),
                                       search_for.size());

  if (case_sensitivity) {
    return source == search_for;
  } else {
    return std::equal(
             source.begin(), source.end(),
             search_for.begin(),
             CaseInsensitiveCompareASCII());
  }
}

std::string ToLower(oss::StringPiece str) {
  std::string  ret;
  ret.reserve(str.size());
  for (size_t i = 0; i < str.size(); i++)
    ret.push_back(ToLowerASCII(str[i]));
  return ret;
}

std::string ToUpper(oss::StringPiece str) {
  std::string ret;
  ret.reserve(str.size());
  for (size_t i = 0; i < str.size(); i++)
    ret.push_back(ToUpperASCII(str[i]));
  return ret;
}

bool StringToBool(const std::string& str) {
  return !str.empty() &&
         (stricmp(str.c_str(), "true") == 0 ||
          atoi(str.c_str()) != 0);
}

TrimPositions TrimStringT(const std::string& input,
                          oss::StringPiece trim_chars,
                          TrimPositions positions,
                          std::string* output) {
  // Find the edges of leading/trailing whitespace as desired. Need to use
  // a StringPiece version of input to be able to call find* on it with the
  // StringPiece version of trim_chars (normally the trim_chars will be a
  // constant so avoid making a copy).
  oss::StringPiece input_piece(input);
  const size_t last_char = input.length() - 1;
  const size_t first_good_char = (positions & TRIM_LEADING) ?
                                 input_piece.find_first_not_of(trim_chars) : 0;
  const size_t last_good_char = (positions & TRIM_TRAILING) ?
                                input_piece.find_last_not_of(trim_chars) :
                                last_char;

  // When the string was all trimmed, report that we stripped off characters
  // from whichever position the caller was interested in. For empty input, we
  // stripped no characters, but we still need to clear |output|.
  if (input.empty() ||
      (first_good_char == std::string::npos) ||
      (last_good_char == std::string::npos)) {
    bool input_was_empty = input.empty();  // in case output == &input
    output->clear();
    return input_was_empty ? TRIM_NONE : positions;
  }

  // Trim.
  *output =
    input.substr(first_good_char, last_good_char - first_good_char + 1);

  // Return where we trimmed from.
  return static_cast<TrimPositions>(
           ((first_good_char == 0) ? TRIM_NONE : TRIM_LEADING) |
           ((last_good_char == last_char) ? TRIM_NONE : TRIM_TRAILING));
}

bool TrimString(const std::string& input,
                oss::StringPiece trim_chars,
                std::string* output) {
  return TrimStringT(input, trim_chars, TRIM_ALL, output) != TRIM_NONE;
}

bool TrimWhiteSpaces(const std::string& input, std::string* output) {
  return TrimStringT(input, " \n\r\t", TRIM_ALL, output) != TRIM_NONE;
}

std::string JoinStringList(const std::list<std::string>& strings,
                           const std::string& separator) {
  std::string result;
  bool first = true;
  for (const auto &str : strings) {
    if (first) {
      first = false;
    } else {
      result += separator;
    }
    result += str;
  }
  return result;
}

template <typename CharType>
void ReplaceSubstringT(std::basic_string<CharType>* ocean,
                       const std::basic_string<CharType>& needle,
                       const std::basic_string<CharType>& replacements) {
  if (needle.empty())
    return;

  typename std::basic_string<CharType>::size_type pos = 0;
  while ((pos = ocean->find(needle, pos))
         != std::basic_string<CharType>::npos) {
    ocean->replace(pos, needle.length(), replacements);
    pos += replacements.length();
  }
}

void ReplaceSubstring(std::string* ocean,
                      const std::string& needle,
                      const std::string& replacements) {
  return ReplaceSubstringT<char>(ocean, needle, replacements);
}

}  // namespace oss
