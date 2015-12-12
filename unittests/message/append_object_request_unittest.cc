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

#include "oss_sdk_cpp/message/append_object_request.h"

namespace oss {

TEST(AppendObjectRequest, Basic) {
  std::string bucket_name = "mybucket";
  std::string key = "mykey";
  std::string file_path = "/home/hello/abc.txt";
  uint64_t position = 999;
  std::string query_string = "mykey?append&position=999";

  {
    AppendObjectRequest request(bucket_name, key, file_path, position);
    EXPECT_EQ(bucket_name, request.GetBucketName());
    EXPECT_EQ(key, request.GetKey());
    EXPECT_EQ(file_path, request.GetFilePath());
    EXPECT_EQ(position, request.GetPosition());

    EXPECT_EQ(query_string, request.BuildQueryString());
  }

  {
    AppendObjectRequest request;
    request.SetBucketName(bucket_name);
    EXPECT_EQ(bucket_name, request.GetBucketName());

    request.SetKey(key);
    EXPECT_EQ(key, request.GetKey());

    request.SetFilePath(file_path);
    EXPECT_EQ(file_path, request.GetFilePath());

    request.SetPosition(position);
    EXPECT_EQ(position, request.GetPosition());

    EXPECT_EQ(query_string, request.BuildQueryString());
  }
}

}  // namespace oss
