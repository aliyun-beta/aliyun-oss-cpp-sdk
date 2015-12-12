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
#include "oss_sdk_cpp/message/get_bucket_cors_result.h"

namespace oss {

static const char* kXmlContent =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<CORSConfiguration>\n"
  "  <CORSRule>\n"
  "    <AllowedOrigin>http://www.a.com</AllowedOrigin>\n"
  "    <AllowedMethod>POST</AllowedMethod>\n"
  "    <AllowedHeader>*</AllowedHeader>\n"
  "    <ExposeHeader>x-oss-test</ExposeHeader>\n"
  "    <MaxAgeSeconds>300</MaxAgeSeconds>\n"
  "  </CORSRule>\n"
  "  <CORSRule>\n"
  "    <AllowedOrigin>http://www.google.com</AllowedOrigin>\n"
  "    <AllowedOrigin>http://www.facebook.com</AllowedOrigin>\n"
  "    <AllowedOrigin>http://www.aliyun.com</AllowedOrigin>\n"
  "    <AllowedMethod>POST</AllowedMethod>\n"
  "    <AllowedMethod>GET</AllowedMethod>\n"
  "    <AllowedHeader>a</AllowedHeader>\n"
  "    <AllowedHeader>b</AllowedHeader>\n"
  "    <AllowedHeader>c</AllowedHeader>\n"
  "    <ExposeHeader>x-oss-test1</ExposeHeader>\n"
  "    <ExposeHeader>x-oss-test2</ExposeHeader>\n"
  "    <MaxAgeSeconds>200</MaxAgeSeconds>\n"
  "  </CORSRule>\n"
  "</CORSConfiguration>\n";

TEST(GetBucketCorsResult, Normal) {
  GetBucketCorsResult result;
  bool parse_ok = result.DeserializeFromXml(kXmlContent);
  EXPECT_TRUE(parse_ok);
  EXPECT_EQ(result.GetRules().size(), 2u);

  auto rules = result.GetRules();
  {
    auto& rule = rules.front();
    EXPECT_TRUE(Contains(rule.GetAllowedOrigins(), "http://www.a.com"));
    EXPECT_TRUE(Contains(rule.GetAllowedMethods(), "POST"));
    EXPECT_TRUE(Contains(rule.GetAllowedHeaders(), "*"));
    EXPECT_TRUE(Contains(rule.GetExposeHeaders(), "x-oss-test"));
    EXPECT_EQ(rule.GetMaxAgeSeconds(), 300);
  }

  {
    auto& rule = rules.back();
    EXPECT_TRUE(Contains(rule.GetAllowedOrigins(), "http://www.google.com"));
    EXPECT_FALSE(Contains(rule.GetAllowedOrigins(), "http://www.alibaba.com"));
    EXPECT_TRUE(Contains(rule.GetAllowedMethods(), "GET"));
    EXPECT_FALSE(Contains(rule.GetAllowedMethods(), "PUT"));
    EXPECT_TRUE(Contains(rule.GetAllowedHeaders(), "a"));
    EXPECT_TRUE(Contains(rule.GetAllowedHeaders(), "b"));
    EXPECT_TRUE(Contains(rule.GetExposeHeaders(), "x-oss-test1"));
    EXPECT_EQ(rule.GetMaxAgeSeconds(), 200);
  }
}


TEST(GetBucketCorsResult, ParseFailed) {
  GetBucketCorsResult result;
  bool parse_ok = result.DeserializeFromXml("I am invalid xml text");
  EXPECT_FALSE(parse_ok);
}

TEST(GetBucketCorsResult, XmlNoRoot) {
  const char* kNoRootXml =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<Test>abc</Test>\n";
  GetBucketCorsResult result;
  bool parse_ok = result.DeserializeFromXml(kNoRootXml);
  EXPECT_FALSE(parse_ok);
}

}  // namespace oss
