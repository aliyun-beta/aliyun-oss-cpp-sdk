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

#include <sstream>
#include <list>
#include <vector>

#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/utils/apr_utils.h"
#include "oss_sdk_cpp/utils/string_utils.h"

#include "samples/normal_samples.h"

namespace oss {

static const char* endpoint = "oss-cn-hangzhou.aliyuncs.com";
static const char* access_key_id = "0w8ppPOLTpnzeFle";
static const char* access_key_secret = "lcpdx8XlYn2IJHKMIlizJyJtdY7Tkf";

std::string RandomString() {
  std::ostringstream stream;
  stream << rand() << rand() << rand() << rand();  // NOLINT, test only.
  return stream.str();
}

NormalSamples::NormalSamples()
  : client_(endpoint, access_key_id, access_key_secret) {
  Init();
}

NormalSamples::~NormalSamples() {
  Deinit();
}

void NormalSamples::Init() {
  source_bucket_name_ = "source" + RandomString();
  target_bucket_name_ = "target" + RandomString();
  bucket_name_ = "mybucket" + RandomString();

  if (!client_.CreateBucket(source_bucket_name_).Ok()) {
    std::cout << "CreateBucket failed in constructor\n";
  }
  if (!client_.CreateBucket(target_bucket_name_).Ok()) {
    std::cout << "CreateBucket failed in constructor\n";
  }
  if (!client_.CreateBucket(bucket_name_).Ok()) {
    std::cout << "CreateBucket failed in constructor\n";
  }
  test_file_dir_ = GetExecutableDirectory() + kPathSlash +
                   std::string("test_files") + kPathSlash;

  niu_file_path_ = test_file_dir_ + "niu.c";

  always_exists_key_ = "alwaysexists.txt";
  Status status = client_.PutObject(bucket_name_,
                                    always_exists_key_,
                                    niu_file_path_);
  if (!status.Ok()) {
    std::cout << "CreateBucket failed in constructor\n";
  }
}

void NormalSamples::Deinit() {
  std::list<std::string> buckets = { source_bucket_name_,
                                     target_bucket_name_,
                                     bucket_name_
                                   };
  for (auto& bucket_name : buckets) {
    if (!client_.DeleteBucket(bucket_name).Ok()) {
      ClearBucket(bucket_name);
      if (!client_.DeleteBucket(bucket_name).Ok()) {
        std::cout << "DeleteBucket failed in destructor\n";
      }
    }
  }
}

void NormalSamples::Trace(const Status& status,
                          const std::string& funciton_name) {
  if (status.Ok()) {
    std::cout << funciton_name << " succeed" << std::endl;
  } else {
    std::cout << funciton_name << " failed with:"
              << status.ErrorCode() << std::endl;
  }
}

void NormalSamples::ListBuckets() {
  ListBucketsRequest request;
  request.SetMaxKeys(2);
  request.SetPrefix("m");

  ListBucketsResult result;
  Status status = client_.ListBuckets(request, &result);
  Trace(status, "ListBuckets");
  for (auto& bucket : result.GetBuckets()) {
    std::cout << bucket.GetName() << ", " << bucket.GetLocation()
              << ", " << bucket.GetCreationDate() << std::endl;
  }
  std::cout << std::endl;
}

void NormalSamples::ListBuckets2() {
  std::vector<Bucket> buckets;
  Status status = client_.ListBuckets(&buckets);
  Trace(status, "ListBuckets");
  for (auto& bucket : buckets) {
    std::cout << bucket.GetName() << ", " << bucket.GetLocation()
              << ", " << bucket.GetCreationDate() << std::endl;
  }
  std::cout << std::endl;
}

void NormalSamples::CreateBucket() {
  std::string bucket_name = "mybucket" + RandomString();
  Status status = client_.CreateBucket(bucket_name, "public-read");
  Trace(status, "CreateBucket");
  if (status.Ok()) {
    status = client_.DeleteBucket(bucket_name);
    Trace(status, "DeleteBucket");
  }
}

void NormalSamples::SetBucketAcl() {
  Status status = client_.SetBucketAcl(bucket_name_, "public-read");
  Trace(status, "SetBucketAcl");
}

void NormalSamples::GetBucketAcl() {
  std::string acl;
  Status status = client_.GetBucketAcl(bucket_name_, &acl);
  Trace(status, "GetBucketAcl");
}

void NormalSamples::GetBucketAcl2() {
  GetBucketAclResult result;
  Status status = client_.GetBucketAcl(bucket_name_, &result);
  Trace(status, "GetBucketAcl");
}

void NormalSamples::BucketExists() {
  bool exist = false;
  Status status = client_.BucketExists(bucket_name_, &exist);
  Trace(status, "BucketExists");
}

void NormalSamples::GetBucketLocation() {
  std::string location;
  Status status = client_.GetBucketLocation(bucket_name_, &location);
  Trace(status, "GetBucketLocation");
}
void NormalSamples::SetBucketLogging() {
  std::string target_prefix = "prefix123";
  SetBucketLoggingRequest request(target_bucket_name_,
                                  target_prefix,
                                  bucket_name_);
  Status status = client_.SetBucketLogging(request);
  Trace(status, "SetBucketLogging");
}

void NormalSamples::GetBucketLogging() {
  GetBucketLoggingResult result;
  Status status = client_.GetBucketLogging(bucket_name_, &result);
  Trace(status, "GetBucketLogging");
}

void NormalSamples::DeleteBucketLogging() {
  Status status = client_.DeleteBucketLogging(bucket_name_);
  Trace(status, "DeleteBucketLogging");
}

void NormalSamples::SetBucketWebsite() {
  Status status = client_.SetBucketWebsite(bucket_name_,
                  "myindex.html",
                  "myerror.html");
  Trace(status, "SetBucketWebsite");
}

void NormalSamples::SetBucketWebsite2() {
  SetBucketWebsiteRequest request(bucket_name_, "index.html", "404.html");
  Status status = client_.SetBucketWebsite(request);
  Trace(status, "SetBucketWebsite");
}

void NormalSamples::GetBucketWebsite() {
  GetBucketWebsiteResult result;
  Status status = client_.GetBucketWebsite(bucket_name_, &result);
  Trace(status, "GetBucketWebsite");
}

void NormalSamples::DeleteBucketWebsite() {
  Status status = client_.DeleteBucketWebsite(bucket_name_);
  Trace(status, "DeleteBucketWebsite");
}

void NormalSamples::SetBucketReferer() {
  SetBucketRefererRequest request("moon123456");
  request.AddReferer("http://www.yahoo.com");
  request.AddReferer("http://www.microsoft.com");
  request.AddReferer("http://www.msn.com");

  request.AddReferer("http://www.aliyun.com");
  request.AddReferer("http://www.*.com");
  request.AddReferer("http://www.?.aliyuncs.com");

  Status status = client_.SetBucketReferer(request);
  Trace(status, "SetBucketReferer");
}

void NormalSamples::GetBucketReferer() {
  GetBucketRefererResult result;
  Status status = client_.GetBucketReferer(bucket_name_, &result);
  Trace(status, "GetBucketReferer");
}

void NormalSamples::SetBucketLifecycle() {
  SetBucketLifecycleRequest request(bucket_name_);

  LifeCycleRule rule;
  rule.SetEnabled(true);
  rule.SetId("test1");
  rule.SetPrefix("filter1");
  rule.SetExpirationDays(25);
  request.AddRule(rule);

  LifeCycleRule rule2;
  rule2.SetEnabled(false);
  rule2.SetId("test2");
  rule2.SetPrefix("filter2");
  rule2.SetExpirationDate("2022-10-11T00:00:00.000Z");
  request.AddRule(rule2);

  Status status = client_.SetBucketLifecycle(request);
  Trace(status, "SetBucketLifecycle");
}

void NormalSamples::GetBucketLifecycle() {
  GetBucketLifecycleResult result;
  Status status = client_.GetBucketLifecycle(bucket_name_, &result);
  Trace(status, "GetBucketLifecycle");
}

void NormalSamples::DeleteBucketLifecycle() {
  Status status = client_.DeleteBucketConfig(bucket_name_, "lifecycle");
  Trace(status, "DeleteBucketConfig");
}

void NormalSamples::SetBucketCors() {
  SetBucketCorsRequest request(bucket_name_);

  {
    CorsRule rule;
    rule.AddAllowedOrigin("http://www.a.com");
    rule.AddAllowedMethod("POST");
    rule.AddAllowedHeader("*");
    rule.AddExposeHeader("x-oss-test");
    rule.SetMaxAgeSeconds(300);

    request.AddRule(rule);
  }

  {
    CorsRule rule;
    rule.AddAllowedOrigin("http://www.google.com");
    rule.AddAllowedOrigin("http://www.facebook.com");
    rule.AddAllowedOrigin("http://www.aliyun.com");

    rule.AddAllowedMethod("POST");
    rule.AddAllowedMethod("GET");
    rule.AddAllowedHeader("a");
    rule.AddAllowedHeader("b");
    rule.AddAllowedHeader("c");

    rule.AddExposeHeader("x-oss-test1");
    rule.AddExposeHeader("x-oss-test2");

    rule.SetMaxAgeSeconds(200);
    request.AddRule(rule);
  }

  Status status = client_.SetBucketCors(request);
  Trace(status, "SetBucketCors");
}

void NormalSamples::GetBucketCors() {
  GetBucketCorsResult result;
  Status status = client_.GetBucketCors(bucket_name_, &result);
  Trace(status, "GetBucketCors");
}

void NormalSamples::DeleteBucketCors() {
  Status status = client_.DeleteBucketCors(bucket_name_);
  Trace(status, "DeleteBucketCors");
}

void NormalSamples::ListObjects() {
  std::string key = "hello.txt";
  client_.PutString(bucket_name_, key, "just for test");
  ListObjectsRequest request;
  request.SetBucketName(bucket_name_);
  request.SetMaxKeys(100);
  request.SetPrefix("");

  ListObjectsResult result;
  Status status = client_.ListObjects(request, &result);
  Trace(status, "ListObjects");

  for (auto& content : result.GetContents()) {
    (void)content;
    // print object information here.
  }
  client_.DeleteObject(bucket_name_, "hello.txt");
  std::cout << std::endl;
}

void NormalSamples::CreateFolder() {
  const std::string folder_name = "testfolder1/";
  Status status = client_.CreateFolder(bucket_name_, folder_name);
  Trace(status, "CreateFolder");
  if (status.Ok()) {
    status = client_.DeleteObject(bucket_name_, folder_name);
    Trace(status, "DeleteObject");
  }
}

void NormalSamples::ObjectExists() {
  std::string key = "hello.txt";
  client_.PutString(bucket_name_, key, "just for test");
  bool exist = false;
  Status status = client_.ObjectExists(bucket_name_, key, &exist);
  Trace(status, "ObjectExists");
  client_.DeleteObject(bucket_name_, "hello.txt");
}

void NormalSamples::PutString() {
  std::string key = "hello.txt";
  Status status = client_.PutString(bucket_name_, key, "just for test");
  Trace(status, "PutString");
  client_.DeleteObject(bucket_name_, "hello.txt");
}

void NormalSamples::PutObject1() {
  std::string test_key =  "test.c";
  Status status = client_.PutObject(bucket_name_, test_key, niu_file_path_);
  Trace(status, "PutObject");
  client_.DeleteObject(bucket_name_, test_key);
}

void NormalSamples::PutObject2() {
  Status status;
  std::string key = "testkey.txt";
  std::ifstream stream;
  OpenStream(&stream, niu_file_path_, std::ios::in | std::ios::binary);
  if (!stream) {
    std::cout << "OpenStream failed!" << std::endl;
    return;
  }

  std::unique_ptr<ObjectMetadata> object_metadata(new ObjectMetadata);
  object_metadata->AddHeader("Content-Type", "application/pdf");

  std::string content_md5 = AprBase64Encode(AprComputeFileMd5(&stream));
  object_metadata->AddHeader("Content-MD5", content_md5);

  status = client_.PutObject(bucket_name_, key, &stream);
  Trace(status, "PutObject");
  client_.DeleteObject(bucket_name_, key);
}


void NormalSamples::DeleteObject() {
  std::string key = "hello.txt";
  Status status = client_.PutString(bucket_name_, key, "just for test");
  Trace(status, "PutString");
  status = client_.DeleteObject(bucket_name_, "hello.txt");
  Trace(status, "DeleteObject");
}

void NormalSamples::DeleteMultipleObjects() {
  std::list<std::string> keys = { "foo.txt"};
  for (auto& key : keys) {
    client_.PutString(bucket_name_, key, "just for test");
  }

  DeleteMultipleObjectsRequest request(bucket_name_, keys);
  DeleteMultipleObjectsResult result;
  Status status = client_.DeleteMultipleObjects(request, &result);
  Trace(status, "DeleteMultipleObjects");

  for (auto& key : result.GetKeyList()) {
    (void)key;
    // print key here
  }
}

void NormalSamples::OptionObject() {
  {
    SetBucketCorsRequest request(bucket_name_);
    CorsRule rule;
    rule.AddAllowedOrigin("http://www.google.com");
    rule.AddAllowedOrigin("http://www.facebook.com");
    rule.AddAllowedOrigin("http://www.aliyun.com");

    rule.AddAllowedMethod("POST");
    rule.AddAllowedMethod("GET");
    rule.AddAllowedHeader("a");
    rule.AddAllowedHeader("b");
    rule.AddAllowedHeader("c");

    rule.AddExposeHeader("x-oss-test1");
    rule.AddExposeHeader("x-oss-test2");

    rule.SetMaxAgeSeconds(200);
    request.AddRule(rule);

    client_.SetBucketCors(request);
  }

  std::string key = "testoption.txt";
  client_.PutString(bucket_name_,
                    key,
                    " It came to me, my own, my love... my... preciousssss.");

  OptionObjectRequest request(
    bucket_name_,
    key,
    "http://www.google.com",
    "POST",
    "a");

  OptionObjectResult result;
  Status status = client_.OptionObject(request, &result);
  Trace(status, "OptionObject");
  client_.DeleteObject(bucket_name_, key);
}

void NormalSamples::CopyObject() {
  Status status;
  std::string source_key = "mysource.txt";
  std::string target_key = "mytarget.txt";

  // ensure source key exists.
  client_.PutString(source_bucket_name_,
                    source_key,
                    "It came to me, my own, my love... my... preciousssss.");

  CopyObjectRequest request;
  request.SetSourceBucket(source_bucket_name_);
  request.SetSourceKey(source_key);
  request.SetTargetBucket(target_bucket_name_);
  request.SetTargetKey(target_key);

  std::unique_ptr<ObjectMetadata> object_metadata(new ObjectMetadata);
  object_metadata->AddHeader("foo", "bar");
  object_metadata->AddHeader("hello", "world");
  object_metadata->AddHeader("highest", "everest");
  request.SetNewObjectMetaData(object_metadata.release());

  CopyObjectResult result;
  status = client_.CopyObject(request, &result);
  Trace(status, "CopyObject");
  client_.DeleteObject(source_bucket_name_, source_key);
  client_.DeleteObject(target_bucket_name_, target_key);
}

void NormalSamples::GetObject() {
  std::string down_path = GetExecutableDirectory() +
                          kPathSlash + std::string("test_files") +
                          kPathSlash + "download1.niu.c";

  GetObjectRequest request;
  request.SetBucket(bucket_name_);
  request.SetKey(always_exists_key_);
  request.SetFilePath(down_path);

  Status status = client_.GetObject(request);
  Trace(status, "GetObject");
}

void NormalSamples::GetObjectMetadata() {
  std::unique_ptr<ObjectMetadata> object_metadata;
  Status status = client_.GetObjectMetadata(bucket_name_,
                  always_exists_key_,
                  &object_metadata);
  Trace(status, "GetObjectMetadata");
}

void NormalSamples::AppendObject() {
  std::string append_key = "myappend.txt";
  int64_t file_size = 0;
  std::string file_path = test_file_dir_ + "foo.txt";
  Status status;
  // ignore failure on deletion.
  client_.DeleteObject(bucket_name_, append_key);

  // phase 1, append from 0.
  {
    AppendObjectRequest request(bucket_name_,
                                append_key,
                                file_path,
                                0);  // first time file path should be 0;

    std::unique_ptr<ObjectMetadata> object_metadata(new ObjectMetadata);
    std::string content_md5 = AprBase64Encode(AprComputeFileMd5(file_path));
    object_metadata->AddHeader("Content-MD5", content_md5);

    status = client_.AppendObject(request, object_metadata.get());
    if (!status.Ok()) {
      std::cout << "AppendObject failed.\n";
      return;
    }
  }

  // phase 2, get append position.
  {
    std::unique_ptr<ObjectMetadata> object_metadata;
    client_.GetObjectMetadata(bucket_name_,
                              append_key,
                              &object_metadata);

    file_size = object_metadata->GetContentLength();
  }

  // phase 3, append from position.
  {
    AppendObjectRequest request(bucket_name_,
                                append_key,
                                file_path,
                                file_size);

    std::unique_ptr<ObjectMetadata> object_metadata(new ObjectMetadata);
    std::string content_md5 = AprBase64Encode(AprComputeFileMd5(file_path));
    object_metadata->AddHeader("Content-MD5", content_md5);
    AppendObjectResult result;
    status = client_.AppendObject(request, object_metadata.get(), &result);
    Trace(status, "AppendObject");
  }
}


void NormalSamples::UploadPart() {
  Status status;
  const std::string key = "niu.c";
  std::string upload_id;
  {
    InitiateMultipartUploadRequest request(bucket_name_, key);
    InitiateMultipartUploadResult result;
    status = client_.InitiateMultipartUpload(request, &result);
    if (!status.Ok()) {
      std::cout << "InitiateMultipartUpload failed\n";
      return;
    }
    upload_id = result.GetUploadId();
  }

  int64_t file_size = GetFileSize(niu_file_path_);
  if (file_size == -1) {
    std::cout << "GetFileSize failed\n";
    return;
  }

  std::list<PartEtag> part_etags;
  int64_t part_size = 100 * 1024;
  auto part_count = (file_size + part_size - 1) / part_size;
  std::vector<std::unique_ptr<std::ifstream>> streams;
  for (auto i = 0; i < part_count; ++i) {
    streams.push_back(
      std::move(std::unique_ptr<std::ifstream>(new std::ifstream)));
    std::ifstream& stream = *streams[i];
    OpenStream(&stream, niu_file_path_, std::ios::in | std::ios::binary);
    if (!stream) {
      throw "OpenStream failed.";
    }

    streams[i]->seekg(part_size * i, std::ios::beg);
    int64_t actual_size = (i + 1 != part_count) ?
                          part_size : (file_size - part_size * i);

    std::string md5_digest =
      AprBase64Encode(AprComputeFileMd5(&stream, actual_size));

    UploadPartRequest request{
      bucket_name_,
      key,
      upload_id,
      &stream,
      i + 1,
      actual_size,
      md5_digest
    };

    UploadPartResult result;
    status = client_.UploadPart(request, &result);
    if (!status.Ok()) {
      std::cout << "UploadPart failed\n";
      return;
    }

    part_etags.push_back(PartEtag(result.GetEtag(), i + 1));
  }

  {
    CompleteMultipartUploadrequest request(bucket_name_, key, upload_id);
    CompleteMultipartUploadResult result;
    request.MutableEtagList().swap(part_etags);
    status = client_.CompleteMultipartUpload(request, &result);
    Trace(status, "CompleteMultipartUpload");
  }
}

void NormalSamples::UploadPartCopy() {
  Status status;
  std::string source_key = "mysource1.txt";
  std::string target_key = "mytarget1.txt";

  // ensure source key exists
  status = client_.PutObject(source_bucket_name_, source_key, niu_file_path_);
  if (!status.Ok()) {
    std::cout << "PutObject failed\n";
    return;
  }

  int64_t part_size = 100 * 1024;
  int64_t source_file_size = 0;
  {
    std::unique_ptr<ObjectMetadata> object_metadata;
    client_.GetObjectMetadata(
      source_bucket_name_,
      source_key,
      &object_metadata);
    source_file_size = object_metadata->GetContentLength();
  }

  std::string upload_id;
  {
    InitiateMultipartUploadRequest request(target_bucket_name_, target_key);
    InitiateMultipartUploadResult result;
    status = client_.InitiateMultipartUpload(request, &result);
    if (!status.Ok()) {
      std::cout << "InitiateMultipartUpload failed\n";
      return;
    }
    upload_id = result.GetUploadId();
  }

  int64_t file_size = source_file_size;
  std::list<PartEtag> part_etags;

  auto part_count = (file_size + part_size - 1) / part_size;
  for (auto i = 0; i < part_count; ++i) {
    int64_t actual_size = (i + 1 != part_count) ?
                          part_size : (file_size - part_size * i);

    UploadPartCopyRequest request{
      source_bucket_name_,
      source_key,
      target_bucket_name_,
      target_key,
      upload_id,
      i + 1,
      actual_size,
      i * part_size
    };

    UploadPartCopyResult result;
    status = client_.UploadPartCopy(request, &result);
    part_etags.push_back(PartEtag(result.GetEtag(), i + 1));
    if (!status.Ok()) {
      std::cout << "UploadPartCopy failed\n";
      return;
    }
  }

  {
    CompleteMultipartUploadrequest request(target_bucket_name_,
                                           target_key,
                                           upload_id);
    CompleteMultipartUploadResult result;
    request.MutableEtagList().swap(part_etags);
    status = client_.CompleteMultipartUpload(request, &result);
    Trace(status, "CompleteMultipartUpload");
  }
}


void NormalSamples::ListMultipartUploads() {
  Status status;
  for (int i = 0; i < 5; ++i) {
    InitiateMultipartUploadRequest request(bucket_name_, "temp_part");
    InitiateMultipartUploadResult result;
    status = client_.InitiateMultipartUpload(request, &result);
    if (!status.Ok()) {
      std::cout << "InitiateMultipartUpload failed" << std::endl;
      return;
    }
  }

  ListMultipartUploadsRequest request;
  request.SetBucketName(bucket_name_);
  request.SetMaxUploads(1000);
  ListMultipartUploadsResult result;
  status = client_.ListMultipartUploads(request, &result);
  if (!status.Ok()) {
    std::cout << "ListMultipartUploads failed" << std::endl;
    return;
  }
  for (auto& upload : result.GetMultipartUpload()) {
    client_.AbortMultipartUpload(bucket_name_,
                                 upload.GetKey(),
                                 upload.GetUploadId());
  }
  std::cout << "ListMultipartUploads succeed" << std::endl;
}

void NormalSamples::ListParts() {
  Status status;
  const std::string key = "niu.c";
  std::string upload_id;
  {
    InitiateMultipartUploadRequest request(bucket_name_, key);
    InitiateMultipartUploadResult result;
    status = client_.InitiateMultipartUpload(request, &result);
    if (!status.Ok()) {
      std::cout << "InitiateMultipartUpload failed\n";
      return;
    }
    upload_id = result.GetUploadId();
  }

  int64_t file_size = GetFileSize(niu_file_path_);
  if (file_size == -1) {
    std::cout << "GetFileSize failed\n";
    return;
  }

  std::list<PartEtag> part_etags;
  int64_t part_size = 100 * 1024;
  auto part_count = (file_size + part_size - 1) / part_size;
  std::vector<std::unique_ptr<std::ifstream>> streams;
  for (auto i = 0; i < part_count; ++i) {
    streams.push_back(
      std::move(std::unique_ptr<std::ifstream>(new std::ifstream)));
    std::ifstream& stream = *streams[i];
    OpenStream(&stream, niu_file_path_, std::ios::in | std::ios::binary);
    if (!stream) {
      throw "OpenStream failed.";
    }

    streams[i]->seekg(part_size * i, std::ios::beg);
    int64_t actual_size = (i + 1 != part_count) ?
                          part_size : (file_size - part_size * i);

    std::string md5_digest =
      AprBase64Encode(AprComputeFileMd5(&stream, actual_size));

    UploadPartRequest request{
      bucket_name_,
      key,
      upload_id,
      &stream,
      i + 1,
      actual_size,
      md5_digest
    };

    UploadPartResult result;
    status = client_.UploadPart(request, &result);
    if (!status.Ok()) {
      std::cout << "UploadPart failed\n";
      return;
    }

    part_etags.push_back(PartEtag(result.GetEtag(), i + 1));
  }

  {
    ListPartsRequest request;
    request.SetBucketName(bucket_name_);
    request.SetKey(key);
    request.SetUploadId(upload_id);
    request.SetMaxParts(2);

    ListPartsResult result;
    status = client_.ListParts(request, &result);
    if (!status.Ok()) {
      std::cout << "ListParts failed\n";
      return;
    }

    for (auto& part : result.GetParts()) {
      (void)part;
      // print part etag here.
    }
  }

  status = client_.AbortMultipartUpload(bucket_name_, key, upload_id);
  if (!status.Ok()) {
    std::cout << "AbortMultipartUpload failed\n";
    return;
  }

  std::cout << "ListParts succeed!" << std::endl;
}

void NormalSamples::ClearBucket(const std::string & bucket_name) {
  Status status;
  {
    ListObjectsRequest request;
    request.SetBucketName(bucket_name);
    request.SetMaxKeys(1000);
    ListObjectsResult result;
    status = client_.ListObjects(request, &result);
    if (!status.Ok()) {
      std::cout << "ListObjects failed\n";
      return;
    }

    if (!result.GetContents().empty()) {
      DeleteMultipleObjectsRequest delete_request;
      delete_request.SetBucketName(bucket_name);
      for (auto& content : result.GetContents()) {
        delete_request.AddKey(content.GetKey());
      }

      DeleteMultipleObjectsResult delete_result;
      status = client_.DeleteMultipleObjects(delete_request, &delete_result);
      if (!status.Ok()) {
        std::cout << "DeleteMultipleObjects failed\n";
        return;
      }
    }
  }

  {
    ListMultipartUploadsRequest request;
    ListMultipartUploadsResult result;

    request.SetBucketName(bucket_name);
    request.SetMaxUploads(1000);
    status = client_.ListMultipartUploads(request, &result);
    if (status.Ok()) {
      for (auto& upload : result.GetMultipartUpload()) {
        client_.AbortMultipartUpload(bucket_name,
                                     upload.GetKey(),
                                     upload.GetUploadId());
      }
    } else {
      std::cout << "ListMultipartUploads failed\n";
    }
  }
}

void RunNormalSamples() {
//  NormalSamples samples;
//  samples.ListBuckets();
//  samples.ListBuckets2();
//  samples.CreateBucket();
//  samples.SetBucketAcl();
//  samples.GetBucketAcl();
//  samples.GetBucketAcl2();
//  samples.BucketExists();
//  samples.GetBucketLocation();
//  samples.SetBucketLogging();
//  samples.GetBucketLogging();
//  samples.DeleteBucketLogging();
//  samples.SetBucketWebsite();
//  samples.SetBucketWebsite2();
//  samples.GetBucketWebsite();
//  samples.DeleteBucketWebsite();
//  samples.SetBucketReferer();
//  samples.GetBucketReferer();
//  samples.SetBucketLifecycle();
//  samples.GetBucketLifecycle();
//  samples.DeleteBucketLifeCycle();
//  samples.SetBucketCors();
//  samples.GetBucketCors();
//  samples.DeleteBucketCors();
//  samples.ListObjects();
//  samples.CreateFolder();
//  samples.ObjectExists();
//  samples.PutString();
//  samples.PutObject1();
//  samples.PutObject2();
//  samples.DeleteObject();
//  samples.DeleteMultipleObjects();
//  samples.OptionObject();
//  samples.CopyObject();
//  samples.GetObject();
//  samples.GetObjectMetadata();
//  samples.AppendObject();
//  samples.UploadPart();
//  samples.UploadPartCopy();
//  samples.ListMultipartUploads();
//  samples.ListParts();
}

}  // namespace oss
