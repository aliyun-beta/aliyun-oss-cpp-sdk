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

#include <apr_strings.h>
#include <string>

#include "oss_sdk_cpp/utils/string_utils.h"
#include "oss_sdk_cpp/utils/utils.h"

#include "oss_sdk_cpp/message/append_object_result.h"

namespace oss {

void AppendObjectResult::ParseFromHeader(const StringMap& headers) {
  StringMap::const_iterator iter;

  iter = headers.find("ETag");
  if (iter != headers.end()) {
    etag_ = iter->second;
  }

  iter = headers.find("x-oss-hash-crc64ecma");
  if (iter != headers.end()) {
    crc64ecma_ = iter->second;
  }

  iter = headers.find("x-oss-next-append-position");
  if (iter != headers.end()) {
    next_append_position_ = apr_atoi64(iter->second.c_str());
  }
}

const std::string& AppendObjectResult::GetEtag() {
  return etag_;
}

const std::string& AppendObjectResult::GetCrc64Ecma() {
  return crc64ecma_;
}

int64_t AppendObjectResult::GetNextAppendPosition() {
  return next_append_position_;
}

}  // namespace oss
