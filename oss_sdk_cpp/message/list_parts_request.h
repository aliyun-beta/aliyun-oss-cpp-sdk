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

#ifndef OSS_SDK_CPP_MESSAGE_LIST_PARTS_REQUEST_H_
#define OSS_SDK_CPP_MESSAGE_LIST_PARTS_REQUEST_H_

#include <string>

#include "oss_sdk_cpp/base/base.h"

namespace oss {

class ListPartsRequest {
 public:
  ListPartsRequest();

  ListPartsRequest(const std::string& bucket_name,
                   const std::string& key,
                   const std::string& upload_id,
                   int max_parts,
                   int part_number_marker);

  ~ListPartsRequest();

  std::string BuildQueryString() const;

  void SetBucketName(const std::string& bucket_name);
  void SetKey(const std::string& key);
  void SetUploadId(const std::string& delimiter);
  void SetMaxParts(int max_parts);
  void SetPartNumberMarker(int part_number_marker);

  const std::string& GetBucketName() const;
  const std::string& GetKey() const;
  const std::string GetUploaId() const;

 private:
  std::string bucket_name_;
  std::string key_;
  std::unique_ptr<std::string> upload_id_;
  std::unique_ptr<std::string> max_parts_;
  std::unique_ptr<std::string> part_number_marker_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_LIST_PARTS_REQUEST_H_
