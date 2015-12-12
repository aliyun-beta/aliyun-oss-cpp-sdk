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

#ifndef OSS_SDK_CPP_OSS_OSS_STATUS_H_
#define OSS_SDK_CPP_OSS_OSS_STATUS_H_

#include <string>

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/oss/oss_exception.h"

namespace oss {

class Status {
 public:
  Status();

  explicit Status(const std::string& code);

  // move assignment
  Status& operator=(Status&& rhs);

  // move constructor.
  Status(Status&& rhs);

  const std::string& ErrorCode() const;

  void SetErrorCode(const std::string& code);

  std::string& MutableErrorCode();

  bool Ok() const;

  OssException& MutableOssException();

  void SetHttpStausCode(HttpStatusType http_status_code);

  HttpStatusType HttpStausCode() const;

  const OssException& GetOssException() const;

 private:
  void Init();

 private:
  OssException oss_exception_;
  std::string code_;
  HttpStatusType http_status_code_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_OSS_OSS_STATUS_H_
