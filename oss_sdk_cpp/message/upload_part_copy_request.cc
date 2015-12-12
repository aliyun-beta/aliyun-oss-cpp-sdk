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
#include "oss_sdk_cpp/utils/http_utils.h"
#include "oss_sdk_cpp/http/http_headers.h"

#include "oss_sdk_cpp/message/upload_part_copy_request.h"

namespace oss {

UploadPartCopyRequest::UploadPartCopyRequest() {
}

UploadPartCopyRequest::UploadPartCopyRequest(
  const std::string& source_bucket,
  const std::string& key,
  const std::string& target_bucket,
  const std::string& target_key,
  std::string upload_id,
  int part_number,
  int64_t part_size,
  int64_t stream_pos)
  : source_bucket_(source_bucket),
    source_key_(key),
    target_bucket_(target_bucket),
    target_key_(target_key),
    upload_id_(upload_id),
    part_number_(part_number),
    part_size_(part_size),
    stream_pos_(stream_pos) {
}

const std::string& UploadPartCopyRequest::GetSourceBucket() const {
  return source_bucket_;
}

void UploadPartCopyRequest::SetSourceBucket(const std::string& val) {
  source_bucket_ = val;
}

const std::string& UploadPartCopyRequest::GetSourceKey() const {
  return source_key_;
}

void UploadPartCopyRequest::SetSourceKey(const std::string& val) {
  source_key_ = val;
}

const std::string& UploadPartCopyRequest::GetTargetBucket() const {
  return target_bucket_;
}

void UploadPartCopyRequest::SetTargetBucket(const std::string& val) {
  target_bucket_ = val;
}

const std::string& UploadPartCopyRequest::GetTargetKey() const {
  return target_key_;
}

void UploadPartCopyRequest::SetTargetKey(const std::string& val) {
  target_key_ = val;
}

const std::string& UploadPartCopyRequest::GetUploadId() const {
  return upload_id_;
}

void UploadPartCopyRequest::SetUploadId(const std::string& upload_id) {
  upload_id_ = upload_id;
}

int UploadPartCopyRequest::GetPartNumber() const {
  return part_number_;
}

void UploadPartCopyRequest::SetPartNumber(int part_number) {
  part_number_ = part_number;
}

int64_t UploadPartCopyRequest::GetPartSize() const {
  return part_size_;
}

void UploadPartCopyRequest::SetPartPartSize(int64_t part_size) {
  part_size_ = part_size;
}

int64_t UploadPartCopyRequest::GetStreamPos() const {
  return stream_pos_;
}

void UploadPartCopyRequest::SetStreamPos(const int64_t stream_pos) {
  stream_pos_ = stream_pos;
}

std::string UploadPartCopyRequest::BuildQueryString() const {
  std::string str;
  str.reserve(128);
  str.append(target_key_).append("?")
  .append("partNumber=").append(std::to_string(part_number_)).append("&")
  .append("uploadId=").append(upload_id_);
  return str;
}

void UploadPartCopyRequest::SetNewObjectMetaData(ObjectMetadata* metadata) {
  object_meta_data_.reset(metadata);
}

void UploadPartCopyRequest::AddToParameterList(StringMap* headers_ptr) const {
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

  headers[oss::http::kContentLength] = std::to_string(part_size_);

  std::string content_range;
  content_range.append("bytes=").append(std::to_string(stream_pos_))
  .append("-").append(std::to_string(stream_pos_ + part_size_ - 1));

  headers[oss::http::kOssCopySourceRange] = content_range;

  if (object_meta_data_) {
    object_meta_data_->AddToParameterList(&headers);
  }

  headers.erase("Content-Length");
}

std::string UploadPartCopyRequest::GetCopySource() const {
  return "/" + source_bucket_ + "/" + UrlEscape(source_key_);
}

OptionalDateTime UploadPartCopyRequest::GetModifiedSinceConstraint() {
  return modified_since_constraint_;
}

void UploadPartCopyRequest::SetModifiedSinceConstraint(const OptionalDateTime&
    val) {
  modified_since_constraint_ = val;
}

OptionalDateTime UploadPartCopyRequest::GetUnmodifiedSinceConstraint() {
  return unmodified_since_constraint_;
}

void UploadPartCopyRequest::SetUnmodifiedSinceConstraint(
  const OptionalDateTime& val) {
  unmodified_since_constraint_ = val;
}

std::list<std::string> UploadPartCopyRequest::GetMatchingETagConstraints() {
  return matching_etag_constraints_;
}

void UploadPartCopyRequest::SetMatchingETagConstraints(
  const std::list<std::string>& val) {
  matching_etag_constraints_ = val;
}

std::list<std::string> UploadPartCopyRequest::GetNonmatchingEtagConstraints() {
  return nonmatching_etag_constraints_;
}

void UploadPartCopyRequest::SetNonmatchingEtagConstraints(
  const std::list<std::string>& val) {
  nonmatching_etag_constraints_ = val;
}

}  // namespace oss
