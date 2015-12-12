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

#include "oss_sdk_cpp/message/initiate_multipart_upload_request.h"

namespace oss {

InitiateMultipartUploadRequest::InitiateMultipartUploadRequest() {
}

InitiateMultipartUploadRequest::InitiateMultipartUploadRequest(
  const std::string& bucket_name,
  const std::string& key)
  : bucket_name_(bucket_name),
    key_(key) {
}

const std::string& InitiateMultipartUploadRequest::GetBucketName() const {
  return bucket_name_;
}

void InitiateMultipartUploadRequest::SetBucketName(const std::string& name) {
  bucket_name_ = name;
}

const std::string& InitiateMultipartUploadRequest::GetKey() const {
  return key_;
}

void InitiateMultipartUploadRequest::SetKey(const std::string& key) {
  key_ = key;
}

std::string InitiateMultipartUploadRequest::BuildQueryString() const {
  return key_ + "?uploads";
}

}  // namespace oss
