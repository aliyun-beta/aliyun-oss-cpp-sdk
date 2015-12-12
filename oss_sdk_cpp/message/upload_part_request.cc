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

#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/utils/string_utils.h"

#include "oss_sdk_cpp/message/upload_part_request.h"

namespace oss {

UploadPartRequest::UploadPartRequest() {
}

UploadPartRequest::UploadPartRequest(const std::string& bucket_name,
                                     const std::string& key,
                                     std::string upload_id,
                                     std::ifstream* input_stream,
                                     int part_number,
                                     int64_t part_size,
                                     const std::string& md5_digest)
  : bucket_name_(bucket_name),
    key_(key),
    upload_id_(upload_id),
    input_stream_(input_stream),
    part_number_(part_number),
    part_size_(part_size),
    md5_digest_(md5_digest) {
}

const std::string& UploadPartRequest::GetBucketName() const {
  return bucket_name_;
}

void UploadPartRequest::SetBucketName(const std::string& name) {
  bucket_name_ = name;
}

const std::string& UploadPartRequest::GetKey() const {
  return key_;
}

void UploadPartRequest::SetKey(const std::string& key) {
  key_ = key;
}

const std::string& UploadPartRequest::GetUploadId() const {
  return upload_id_;
}

void UploadPartRequest::SetUploadId(const std::string& upload_id) {
  upload_id_ = upload_id;
}

std::ifstream* UploadPartRequest::GetInputStream() const {
  return input_stream_;
}

void UploadPartRequest::SetInputStream(std::ifstream* input_stream) {
  input_stream_ = input_stream;
}

int UploadPartRequest::GetPartNumber() const {
  return part_number_;
}

void UploadPartRequest::SetPartNumber(int part_number) {
  part_number_ = part_number;
}

int64_t UploadPartRequest::GetPartSize() const {
  return part_size_;
}

void UploadPartRequest::SetPartPartSize(int64_t part_size) {
  part_size_ = part_size;
}

const std::string& UploadPartRequest::GetMd5Digest() const {
  return md5_digest_;
}

void UploadPartRequest::SetMd5Digest(const std::string& digest) {
  md5_digest_ = digest;
}

std::string UploadPartRequest::BuildQueryString() const {
  std::string str;
  str.reserve(128);
  str.append(key_).append("?")
  .append("partNumber=").append(std::to_string(part_number_)).append("&")
  .append("uploadId=").append(upload_id_);

  return str;
}

}  // namespace oss
