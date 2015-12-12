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

#ifndef OSS_SDK_CPP_MESSAGE_UPLOAD_PART_REQUEST_H_
#define OSS_SDK_CPP_MESSAGE_UPLOAD_PART_REQUEST_H_

#include <time.h>
#include <string>
#include <list>

#include "oss_sdk_cpp/base/base.h"

namespace oss {

class UploadPartRequest {
 public:
  UploadPartRequest();

  UploadPartRequest(const std::string& bucket_name,
                    const std::string& key,
                    std::string upload_id,
                    std::ifstream* input_stream,
                    int part_number,
                    int64_t part_size,
                    const std::string& md5_digest = "");

  const std::string& GetBucketName() const;

  void SetBucketName(const std::string& name);

  const std::string& GetKey() const;

  void SetKey(const std::string& key);

  const std::string& GetUploadId() const;

  void SetUploadId(const std::string& upload_id);

  std::ifstream* GetInputStream() const;

  void SetInputStream(std::ifstream* input_stream);

  int GetPartNumber() const;

  void SetPartNumber(int part_number);

  int64_t GetPartSize() const;

  void SetPartPartSize(int64_t part_size);

  const std::string& GetMd5Digest() const;

  void SetMd5Digest(const std::string& digest);

  std::string BuildQueryString() const;

 private:
  std::string bucket_name_;
  std::string key_;
  std::string upload_id_;

  std::ifstream* input_stream_;
  int part_number_;
  int64_t part_size_;
  std::string md5_digest_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_UPLOAD_PART_REQUEST_H_
