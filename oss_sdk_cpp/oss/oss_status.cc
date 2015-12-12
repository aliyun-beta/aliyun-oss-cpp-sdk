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

#include "oss_sdk_cpp/oss/oss_status.h"

namespace oss {

Status::Status() {
  Init();
}

Status::Status(const std::string& code)
  : code_(code) {
  Init();
}

// move assignment
Status& Status::operator=(Status&& rhs) {
  code_ = std::move(rhs.code_);
  oss_exception_ = std::move(rhs.oss_exception_);
  http_status_code_ = rhs.http_status_code_;
  rhs.http_status_code_ = 0;

  return *this;
}

// move constructor.
Status::Status(Status&& rhs)
  : oss_exception_(std::move(rhs.oss_exception_)),
  code_(std::move(rhs.code_)),
  http_status_code_(rhs.http_status_code_) {
}

const std::string& Status::ErrorCode() const {
  return code_;
}

void Status::SetErrorCode(const std::string& code) {
  code_ = code;
}

std::string& Status::MutableErrorCode() {
  return code_;
}

bool Status::Ok() const {
  return code_.empty();
}

OssException& Status::MutableOssException() {
  return oss_exception_;
}

void Status::SetHttpStausCode(HttpStatusType http_status_code) {
  http_status_code_ = http_status_code;
}

HttpStatusType Status::HttpStausCode() const {
  return http_status_code_;
}

const OssException& Status::GetOssException() const {
  return oss_exception_;
}

void Status::Init() {
  http_status_code_ = 0;
}

}  // namespace oss
