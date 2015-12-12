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

#include "oss_sdk_cpp/message/list_multipart_uploads_request.h"

namespace oss {

ListMultipartUploadsRequest::ListMultipartUploadsRequest() {
}

ListMultipartUploadsRequest::ListMultipartUploadsRequest(
  const std::string& bucket_name,
  const std::string& delimiter,
  int max_uploads,
  const std::string& key_marker,
  const std::string& prefix,
  const std::string& upload_id_marker)
  : bucket_name_(bucket_name),
    delimiter_(new std::string(delimiter)),
    max_uploads_(new std::string(std::to_string(max_uploads))),
    key_marker_(new std::string(key_marker)),
    prefix_(new std::string(prefix)),
    upload_id_marker_(new std::string(upload_id_marker)) {
}

ListMultipartUploadsRequest::~ListMultipartUploadsRequest() {
}

void ListMultipartUploadsRequest::AddToParameterList(
  StringMap* parammeters) const {
  if (delimiter_)
    (*parammeters)["delimiter"] = *delimiter_;

  if (prefix_)
    (*parammeters)["prefix"] = *prefix_;

  if (key_marker_)
    (*parammeters)["key-marker"] = *key_marker_;

  if (max_uploads_)
    (*parammeters)["max-uploads"] = *max_uploads_;

  if (upload_id_marker_)
    (*parammeters)["upload-id-marker"] = *upload_id_marker_;
}

std::string ListMultipartUploadsRequest::BuildQueryString() const {
  StringMap parammeters;
  AddToParameterList(&parammeters);
  std::string result;
  result.reserve(1024);

  // sounds no necessary to do url escape.
  for (auto& kv : parammeters) {
    if (!result.empty())
      result.append("&");
    result.append(kv.first);
    if (!kv.second.empty())
      result.append("=");
    result.append(kv.second);
  }

  return result;
}

void ListMultipartUploadsRequest::SetDelimiter(const std::string& delimiter) {
  delimiter_.reset(new std::string(delimiter));
}

void ListMultipartUploadsRequest::SetMaxUploads(int max_uploads) {
  if (max_uploads < 0)
    max_uploads = 0;
  max_uploads_.reset(new std::string(std::to_string(max_uploads)));
}

void ListMultipartUploadsRequest::SetKeyMarker(const std::string& key_marker) {
  key_marker_.reset(new std::string(key_marker));
}

void ListMultipartUploadsRequest::SetPrefix(const std::string& prefix) {
  prefix_.reset(new std::string(prefix));
}

void ListMultipartUploadsRequest::SetUploadIdMarker(const std::string& marker) {
  upload_id_marker_.reset(new std::string(marker));
}

void ListMultipartUploadsRequest::SetBucketName(const std::string& name) {
  bucket_name_ = name;
}

const std::string& ListMultipartUploadsRequest::GetBucketName() const {
  return bucket_name_;
}

}  // namespace oss
