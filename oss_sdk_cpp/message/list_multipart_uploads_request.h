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

#ifndef OSS_SDK_CPP_MESSAGE_LIST_MULTIPART_UPLOADS_REQUEST_H_
#define OSS_SDK_CPP_MESSAGE_LIST_MULTIPART_UPLOADS_REQUEST_H_

#include <string>

#include "oss_sdk_cpp/base/base.h"

namespace oss {

class ListMultipartUploadsRequest {
 public:
  ListMultipartUploadsRequest();

  ListMultipartUploadsRequest(
    const std::string& bucket_name,
    const std::string& delimiter,
    int max_uploads,
    const std::string& key_marker,
    const std::string& prefix,
    const std::string& upload_id_marker);

  ~ListMultipartUploadsRequest();

  void AddToParameterList(StringMap* parammeters) const;

  std::string BuildQueryString() const;

  void SetDelimiter(const std::string& delimiter);
  void SetMaxUploads(int max_uploads);
  void SetKeyMarker(const std::string& key_marker);
  void SetPrefix(const std::string& prefix);
  void SetUploadIdMarker(const std::string& upload_id_marker);
  void SetBucketName(const std::string& bucket_name);

  const std::string& GetBucketName() const;

 private:
  std::string bucket_name_;
  std::unique_ptr<std::string> delimiter_;
  std::unique_ptr<std::string> max_uploads_;
  std::unique_ptr<std::string> key_marker_;
  std::unique_ptr<std::string> prefix_;
  std::unique_ptr<std::string> upload_id_marker_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_LIST_MULTIPART_UPLOADS_REQUEST_H_
