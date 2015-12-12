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

#include "oss_sdk_cpp/oss/oss.h"

namespace oss {

const char kAclPrivate[] = "private";
const char kAclPublicReadWrite[] = "public-read-write";
const char kAclPublicRead[] = "public-read";

const char kOssPrefix[] = "x-oss-";
const char kOssUserMetaPrefix[] = "x-oss-meta-";
const char kOssAcl[] = "x-oss-acl";

const char kObjectDefaultContentType[] = "application/octet-stream";

int InitOssSdk() {
  return static_cast<int>(curl_global_init(CURL_GLOBAL_DEFAULT));
}

void DeinitOssSdk() {
  curl_global_cleanup();
}

}  // namespace oss
