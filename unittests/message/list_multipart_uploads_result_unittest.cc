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

#include "oss_sdk_cpp/message/list_multipart_uploads_result.h"

namespace oss {

static const char* kXmlContent =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<ListMultipartUploadsResult>\n"
"  <Bucket>wuhawukawuha12</Bucket>\n"
"  <KeyMarker></KeyMarker>\n"
"  <UploadIdMarker></UploadIdMarker>\n"
"  <NextKeyMarker>temp_part</NextKeyMarker>\n"
"  <NextUploadIdMarker>CD8FBE77132446FCA1C7B479B85AE96D</NextUploadIdMarker>\n"
"  <Delimiter></Delimiter>\n"
"  <Prefix></Prefix>\n"
"  <MaxUploads>1000</MaxUploads>\n"
"  <IsTruncated>false</IsTruncated>\n"
"  <Upload>\n"
"    <Key>temp_part</Key>\n"
"    <UploadId>379AAA7677554387AA6624A3E88729AB</UploadId>\n"
"    <StorageClass>Standard</StorageClass>\n"
"    <Initiated>2015-11-23T04:35:36.000Z</Initiated>\n"
"  </Upload>\n"
"  <Upload>\n"
"    <Key>temp_part</Key>\n"
"    <UploadId>61B565C33F7542FAA44E94C8F2AD746F</UploadId>\n"
"    <StorageClass>Standard</StorageClass>\n"
"    <Initiated>2015-11-23T04:35:36.000Z</Initiated>\n"
"  </Upload>\n"
"  <Upload>\n"
"    <Key>temp_part</Key>\n"
"    <UploadId>9B5751FA7DC04477A3EE7C2B66CFE08E</UploadId>\n"
"    <StorageClass>Standard</StorageClass>\n"
"    <Initiated>2015-11-23T04:35:36.000Z</Initiated>\n"
"  </Upload>\n"
"  <Upload>\n"
"    <Key>temp_part</Key>\n"
"    <UploadId>9EF509E750B646E6B9B0925A2B3C544D</UploadId>\n"
"    <StorageClass>Standard</StorageClass>\n"
"    <Initiated>2015-11-23T04:35:36.000Z</Initiated>\n"
"  </Upload>\n"
"  <Upload>\n"
"    <Key>temp_part</Key>\n"
"    <UploadId>CD8FBE77132446FCA1C7B479B85AE96D</UploadId>\n"
"    <StorageClass>Standard</StorageClass>\n"
"    <Initiated>2015-11-23T04:35:36.000Z</Initiated>\n"
"  </Upload>\n"
"</ListMultipartUploadsResult>\n"
"";

TEST(ListMultipartUploadsResult, allinone) {
  ListMultipartUploadsResult result;
  bool parse_ok = result.DeserializeFromXml(kXmlContent);
  EXPECT_TRUE(parse_ok);

  EXPECT_EQ(result.GetBucketName(), "wuhawukawuha12");
  EXPECT_EQ(result.GetKeyMarker(), "");
  EXPECT_EQ(result.GetUploadIdMarker(), "");
  EXPECT_EQ(result.GetNextKeyMarker(), "temp_part");
  EXPECT_EQ(result.GetNextUploadIdMarker(), "CD8FBE77132446FCA1C7B479B85AE96D");
  EXPECT_EQ(result.GetDelimiter(), "");
  EXPECT_EQ(result.GetPrefix(), "");
  EXPECT_EQ(result.GetMaxUploads(), 1000);
  EXPECT_EQ(result.GetIsTruncated(), false);

  auto& uploads = result.GetMultipartUpload();
  auto& upload = uploads.front();

  EXPECT_EQ(uploads.size(), 5u);
  EXPECT_EQ(upload.GetKey(), "temp_part");
  EXPECT_EQ(upload.GetUploadId(), "379AAA7677554387AA6624A3E88729AB");
  EXPECT_EQ(upload.GetInitiated(), "2015-11-23T04:35:36.000Z");
}

TEST(ListMultipartUploadsResult, ParseFailed) {
  ListMultipartUploadsResult result;
  bool parse_ok = result.DeserializeFromXml("I am invalid xml text");
  EXPECT_FALSE(parse_ok);
}

TEST(ListMultipartUploadsResult, XmlNoRoot) {
  const char* kNoRootXml =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<Test>abc</Test>\n";
  ListMultipartUploadsResult result;
  bool parse_ok = result.DeserializeFromXml(kNoRootXml);
  EXPECT_FALSE(parse_ok);
}

}  // namespace oss
