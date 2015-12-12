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

#ifndef OSS_SDK_CPP_MESSAGE_LIST_OBJECTS_RESULT_H_
#define OSS_SDK_CPP_MESSAGE_LIST_OBJECTS_RESULT_H_

#include <string>
#include <list>

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/message/bucket.h"
#include "oss_sdk_cpp/message/object_content.h"

namespace oss {

// Equivalent to ListBucketResult, list all objects in a bucket.
class ListObjectsResult {
 public:
  ListObjectsResult();

  ~ListObjectsResult();

  const std::list<ObjectContent>& GetContents() const;

  bool GetIsTruncated() const;

  int GetMaxKeys() const;

  const std::string& GetMarker() const;

  const std::string& GetPrefix() const;

  const std::string& GetDelimiter() const;

  const std::string& GetBucketName() const;

  const std::string& GetNextMarker() const;

  std::list<ObjectContent>& MutableContents();

  const StringList& GetCommonPrefixes() const;

  bool DeserializeFromXml(const std::string& content);

 private:
  std::list<ObjectContent> contents_;

  // optional fields
  bool        is_truncated_;
  int         max_keys_;
  std::string marker_;
  std::string prefix_;
  std::string delimiter_;
  std::string next_marker_;
  std::string bucket_name_;
  StringList common_prefixes_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_LIST_OBJECTS_RESULT_H_
