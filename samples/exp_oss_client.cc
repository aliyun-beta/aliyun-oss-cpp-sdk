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

#include <string>
#include <vector>

#include "samples/exp_oss_client.h"

namespace oss {

ExpOssClient::ExpOssClient(const std::string& access_key_id,
                           const std::string& access_key_secret)
  : client_(access_key_id, access_key_secret) {
}

ExpOssClient::ExpOssClient(const std::string& endpoint,
                           const std::string& access_key_id,
                           const std::string& access_key_secret,
                           const ClientConfiguration& client_config)
  : client_(endpoint, access_key_id, access_key_secret, client_config) {
}

ListBucketsResult ExpOssClient::ListBuckets(const ListBucketsRequest& request) {
  ListBucketsResult result;
  Status status = client_.ListBuckets(request, &result);
  if (!status.Ok()) {
    throw std::string("ListBuckets failed with ") + status.ErrorCode();
  }
  return result;
}

std::vector<Bucket> ExpOssClient::ListBuckets() {
  std::vector<Bucket> buckets;
  Status status = client_.ListBuckets(&buckets);
  if (!status.Ok()) {
    throw std::string("ListBuckets failed with ") + status.ErrorCode();
  }
  return buckets;
}

void ExpOssClient::CreateBucket(const std::string& bucket_name,
                                const std::string& permission) {
  Status status = client_.CreateBucket(bucket_name, permission);
  if (!status.Ok()) {
    throw std::string("CreateBucket failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::DeleteBucket(const std::string& bucket_name) {
  Status status = client_.DeleteBucket(bucket_name);
  if (!status.Ok()) {
    throw std::string("DeleteBucket failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::SetBucketAcl(const std::string& bucket_name,
                                const std::string& permission) {
  Status status = client_.SetBucketAcl(bucket_name, permission);
  if (!status.Ok()) {
    throw std::string("SetBucketAcl failed with ") + status.ErrorCode();
  }
}

GetBucketAclResult ExpOssClient::GetBucketAcl(const std::string& bucket_name) {
  GetBucketAclResult result;
  Status status = client_.GetBucketAcl(bucket_name, &result);
  if (!status.Ok()) {
    throw std::string("GetBucketAcl failed with ") + status.ErrorCode();
  }

  return result;
}

void ExpOssClient::EnsureBucketExit(const std::string& bucket_name,
                                    const std::string& acl) {
  if (!BucketExists(bucket_name)) {
    CreateBucket(bucket_name, acl);
  }
}

bool ExpOssClient::BucketExists(const std::string& bucket_name) {
  bool exist;
  Status status = client_.BucketExists(bucket_name, &exist);
  if (!status.Ok()) {
    throw std::string("BucketExists failed with ") + status.ErrorCode();
  }

  return exist;
}

std::string ExpOssClient::GetBucketLocation(const std::string& bucket_name) {
  std::string location;
  Status status = client_.GetBucketLocation(bucket_name, &location);
  if (!status.Ok()) {
    throw std::string("GetBucketLocation failed with ") + status.ErrorCode();
  }

  return location;
}

GetBucketLoggingResult ExpOssClient::GetBucketLogging(
  const std::string& bucket_name) {
  GetBucketLoggingResult result;
  Status status = client_.GetBucketLogging(bucket_name, &result);
  if (!status.Ok()) {
    throw std::string("GetBucketLogging failed with ") + status.ErrorCode();
  }

  return result;
}

void ExpOssClient::SetBucketLogging(const SetBucketLoggingRequest& request) {
  Status status = client_.SetBucketLogging(request);
  if (!status.Ok()) {
    throw std::string("SetBucketLogging failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::DeleteBucketLogging(const std::string& bucket_name) {
  Status status = client_.DeleteBucketLogging(bucket_name);
  if (!status.Ok()) {
    throw std::string("DeleteBucketLogging failed with ") + status.ErrorCode();
  }
}

GetBucketWebsiteResult ExpOssClient::GetBucketWebsite(
  const std::string& bucket_name) {
  GetBucketWebsiteResult result;
  Status status = client_.GetBucketWebsite(bucket_name, &result);
  if (!status.Ok()) {
    throw std::string("GetBucketWebsite failed with ") + status.ErrorCode();
  }

  return result;
}

void ExpOssClient::SetBucketWebsite(const SetBucketWebsiteRequest& request) {
  Status status = client_.SetBucketWebsite(request);
  if (!status.Ok()) {
    throw std::string("SetBucketWebsite failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::SetBucketWebsite(const std::string& bucket_name,
                                    const std::string& index_page,
                                    const std::string& error_page) {
  Status status = client_.SetBucketWebsite(bucket_name, index_page, error_page);
  if (!status.Ok()) {
    throw std::string("SetBucketWebsite failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::DeleteBucketWebsite(const std::string& bucket_name) {
  Status status = client_.DeleteBucketWebsite(bucket_name);
  if (!status.Ok()) {
    throw std::string("DeleteBucketWebsite failed with ") + status.ErrorCode();
  }
}

GetBucketRefererResult ExpOssClient::GetBucketReferer(
  const std::string& bucket_name) {
  GetBucketRefererResult result;
  Status status = client_.GetBucketReferer(bucket_name, &result);
  if (!status.Ok()) {
    throw std::string("GetBucketReferer failed with ") + status.ErrorCode();
  }

  return result;
}

void ExpOssClient::SetBucketReferer(const SetBucketRefererRequest& request) {
  Status status = client_.SetBucketReferer(request);
  if (!status.Ok()) {
    throw std::string("SetBucketReferer failed with ") + status.ErrorCode();
  }
}

GetBucketLifecycleResult ExpOssClient::GetBucketLifecycle(
  const std::string& bucket_name) {
  GetBucketLifecycleResult result;
  Status status = client_.GetBucketLifecycle(bucket_name, &result);
  if (!status.Ok()) {
    throw std::string("GetBucketLifecycle failed with ") + status.ErrorCode();
  }

  return result;
}

void ExpOssClient::SetBucketLifecycle(
  const SetBucketLifecycleRequest &request) {
  Status status = client_.SetBucketLifecycle(request);
  if (!status.Ok()) {
    throw std::string("SetBucketLifecycle failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::DeleteBucketLifecycle(const std::string& bucket_name) {
  Status status = client_.DeleteBucketLifecycle(bucket_name);
  if (!status.Ok()) {
    throw std::string("DeleteBucketLifecycle failed with ") +
    status.ErrorCode();
  }
}

GetBucketCorsResult ExpOssClient::GetBucketCors(const std::string&
    bucket_name) {
  GetBucketCorsResult result;
  Status status = client_.GetBucketCors(bucket_name, &result);
  if (!status.Ok()) {
    throw std::string("GetBucketCors failed with ") + status.ErrorCode();
  }

  return result;
}

void ExpOssClient::SetBucketCors(const SetBucketCorsRequest& request) {
  Status status = client_.SetBucketCors(request);
  if (!status.Ok()) {
    throw std::string("SetBucketCors failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::DeleteBucketCors(const std::string& bucket_name) {
  Status status = client_.DeleteBucketCors(bucket_name);
  if (!status.Ok()) {
    throw std::string("DeleteBucketCors failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::DeleteBucketConfig(const std::string& bucket_name,
                                      const std::string& config_name) {
  Status status = client_.DeleteBucketConfig(bucket_name, config_name);
  if (!status.Ok()) {
    throw std::string("DeleteBucketConfig failed with ") + status.ErrorCode();
  }
}

ListObjectsResult ExpOssClient::ListObjects(const ListObjectsRequest& request) {
  ListObjectsResult result;
  Status status = client_.ListObjects(request, &result);
  if (!status.Ok()) {
    throw std::string("ListObjects failed with ") + status.ErrorCode();
  }

  return result;
}

void ExpOssClient::CreateFolder(const std::string& bucket_name,
                                const std::string& folder_name) {
  Status status = client_.CreateFolder(bucket_name, folder_name);
  if (!status.Ok()) {
    throw std::string("CreateFolder failed with ") + status.ErrorCode();
  }
}


bool ExpOssClient::ObjectExists(const std::string& bucket_name,
                                const std::string& key) {
  bool exist;
  auto status = client_.ObjectExists(bucket_name, key, &exist);
  if (!status.Ok()) {
    throw std::string("ObjectExists failed with ") + status.ErrorCode();
  }

  return exist;
}


void ExpOssClient::PutString(const std::string & bucket_name,
                             const std::string & key,
                             const std::string & str,
                             const ObjectMetadata* object_metadata) {
  Status status = client_.PutString(bucket_name, key, str, object_metadata);
  if (!status.Ok()) {
    throw std::string("PutString failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::PutObject(const std::string & bucket_name,
                             const std::string & key,
                             const std::string & file_path,
                             const ObjectMetadata* metadata ) {
  Status status = client_.PutObject(bucket_name, key, file_path, metadata);
  if (!status.Ok()) {
    throw std::string("PutObject failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::PutObject(const std::string& bucket_name,
                             const std::string& key,
                             const std::string& file_path,
                             int64_t stream_bytes,
                             const ObjectMetadata* metadata) {
  Status status = client_.PutObject(bucket_name,
                                    key,
                                    file_path,
                                    stream_bytes,
                                    metadata);
  if (!status.Ok()) {
    throw std::string("PutObject failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::PutObject(const std::string & bucket_name,
                             const std::string & key,
                             std::ifstream* stream,
                             const ObjectMetadata* metadata) {
  Status status = client_.PutObject(bucket_name, key, stream, metadata);
  if (!status.Ok()) {
    throw std::string("PutObject failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::PutObject(const std::string & bucket_name,
                             const std::string & key,
                             std::ifstream* stream,
                             int64_t stream_bytes,
                             const ObjectMetadata* metadata) {
  Status status = client_.PutObject(bucket_name,
                                    key,
                                    stream,
                                    stream_bytes,
                                    metadata);
  if (!status.Ok()) {
    throw std::string("PutObject failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::DeleteObject(const std::string & bucket_name,
                                const std::string & key) {
  Status status = client_.DeleteObject(bucket_name, key);
  if (!status.Ok()) {
    throw std::string("DeleteObject failed with ") + status.ErrorCode();
  }
}

DeleteMultipleObjectsResult ExpOssClient::DeleteMultipleObjects(
  const DeleteMultipleObjectsRequest& request) {
  DeleteMultipleObjectsResult result;
  Status status = client_.DeleteMultipleObjects(request, &result);
  if (!status.Ok()) {
    throw std::string("DeleteMultipleObjects failed with ") +
    status.ErrorCode();
  }

  return result;
}

OptionObjectResult ExpOssClient::OptionObject(const OptionObjectRequest& req) {
  OptionObjectResult result;
  Status status = client_.OptionObject(req, &result);
  if (!status.Ok()) {
    throw std::string("OptionObject failed with ") + status.ErrorCode();
  }

  return result;
}

CopyObjectResult ExpOssClient::CopyObject(const CopyObjectRequest & request) {
  CopyObjectResult result;
  Status status = client_.CopyObject(request, &result);
  if (!status.Ok()) {
    throw std::string("CopyObject failed with ") + status.ErrorCode();
  }

  return result;
}

void ExpOssClient::GetObject(const GetObjectRequest & request) {
  Status status = client_.GetObject(request);
  if (!status.Ok()) {
    throw std::string("GetObject failed with ") + status.ErrorCode();
  }
}


InitiateMultipartUploadResult ExpOssClient::InitiateMultipartUpload(
  const InitiateMultipartUploadRequest& request) {
  InitiateMultipartUploadResult result;
  Status status = client_.InitiateMultipartUpload(request, &result);
  if (!status.Ok()) {
    throw std::string("InitiateMultipartUpload failed with ") +
    status.ErrorCode();
  }

  return result;
}

UploadPartResult ExpOssClient::UploadPart(const UploadPartRequest& request) {
  UploadPartResult result;
  Status status = client_.UploadPart(request, &result);
  if (!status.Ok()) {
    throw std::string("UploadPart failed with ") + status.ErrorCode();
  }

  return result;
}

UploadPartCopyResult ExpOssClient::UploadPartCopy(
  const UploadPartCopyRequest& request) {
  UploadPartCopyResult result;
  Status status = client_.UploadPartCopy(request, &result);
  if (!status.Ok()) {
    throw std::string("UploadPartCopy failed with ") + status.ErrorCode();
  }

  return result;
}

CompleteMultipartUploadResult ExpOssClient::CompleteMultipartUpload(
  const CompleteMultipartUploadrequest& request) {
  CompleteMultipartUploadResult result;
  Status status = client_.CompleteMultipartUpload(request, &result);
  if (!status.Ok()) {
    throw "CompleteMultipartUpload failed with " +status.ErrorCode();
  }

  return result;
}

void ExpOssClient::AbortMultipartUpload(const std::string& bucket_name,
                                        const std::string& key,
                                        const std::string& upload_id) {
  Status status = client_.AbortMultipartUpload(bucket_name, key, upload_id);
  if (!status.Ok()) {
    throw std::string("AbortMultipartUpload failed with ") +
    status.ErrorCode();
  }
}

ListMultipartUploadsResult ExpOssClient::ListMultipartUploads(
  const ListMultipartUploadsRequest& request) {
  ListMultipartUploadsResult result;
  Status status = client_.ListMultipartUploads(request, &result);
  if (!status.Ok()) {
    throw std::string("ListMultipartUploads failed with ") + status.ErrorCode();
  }

  return result;
}

ListPartsResult ExpOssClient::ListParts(const ListPartsRequest& request) {
  ListPartsResult result;
  Status status = client_.ListParts(request, &result);
  if (!status.Ok()) {
    throw std::string("ListParts failed with ") + status.ErrorCode();
  }

  return result;
}

void ExpOssClient::GetObjectMetadata(const std::string & bucket_name,
                                     const std::string & key,
                                     std::unique_ptr<ObjectMetadata>* meta) {
  Status status = client_.GetObjectMetadata(bucket_name, key, meta);
  if (!status.Ok()) {
    throw std::string("GetObjectMetadata failed with ") + status.ErrorCode();
  }
}
//
void ExpOssClient::AppendObject(const AppendObjectRequest& request) {
  Status status = client_.AppendObject(request);
  if (!status.Ok()) {
    throw std::string("AppendObject failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::AppendObject(const AppendObjectRequest& request,
                                const ObjectMetadata* object_meta_data) {
  Status status = client_.AppendObject(request, object_meta_data);
  if (!status.Ok()) {
    throw std::string("AppendObject failed with ") + status.ErrorCode();
  }
}

void ExpOssClient::AppendObject(const AppendObjectRequest& request,
                                const ObjectMetadata* object_meta_data,
                                AppendObjectResult* result) {
  Status status = client_.AppendObject(request, object_meta_data, result);
  if (!status.Ok()) {
    throw std::string("AppendObject failed with ") + status.ErrorCode();
  }
}

}  // namespace oss
