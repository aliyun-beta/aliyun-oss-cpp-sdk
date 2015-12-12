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

#include "oss_sdk_cpp/message/list_objects_request.h"

namespace oss {

ListObjectsRequest::ListObjectsRequest() {
}

ListObjectsRequest::ListObjectsRequest(
  const std::string& bucket_name,
  const std::string& delimiter,
  const std::string& prefix,
  const std::string& marker,
  int max_keys)
  : delimiter_(new std::string(delimiter)),
    prefix_(new std::string(prefix)),
    marker_(new std::string(marker)),
    max_keys_(new std::string(std::to_string(max_keys))),
    bucket_name_(bucket_name) {
}

ListObjectsRequest::~ListObjectsRequest() {
}

void ListObjectsRequest::AddToParameterList(StringMap* parammeters) const {
  if (delimiter_)
    (*parammeters)["delimiter"] = *delimiter_;

  if (prefix_)
    (*parammeters)["prefix"] = *prefix_;

  if (marker_)
    (*parammeters)["marker"] = *marker_;

  if (max_keys_)
    (*parammeters)["max-keys"] = *max_keys_;
}

std::string ListObjectsRequest::BuildQueryString() const {
  StringMap parammeters;
  AddToParameterList(&parammeters);
  std::string result;
  result.reserve(1024);

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

void ListObjectsRequest::SetDelimiter(const std::string& delimiter) {
  delimiter_.reset(new std::string(delimiter));
}

void ListObjectsRequest::SetPrefix(const std::string& prefix) {
  prefix_.reset(new std::string(prefix));
}

void ListObjectsRequest::SetMarker(const std::string& marker) {
  marker_.reset(new std::string(marker));
}

void ListObjectsRequest::SetMaxKeys(int max_keys) {
  if (max_keys < 0)
    max_keys = 0;
  max_keys_.reset(new std::string(std::to_string(max_keys)));
}

void ListObjectsRequest::SetBucketName(const std::string& bucket_name) {
  bucket_name_ = bucket_name;
}

const std::string& ListObjectsRequest::GetBucketName() const {
  return bucket_name_;
}

}  // namespace oss
