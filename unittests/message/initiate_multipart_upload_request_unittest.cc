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

#include "oss_sdk_cpp/message/initiate_multipart_upload_request.h"

namespace oss {

TEST(InitiateMultipartUploadRequest, Basic) {
  std::string bucket_name = "mybucket";
  std::string key = "mykey";
  std::string query_string = "mykey?uploads";

  {
    InitiateMultipartUploadRequest request(bucket_name, key);
    EXPECT_EQ(bucket_name, request.GetBucketName());
    EXPECT_EQ(key, request.GetKey());
    EXPECT_EQ(query_string, request.BuildQueryString());
  }

  {
    InitiateMultipartUploadRequest request;
    request.SetBucketName(bucket_name);
    request.SetKey(key);
    EXPECT_EQ(bucket_name, request.GetBucketName());
    EXPECT_EQ(key, request.GetKey());
    EXPECT_EQ(query_string, request.BuildQueryString());
  }
}

}  // namespace oss
