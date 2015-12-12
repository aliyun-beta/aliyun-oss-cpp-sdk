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

#ifndef OSS_SDK_CPP_MESSAGE_OPTION_OBJECT_REQUEST_H_
#define OSS_SDK_CPP_MESSAGE_OPTION_OBJECT_REQUEST_H_

#include <time.h>
#include <string>
#include <list>

#include "oss_sdk_cpp/base/base.h"

namespace oss {

class OptionObjectRequest {
 public:
  OptionObjectRequest();

  OptionObjectRequest(const std::string& bucket_name,
                      const std::string& key,
                      const std::string& origin,
                      const std::string& request_method,
                      const std::string& request_headers);

  ~OptionObjectRequest();

  const std::string& GetBucketName() const;

  void SetBucketName(const std::string& name);

  const std::string& GetKey() const;

  void SetKey(const std::string& key);

  const std::string& GetOrigin() const;

  void SetOrigin(const std::string& origin);

  const std::string& GetRequestMethod() const;

  void SetRequestMethod(const std::string& request_method);

  const std::string& GetRequestHeaders() const;

  void SetRequestHeaders(const std::string& request_header);

 private:
  std::string bucket_name_;
  std::string key_;
  std::string origin_;
  std::string request_method_;
  std::string request_headers_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_OPTION_OBJECT_REQUEST_H_
