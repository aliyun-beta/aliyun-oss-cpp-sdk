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

#ifndef OSS_SDK_CPP_MESSAGE_SET_BUCKET_CORS_REQUEST_H_
#define OSS_SDK_CPP_MESSAGE_SET_BUCKET_CORS_REQUEST_H_

#include <string>
#include <list>

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/message/bucket_cors.h"

namespace oss {

class SetBucketCorsRequest {
 public:
  SetBucketCorsRequest();

  SetBucketCorsRequest(const std::string& bucket_name);

  ~SetBucketCorsRequest();

  const std::string& GetBucketName() const;

  void SetBucketName(const std::string& name);

  void AddRule(const CorsRule& rule);

  CorsRule* AddRule();

  const std::list<CorsRule>& GetRules() const;

  void SetRules(const std::list<CorsRule>& rules);

  std::string SerializeToXml() const;

 private:
  std::string bucket_name_;
  std::list<CorsRule> rules_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_SET_BUCKET_CORS_REQUEST_H_
