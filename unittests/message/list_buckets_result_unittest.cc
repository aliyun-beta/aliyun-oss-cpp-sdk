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

#include "oss_sdk_cpp/message/list_buckets_result.h"

namespace oss {

static const char* kXmlContent =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<ListAllMyBucketsResult>\n"
  "  <Owner>\n"
  "    <ID>1015294163318850</ID>\n"
  "    <DisplayName>1015294163318850</DisplayName>\n"
  "  </Owner>\n"
  "  <Buckets>\n"
  "    <Bucket>\n"
  "      <CreationDate>2015-11-12T08:38:00.000Z</CreationDate>\n"
  "      <Location>oss-cn-hangzhou</Location>\n"
  "      <Name>bigbanglog1</Name>\n"
  "    </Bucket>\n"
  "  </Buckets>\n"
  "  <Prefix></Prefix>\n"
  "  <Marker></Marker>\n"
  "  <MaxKeys>1</MaxKeys>\n"
  "  <IsTruncated>true</IsTruncated>\n"
  "  <NextMarker>bigbanglog1</NextMarker>\n"
  "</ListAllMyBucketsResult>\n"
  "";

TEST(ListBucketsResult, Normal) {
  ListBucketsResult result;
  bool parse_ok = result.DeserializeFromXml(kXmlContent);
  EXPECT_TRUE(parse_ok);

  EXPECT_EQ(result.GetNextMarker(), "bigbanglog1");
  EXPECT_EQ(result.GetIsTruncated(), true);
  EXPECT_EQ(result.GetMaxKeys(), 1);
  EXPECT_EQ(result.GetMarker(), "");
  EXPECT_EQ(result.GetPrefix(), "");
  EXPECT_EQ(result.GetOwnerId(), "1015294163318850");
  EXPECT_EQ(result.GetOwnerDisplayName(), "1015294163318850");
  EXPECT_EQ(result.GetBuckets().size(), 1u);

  const Bucket& bucket = result.GetBuckets().front();

  EXPECT_EQ(bucket.GetName(), "bigbanglog1");
  EXPECT_EQ(bucket.GetLocation(), "oss-cn-hangzhou");
  EXPECT_EQ(bucket.GetCreationDate(), "2015-11-12T08:38:00.000Z");

  size_t bucket_count = result.GetBuckets().size();
  std::vector<Bucket> buckets_out;
  result.MutableBuckets().swap(buckets_out);
  EXPECT_EQ(buckets_out.size(), bucket_count);
}

TEST(ListBucketsResult, ParseFailed) {
  ListBucketsResult result;
  bool parse_ok = true;
  parse_ok = result.DeserializeFromXml("I am invalid xml text");
  EXPECT_FALSE(parse_ok);
  parse_ok = result.DeserializeFromXml(
               "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Test>ab</Test>\n");
  EXPECT_FALSE(parse_ok);
}

TEST(ListBucketsResult, NoOwnerNode) {
  static const char* kXmlText =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<ListAllMyBucketsResult>abc</ListAllMyBucketsResult>\n";
  ListBucketsResult result;
  bool parse_ok = true;
  parse_ok = result.DeserializeFromXml(kXmlText);
  EXPECT_FALSE(parse_ok);
}

TEST(ListBucketsResult, NoBucketsNode) {
  static const char* kXmlText =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<ListAllMyBucketsResult>\n"
    "  <Owner>\n"
    "    <ID>1015294163318850</ID>\n"
    "    <DisplayName>1015294163318850</DisplayName>\n"
    "  </Owner>\n"
    "</ListAllMyBucketsResult>\n"
    "";
  ListBucketsResult result;
  bool parse_ok = true;
  parse_ok = result.DeserializeFromXml(kXmlText);
  EXPECT_FALSE(parse_ok);
}

}  // namespace oss
