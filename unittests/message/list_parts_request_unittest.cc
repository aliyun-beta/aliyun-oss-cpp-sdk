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

#include "oss_sdk_cpp/message/list_parts_request.h"

namespace oss {

TEST(ListPartsRequest, Basic) {
  std::string bucket_name = "mybucket";
  std::string key = "mykey";
  std::string upload_id = "858089EC0A36427581779DC7659E1EBD";
  int max_parts = 999;
  int part_number_marker = 888;

  std::string query_string =
    "uploadId=858089EC0A36427581779DC7659E1EBD"
    "&max-parts=999&part-number-marker=888";

  {
    ListPartsRequest request;
    request.SetBucketName(bucket_name);
    request.SetKey(key);
    request.SetUploadId(upload_id);
    request.SetMaxParts(max_parts);
    request.SetPartNumberMarker(part_number_marker);

    EXPECT_EQ(request.GetBucketName(), bucket_name);
    EXPECT_EQ(request.GetKey(), key);
    EXPECT_EQ(request.GetUploaId(), upload_id);
    std::string str = request.BuildQueryString();

    EXPECT_EQ(query_string, request.BuildQueryString());
  }

  {
    ListPartsRequest request(
      bucket_name,
      key,
      upload_id,
      max_parts,
      part_number_marker);


    EXPECT_EQ(request.GetBucketName(), bucket_name);
    EXPECT_EQ(request.GetKey(), key);
    EXPECT_EQ(request.GetUploaId(), upload_id);
    std::string str = request.BuildQueryString();

    EXPECT_EQ(query_string, request.BuildQueryString());
  }

  {
    ListPartsRequest request;
    request.SetMaxParts(-1);
    request.SetPartNumberMarker(-1);

    query_string = request.BuildQueryString();
    EXPECT_EQ(query_string, "max-parts=0&part-number-marker=0");
  }
}

}  // namespace oss
