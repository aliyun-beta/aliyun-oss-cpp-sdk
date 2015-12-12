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

#ifndef OSS_SDK_CPP_MESSAGE_LIST_BUCKETS_RESULT_H_
#define OSS_SDK_CPP_MESSAGE_LIST_BUCKETS_RESULT_H_

#include <string>
#include <vector>
#include "oss_sdk_cpp/message/bucket.h"

namespace oss {

class ListBucketsResult {
 public:
  ListBucketsResult();

  ~ListBucketsResult();

  const std::vector<Bucket>& GetBuckets() const;

  const std::string& GetOwnerId() const;

  const std::string& GetOwnerDisplayName() const;

  bool GetIsTruncated() const;

  int GetMaxKeys() const;

  const std::string& GetMarker() const;

  const std::string& GetNextMarker() const;

  const std::string& GetPrefix() const;

  std::vector<Bucket>& MutableBuckets();

  bool DeserializeFromXml(const std::string& content);

 private:
  std::vector<Bucket> buckets_;
  std::string owner_id_;
  std::string owner_display_name_;

  // optional fields
  bool        is_truncated_;
  int         max_keys_;
  std::string marker_;
  std::string next_marker_;
  std::string prefix_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_LIST_BUCKETS_RESULT_H_
