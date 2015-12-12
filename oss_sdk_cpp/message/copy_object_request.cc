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

#include "oss_sdk_cpp/base/nullable.h"
#include "oss_sdk_cpp/utils/http_utils.h"
#include "oss_sdk_cpp/utils/string_utils.h"
#include "oss_sdk_cpp/http/http_headers.h"

#include "oss_sdk_cpp/message/copy_object_request.h"

namespace oss {

CopyObjectRequest::CopyObjectRequest() {
}

CopyObjectRequest::~CopyObjectRequest() {
}

std::string CopyObjectRequest::GetCopySource() const {
  return "/" + source_bucket_ + "/" + UrlEscape(source_key_);
}

void CopyObjectRequest::AddToParameterList(StringMap* headers_ptr) const {
  StringMap& headers = *headers_ptr;
  headers[oss::http::kOssCopySource] = GetCopySource();

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

  headers.erase("Content-Length");
}

const std::string& CopyObjectRequest::GetSourceBucket() const {
  return source_bucket_;
}

void CopyObjectRequest::SetSourceBucket(const std::string& val) {
  source_bucket_ = val;
}

const std::string& CopyObjectRequest::GetSourceKey() const {
  return source_key_;
}

void CopyObjectRequest::SetSourceKey(const std::string& val) {
  source_key_ = val;
}

const std::string& CopyObjectRequest::GetTargetBucket() const {
  return target_bucket_;
}

void CopyObjectRequest::SetTargetBucket(const std::string& val) {
  target_bucket_ = val;
}

const std::string& CopyObjectRequest::GetTargetKey() const {
  return target_key_;
}

void CopyObjectRequest::SetTargetKey(const std::string& val) {
  target_key_ = val;
}

OptionalDateTime CopyObjectRequest::GetModifiedSinceConstraint() {
  return modified_since_constraint_;
}

void CopyObjectRequest::SetModifiedSinceConstraint(const OptionalDateTime&
    val) {
  modified_since_constraint_ = val;
}

OptionalDateTime CopyObjectRequest::GetUnmodifiedSinceConstraint() {
  return unmodified_since_constraint_;
}

void CopyObjectRequest::SetUnmodifiedSinceConstraint(const OptionalDateTime&
    val) {
  unmodified_since_constraint_ = val;
}

std::list<std::string> CopyObjectRequest::GetMatchingETagConstraints() {
  return matching_etag_constraints_;
}

void CopyObjectRequest::SetMatchingETagConstraints(
  const std::list<std::string>& val) {
  matching_etag_constraints_ = val;
}

std::list<std::string> CopyObjectRequest::GetNonmatchingEtagConstraints() {
  return nonmatching_etag_constraints_;
}

void CopyObjectRequest::SetNonmatchingEtagConstraints(
  const std::list<std::string>& val) {
  nonmatching_etag_constraints_ = val;
}

void CopyObjectRequest::SetNewObjectMetaData(ObjectMetadata* metadata) {
  object_meta_data_.reset(metadata);
}

}  // namespace oss
