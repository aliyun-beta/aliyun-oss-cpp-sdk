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

#ifndef OSS_SDK_CPP_MESSAGE_APPEND_OBJECT_REQUEST_H_
#define OSS_SDK_CPP_MESSAGE_APPEND_OBJECT_REQUEST_H_

#include <stdint.h>
#include <string>

namespace oss {

class AppendObjectRequest {
 public:
  AppendObjectRequest();

  AppendObjectRequest(const std::string& bucket_name,
                      const std::string& object_name,
                      const std::string& file_path,
                      int64_t stream_position);

  ~AppendObjectRequest();

  const std::string& GetBucketName() const;

  void SetBucketName(const std::string& name);

  const std::string& GetKey() const;

  void SetKey(const std::string& key);

  const std::string& GetFilePath() const;

  void SetFilePath(const std::string& file_path);

  uint64_t GetPosition() const;

  void SetPosition(const uint64_t position);

  std::string BuildQueryString() const;

 private:
  std::string bucket_name_;
  std::string key_;
  std::string file_path_;
  int64_t position_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_APPEND_OBJECT_REQUEST_H_
