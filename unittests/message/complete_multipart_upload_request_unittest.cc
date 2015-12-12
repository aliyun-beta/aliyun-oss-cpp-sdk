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

#include "oss_sdk_cpp/message/complete_multipart_upload_request.h"

namespace oss {

TEST(CompleteMultipartUploadrequest, Basic) {
  std::string bucket_name = "mybucket";
  std::string key = "mykey";
  std::string upload_id = "858089EC0A36427581779DC7659E1EBD";
  // uploadId, I is uppercase.
  std::string query_string = "mykey?uploadId=858089EC0A36427581779DC7659E1EBD";
  std::list<PartEtag> etag_list = {
    { "2C0FC53DB041AB32EC663867DF02EDE3", 1 },
    { "24196B4D8EAB6F08A4B141D3D594531C", 2 },
    { "4ADAD0363F0B0F612FD28B15A51DDD80", 3 }
  };

  // constructor1
  {
    CompleteMultipartUploadrequest request(bucket_name, key, upload_id);

    EXPECT_EQ(bucket_name, request.GetBucketName());
    EXPECT_EQ(key, request.GetKey());
    EXPECT_EQ(upload_id, request.GetUploadId());
    EXPECT_EQ(query_string, request.BuildQueryString());
  }

  // constructor2
  {
    CompleteMultipartUploadrequest request(bucket_name,
                                           key, upload_id, etag_list);

    EXPECT_EQ(bucket_name, request.GetBucketName());
    EXPECT_EQ(key, request.GetKey());
    EXPECT_EQ(etag_list.size(), request.GetEtagList().size());
    EXPECT_EQ(upload_id, request.GetUploadId());
    EXPECT_EQ(query_string, request.BuildQueryString());

    std::string xml = request.SerializeToXml();
    EXPECT_TRUE(xml.find("2C0FC53DB041AB32EC663867DF02EDE3")
                != std::string::npos);

    size_t count = request.GetEtagList().size();
    std::list<PartEtag> etags;
    request.MutableEtagList().swap(etags);
    EXPECT_EQ(etags.size(), count);
  }

  {
    CompleteMultipartUploadrequest request;
    EXPECT_TRUE(request.GetBucketName().empty());
    EXPECT_TRUE(request.GetKey().empty());
    EXPECT_TRUE(request.GetEtagList().empty());

    request.SetBucketName(bucket_name);
    EXPECT_EQ(bucket_name, request.GetBucketName());

    request.SetKey(key);
    EXPECT_EQ(key, request.GetKey());

    request.SetUploadId(upload_id);
    EXPECT_EQ(upload_id, request.GetUploadId());

    request.SetEtagList(etag_list);
    EXPECT_EQ(etag_list.size(), request.GetEtagList().size());
    EXPECT_EQ(query_string, request.BuildQueryString());
  }
}

}  // namespace oss
