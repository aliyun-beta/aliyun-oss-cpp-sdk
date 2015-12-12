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

#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/message/get_bucket_referer_result.h"

namespace oss {

static const char* kXmlContent =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<RefererConfiguration>\n"
  "  <AllowEmptyReferer>true</AllowEmptyReferer>\n"
  "  <RefererList>\n"
  "    <Referer>http://www.*.com</Referer>\n"
  "    <Referer>http://www.?.aliyuncs.com</Referer>\n"
  "    <Referer>http://www.aliyun.com</Referer>\n"
  "    <Referer>http://www.microsoft.com</Referer>\n"
  "    <Referer>http://www.msn.com</Referer>\n"
  "    <Referer>http://www.yahoo.com</Referer>\n"
  "  </RefererList>\n"
  "</RefererConfiguration>\n"
  "";

TEST(GetBucketRefererResult, allinone) {
  GetBucketRefererResult result;
  bool parse_ok = result.DeserializeFromXml(kXmlContent);
  EXPECT_TRUE(parse_ok);

  EXPECT_TRUE(result.GetAllowEmpty());
  auto referers = result.GetBucketReferer();
  EXPECT_TRUE(Contains(referers, "http://www.?.aliyuncs.com"));
  EXPECT_TRUE(Contains(referers, "http://www.microsoft.com"));
  EXPECT_TRUE(Contains(referers, "http://www.aliyun.com"));
  EXPECT_FALSE(Contains(referers, "http://www.alibaba.com"));
}

TEST(GetBucketRefererResult, ParseFailed) {
  GetBucketRefererResult result;
  bool parse_ok = true;
  parse_ok = result.DeserializeFromXml("I am invalid xml text");
  EXPECT_FALSE(parse_ok);
  parse_ok = result.DeserializeFromXml(
               "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Test>ab</Test>\n");
  EXPECT_FALSE(parse_ok);
}

TEST(GetBucketRefererResult, NoAllowEmpty) {
  static const char* kXmlText =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<RefererConfiguration>123</RefererConfiguration>\n";
  GetBucketRefererResult result;
  bool parse_ok = true;
  parse_ok = result.DeserializeFromXml(kXmlText);
  EXPECT_FALSE(parse_ok);
}

TEST(GetBucketRefererResult, NoRefererNode) {
  static const char* kXmlText =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<RefererConfiguration>\n"
    "  <AllowEmptyReferer>true</AllowEmptyReferer>\n"
    "</RefererConfiguration>\n"
    "";
  GetBucketRefererResult result;
  bool parse_ok = true;
  parse_ok = result.DeserializeFromXml(kXmlText);
  EXPECT_FALSE(parse_ok);
}

}  // namespace oss
