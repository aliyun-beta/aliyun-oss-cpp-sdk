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

#include <curl/curl.h>

#include "oss_sdk_cpp/http/curl_warppers.h"

namespace oss {

CUrl::CUrl() {
  curl_ = curl_easy_init();
}

CUrl::~CUrl() {
  if (curl_ != NULL) {
    curl_easy_cleanup(curl_);
    curl_ = NULL;
  }
}

void* CUrl::Get() {
  return curl_;
}

void CUrl::Close() {
  if (curl_ != NULL) {
    curl_easy_cleanup(curl_);
    curl_ = NULL;
  }
}

void CUrl::ReCreate() {
  Close();
  curl_ = curl_easy_init();
}

void CUrl::ResetState() {
  if (curl_ != NULL) {
    curl_easy_reset(curl_);
  }
}

CURL* CUrl::Create() {
  if (curl_ == NULL) {
    curl_ = curl_easy_init();
  }
  return curl_;
}

CUrlSlist::CUrlSlist() {
  slist_ = NULL;
}

CUrlSlist::~CUrlSlist() {
  if (slist_ != NULL) {
    curl_slist_free_all(slist_);
    slist_ = NULL;
  }
}

void CUrlSlist::AddHeader(const std::string& key, const std::string& value) {
  std::string str = key + ": " + value;
  slist_ = curl_slist_append(slist_, str.c_str());
}

curl_slist* CUrlSlist::Get() {
  return slist_;
}

}  // namespace oss
