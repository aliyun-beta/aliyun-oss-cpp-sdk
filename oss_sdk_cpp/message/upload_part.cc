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

#include "oss_sdk_cpp/message/upload_part.h"

namespace oss {

int UploadPart::GetPartNumber() const {
  return part_number_;
}

void UploadPart::SetPartNumber(const int part_number) {
  part_number_ = part_number;
}

const std::string& UploadPart::GetEtag() const {
  return etag_;
}

void UploadPart::SetEtag(const std::string& etag) {
  etag_ = etag;
}

const std::string& UploadPart::GetLastModified() const {
  return last_modified_;
}

void UploadPart::SetLastModified(const std::string& last_modified) {
  last_modified_ = last_modified;
}

int64_t UploadPart::GetSize() const {
  return size_;
}

void UploadPart::SetSize(const int64_t size) {
  size_ = size;
}

}  // namespace oss
