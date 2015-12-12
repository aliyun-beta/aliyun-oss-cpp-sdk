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

#include "oss_sdk_cpp/message/object_content.h"

namespace oss {

ObjectContent::ObjectContent()
  : size_(0) {
}

ObjectContent::ObjectContent(std::string key,
                             std::string last_modified,
                             std::string etag,
                             std::string type,
                             size_t size,
                             std::string storage_class,
                             std::string owner_id,
                             std::string owner_display_name)
  : key_(key),
    last_modified_(last_modified),
    etag_(etag),
    type_(type),
    size_(size),
    storage_class_(storage_class),
    owner_id_(owner_id),
    owner_display_name_(owner_display_name) {
}

ObjectContent::~ObjectContent() {}

const std::string& ObjectContent::GetKey() const {
  return key_;
}

void ObjectContent::SetKey(const std::string& val) {
  key_ = val;
}

const std::string& ObjectContent::GetLastModified() const {
  return last_modified_;
}

void ObjectContent::SetLastModified(const std::string& val) {
  last_modified_ = val;
}

const std::string& ObjectContent::GetEtag() const {
  return etag_;
}

void ObjectContent::SetEtag(const std::string& val) {
  etag_ = val;
}

const std::string& ObjectContent::GetType() const {
  return type_;
}

void ObjectContent::SetType(const std::string& val) {
  type_ = val;
}

size_t ObjectContent::GetSize() const {
  return size_;
}

void ObjectContent::SetSize(const size_t& val) {
  size_ = val;
}

const std::string& ObjectContent::GetStorageClass() const {
  return storage_class_;
}

void ObjectContent::SetStorageClass(const std::string& val) {
  storage_class_ = val;
}

const std::string& ObjectContent::GetOwnerId() const {
  return owner_id_;
}

void ObjectContent::SetOwnerId(const std::string& val) {
  owner_id_ = val;
}

const std::string& ObjectContent::GetOwnerDisplayName() const {
  return owner_display_name_;
}

void ObjectContent::SetOwnerDisplayName(const std::string& val) {
  owner_display_name_ = val;
}

}  // namespace oss
