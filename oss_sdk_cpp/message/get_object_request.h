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

#ifndef OSS_SDK_CPP_MESSAGE_GET_OBJECT_REQUEST_H_
#define OSS_SDK_CPP_MESSAGE_GET_OBJECT_REQUEST_H_

#include <time.h>
#include <string>
#include <list>

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/message/object_metadata.h"

namespace oss {

class GetObjectRequest {
 public:
  GetObjectRequest();

  ~GetObjectRequest();

  void AddToParameterList(StringMap* headers) const;

  GetObjectRequest(const std::string& bucket_name,
                   const std::string& key,
                   const std::string& file_path);

  GetObjectRequest(const std::string& bucket_name,
                   const std::string& key,
                   std::ofstream* output_stream);

  const std::string& GetBucket() const;

  void SetBucket(const std::string& bucket);

  const std::string& GetKey() const;

  void SetKey(const std::string& key);

  const std::string& GetFilePath() const;

  void SetFilePath(const std::string& file_path);

  std::ofstream* GetOutputStream() const;

  void SetOutputStream(std::ofstream* stream);

  OptionalRange GetRange() const;

  void SetRange(const OptionalRange& range);

  OptionalDateTime GetModifiedSinceConstraint();
  void SetModifiedSinceConstraint(const OptionalDateTime& val);

  OptionalDateTime GetUnmodifiedSinceConstraint();
  void SetUnmodifiedSinceConstraint(const OptionalDateTime& val);

  std::list<std::string> GetMatchingETagConstraints();
  void SetMatchingETagConstraints(const std::list<std::string>& val);

  std::list<std::string> GetNonmatchingEtagConstraints();
  void SetNonmatchingEtagConstraints(const std::list<std::string>& val);

  void SetNewObjectMetaData(ObjectMetadata* metadata);

 public:
  std::string bucket_name_;

  std::string key_;

  std::string file_path_;

  std::ofstream* output_stream_;
  // header arguments.
  OptionalRange range_;

  OptionalDateTime modified_since_constraint_;

  OptionalDateTime unmodified_since_constraint_;

  std::list<std::string> matching_etag_constraints_;

  std::list<std::string> nonmatching_etag_constraints_;

  std::unique_ptr<ObjectMetadata> object_meta_data_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_GET_OBJECT_REQUEST_H_
