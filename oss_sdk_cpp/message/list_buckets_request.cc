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

#include "oss_sdk_cpp/message/list_buckets_request.h"

namespace oss {

ListBucketsRequest::ListBucketsRequest() {
}

ListBucketsRequest::ListBucketsRequest(const std::string& prefix,
                                       const std::string& marker,
                                       int max_keys)
  : prefix_(new std::string(prefix)),
    marker_(new std::string(marker)) {
  std::string str = std::to_string(max_keys);
  max_keys_.reset(new std::string(str));
}

ListBucketsRequest::~ListBucketsRequest() {
}

void ListBucketsRequest::AddToParameterList(StringMap* parammeters) const {
  if (prefix_)
    (*parammeters)["prefix"] = *prefix_;

  if (marker_)
    (*parammeters)["marker"] = *marker_;

  if (max_keys_)
    (*parammeters)["max-keys"] = *max_keys_;
}

void ListBucketsRequest::SetPrefix(const std::string& prefix) {
  prefix_.reset(new std::string(prefix));
}

void ListBucketsRequest::SetMarker(const std::string& marker) {
  marker_.reset(new std::string(marker));
}

void ListBucketsRequest::SetMaxKeys(int max_keys) {
  if (max_keys < 0)
    max_keys = 0;
  max_keys_.reset(new std::string(std::to_string(max_keys)));
}

}  // namespace oss
