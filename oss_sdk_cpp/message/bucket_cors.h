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

#ifndef OSS_SDK_CPP_MESSAGE_BUCKET_CORS_H_
#define OSS_SDK_CPP_MESSAGE_BUCKET_CORS_H_

#include <string>
#include "oss_sdk_cpp/base/base.h"

namespace oss {

class CorsRule {
 public:
  CorsRule();

  const StringList& GetAllowedOrigins() const;

  const StringList& GetAllowedMethods() const;

  const StringList& GetAllowedHeaders() const;

  const StringList& GetExposeHeaders() const;

  void AddAllowedOrigin(const std::string& str);

  void AddAllowedMethod(const std::string& str);

  void AddAllowedHeader(const std::string& str);

  void AddExposeHeader(const std::string& str);

  int GetMaxAgeSeconds() const;

  void SetMaxAgeSeconds(const int seconds);

 private:
  StringList allowed_origins_;
  StringList allowed_methods_;
  StringList allowed_headers_;
  StringList expose_headers_;
  int max_age_seconds_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_BUCKET_CORS_H_
