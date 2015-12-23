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

#ifndef OSS_SDK_CPP_OSS_OSS_CLIENT_H_
#define OSS_SDK_CPP_OSS_OSS_CLIENT_H_

#include <string>
#include <vector>
#include <memory>
#include <fstream>

#include "oss_sdk_cpp/oss/oss_status.h"
#include "oss_sdk_cpp/oss/oss.h"
#include "oss_sdk_cpp/oss/oss_client_configuration.h"

#include "oss_sdk_cpp/message/copy_object_request.h"
#include "oss_sdk_cpp/message/copy_object_result.h"
#include "oss_sdk_cpp/message/get_object_request.h"
#include "oss_sdk_cpp/message/list_buckets_request.h"
#include "oss_sdk_cpp/message/list_buckets_result.h"
#include "oss_sdk_cpp/message/list_objects_request.h"
#include "oss_sdk_cpp/message/list_objects_result.h"
#include "oss_sdk_cpp/message/get_bucket_acl_result.h"
#include "oss_sdk_cpp/message/get_bucket_location_result.h"
#include "oss_sdk_cpp/message/get_bucket_logging_result.h"
#include "oss_sdk_cpp/message/set_bucket_logging_request.h"
#include "oss_sdk_cpp/message/get_bucket_website_result.h"
#include "oss_sdk_cpp/message/set_bucket_website_request.h"
#include "oss_sdk_cpp/message/get_bucket_referer_result.h"
#include "oss_sdk_cpp/message/set_bucket_referer_request.h"
#include "oss_sdk_cpp/message/get_bucket_lifecycle_result.h"
#include "oss_sdk_cpp/message/set_bucket_lifecycle_request.h"
#include "oss_sdk_cpp/message/get_bucket_cors_result.h"
#include "oss_sdk_cpp/message/set_bucket_cors_request.h"
#include "oss_sdk_cpp/message/delete_multiple_objects_result.h"
#include "oss_sdk_cpp/message/delete_multiple_objects_request.h"
#include "oss_sdk_cpp/message/option_object_request.h"
#include "oss_sdk_cpp/message/option_object_result.h"
#include "oss_sdk_cpp/message/initiate_multipart_upload_request.h"
#include "oss_sdk_cpp/message/initiate_multipart_upload_result.h"
#include "oss_sdk_cpp/message/upload_part_request.h"
#include "oss_sdk_cpp/message/upload_part_result.h"
#include "oss_sdk_cpp/message/complete_multipart_upload_request.h"
#include "oss_sdk_cpp/message/complete_multipart_upload_result.h"
#include "oss_sdk_cpp/message/list_multipart_uploads_request.h"
#include "oss_sdk_cpp/message/list_multipart_uploads_result.h"
#include "oss_sdk_cpp/message/list_parts_request.h"
#include "oss_sdk_cpp/message/list_parts_result.h"
#include "oss_sdk_cpp/message/upload_part_copy_request.h"
#include "oss_sdk_cpp/message/upload_part_copy_result.h"
#include "oss_sdk_cpp/message/append_object_request.h"
#include "oss_sdk_cpp/message/append_object_result.h"

// to avoid conflicts with Windows MACRO GetObject.
#undef GetObject

namespace oss {

class HttpEngineInput;
class HttpEngineOutput;
class HttpEngine;

class OssClient {
 public:
  OssClient(const std::string& access_key_id,
            const std::string& access_key_secret);

  OssClient(const std::string& endpoint,
            const std::string& access_key_id,
            const std::string& access_key_secret,
            const ClientConfiguration& config = ClientConfiguration());

  ~OssClient();

  // Bucket
  Status ListBuckets(const ListBucketsRequest& request,
                     ListBucketsResult* result);

  Status ListBuckets(std::vector<Bucket>* buckets);

  // permission can be public-read-write, public-read or private.
  Status CreateBucket(const std::string& bucket_name,
                      const std::string& acl = kAclPrivate);

  Status DeleteBucket(const std::string& bucket_name);

  Status BucketExists(const std::string& bucket_name, bool* exist);

  Status SetBucketAcl(const std::string& bucket_name,
                      const std::string& acl = kAclPrivate);

  Status GetBucketAcl(const std::string& bucket_name,
                      GetBucketAclResult* result);

  Status GetBucketAcl(const std::string& bucket_name,
                      std::string* acl);

  Status GetBucketLocation(const std::string& bucket_name,
                           std::string* location);

  // bucket logging
  Status GetBucketLogging(const std::string& bucket_name,
                          GetBucketLoggingResult* result);

  Status SetBucketLogging(const SetBucketLoggingRequest& request);

  Status DeleteBucketLogging(const std::string& bucket_name);

  // bucket website.
  Status GetBucketWebsite(const std::string& bucket_name,
                          GetBucketWebsiteResult* result);

