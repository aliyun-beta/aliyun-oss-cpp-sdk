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

#include <stdint.h>

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/utils/http_utils.h"
#include "oss_sdk_cpp/utils/string_utils.h"
#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/build_config.h"

namespace oss {

std::string GmtTime(time_t t) {
  // 128 bytes is enough to hold a GMT time string.
  char buffer[128] = "";
  struct tm tm_result;
  GmTime(t, &tm_result);
  strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", &tm_result);
  return buffer;
}

std::string GmtTimeNow() {
  return GmtTime(time(NULL));
}

std::string Iso8601Date(time_t timestamp) {
  struct tm exploded_time;
  GmTime(timestamp, &exploded_time);
  char buf[sizeof "1970-01-01T00:00:00.000Z"];
  strftime(buf, sizeof buf, "%Y-%m-%dT00:00:00.000Z", &exploded_time);
  return buf;
}

static const char kHexAlphabet[] = "0123456789ABCDEF";

inline bool IsRfc3986UnreservedCharacter(char c) {
  return ('a' <= c && c <= 'z') ||
         ('A' <= c && c <= 'Z') ||
         ('0' <= c && c <= '9') ||
         c == '~' ||
         c == '-' ||
         c == '_' ||
         c == '.';
}

std::string UrlEscape(const std::string& text) {
  std::string escaped;
  escaped.reserve(text.length() * 3);
  for (unsigned int i = 0; i < text.length(); ++i) {
    unsigned char c = static_cast<unsigned char>(text[i]);
    if (IsRfc3986UnreservedCharacter(c)) {
      escaped.push_back(c);
    } else {
      escaped.push_back('%');
      escaped.push_back(kHexAlphabet[c >> 4]);
      escaped.push_back(kHexAlphabet[c & 0xf]);
    }
  }
  return escaped;
}

}  // namespace oss
