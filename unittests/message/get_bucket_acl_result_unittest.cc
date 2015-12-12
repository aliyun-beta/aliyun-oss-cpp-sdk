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

#include "oss_sdk_cpp/message/get_bucket_acl_result.h"

namespace oss {

static const char* kXmlContent =
  "<?xml version=\"1.0\" ?>\n"
  "<AccessControlPolicy>\n"
  "    <Owner>\n"
  "        <ID>00220120222</ID>\n"
  "        <DisplayName>user_example</DisplayName>\n"
  "    </Owner>\n"
  "    <AccessControlList>\n"
  "        <Grant>public-read</Grant>\n"
  "    </AccessControlList>\n"
  "</AccessControlPolicy>"
  "\n";

TEST(GetBucketAclResult, allinone) {
  GetBucketAclResult result;
  bool parse_ok = result.DeserializeFromXml(kXmlContent);
  EXPECT_TRUE(parse_ok);

  EXPECT_EQ(result.GetOwnerDisplayName(), "user_example");
  EXPECT_EQ(result.GetOwnerId(), "00220120222");
  EXPECT_EQ(result.GetAcl(), "public-read");
}

TEST(GetBucketAclResult, ParseFailed) {
  GetBucketAclResult result;
  bool parse_ok = true;
  parse_ok = result.DeserializeFromXml("I am invalid xml text");
  EXPECT_FALSE(parse_ok);
  parse_ok = result.DeserializeFromXml(
               "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Test>ab</Test>\n");
  EXPECT_FALSE(parse_ok);
}

}  // namespace oss
