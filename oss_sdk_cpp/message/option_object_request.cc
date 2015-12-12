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

#include "oss_sdk_cpp/message/option_object_request.h"

namespace oss {

OptionObjectRequest::OptionObjectRequest() {
}

OptionObjectRequest::OptionObjectRequest(const std::string& bucket_name,
    const std::string& key,
    const std::string& origin,
    const std::string& request_method,
    const std::string& request_headers)
  : bucket_name_(bucket_name),
    key_(key),
    origin_(origin),
    request_method_(request_method),
    request_headers_(request_headers) {
}

OptionObjectRequest::~OptionObjectRequest() {
}

const std::string& OptionObjectRequest::GetBucketName() const {
  return bucket_name_;
}

void OptionObjectRequest::SetBucketName(const std::string& name) {
  bucket_name_ = name;
}

const std::string& OptionObjectRequest::GetKey() const {
  return key_;
}

void OptionObjectRequest::SetKey(const std::string& key) {
  key_ = key;
}

const std::string& OptionObjectRequest::GetOrigin() const {
  return origin_;
}

void OptionObjectRequest::SetOrigin(const std::string& origin) {
  origin_ = origin;
}

const std::string& OptionObjectRequest::GetRequestMethod() const {
  return request_method_;
}

void OptionObjectRequest::SetRequestMethod(const std::string& request_method) {
  request_method_ = request_method;
}

const std::string& OptionObjectRequest::GetRequestHeaders() const {
  return request_headers_;
}

void OptionObjectRequest::SetRequestHeaders(const std::string& request_header) {
  request_headers_ = request_header;
}

}  // namespace oss
