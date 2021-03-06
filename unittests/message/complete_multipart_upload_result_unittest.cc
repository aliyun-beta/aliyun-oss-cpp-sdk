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

#include "oss_sdk_cpp/message/complete_multipart_upload_result.h"

namespace oss {

static const char* kXmlContent =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<CompleteMultipartUploadResult"
  "    xmlns=\"http://doc.oss-cn-hangzhou.aliyuncs.com\">"
  "    <Location>http://abc.oss-cn-hangzhou.aliyuncs.com/xyz.data</Location>"
  "    <Bucket>oss-example</Bucket>"
  "    <Key>multipart.data</Key>"
  "    <ETag>B864DB6A936D376F9F8D3ED3BBE540DD-3</ETag>"
  "</CompleteMultipartUploadResult>"
  "\n";

TEST(CompleteMultipartUploadResult, allinone) {
  CompleteMultipartUploadResult result;
  bool parse_ok = result.DeserializeFromXml(kXmlContent);
  EXPECT_TRUE(parse_ok);

  std::string bucket_name = "oss-example";
  std::string key = "multipart.data";
  std::string etag = "B864DB6A936D376F9F8D3ED3BBE540DD-3";
  std::string location =
    "http://abc.oss-cn-hangzhou.aliyuncs.com/xyz.data";

  EXPECT_EQ(bucket_name, result.GetBucketName());
  EXPECT_EQ(key, result.GetKey());
  EXPECT_EQ(location, result.GetLocation());
  EXPECT_EQ(etag, result.GetEtag());
}

TEST(CompleteMultipartUploadResult, ParseFailed) {
  CompleteMultipartUploadResult result;
  bool parse_ok = true;
  parse_ok = result.DeserializeFromXml("I am invalid xml text");
  EXPECT_FALSE(parse_ok);
  parse_ok = result.DeserializeFromXml(
               "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Test>ab</Test>\n");
  EXPECT_FALSE(parse_ok);
}

}  // namespace oss
