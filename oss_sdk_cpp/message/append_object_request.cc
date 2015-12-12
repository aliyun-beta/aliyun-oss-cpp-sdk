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

#include "oss_sdk_cpp/utils/string_utils.h"
#include "oss_sdk_cpp/utils/utils.h"

#include "oss_sdk_cpp/message/append_object_request.h"

namespace oss {

AppendObjectRequest::AppendObjectRequest() :
  position_(0) {
}

AppendObjectRequest::AppendObjectRequest(
  const std::string& bucket_name,
  const std::string& object_name,
  const std::string& file_path,
  int64_t stream_position)
  : bucket_name_(bucket_name),
    key_(object_name),
    file_path_(file_path),
    position_(stream_position) {
}

AppendObjectRequest::~AppendObjectRequest() {
}

const std::string& AppendObjectRequest::GetBucketName() const {
  return bucket_name_;
}

void AppendObjectRequest::SetBucketName(const std::string& name) {
  bucket_name_ = name;
}

const std::string& AppendObjectRequest::GetKey() const {
  return key_;
}

void AppendObjectRequest::SetKey(const std::string& key) {
  key_ = key;
}

const std::string& AppendObjectRequest::GetFilePath() const {
  return file_path_;
}

void AppendObjectRequest::SetFilePath(const std::string& file_path) {
  file_path_ = file_path;
}

uint64_t AppendObjectRequest::GetPosition() const {
  return position_;
}

void AppendObjectRequest::SetPosition(const uint64_t position) {
  position_ = position;
}

std::string AppendObjectRequest::BuildQueryString() const {
  return key_ + "?append&position=" + std::to_string(position_);
}

}  // namespace oss
