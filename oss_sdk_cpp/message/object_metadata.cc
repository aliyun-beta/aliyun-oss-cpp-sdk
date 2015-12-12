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

#include <apr_strings.h>

#include "oss_sdk_cpp/http/http_headers.h"
#include "oss_sdk_cpp/utils/http_utils.h"
#include "oss_sdk_cpp/oss/oss.h"

#include "oss_sdk_cpp/message/object_metadata.h"

namespace oss {

ObjectMetadata::ObjectMetadata() {
}

ObjectMetadata::~ObjectMetadata() {
}

void ObjectMetadata::AddToParameterList(StringMap* headers_ptr) const {
  StringMap& headers = *headers_ptr;
  for (const auto& kv : user_metadata_) {
    std::string newkey = kOssPrefix + kv.first;
    headers[newkey] = kv.second;
  }

  if (headers.find(oss::http::kContentType) == headers.end()) {
    headers[oss::http::kContentType] = kObjectDefaultContentType;
  }

  for (const auto& kv : metadata_) {
    headers[kv.first] = kv.second;
  }
}

OptionalString ObjectMetadata::GetCacheControl() const {
  return FindMetaString(oss::http::kCacheControl);
}

void ObjectMetadata::SetCacheControl(const std::string& cache_control) {
  metadata_[oss::http::kCacheControl] = cache_control;
}

OptionalInt64 ObjectMetadata::GetContentLength() const {
  auto iter = metadata_.find(oss::http::kContentLength);
  if (iter != metadata_.end()) {
    return apr_atoi64(iter->second.c_str());
  }
  return OptionalInt64();
}

void ObjectMetadata::SetContentLength(const int64_t length) {
  metadata_[oss::http::kContentLength] = std::to_string(length);
}

OptionalString ObjectMetadata::GetContentType() const {
  return FindMetaString(oss::http::kContentType);
}

void ObjectMetadata::SetContentType(const std::string& type) {
  metadata_[oss::http::kContentType] = type;
}

OptionalString ObjectMetadata::GetContentMd5() const {
  return FindMetaString(oss::http::kContentMd5);
}

void ObjectMetadata::SetContentMd5(const std::string& md5) {
  metadata_[oss::http::kContentMd5] = md5;
}

OptionalString ObjectMetadata::GetContentEncoding() const {
  return FindMetaString(oss::http::kContentEncoding);
}

void ObjectMetadata::SetContentEncoding(const std::string& encoding) {
  metadata_[oss::http::kContentEncoding] = encoding;
}

OptionalString ObjectMetadata::GetContentDisposition() const {
  return FindMetaString(oss::http::kContentDisposition);
}

void ObjectMetadata::SetContentDisposition(const std::string& disposition) {
  metadata_[oss::http::kContentDisposition] = disposition;
}

OptionalString ObjectMetadata::GetExpirationTime() const {
  return FindMetaString(oss::http::kExpires);
}

void ObjectMetadata::SetExpirationTime(const std::string& expiration) {
  metadata_[oss::http::kExpires] = expiration;
}

OptionalString ObjectMetadata::GetLastModified() const {
  return FindMetaString(oss::http::kLastModified);
}

void ObjectMetadata::SetLastModified(const std::string& last_modified) {
  metadata_[oss::http::kLastModified] = last_modified;
}

OptionalString ObjectMetadata::GetServerSideEncryption() const {
  return FindMetaString(oss::http::kServerSideEncryption);
}

void ObjectMetadata::SetServerSideEncryption(const std::string& encryption) {
  metadata_[oss::http::kServerSideEncryption] = encryption;
}

void ObjectMetadata::AddHeader(const std::string& key,
                               const std::string& value) {
  metadata_[key] = value;
}

void ObjectMetadata::AddUserHeader(const std::string& key,
                                   const std::string& value) {
  user_metadata_[key] = value;
}

void ObjectMetadata::SetMetadata(const StringMap& headers) {
  metadata_ = headers;
}

OptionalString ObjectMetadata::FindMetaString(const std::string& key) const {
  auto iter = metadata_.find(key);
  if (iter != metadata_.end()) {
    return iter->second;
  }
  return OptionalString();
}

}  // namespace oss
