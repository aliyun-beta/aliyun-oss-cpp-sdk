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

#include "oss_sdk_cpp/message/list_objects_result.h"

namespace oss {

static const char* kXmlContent =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<ListBucketResult>\n"
  "  <Name>wuhawukawuha12</Name>\n"
  "  <Prefix></Prefix>\n"
  "  <Marker></Marker>\n"
  "  <MaxKeys>100</MaxKeys>\n"
  "  <Delimiter></Delimiter>\n"
  "  <IsTruncated>false</IsTruncated>\n"
  "  <Contents>\n"
  "    <Key>alwaysexists.txt</Key>\n"
  "    <LastModified>2015-11-23T05:02:46.000Z</LastModified>\n"
  "    <ETag>\"407ABFFD639CDC0D8D0EC42DE7AEBD5F\"</ETag>\n"
  "    <Type>Normal</Type>\n"
  "    <Size>234593</Size>\n"
  "    <StorageClass>Standard</StorageClass>\n"
  "    <Owner>\n"
  "      <ID>1015294163318850</ID>\n"
  "      <DisplayName>1015294163318850</DisplayName>\n"
  "    </Owner>\n"
  "  </Contents>\n"
  "  <Contents>\n"
  "    <Key>bar.txt</Key>\n"
  "    <LastModified>2015-11-23T05:02:46.000Z</LastModified>\n"
  "    <ETag>\"205F9F37B71D20957042D251A8DD0269\"</ETag>\n"
  "    <Type>Normal</Type>\n"
  "    <Size>12</Size>\n"
  "    <StorageClass>Standard</StorageClass>\n"
  "    <Owner>\n"
  "      <ID>1015294163318850</ID>\n"
  "      <DisplayName>1015294163318850</DisplayName>\n"
  "    </Owner>\n"
  "  </Contents>\n"
  "  <CommonPrefixes>\n"
  "    <Prefix>documents/2014/Sunday/</Prefix>\n"
  "  </CommonPrefixes>\n"
  "  <CommonPrefixes>\n"
  "    <Prefix>documents/2015/Friday/</Prefix>\n"
  "  </CommonPrefixes>"
  "</ListBucketResult>\n"
  "";

TEST(ListObjectsResult, allinone) {
  ListObjectsResult result;
  bool parse_ok = result.DeserializeFromXml(kXmlContent);
  EXPECT_TRUE(parse_ok);

  EXPECT_EQ(result.GetBucketName(), "wuhawukawuha12");
  EXPECT_EQ(result.GetPrefix(), "");
  EXPECT_EQ(result.GetMarker(), "");
  EXPECT_EQ(result.GetMaxKeys(), 100);
  EXPECT_EQ(result.GetDelimiter(), "");
  EXPECT_EQ(result.GetIsTruncated(), false);
  EXPECT_EQ(result.GetNextMarker(), "");
  EXPECT_EQ(result.MutableContents().size(), 2u);
  EXPECT_EQ(result.GetCommonPrefixes().size(), 2u);


  auto& contents = result.GetContents();
  auto& content = contents.front();

  EXPECT_EQ(contents.size(), 2u);
  EXPECT_EQ(content.GetKey(), "alwaysexists.txt");
  EXPECT_EQ(content.GetLastModified(), "2015-11-23T05:02:46.000Z");
  EXPECT_EQ(content.GetEtag(), "\"407ABFFD639CDC0D8D0EC42DE7AEBD5F\"");
  EXPECT_EQ(content.GetType(), "Normal");
  EXPECT_EQ(content.GetSize(), 234593u);
  EXPECT_EQ(content.GetStorageClass(), "Standard");
  EXPECT_EQ(content.GetOwnerId(), "1015294163318850");
  EXPECT_EQ(content.GetOwnerDisplayName(), "1015294163318850");
}

TEST(ListObjectsResult, ParseFailed) {
  ListObjectsResult result;
  bool parse_ok = true;
  parse_ok = result.DeserializeFromXml("I am invalid xml text");
  EXPECT_FALSE(parse_ok);
  parse_ok = result.DeserializeFromXml(
               "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Test>ab</Test>\n");
  EXPECT_FALSE(parse_ok);
}

}  // namespace oss
