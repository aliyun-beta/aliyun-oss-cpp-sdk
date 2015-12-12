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

#include "oss_sdk_cpp/message/object_metadata.h"
#include "oss_sdk_cpp/utils/http_utils.h"

namespace oss {

TEST(ObjectMetadata, Basic) {
  std::string cache_control = "No-Cache";
  int content_length = 789789899;
  std::string content_type = "image/jpg";
  std::string content_md5 = " ODBGOERFMDMzQTczRUY3NUE3NzA5QzdFNUYzMDQxNEM=";
  std::string content_encoding = "utf-8";
  std::string content_disposition = "form-data; name=\"key\"";
  std::string expiration_time = GmtTime(time(NULL) + 86400 * 30);
  std::string last_modified = GmtTime(time(NULL));
  std::string server_side_encryption = "AES256";

  {
    ObjectMetadata metadata;

    metadata.SetCacheControl(cache_control);
    metadata.SetContentLength(content_length);
    metadata.SetContentType(content_type);
    metadata.SetContentMd5(content_md5);
    metadata.SetContentEncoding(content_encoding);
    metadata.SetContentDisposition(content_disposition);
    metadata.SetExpirationTime(expiration_time);
    metadata.SetLastModified(last_modified);
    metadata.SetServerSideEncryption(server_side_encryption);

    metadata.AddUserHeader("apple", "100");
    metadata.AddUserHeader("orange", "50");

    EXPECT_EQ(metadata.GetCacheControl(), cache_control);
    EXPECT_EQ(metadata.GetContentLength().Value(), content_length);
    EXPECT_EQ(metadata.GetContentType(), content_type);
    EXPECT_EQ(metadata.GetContentMd5(), content_md5);
    EXPECT_EQ(metadata.GetContentEncoding(), content_encoding);
    EXPECT_EQ(metadata.GetContentDisposition(), content_disposition);
    EXPECT_EQ(metadata.GetExpirationTime().Value(), expiration_time);
    EXPECT_EQ(metadata.GetLastModified().Value(), last_modified);
    EXPECT_EQ(metadata.GetServerSideEncryption(), server_side_encryption);

    StringMap headers;
    metadata.AddToParameterList(&headers);

    EXPECT_EQ(headers["x-oss-apple"], "100");
    EXPECT_EQ(headers["x-oss-orange"], "50");
  }

  {
    ObjectMetadata object_metadata;
    std::string initia_content_type = "application/pdf";
    StringMap initial_headers;
    initial_headers["Content-Type"] = initia_content_type;
    object_metadata.SetMetadata(initial_headers);
    EXPECT_EQ(object_metadata.GetContentType(), initia_content_type);
  }

  {
    ObjectMetadata object_meta_data;
    EXPECT_TRUE(object_meta_data.GetContentLength().IsNull());
    EXPECT_TRUE(object_meta_data.GetLastModified().IsNull());
  }
}

}  // namespace oss
