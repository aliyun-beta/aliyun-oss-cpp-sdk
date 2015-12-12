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

#include "oss_sdk_cpp/message/list_parts_result.h"

namespace oss {

static const char* kXmlContent =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<ListPartsResult>\n"
  "  <Bucket>wuhawukawuha12</Bucket>\n"
  "  <Key>niu.c</Key>\n"
  "  <UploadId>627213BC81394969B70221F09C2032F7</UploadId>\n"
  "  <StorageClass>Standard</StorageClass>\n"
  "  <PartNumberMarker>0</PartNumberMarker>\n"
  "  <NextPartNumberMarker>2</NextPartNumberMarker>\n"
  "  <MaxParts>2</MaxParts>\n"
  "  <IsTruncated>true</IsTruncated>\n"
  "  <Part>\n"
  "    <PartNumber>1</PartNumber>\n"
  "    <LastModified>2015-11-23T05:53:30.000Z</LastModified>\n"
  "    <ETag>\"2C0FC53DB041AB32EC663867DF02EDE3\"</ETag>\n"
  "    <Size>102400</Size>\n"
  "  </Part>\n"
  "  <Part>\n"
  "    <PartNumber>2</PartNumber>\n"
  "    <LastModified>2015-11-23T05:53:30.000Z</LastModified>\n"
  "    <ETag>\"24196B4D8EAB6F08A4B141D3D594531C\"</ETag>\n"
  "    <Size>102400</Size>\n"
  "  </Part>\n"
  "</ListPartsResult>\n"
  "";

TEST(ListPartsResult, allinone) {
  ListPartsResult result;
  bool parse_ok = result.DeserializeFromXml(kXmlContent);
  EXPECT_TRUE(parse_ok);

  EXPECT_EQ(result.GetBucketName(), "wuhawukawuha12");
  EXPECT_EQ(result.GetKey(), "niu.c");
  EXPECT_EQ(result.GetUploadId(), "627213BC81394969B70221F09C2032F7");
  EXPECT_EQ(result.GetStorageClass(), "Standard");
  EXPECT_EQ(result.GetPartNumberMarker(), 0);
  EXPECT_EQ(result.GetNextPartNumberMarker(), 2);
  EXPECT_EQ(result.GetMaxParts(), 2);
  EXPECT_EQ(result.GetIsTruncated(), true);

  auto& parts = result.GetParts();
  auto& part = parts.front();

  EXPECT_EQ(parts.size(), 2u);
  EXPECT_EQ(part.GetPartNumber(), 1);
  EXPECT_EQ(part.GetLastModified(), "2015-11-23T05:53:30.000Z");
  EXPECT_EQ(part.GetEtag(), "\"2C0FC53DB041AB32EC663867DF02EDE3\"");
  EXPECT_EQ(part.GetSize(), 102400u);
}

TEST(ListPartsResult, ParseFailed) {
  ListPartsResult result;
  bool parse_ok = true;
  parse_ok = result.DeserializeFromXml("I am invalid xml text");
  EXPECT_FALSE(parse_ok);
  parse_ok = result.DeserializeFromXml(
               "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Test>ab</Test>\n");
  EXPECT_FALSE(parse_ok);
}

}  // namespace oss
