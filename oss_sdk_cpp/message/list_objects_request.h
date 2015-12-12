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

#ifndef OSS_SDK_CPP_MESSAGE_LIST_OBJECTS_REQUEST_H_
#define OSS_SDK_CPP_MESSAGE_LIST_OBJECTS_REQUEST_H_

#include <string>
#include "oss_sdk_cpp/base/base.h"

namespace oss {

class ListObjectsRequest {
 public:
  ListObjectsRequest();

  ListObjectsRequest(const std::string& bucket_name,
                     const std::string& delimiter,
                     const std::string& prefix,
                     const std::string& marker,
                     int max_keys);

  ~ListObjectsRequest();

  void AddToParameterList(StringMap* parammeters) const;

  std::string BuildQueryString() const;

  void SetDelimiter(const std::string& delimiter);

  void SetPrefix(const std::string& prefix);

  void SetMarker(const std::string& marker_);

  void SetMaxKeys(int max_keys);

  void SetBucketName(const std::string& bucket_name);

  const std::string& GetBucketName() const;

 private:
  std::unique_ptr<std::string> delimiter_;
  std::unique_ptr<std::string> prefix_;
  std::unique_ptr<std::string> marker_;
  std::unique_ptr<std::string> max_keys_;
  std::string bucket_name_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_LIST_OBJECTS_REQUEST_H_
