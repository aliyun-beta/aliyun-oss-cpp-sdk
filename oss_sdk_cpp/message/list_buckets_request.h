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

#ifndef OSS_SDK_CPP_MESSAGE_LIST_BUCKETS_REQUEST_H_
#define OSS_SDK_CPP_MESSAGE_LIST_BUCKETS_REQUEST_H_

#include <string>

#include "oss_sdk_cpp/base/base.h"

namespace oss {

class ListBucketsRequest {
 public:
  ListBucketsRequest();
  ListBucketsRequest(const std::string& prefix,
                     const std::string& marker,
                     int max_keys);

  ~ListBucketsRequest();

  void AddToParameterList(StringMap* parammeters) const;
  void SetPrefix(const std::string& prefix);
  void SetMarker(const std::string& marker);
  void SetMaxKeys(int max_keys);

 private:
  std::unique_ptr<std::string> prefix_;
  std::unique_ptr<std::string> marker_;
  std::unique_ptr<std::string> max_keys_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_LIST_BUCKETS_REQUEST_H_
