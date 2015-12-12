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

#include <string>

#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/utils/string_utils.h"

#include "oss_sdk_cpp/message/option_object_result.h"

namespace oss {

const std::string& OptionObjectResult::GetAllowOrigin() {
  return allow_origin_;
}

const std::string& OptionObjectResult::GetAllowMethods() {
  return allow_methods_;
}

const std::string& OptionObjectResult::GeExposeHeaders() {
  return expose_headers_;
}

void OptionObjectResult::ParseFromHeader(const StringMap& headers) {
  StringMap::const_iterator iter;
  iter = headers.find("Access-Control-Allow-Origin");
  if (iter != headers.end()) {
    allow_origin_ = iter->second;
  }

  iter = headers.find("Access-Control-Allow-Methods");
  if (iter != headers.end()) {
    allow_methods_ = iter->second;
  }

  iter = headers.find("Access-Control-Expose-Headers");
  if (iter != headers.end()) {
    expose_headers_ = iter->second;
  }
}

}  // namespace oss
