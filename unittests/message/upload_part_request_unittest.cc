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

#include <fstream>

#include "gtest/gtest.h"

#include "oss_sdk_cpp/message/upload_part_request.h"

namespace oss {

TEST(UploadPartRequest, Basic) {
  std::string bucket_name = "mybucket";
  std::string key = "mykey";
  std::string upload_id = "858089EC0A36427581779DC7659E1EBD";
  std::ifstream input_stream;
  int part_number = 2;
  int64_t part_size = 1024 * 1024;
  std::string content_md5 = " ODBGOERFMDMzQTczRUY3NUE3NzA5QzdFNUYzMDQxNEM=";

  std::string query_string =
    "mykey?partNumber=2&uploadId=858089EC0A36427581779DC7659E1EBD";

  {
    UploadPartRequest request(
      bucket_name,
      key,
      upload_id,
      &input_stream,
      part_number,
      part_size,
      content_md5);

    EXPECT_EQ(bucket_name, request.GetBucketName());
    EXPECT_EQ(key, request.GetKey());
    EXPECT_EQ(upload_id, request.GetUploadId());
    EXPECT_EQ(&input_stream, request.GetInputStream());
    EXPECT_EQ(part_number, request.GetPartNumber());
    EXPECT_EQ(part_size, request.GetPartSize());
    EXPECT_EQ(content_md5, request.GetMd5Digest());
    EXPECT_EQ(upload_id, request.GetUploadId());

    EXPECT_EQ(query_string, request.BuildQueryString());
  }

  {
    UploadPartRequest request;
    request.SetBucketName(bucket_name);
    request.SetKey(key);
    request.SetUploadId(upload_id);
    request.SetInputStream(&input_stream);
    request.SetPartNumber(part_number);
    request.SetPartPartSize(part_size);
    request.SetMd5Digest(content_md5);

    EXPECT_EQ(bucket_name, request.GetBucketName());
    EXPECT_EQ(key, request.GetKey());
    EXPECT_EQ(upload_id, request.GetUploadId());
    EXPECT_EQ(&input_stream, request.GetInputStream());
    EXPECT_EQ(part_number, request.GetPartNumber());
    EXPECT_EQ(part_size, request.GetPartSize());
    EXPECT_EQ(content_md5, request.GetMd5Digest());
    EXPECT_EQ(upload_id, request.GetUploadId());

    EXPECT_EQ(query_string, request.BuildQueryString());
  }
}

}  // namespace oss
