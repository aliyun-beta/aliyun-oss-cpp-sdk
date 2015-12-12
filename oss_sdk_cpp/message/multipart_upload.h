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

#ifndef OSS_SDK_CPP_MESSAGE_MULTIPART_UPLOAD_H_
#define OSS_SDK_CPP_MESSAGE_MULTIPART_UPLOAD_H_

#include <list>
#include <string>

namespace oss {

class MultipartUpload {
 public:
  const std::string& GetKey() const;

  void SetKey(const std::string& val);

  const std::string& GetUploadId() const;

  void SetUploadId(const std::string& upload_id);

  const std::string& GetInitiated() const;

  void SetInitiated(const std::string& initiated);

 private:
  std::string key;
  std::string upload_id_;
  std::string initiated_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_MULTIPART_UPLOAD_H_
