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

#ifndef OSS_SDK_CPP_MESSAGE_UPLOAD_PART_H_
#define OSS_SDK_CPP_MESSAGE_UPLOAD_PART_H_

#include <stdint.h>
#include <string>

namespace oss {

class UploadPart {
 public:
  int GetPartNumber() const;

  void SetPartNumber(const int part_number);

  const std::string& GetEtag() const;

  void SetEtag(const std::string& etag);

  const std::string& GetLastModified() const;

  void SetLastModified(const std::string& last_modified);

  int64_t GetSize() const;

  void SetSize(const int64_t size);

 private:
  int part_number_;
  std::string last_modified_;
  std::string etag_;
  int64_t size_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_UPLOAD_PART_H_
