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

#include "oss_sdk_cpp/message/list_parts_request.h"

namespace oss {

ListPartsRequest::ListPartsRequest(
  const std::string& bucket_name,
  const std::string& key,
  const std::string& upload_id,
  int max_parts,
  int part_number_marker)
  : bucket_name_(bucket_name),
    key_(key),
    upload_id_(new std::string(upload_id)),
    max_parts_(new std::string(std::to_string(max_parts))),
    part_number_marker_(new std::string(std::to_string(part_number_marker))) {
}

ListPartsRequest::ListPartsRequest() {
}

ListPartsRequest::~ListPartsRequest() {
}

std::string ListPartsRequest::BuildQueryString() const {
  std::string query_string;
  int argument_count = 0;
  if (upload_id_) {
    query_string.append("uploadId=").append(*upload_id_);
    argument_count++;
  }

  if (max_parts_) {
    if (argument_count != 0)
      query_string.append("&");
    query_string.append("max-parts=").append(*max_parts_);
    argument_count++;
  }

  if (part_number_marker_) {
    if (argument_count != 0)
      query_string.append("&");
    query_string.append("part-number-marker=").append(*part_number_marker_);
    argument_count++;
  }

  return query_string;
}

void ListPartsRequest::SetBucketName(const std::string& bucket_name) {
  bucket_name_ = bucket_name;
}

void ListPartsRequest::SetKey(const std::string& key) {
  key_ = key;
}

void ListPartsRequest::SetUploadId(const std::string& upload_id) {
  upload_id_.reset(new std::string(upload_id));
}

void ListPartsRequest::SetMaxParts(int max_parts) {
  if (max_parts < 0)
    max_parts = 0;
  max_parts_.reset(new std::string(std::to_string(max_parts)));
}

void ListPartsRequest::SetPartNumberMarker(int part_number_marker) {
  if (part_number_marker < 0)
    part_number_marker = 0;
  part_number_marker_.reset(
    new std::string(std::to_string(part_number_marker)));
}

const std::string& ListPartsRequest::GetBucketName() const {
  return bucket_name_;
}

const std::string& ListPartsRequest::GetKey() const {
  return key_;
}

const std::string ListPartsRequest::GetUploaId() const {
  if (upload_id_)
    return *upload_id_;
  else
    return std::string();
}

}  // namespace oss