  Status SetBucketWebsite(const SetBucketWebsiteRequest& request);

  Status SetBucketWebsite(const std::string& bucket_name,
                          const std::string& index_page,
                          const std::string& error_page);

  Status DeleteBucketWebsite(const std::string& bucket_name);

  // bucket referer
  Status GetBucketReferer(const std::string& bucket_name,
                          GetBucketRefererResult* result);

  Status SetBucketReferer(const SetBucketRefererRequest& request);

  // bucket life cycle.
  Status GetBucketLifecycle(const std::string& bucket_name,
                            GetBucketLifecycleResult* result);

  Status SetBucketLifecycle(const SetBucketLifecycleRequest &request);

  Status DeleteBucketLifecycle(const std::string& bucket_name);

  // bucket cors.
  Status GetBucketCors(const std::string& bucket_name,
                       GetBucketCorsResult* result);

  Status SetBucketCors(const SetBucketCorsRequest& request);

  Status DeleteBucketCors(const std::string& bucket_name);

  // delete bucket configs.
  Status DeleteBucketConfig(const std::string& bucket_name,
                            const std::string& config_name);

  // list all objects in a bucket.
  Status ListObjects(const ListObjectsRequest& request,
                     ListObjectsResult* result);

  Status CreateFolder(const std::string& bucket_name,
                      const std::string& folder_name);

  Status ObjectExists(const std::string& bucket_name,
                      const std::string& key,
                      bool* exist);

  // Object
  Status PutString(const std::string & bucket_name,
                   const std::string & key,
                   const std::string & str,
                   const ObjectMetadata* object_metadata = NULL);

  Status PutObject(const std::string & bucket_name,
                   const std::string & key,
                   const std::string & file_path,
                   const ObjectMetadata* object_metadata = NULL);

  Status PutObject(const std::string& bucket_name,
                   const std::string& key,
                   const std::string& file_path,
                   int64_t stream_bytes,
                   const ObjectMetadata* object_metadata = NULL);


  Status PutObject(const std::string& bucket_name,
                   const std::string& key,
                   std::ifstream* stream,
                   const ObjectMetadata* object_metadata = NULL);

  Status PutObject(const std::string& bucket_name,
                   const std::string& key,
                   std::ifstream* stream,
                   int64_t stream_bytes,
                   const ObjectMetadata* object_metadata = NULL);

  Status DeleteObject(const std::string& bucket_name,
                      const std::string& key);

  Status DeleteMultipleObjects(const DeleteMultipleObjectsRequest& request,
                               DeleteMultipleObjectsResult* result);

  Status OptionObject(const OptionObjectRequest& request,
                      OptionObjectResult* result);

  Status CopyObject(const CopyObjectRequest & request,
                    CopyObjectResult* result);

  Status GetObject(const GetObjectRequest & request);

  Status GetObjectMetadata(const std::string & bucket_name,
                           const std::string & key,
                           std::unique_ptr<ObjectMetadata>* object_meta_data);

  Status AppendObject(const AppendObjectRequest& request);

  Status AppendObject(const AppendObjectRequest& request,
                      const ObjectMetadata* object_metadata);

  Status AppendObject(const AppendObjectRequest& request,
                      const ObjectMetadata* object_metadata,
                      AppendObjectResult* result);

  Status InitiateMultipartUpload(const InitiateMultipartUploadRequest& request,
                                 InitiateMultipartUploadResult* result);

  Status UploadPart(const UploadPartRequest& request, UploadPartResult* result);

  Status UploadPartCopy(const UploadPartCopyRequest& request,
                        UploadPartCopyResult* result);

  Status CompleteMultipartUpload(const CompleteMultipartUploadrequest& request,
                                 CompleteMultipartUploadResult* result);

  Status AbortMultipartUpload(const std::string& bucket_name,
                              const std::string& key,
                              const std::string& upload_id);

  Status ListMultipartUploads(const ListMultipartUploadsRequest& request,
                              ListMultipartUploadsResult* result);

  Status ListParts(const ListPartsRequest& request, ListPartsResult* result);

 public:
  void SetEndpoint(const std::string& endpoint);

  // intrusive interface for unit test, just for unit test.
  void SetUnitTestMode();

 private:
  void ParseEndpoint(const std::string& endpoint);

  std::string CalculateAuthorization(const std::string& resource,
                                     const HttpEngineInput& input);

  HttpEngineOutput ExecuteHttp(HttpEngineInput* input,
                               const std::string& resource);

 private:
  std::string access_key_id_;
  std::string access_key_secret_;
  std::string endpoint_;
  std::string protocol_;
  std::string security_token_;
  ClientConfiguration client_config_;
  std::unique_ptr<HttpEngine> engine_;

  // unit test only.
  bool unit_test_mode_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_OSS_OSS_CLIENT_H_
