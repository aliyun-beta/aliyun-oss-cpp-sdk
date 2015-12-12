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

#include "oss_sdk_cpp/message/initiate_multipart_upload_result.h"

namespace oss {

static const char* kXmlContent =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<InitiateMultipartUploadResult>\n"
  "  <Bucket>wuhawukawuha12</Bucket>\n"
  "  <Key>niu.c</Key>\n"
  "  <UploadId>F2CD3600C4B3442EBF77D69630D74A6C</UploadId>\n"
  "</InitiateMultipartUploadResult>\n"
  "";

TEST(InitiateMultipartUploadResult, allinone) {
  InitiateMultipartUploadResult result;
  bool parse_ok = result.DeserializeFromXml(kXmlContent);
  EXPECT_TRUE(parse_ok);

  EXPECT_EQ(result.GetBucketName(), "wuhawukawuha12");
  EXPECT_EQ(result.GetKey(), "niu.c");
  EXPECT_EQ(result.GetUploadId(), "F2CD3600C4B3442EBF77D69630D74A6C");
}

TEST(InitiateMultipartUploadResult, ParseFailed) {
  InitiateMultipartUploadResult result;
  bool parse_ok = true;
  parse_ok = result.DeserializeFromXml("I am invalid xml text");
  EXPECT_FALSE(parse_ok);
  parse_ok = result.DeserializeFromXml(
               "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Test>ab</Test>\n");
  EXPECT_FALSE(parse_ok);
}

}  // namespace oss
