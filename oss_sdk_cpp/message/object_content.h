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

#ifndef OSS_SDK_CPP_MESSAGE_OBJECT_CONTENT_H_
#define OSS_SDK_CPP_MESSAGE_OBJECT_CONTENT_H_

#include <list>
#include <string>

namespace oss {

class ObjectContent {
 public:
  ObjectContent();

  ObjectContent(std::string key,
                std::string last_modified,
                std::string etag,
                std::string type,
                size_t size,
                std::string storage_class,
                std::string owner_id,
                std::string owner_display_name);

  ~ObjectContent();

  const std::string& GetKey() const;

  void SetKey(const std::string& val);

  const std::string& GetLastModified() const;

  void SetLastModified(const std::string& val);

  const std::string& GetEtag() const;

  void SetEtag(const std::string& val);

  const std::string& GetType() const;

  void SetType(const std::string& val);

  size_t GetSize() const;

  void SetSize(const size_t& val);

  const std::string& GetStorageClass() const;

  void SetStorageClass(const std::string& val);

  const std::string& GetOwnerId() const;

  void SetOwnerId(const std::string& val);

  const std::string& GetOwnerDisplayName() const;

  void SetOwnerDisplayName(const std::string& val);

 private:
  std::string key_;
  std::string last_modified_;
  std::string etag_;
  std::string type_;
  size_t size_;
  std::string storage_class_;
  std::string owner_id_;
  std::string owner_display_name_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_OBJECT_CONTENT_H_
