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

#include "gtest/gtest.h"

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/oss/oss_client.h"
#include "oss_sdk_cpp/oss/oss_error_code.h"

static const char* endpoint = "oss-cn-hangzhou.aliyuncs.com";
static const char* access_key_id = "mykeyid";
static const char* access_key_secret = "mykeysecret";

namespace oss {

class OssClientTest : public ::testing::Test {
 public:
  OssClientTest()
    : client_(endpoint, access_key_id, access_key_secret),
      client2_(access_key_id, access_key_secret) {
  }
 protected:
  virtual void SetUp() {
    client_.SetUnitTestMode();
    bucket_name_ = "mybucket";
    key_name_ = "mykey";
    client2_.SetEndpoint(endpoint);
  }

  Status status_;
  OssClient client_;
  OssClient client2_;
  std::string bucket_name_;
  std::string key_name_;
  std::string input_file_path_;
  std::ifstream input_stream_;
  std::ofstream output_stream_;
};

TEST_F(OssClientTest, ListBuckets1) {
  ListBucketsRequest request;
  ListBucketsResult result;
  status_ = client_.ListBuckets(request, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, ListBuckets2) {
  std::vector<Bucket> buckets;
  status_ = client_.ListBuckets(&buckets);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, CreateBucket) {
  status_ = client_.CreateBucket(bucket_name_, kAclPrivate);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, DeleteBucket) {
  status_ = client_.DeleteBucket(bucket_name_);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, SetBucketAcl) {
  status_ = client_.SetBucketAcl(bucket_name_, kAclPrivate);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, GetBucketAcl) {
  GetBucketAclResult result;
  status_ = client_.GetBucketAcl(bucket_name_, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, GetBucketAcl2) {
  std::string acl;
  status_ = client_.GetBucketAcl(bucket_name_, &acl);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, BucketExists) {
  bool exist = false;
  status_ = client_.BucketExists(bucket_name_, &exist);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, GetBucketLocation) {
  std::string location;
  status_ = client_.GetBucketLocation(bucket_name_, &location);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, GetBucketLogging) {
  GetBucketLoggingResult result;
  status_ = client_.GetBucketLogging(bucket_name_, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, SetBucketLogging) {
  SetBucketLoggingRequest request;
  status_ = client_.SetBucketLogging(request);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, DeleteBucketLogging) {
  status_ = client_.DeleteBucketLogging(bucket_name_);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, GetBucketWebsite) {
  GetBucketWebsiteResult result;
  status_ = client_.GetBucketWebsite(bucket_name_, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, SetBucketWebsite) {
  SetBucketWebsiteRequest request;
  status_ = client_.SetBucketWebsite(request);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, SetBucketWebsite2) {
  std::string index_page = "index.html";
  std::string not_found_page = "404.html";

  status_ = client_.SetBucketWebsite(bucket_name_, index_page, not_found_page);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, DeleteBucketWebsite) {
  status_ = client_.DeleteBucketWebsite(bucket_name_);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, GetBucketReferer) {
  GetBucketRefererResult result;
  status_ = client_.GetBucketReferer(bucket_name_, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, SetBucketReferer) {
  SetBucketRefererRequest request;
  status_ = client_.SetBucketReferer(request);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, GetBucketLifecycle) {
  GetBucketLifecycleResult result;
  status_ = client_.GetBucketLifecycle(bucket_name_, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, SetBucketLifecycle) {
  SetBucketLifecycleRequest request;
  status_ = client_.SetBucketLifecycle(request);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, DeleteBucketLifecycle) {
  status_ = client_.DeleteBucketLifecycle(bucket_name_);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, GetBucketCors) {
  GetBucketCorsResult result;
  status_ = client_.GetBucketCors(bucket_name_, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, SetBucketCors) {
  SetBucketCorsRequest request;
  status_ = client_.SetBucketCors(request);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, DeleteBucketCors) {
  status_ = client_.DeleteBucketCors(bucket_name_);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, DeleteBucketConfig) {
  status_ = client_.DeleteBucketConfig(bucket_name_, "website");
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, ListObjects) {
  ListObjectsRequest request;
  ListObjectsResult result;
  status_ = client_.ListObjects(request, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, CreateFolder) {
  status_ = client_.CreateFolder(bucket_name_, "myfolder");
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, ObjectExists) {
  bool exist = false;
  status_ = client_.ObjectExists(bucket_name_, "mykey", &exist);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, PutString) {
  {
    std::unique_ptr<ObjectMetadata> object_meta_data(new ObjectMetadata);
    status_ = client_.PutString(bucket_name_,
                                key_name_,
                                "hello",
                                object_meta_data.get());
    EXPECT_TRUE(status_.Ok());
  }

  {
    status_ = client_.PutString(bucket_name_,
                                key_name_,
                                "hello",
                                NULL);
    EXPECT_TRUE(status_.Ok());
  }
}


TEST_F(OssClientTest, PutObject1) {
  {
    std::unique_ptr<ObjectMetadata> object_meta_data(new ObjectMetadata);
    status_ = client_.PutObject(bucket_name_,
                                key_name_,
                                input_file_path_,
                                object_meta_data.get());
    EXPECT_TRUE(status_.Ok());
  }

  {
    status_ = client_.PutObject(bucket_name_,
                                key_name_,
                                input_file_path_,
                                nullptr);
    EXPECT_TRUE(status_.Ok());
  }
}

TEST_F(OssClientTest, PutObject2) {
  int64_t stream_bytes = 1024;
  {
    std::unique_ptr<ObjectMetadata> object_meta_data(new ObjectMetadata);
    status_ = client_.PutObject(bucket_name_,
                                key_name_,
                                input_file_path_,
                                stream_bytes,
                                object_meta_data.get());
    EXPECT_TRUE(status_.Ok());
  }

  {
    status_ = client_.PutObject(bucket_name_,
                                key_name_,
                                input_file_path_,
                                stream_bytes,
                                nullptr);
    EXPECT_TRUE(status_.Ok());
  }
}

TEST_F(OssClientTest, PutObject3) {
  std::unique_ptr<ObjectMetadata> object_meta_data(new ObjectMetadata);
  status_ = client_.PutObject(bucket_name_,
                              key_name_,
                              &input_stream_,
                              object_meta_data.get());
  EXPECT_TRUE(status_.Ok());
}


TEST_F(OssClientTest, PutObject4) {
  std::unique_ptr<ObjectMetadata> object_meta_data(new ObjectMetadata);
  status_ = client_.PutObject(bucket_name_,
                              key_name_,
                              &input_stream_,
                              1024,
                              object_meta_data.get());
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, DeleteObject) {
  status_ = client_.DeleteObject(bucket_name_, key_name_);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, DeleteMultipleObjects) {
  DeleteMultipleObjectsRequest request;
  DeleteMultipleObjectsResult result;
  status_ = client_.DeleteMultipleObjects(request, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, OptionObject) {
  OptionObjectRequest request;
  OptionObjectResult result;
  status_ = client_.OptionObject(request, &result);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, CopyObject) {
  CopyObjectRequest request;
  CopyObjectResult result;
  status_ = client_.CopyObject(request, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, GetObject) {
  GetObjectRequest request;
  status_ = client_.GetObject(request);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, GetObjectMetadata) {
  std::unique_ptr<ObjectMetadata> object_meta_data(new ObjectMetadata);
  status_ = client_.GetObjectMetadata(bucket_name_,
                                      key_name_,
                                      &object_meta_data);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, AppendObject) {
  AppendObjectRequest request;
  status_ = client_.AppendObject(request);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, AppendObject1) {
  std::unique_ptr<ObjectMetadata> object_meta_data(new ObjectMetadata);
  AppendObjectRequest request;
  status_ = client_.AppendObject(request, object_meta_data.get());
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, AppendObject2) {
  std::unique_ptr<ObjectMetadata> object_meta_data(new ObjectMetadata);
  AppendObjectRequest request;
  AppendObjectResult result;
  status_ = client_.AppendObject(request, object_meta_data.get(), &result);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, InitiateMultipartUpload) {
  InitiateMultipartUploadRequest request;
  InitiateMultipartUploadResult result;
  status_ = client_.InitiateMultipartUpload(request, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, UploadPart) {
  UploadPartRequest request;
  UploadPartResult result;
  status_ = client_.UploadPart(request, &result);
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, UploadPartCopy) {
  UploadPartCopyRequest request;
  UploadPartCopyResult result;
  status_ = client_.UploadPartCopy(request, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, CompleteMultipartUpload) {
  CompleteMultipartUploadrequest request;
  CompleteMultipartUploadResult result;
  status_ = client_.CompleteMultipartUpload(request, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, AbortMultipartUpload) {
  status_ = client_.AbortMultipartUpload(bucket_name_,
                                         key_name_,
                                         "[ upload id ]");
  EXPECT_TRUE(status_.Ok());
}

TEST_F(OssClientTest, ListMultipartUploads) {
  ListMultipartUploadsRequest request;
  ListMultipartUploadsResult result;
  status_ = client_.ListMultipartUploads(request, &result);
  EXPECT_FALSE(status_.Ok());
}

TEST_F(OssClientTest, ListParts) {
  ListPartsRequest request;
  ListPartsResult result;
  status_ = client_.ListParts(request, &result);
  EXPECT_FALSE(status_.Ok());
}

}  // namespace oss
