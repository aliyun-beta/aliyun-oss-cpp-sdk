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

#ifndef SAMPLES_NORMAL_SAMPLES_H_
#define SAMPLES_NORMAL_SAMPLES_H_

#include <string>

#include "oss_sdk_cpp/oss/oss_client.h"

namespace oss {

class NormalSamples {
 public:
  NormalSamples();
  ~NormalSamples();

  // Bucket
  void ListBuckets();

  void ListBuckets2();

  void CreateBucket();

  void SetBucketAcl();

  void GetBucketAcl();

  void GetBucketAcl2();

  void BucketExists();

  void GetBucketLocation();

  void GetBucketLogging();

  void SetBucketLogging();

  void DeleteBucketLogging();

  void GetBucketWebsite();

  void SetBucketWebsite();

  void SetBucketWebsite2();

  void DeleteBucketWebsite();

  void GetBucketReferer();

  void SetBucketReferer();

  void GetBucketLifecycle();

  void SetBucketLifecycle();

  void DeleteBucketLifecycle();

  void GetBucketCors();

  void SetBucketCors();

  void DeleteBucketCors();

  void ListObjects();

  void CreateFolder();

  void ObjectExists();

  void PutString();

  void PutObject1();

  void PutObject2();

  void DeleteObject();

  void DeleteMultipleObjects();

  void OptionObject();

  void CopyObject();

  void GetObject();

  void GetObjectMetadata();

  void AppendObject();

  void UploadPart();

  void UploadPartCopy();

  void ListMultipartUploads();

  void ListParts();

  void ClearBucket(const std::string& bucket_name);

 private:
  void Trace(const Status& status, const std::string& funciton_name);
  void Init();
  void Deinit();

 private:
  OssClient client_;

  std::string source_bucket_name_;
  std::string target_bucket_name_;
  std::string bucket_name_;
  std::string niu_file_path_;
  std::string always_exists_key_;
  std::string test_file_dir_;
};

void RunNormalSamples();

}  // namespace oss
#endif  // SAMPLES_NORMAL_SAMPLES_H_
