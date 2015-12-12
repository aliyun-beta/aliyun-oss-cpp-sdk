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

#include <sstream>

#include "oss_sdk_cpp/base/nullable.h"
#include "oss_sdk_cpp/utils/http_utils.h"
#include "oss_sdk_cpp/utils/string_utils.h"
#include "oss_sdk_cpp/http/http_headers.h"

#include "oss_sdk_cpp/message/get_object_request.h"

namespace oss {

GetObjectRequest::GetObjectRequest(const std::string& bucket_name,
                                   const std::string& key,
                                   const std::string& file_path)
  : bucket_name_(bucket_name), key_(key), file_path_(file_path),
    output_stream_(NULL) {
}

GetObjectRequest::GetObjectRequest(const std::string& bucket_name,
                                   const std::string& key,
                                   std::ofstream* output_stream)
  : bucket_name_(bucket_name), key_(key), output_stream_(output_stream) {
}

GetObjectRequest::GetObjectRequest()
  : output_stream_(NULL) {
}

GetObjectRequest::~GetObjectRequest() {
}

void GetObjectRequest::AddToParameterList(StringMap* headers_ptr) const {
  StringMap& headers = *headers_ptr;
  if (!range_.IsNull()) {
    // example, Content-Range: bytes 0-9/44
    std::ostringstream ss;
    ss << "bytes=" << range_.Value().start << "-" << range_.Value().end;
    headers[oss::http::kRange] = ss.str();
  }

  if (!modified_since_constraint_.IsNull()) {
    headers[oss::http::kOssCopySourceIfModifiedSince] =
      GmtTime(modified_since_constraint_);
  }

  if (!unmodified_since_constraint_.IsNull()) {
    headers[oss::http::kOssCopySourceIfUnmodifiedSince] =
      GmtTime(unmodified_since_constraint_);
  }

  if (!matching_etag_constraints_.empty()) {
    headers[oss::http::kOssCopySourceIfMatch] =
      JoinStringList(matching_etag_constraints_, ", ");
  }

  if (!nonmatching_etag_constraints_.empty()) {
    headers[oss::http::kOssCopySourceIfNoneMatch] =
      JoinStringList(nonmatching_etag_constraints_, ", ");
  }

  if (object_meta_data_) {
    object_meta_data_->AddToParameterList(&headers);
  }

  // always remove "Content-Length" cause...
  headers.erase("Content-Length");
}

const std::string& GetObjectRequest::GetBucket() const {
  return bucket_name_;
}

void GetObjectRequest::SetBucket(const std::string& bucket) {
  bucket_name_ = bucket;
}

const std::string& GetObjectRequest::GetKey() const {
  return key_;
}

void GetObjectRequest::SetKey(const std::string& key) {
  key_ = key;
}

const std::string& GetObjectRequest::GetFilePath() const {
  return file_path_;
}

void GetObjectRequest::SetFilePath(const std::string& file_path) {
  file_path_ = file_path;
}

std::ofstream* GetObjectRequest::GetOutputStream() const {
  return output_stream_;
}

void GetObjectRequest::SetOutputStream(std::ofstream* stream) {
  output_stream_ = stream;
}

OptionalRange GetObjectRequest::GetRange() const {
  return range_;
}

void GetObjectRequest::SetRange(const OptionalRange& range) {
  range_ = range;
}

OptionalDateTime GetObjectRequest::GetModifiedSinceConstraint() {
  return modified_since_constraint_;
}

void GetObjectRequest::SetModifiedSinceConstraint(const OptionalDateTime& val) {
  modified_since_constraint_ = val;
}

OptionalDateTime GetObjectRequest::GetUnmodifiedSinceConstraint() {
  return unmodified_since_constraint_;
}

void GetObjectRequest::SetUnmodifiedSinceConstraint(const OptionalDateTime&
    val) {
  unmodified_since_constraint_ = val;
}

std::list<std::string> GetObjectRequest::GetMatchingETagConstraints() {
  return matching_etag_constraints_;
}

void GetObjectRequest::SetMatchingETagConstraints(
  const std::list<std::string>& val) {
  matching_etag_constraints_ = val;
}

std::list<std::string> GetObjectRequest::GetNonmatchingEtagConstraints() {
  return nonmatching_etag_constraints_;
}

void GetObjectRequest::SetNonmatchingEtagConstraints(
  const std::list<std::string>& val) {
  nonmatching_etag_constraints_ = val;
}

void GetObjectRequest::SetNewObjectMetaData(ObjectMetadata* metadata) {
  object_meta_data_.reset(metadata);
}

}  // namespace oss
