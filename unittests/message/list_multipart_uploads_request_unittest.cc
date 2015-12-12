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

#include "oss_sdk_cpp/message/list_multipart_uploads_request.h"

namespace oss {

TEST(ListMultipartUploadsRequest, Basic) {
  std::string bucket_name = "mybucket";
  std::string delimiter = "mydelimiter";
  int max_uploads = 100;
  std::string key_marker = "mykeymarker";
  std::string prefix = "myprefix";
  std::string upload_id_marker = "foo";

  std::string query_string =
    "delimiter=mydelimiter&key-marker=mykeymarker"
    "&max-uploads=100&prefix=myprefix&upload-id-marker=foo";

  {
    ListMultipartUploadsRequest request;
    request.SetBucketName(bucket_name);
    request.SetDelimiter(delimiter);
    request.SetMaxUploads(max_uploads);
    request.SetKeyMarker(key_marker);
    request.SetPrefix(prefix);
    request.SetUploadIdMarker(upload_id_marker);

    StringMap headers;
    request.AddToParameterList(&headers);

    EXPECT_EQ(headers["delimiter"], delimiter);
    EXPECT_EQ(headers["prefix"], prefix);
    EXPECT_EQ(headers["key-marker"], key_marker);
    EXPECT_EQ(headers["max-uploads"], std::to_string(max_uploads));
    EXPECT_EQ(headers["upload-id-marker"], upload_id_marker);
    EXPECT_EQ(request.GetBucketName(), bucket_name);
    EXPECT_EQ(query_string, request.BuildQueryString());
  }

  {
    ListMultipartUploadsRequest request(
      bucket_name,
      delimiter,
      max_uploads,
      key_marker,
      prefix,
      upload_id_marker);

    StringMap headers;
    request.AddToParameterList(&headers);

    EXPECT_EQ(headers["delimiter"], delimiter);
    EXPECT_EQ(headers["prefix"], prefix);
    EXPECT_EQ(headers["key-marker"], key_marker);
    EXPECT_EQ(headers["max-uploads"], std::to_string(max_uploads));
    EXPECT_EQ(headers["upload-id-marker"], upload_id_marker);
    EXPECT_EQ(request.GetBucketName(), bucket_name);
    EXPECT_EQ(query_string, request.BuildQueryString());
  }

  {
    ListMultipartUploadsRequest request;
    request.SetMaxUploads(-1);
    StringMap headers;
    request.AddToParameterList(&headers);

    EXPECT_EQ(headers["max-uploads"], std::to_string(0));
  }
}

}  // namespace oss
