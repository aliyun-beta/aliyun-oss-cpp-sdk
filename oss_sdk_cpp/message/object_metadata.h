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

#ifndef OSS_SDK_CPP_MESSAGE_OBJECT_METADATA_H_
#define OSS_SDK_CPP_MESSAGE_OBJECT_METADATA_H_

#include <stdint.h>
#include <string>
#include <map>

#include "oss_sdk_cpp/base/base.h"

namespace oss {

class ObjectMetadata {
 public:
  ObjectMetadata();
  ~ObjectMetadata();

  OptionalString GetCacheControl() const;
  void SetCacheControl(const std::string& cache_control);

  OptionalInt64 GetContentLength() const;
  void SetContentLength(const int64_t length);

  OptionalString GetContentType() const;
  void SetContentType(const std::string& type);

  OptionalString GetContentMd5() const;
  void SetContentMd5(const std::string& md5);

  OptionalString GetContentEncoding() const;
  void SetContentEncoding(const std::string& encoding);

  OptionalString GetContentDisposition() const;
  void SetContentDisposition(const std::string& disposition);

  OptionalString GetExpirationTime() const;
  void SetExpirationTime(const std::string& expiration);

  OptionalString GetLastModified() const;
  void SetLastModified(const std::string& last_modified);

  OptionalString GetServerSideEncryption() const;
  void SetServerSideEncryption(const std::string& encryption);

  void AddToParameterList(StringMap* headers) const;

  void AddHeader(const std::string& key, const std::string& value);
  void AddUserHeader(const std::string& key, const std::string& value);

  void SetMetadata(const StringMap& headers);

 private:
  OptionalString FindMetaString(const std::string& key) const;

 private:
  // x-oss-meta prefix.
  StringMap user_metadata_;
  // standard http headers.
  StringMap metadata_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_OBJECT_METADATA_H_
