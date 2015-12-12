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

#ifndef OSS_SDK_CPP_MESSAGE_LIST_MULTIPART_UPLOADS_RESULT_H_
#define OSS_SDK_CPP_MESSAGE_LIST_MULTIPART_UPLOADS_RESULT_H_

#include <string>
#include <list>

#include "oss_sdk_cpp/message/bucket.h"
#include "oss_sdk_cpp/message/multipart_upload.h"

namespace oss {

typedef std::list<MultipartUpload> MultipartList;

class ListMultipartUploadsResult {
 public:
  ListMultipartUploadsResult();

  ~ListMultipartUploadsResult();

  const MultipartList& GetMultipartUpload() const;

  const std::string& GetBucketName() const;

  const std::string& GetKeyMarker() const;

  const std::string& GetUploadIdMarker() const;

  const std::string& GetNextKeyMarker() const;

  const std::string& GetNextUploadIdMarker() const;

  int GetMaxUploads() const;

  const std::string& GetPrefix() const;

  const std::string& GetDelimiter() const;

  bool GetIsTruncated() const;

  bool DeserializeFromXml(const std::string& content);

 private:
  std::list<MultipartUpload> uploads_;
  std::string bucket_name_;
  std::string key_marker_;
  std::string upload_id_marker_;
  std::string next_key_marker_;
  std::string next_upload_id_marker_;
  std::string delimiter_;
  int max_uploads_;
  std::string prefix_;
  bool        is_truncated_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_LIST_MULTIPART_UPLOADS_RESULT_H_
