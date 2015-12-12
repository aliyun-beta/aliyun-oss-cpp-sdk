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

#include <iostream>
#include <functional>
#include <string>
#include <list>
#include <vector>

#include "oss_sdk_cpp/utils/http_utils.h"
#include "oss_sdk_cpp/utils/apr_utils.h"
#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/base/string_piece.h"
#include "oss_sdk_cpp/base/sys_string_conversions.h"

#include "samples/exp_oss_client.h"
#include "samples/exp_samples.h"

namespace oss {

// Himalayas in Chinese
char kUtf8Text1[] =
  "\xE5\x96\x9C\xE9\xA9\xAC\xE6\x8B\x89\xE9\x9B\x85\xE5\xB1\xB1";

// Himalayas in Korean
char kUtf8Text2[] = "\xED\x9E\x88\xEB\xA7\x90\xEB\x9D\xBC\xEC\x95\xBC";

void TestAllExpSamples() {
  std::string endpoint = "http://oss-cn-hangzhou.aliyuncs.com";
  std::string access_key_id = "0w8ppPOLTpnzeFle";
  std::string access_key_secret = "lcpdx8XlYn2IJHKMIlizJyJtdY7Tkf";
  std::string bucket_name = "wuhawukawuha12";
  std::string always_exists_key = "alwaysexists.txt";
  std::string niu_file_path;
  ClientConfiguration config;
  config.http_config.SetReuse(true);
  ExpOssClient client(endpoint, access_key_id, access_key_secret, config);

  niu_file_path = GetExecutableDirectory() +
                  kPathSlash + std::string("test_files") +
                  kPathSlash + "niu.c";

  if (1) {
    ListBucketsRequest request;
    request.SetMaxKeys(1);
    auto result = client.ListBuckets(request);
    (void)result;
  }

  if (1) {
    auto buckets = client.ListBuckets();
    (void)buckets;
  }

  if (1) {
    if (!client.BucketExists(bucket_name)) {
      client.CreateBucket(bucket_name);
    }
    client.PutObject(bucket_name, always_exists_key, niu_file_path);
  }

  if (1) {
    std::vector<std::string> new_acls = { kAclPrivate, kAclPublicRead };
    for (auto& new_acl : new_acls) {
      client.SetBucketAcl(bucket_name, new_acl);
    }
  }

  if (1) {
    client.GetBucketLocation(bucket_name);
  }

  if (1) {
    std::string log_bucket_name = bucket_name + "log564987";
    std::string log_prefix = "test18";
    client.EnsureBucketExit(log_bucket_name);
    SetBucketLoggingRequest request(log_bucket_name, log_prefix, bucket_name);
    client.SetBucketLogging(request);

    auto result = client.GetBucketLogging(bucket_name);
    (void)result;
  }

  if (1) {
    std::string index_page = "myindex.html";
    std::string not_found_page = "my404.html";

    SetBucketWebsiteRequest request(bucket_name, index_page, not_found_page);
    client.SetBucketWebsite(request);

    auto result = client.GetBucketWebsite(bucket_name);
    (void)result;
  }

  if (1) {
    SetBucketRefererRequest request(bucket_name);
    request.AddReferer("http://www.yahoo.com");
    request.AddReferer("http://www.microsoft.com");
    request.AddReferer("http://www.msn.com");
    request.AddReferer("http://www.aliyun.com");
    request.AddReferer("http://www.*.com");
    request.AddReferer("http://www.?.aliyuncs.com");
    client.SetBucketReferer(request);

    auto result = client.GetBucketReferer(bucket_name);
    (void)result;
  }

  if (1) {
    SetBucketLifecycleRequest request(bucket_name);

    {
      LifeCycleRule rule;
      rule.SetEnabled(true);
      rule.SetId("test1");
      rule.SetPrefix("filter1");
      rule.SetExpirationDays(25);
      request.AddRule(rule);
    }

    {
      LifeCycleRule rule;
      rule.SetEnabled(false);
      rule.SetId("test2");
      rule.SetPrefix("filter2");
      rule.SetExpirationDate(Iso8601Date(time(NULL) + 86400 * 11));
      request.AddRule(rule);
    }
    client.SetBucketLifecycle(request);

    auto result = client.GetBucketLifecycle(bucket_name);
    (void)result;
  }

  if (1) {
    SetBucketCorsRequest request(bucket_name);

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

    client.SetBucketCors(request);
    auto result = client.GetBucketCors(bucket_name);
    (void)result;
  }

  if (1) {
    std::string folder_name = "tomorrow20151118";
    client.CreateFolder(bucket_name, folder_name);
    client.DeleteObject(bucket_name, folder_name);

    client.CreateFolder(bucket_name, folder_name);
    client.PutString(bucket_name, "foo.txt", "hey, there");
    client.PutString(bucket_name, "bar.txt", "please copy!");
    client.ObjectExists(bucket_name, "foo.txt");

    ListObjectsRequest request;
    request.SetBucketName(bucket_name);
    request.SetMaxKeys(100);
    request.SetPrefix("");
    client.ListObjects(request);
  }

  if (1) {
    std::string key = std::string(kUtf8Text1) + "1.txt";
    client.PutString(bucket_name,
                     key,
                     " It came to me, my own, my love... my... preciousssss.");
    client.DeleteObject(bucket_name, key);
  }

  if (1) {
    std::string key = std::string(kUtf8Text2) + ".txt";
    std::string path = GetExecutableDirectory() +
                       kPathSlash + std::string("test_files") +
                       kPathSlash + key;
    client.PutObject(bucket_name, key, path);
  }

  if (1) {
    std::string key = std::string(kUtf8Text1) + "11.txt";
    std::string file_name = std::string(kUtf8Text1) + ".txt";
    std::string path = GetExecutableDirectory() +
                       kPathSlash + std::string("test_files") +
                       kPathSlash + file_name;
    client.PutObject(bucket_name, key, path);
    client.DeleteObject(bucket_name, key);
  }

  if (1) {
    std::string key = std::string(kUtf8Text1) + "12.txt";
    std::string file_name = std::string(kUtf8Text1) + ".txt";
    std::string path = GetExecutableDirectory() +
                       kPathSlash + std::string("test_files") +
                       kPathSlash + file_name;
    std::ifstream stream;
    OpenStream(&stream, path, std::ios::in | std::ios::binary);
    if (!stream)
      throw std::string("OpenStream failed!");

    std::unique_ptr<ObjectMetadata> object_metadata(new ObjectMetadata);
    object_metadata->AddHeader("Content-Type", "application/pdf");

    std::string content_md5 = AprBase64Encode(AprComputeFileMd5(&stream));
    object_metadata->AddHeader("Content-MD5", content_md5);

    client.PutObject(bucket_name, key, &stream);
    client.DeleteObject(bucket_name, key);
  }

  if (1) {
    std::string key = std::string(kUtf8Text1) + "15.txt";
    client.PutString(bucket_name,
                     key,
                     " It came to me, my own, my love... my... preciousssss.");

    OptionObjectRequest request(
      bucket_name,
      key,
      "http://www.google.com",
      "POST",
      "a");
    auto result =  client.OptionObject(request);

    //  client.DeleteObject(bucket_name, key);
  }

  if (1) {
    std::string source_bucket = "mysourcetest123";
    client.EnsureBucketExit(source_bucket);
    std::string source_key = "mysource.txt";

    std::string target_bucket = "mytargettest123";
    client.EnsureBucketExit(target_bucket);
    std::string target_key = "mytarget.txt";

    // ensure source key exists.
    client.PutString(source_bucket,
                     source_key,
                     "It came to me, my own, my love... my... preciousssss.");

    CopyObjectRequest request;
    request.SetSourceBucket(source_bucket);
    request.SetSourceKey(source_key);
    request.SetTargetBucket(target_bucket);
    request.SetTargetKey(target_key);

    std::unique_ptr<ObjectMetadata> object_metadata(new ObjectMetadata);
    object_metadata->AddHeader("foo", "bar");
    object_metadata->AddHeader("hello", "world");
    object_metadata->AddHeader("highest", "everest");

    request.SetNewObjectMetaData(object_metadata.release());

    client.CopyObject(request);
  }

  if (1) {
    {
      std::string down_path = GetExecutableDirectory() +
                              kPathSlash + std::string("test_files") +
                              kPathSlash + "download1.niu.c";

      GetObjectRequest request;
      request.SetBucket(bucket_name);
      request.SetKey(always_exists_key);
      request.SetFilePath(down_path);

      client.GetObject(request);
    }

    {
      std::string down_path = GetExecutableDirectory() +
                              kPathSlash + std::string("test_files") +
                              kPathSlash + "download2.niu.c";

      GetObjectRequest request;
      request.SetBucket(bucket_name);
      request.SetKey(always_exists_key);
      request.SetFilePath(down_path);
      request.SetRange(Range(100, 200));
      client.GetObject(request);
    }

    {
      std::string down_path = GetExecutableDirectory() +
                              kPathSlash + std::string("test_files") +
                              kPathSlash + "download3.niu.c";

      std::ofstream stream;
      OpenStream(&stream, down_path, std::ios::out | std::ios::binary);
      if (!stream)
        throw std::string("OpenStream failed!");

      GetObjectRequest request;
      request.SetBucket(bucket_name);
      request.SetKey(always_exists_key);
      request.SetFilePath(down_path);
      request.SetRange(Range(200, 300));
      client.GetObject(request);
    }
  }

  if (1) {
    std::string append_key = "myappend.txt";
    int64_t file_size = 0;
    std::string file_path = GetExecutableDirectory() +
                            kPathSlash + std::string("test_files") +
                            kPathSlash + "foo.txt";

    // ignore failure on deletion.
    try {
      client.DeleteObject(bucket_name, append_key);
    } catch (... ){
    }

    {
      AppendObjectRequest request(bucket_name,
                                  append_key,
                                  file_path,
                                  0);

      std::unique_ptr<ObjectMetadata> object_metadata(new ObjectMetadata);
      std::string content_md5 = AprBase64Encode(AprComputeFileMd5(file_path));
      object_metadata->AddHeader("Content-MD5", content_md5);

      client.AppendObject(request, object_metadata.get());
    }

    {
      std::unique_ptr<ObjectMetadata> object_metadata;
      client.GetObjectMetadata(bucket_name,
                               append_key,
                               &object_metadata);

      file_size = object_metadata->GetContentLength();
    }

    {
      AppendObjectRequest request(bucket_name,
                                  append_key,
                                  file_path,
                                  file_size);

      std::unique_ptr<ObjectMetadata> object_metadata(new ObjectMetadata);
      std::string content_md5 = AprBase64Encode(AprComputeFileMd5(file_path));
      object_metadata->AddHeader("Content-MD5", content_md5);
      AppendObjectResult result;
      client.AppendObject(request, object_metadata.get(), &result);
    }
  }

  if (1) {
    const std::string key = "niu.c";
    std::string upload_id;
    {
      InitiateMultipartUploadRequest request(bucket_name, key);
      auto result = client.InitiateMultipartUpload(request);
      upload_id = result.GetUploadId();
    }

    int64_t file_size = GetFileSize(niu_file_path);
    if (file_size == -1) {
      throw "GetFileSize failed.";
    }
    std::list<PartEtag> part_etags;
    int64_t part_size = 100 * 1024;
    auto part_count = (file_size + part_size - 1) / part_size;
    std::vector<std::unique_ptr<std::ifstream>> streams;
    for (auto i = 0; i < part_count; ++i) {
      streams.push_back(
        std::move(std::unique_ptr<std::ifstream>(new std::ifstream)));
      std::ifstream& stream = *streams[i];
      OpenStream(&stream, niu_file_path, std::ios::in | std::ios::binary);
      if (!stream) {
        throw "OpenStream failed.";
      }

      streams[i]->seekg(part_size * i, std::ios::beg);
      int64_t actual_size = (i + 1 != part_count) ?
                            part_size : (file_size - part_size * i);

      std::string md5_digest =
        AprBase64Encode(AprComputeFileMd5(&stream, actual_size));

      UploadPartRequest request{
        bucket_name,
        key,
        upload_id,
        &stream,
        i + 1,
        actual_size,
        md5_digest
      };

      auto result = client.UploadPart(request);
      part_etags.push_back(PartEtag(result.GetEtag(), i + 1));
    }

    {
      CompleteMultipartUploadrequest request(bucket_name, key, upload_id);
      CompleteMultipartUploadResult result;
      request.MutableEtagList().swap(part_etags);
      client.CompleteMultipartUpload(request);
    }
  }

  if (1) {
    std::string source_bucket = "mysourcetest123";
    client.EnsureBucketExit(source_bucket);
    std::string source_key = "mysource1.txt";

    std::string target_bucket = "mytargettest123";
    client.EnsureBucketExit(target_bucket);
    std::string target_key = "mytarget1.txt";

    // ensure source key exists
    client.PutObject(source_bucket, source_key, niu_file_path);

    int64_t part_size = 100 * 1024;
    int64_t source_file_size = 0;
    {
      std::unique_ptr<ObjectMetadata> object_metadata;
      client.GetObjectMetadata(
        source_bucket,
        source_key,
        &object_metadata);

      source_file_size = object_metadata->GetContentLength();


      std::string upload_id;
      {
        InitiateMultipartUploadRequest request(target_bucket, target_key);
        upload_id = client.InitiateMultipartUpload(request).GetUploadId();
      }

      int64_t file_size = source_file_size;
      std::list<PartEtag> part_etags;

      auto part_count = (file_size + part_size - 1) / part_size;
      for (auto i = 0; i < part_count; ++i) {
        int64_t actual_size = (i + 1 != part_count) ?
                              part_size : (file_size - part_size * i);

        UploadPartCopyRequest request{
          source_bucket,
          source_key,
          target_bucket,
          target_key,
          upload_id,
          i + 1,
          actual_size,
          i * part_size
        };

        auto result = client.UploadPartCopy(request);
        part_etags.push_back(PartEtag(result.GetEtag(), i + 1));
      }

      {
        CompleteMultipartUploadrequest request(target_bucket,
                                               target_key,
                                               upload_id);
        CompleteMultipartUploadResult result;
        request.MutableEtagList().swap(part_etags);
        client.CompleteMultipartUpload(request);
      }
    }
  }

  if (1) {
    for (int i = 0; i < 5; ++i) {
      InitiateMultipartUploadRequest request(bucket_name, "temp_part");
      client.InitiateMultipartUpload(request);
    }

    ListMultipartUploadsRequest request;

    request.SetBucketName(bucket_name);
    request.SetMaxUploads(1000);
    auto result = client.ListMultipartUploads(request);

    for (auto& upload : result.GetMultipartUpload()) {
      client.AbortMultipartUpload(bucket_name,
                                  upload.GetKey(),
                                  upload.GetUploadId());
    }
  }

  if (1) {
    const std::string key = "niu.c";
    std::string upload_id;
    {
      InitiateMultipartUploadRequest request(bucket_name, key);
      auto result = client.InitiateMultipartUpload(request);
      upload_id = result.GetUploadId();
    }

    int64_t file_size = GetFileSize(niu_file_path);
    if (file_size == -1) {
      throw "GetFileSize failed.";
    }
    std::list<PartEtag> part_etags;
    int64_t part_size = 100 * 1024;
    auto part_count = (file_size + part_size - 1) / part_size;
    std::vector<std::unique_ptr<std::ifstream>> streams;
    for (auto i = 0; i < part_count; ++i) {
      streams.push_back(
        std::move(std::unique_ptr<std::ifstream>(new std::ifstream)));
      std::ifstream& stream = *streams[i];
      OpenStream(&stream, niu_file_path, std::ios::in | std::ios::binary);
      if (!stream) {
        throw "OpenStream failed.";
      }

      streams[i]->seekg(part_size * i, std::ios::beg);
      int64_t actual_size = (i + 1 != part_count) ?
                            part_size : (file_size - part_size * i);

      UploadPartRequest request{
        bucket_name,
        key,
        upload_id,
        &stream,
        i + 1,
        actual_size
      };

      auto result = client.UploadPart(request);
      part_etags.push_back(PartEtag(result.GetEtag(), i + 1));
    }

    {
      ListPartsRequest request;
      request.SetBucketName(bucket_name);
      request.SetKey(key);
      request.SetUploadId(upload_id);
      request.SetMaxParts(2);

      auto result = client.ListParts(request);
      (void)result;
    }

    client.AbortMultipartUpload(bucket_name,
                                key,
                                upload_id);
  }

  std::cout << "all passed." << std::endl;
}

void RunExpSamples() {
  try {
    TestAllExpSamples();
  } catch (std::string exception) {
    std::cout << "exception catched: " << exception << std::endl;
  } catch (...) {
    std::cout << "unknown exception.";
  }
}

}  // namespace oss
