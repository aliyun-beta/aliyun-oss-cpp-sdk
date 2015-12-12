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

#include "oss_sdk_cpp/message/bucket_cors.h"

namespace oss {

CorsRule::CorsRule()
  : max_age_seconds_(100) {
}

const StringList& CorsRule::GetAllowedOrigins() const {
  return allowed_origins_;
}

const StringList& CorsRule::GetAllowedMethods() const {
  return allowed_methods_;
}

const StringList& CorsRule::GetAllowedHeaders() const {
  return allowed_headers_;
}

const StringList& CorsRule::GetExposeHeaders() const {
  return expose_headers_;
}

void CorsRule::AddAllowedOrigin(const std::string& str) {
  allowed_origins_.push_back(str);
}

void CorsRule::AddAllowedMethod(const std::string& str) {
  allowed_methods_.push_back(str);
}

void CorsRule::AddAllowedHeader(const std::string& str) {
  allowed_headers_.push_back(str);
}

void CorsRule::AddExposeHeader(const std::string& str) {
  expose_headers_.push_back(str);
}

int CorsRule::GetMaxAgeSeconds() const {
  return max_age_seconds_;
}
void CorsRule::SetMaxAgeSeconds(const int seconds) {
  max_age_seconds_ = seconds;
}

}  // namespace oss
