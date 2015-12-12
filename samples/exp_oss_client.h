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

#ifndef SAMPLES_EXP_OSS_CLIENT_H_
#define SAMPLES_EXP_OSS_CLIENT_H_

#include <string>
#include <vector>

#include "oss_sdk_cpp/oss/oss_client.h"

namespace oss {

// ExpOssClient is just for test purpose,
// cause Google C++ Style Guide disallow exceptions.
class ExpOssClient {
 public:
  ExpOssClient(const std::string& access_key_id,
               const std::string& access_key_secret);

  ExpOssClient(const std::string& endpoint,
               const std::string& access_key_id,
               const std::string& access_key_secret,
               const ClientConfiguration& config = ClientConfiguration());

  ExpOssClient(const std::string& endpoint,
               const std::string& access_key_id,
               const std::string& access_key_secret,
               const std::string& security_token);

  ~ExpOssClient() = default;

  // Bucket
  ListBucketsResult ListBuckets(const ListBucketsRequest& request);

  std::vector<Bucket> ListBuckets();

  void CreateBucket(const std::string& bucket_name,
                    const std::string& acl = kAclPrivate);

  void DeleteBucket(const std::string& bucket_name);

  void EnsureBucketExit(const std::string& bucket_name,
                        const std::string& acl = kAclPrivate);


  void SetBucketAcl(const std::string& bucket_name,
                    const std::string& permission = kAclPrivate);

  bool BucketExists(const std::string& bucket_name);

  GetBucketAclResult GetBucketAcl(const std::string& bucket_name);


  std::string GetBucketLocation(const std::string& bucket_name);

  // bucket logging
  GetBucketLoggingResult GetBucketLogging(const std::string& bucket_name);

  void SetBucketLogging(const SetBucketLoggingRequest& request);

  void DeleteBucketLogging(const std::string& bucket_name);

  // bucket website.
  GetBucketWebsiteResult GetBucketWebsite(const std::string& bucket_name);

  void SetBucketWebsite(const SetBucketWebsiteRequest& request);

  void SetBucketWebsite(const std::string& bucket_name,
                        const std::string& index_page,
                        const std::string& error_page);

  void DeleteBucketWebsite(const std::string& bucket_name);

  // bucket referer
  GetBucketRefererResult GetBucketReferer(const std::string& bucket_name);

  void SetBucketReferer(const SetBucketRefererRequest& request);

  // bucket life cycle.
  GetBucketLifecycleResult GetBucketLifecycle(const std::string& bucket_name);

  void SetBucketLifecycle(const SetBucketLifecycleRequest &request);

  void DeleteBucketLifecycle(const std::string& bucket_name);

  // bucket cors.
  GetBucketCorsResult GetBucketCors(const std::string& bucket_name);

  void SetBucketCors(const SetBucketCorsRequest& request);

  void DeleteBucketCors(const std::string& bucket_name);

  // delete bucket configs.
  void DeleteBucketConfig(const std::string& bucket_name,
                          const std::string& config_name);

  ListObjectsResult ListObjects(const ListObjectsRequest& request);

  void CreateFolder(const std::string& bucket_name,
                    const std::string& folder_name);

  bool ObjectExists(const std::string& bucket_name,
                    const std::string& key);

  // Object
  void PutString(const std::string& bucket_name,
                 const std::string& key,
                 const std::string& str,
                 const ObjectMetadata* object_metadata = NULL);

  void PutObject(const std::string& bucket_name,
                 const std::string& key,
                 const std::string& file_path,
                 const ObjectMetadata* object_metadata = NULL);

  void PutObject(const std::string& bucket_name,
                 const std::string& key,
                 const std::string& file_path,
                 int64_t stream_bytes,
                 const ObjectMetadata* object_metadata = NULL);


  void PutObject(const std::string& bucket_name,
                 const std::string& key,
                 std::ifstream* stream,
                 const ObjectMetadata* object_metadata = NULL);

  void PutObject(const std::string& bucket_name,
                 const std::string& key,
                 std::ifstream* stream,
                 int64_t stream_bytes,
                 const ObjectMetadata* object_metadata = NULL);

  void DeleteObject(const std::string& bucket_name,
                    const std::string& key);

  DeleteMultipleObjectsResult DeleteMultipleObjects(
    const DeleteMultipleObjectsRequest& request);

  OptionObjectResult OptionObject(const OptionObjectRequest& request);

  CopyObjectResult CopyObject(const CopyObjectRequest & request);

  void GetObject(const GetObjectRequest& request);


  void GetObjectMetadata(const std::string& bucket_name,
                         const std::string& key,
                         std::unique_ptr<ObjectMetadata>* object_meta_data);

  void AppendObject(const AppendObjectRequest& request);

  void AppendObject(const AppendObjectRequest& request,
                    const ObjectMetadata* object_meta_data);

  void AppendObject(const AppendObjectRequest& request,
                    const ObjectMetadata* object_meta_data,
                    AppendObjectResult* result);

  InitiateMultipartUploadResult InitiateMultipartUpload(
    const InitiateMultipartUploadRequest& request);

  UploadPartResult UploadPart(const UploadPartRequest& request);

  UploadPartCopyResult UploadPartCopy(const UploadPartCopyRequest& request);

  CompleteMultipartUploadResult CompleteMultipartUpload(
    const CompleteMultipartUploadrequest& request);

  void AbortMultipartUpload(const std::string& bucket_name,
                            const std::string& key,
                            const std::string& upload_id);

  ListMultipartUploadsResult ListMultipartUploads(
    const ListMultipartUploadsRequest& request);

  ListPartsResult ListParts(const ListPartsRequest& request);

 private:
  OssClient client_;
};

}  // namespace oss

#endif  // SAMPLES_EXP_OSS_CLIENT_H_
