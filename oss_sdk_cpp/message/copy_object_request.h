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

#ifndef OSS_SDK_CPP_MESSAGE_COPY_OBJECT_REQUEST_H_
#define OSS_SDK_CPP_MESSAGE_COPY_OBJECT_REQUEST_H_

#include <time.h>
#include <string>
#include <list>

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/message/object_metadata.h"

namespace oss {

class CopyObjectRequest {
 public:
  CopyObjectRequest();

  ~CopyObjectRequest();

  void AddToParameterList(StringMap* headers) const;

  const std::string& GetSourceBucket() const;

  void SetSourceBucket(const std::string& val);

  const std::string& GetSourceKey() const;

  void SetSourceKey(const std::string& val);

  const std::string& GetTargetBucket() const;

  void SetTargetBucket(const std::string& val);

  const std::string& GetTargetKey() const;

  void SetTargetKey(const std::string& val);

  OptionalDateTime GetModifiedSinceConstraint();

  void SetModifiedSinceConstraint(const OptionalDateTime& val);

  OptionalDateTime GetUnmodifiedSinceConstraint();

  void SetUnmodifiedSinceConstraint(const OptionalDateTime& val);

  std::list<std::string> GetMatchingETagConstraints();

  void SetMatchingETagConstraints(const std::list<std::string>& val);

  std::list<std::string> GetNonmatchingEtagConstraints();

  void SetNonmatchingEtagConstraints(const std::list<std::string>& val);

  // set new metadata for target object.
  void SetNewObjectMetaData(ObjectMetadata* metadata);

 private:
  std::string GetCopySource() const;

 public:
  std::string source_bucket_;
  std::string source_key_;
  std::string target_bucket_;
  std::string target_key_;

  // header arguments.
  OptionalDateTime modified_since_constraint_;
  OptionalDateTime unmodified_since_constraint_;
  std::list<std::string> matching_etag_constraints_;
  std::list<std::string> nonmatching_etag_constraints_;
  std::unique_ptr<ObjectMetadata> object_meta_data_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_COPY_OBJECT_REQUEST_H_
