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

#include "oss_sdk_cpp/message/get_bucket_website_result.h"

namespace oss {

static const char* kXmlContent =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<WebsiteConfiguration>\n"
  "  <IndexDocument>\n"
  "    <Suffix>myindex.html</Suffix>\n"
  "  </IndexDocument>\n"
  "  <ErrorDocument>\n"
  "    <Key>my404.html</Key>\n"
  "  </ErrorDocument>\n"
  "</WebsiteConfiguration>\n"
  "";

TEST(GetBucketWebsiteResult, allinone) {
  std::string expected_index_page = "myindex.html";
  std::string expected_error_page = "my404.html";
  {
    GetBucketWebsiteResult result;
    bool parse_ok = result.DeserializeFromXml(kXmlContent);
    EXPECT_TRUE(parse_ok);

    EXPECT_EQ(result.GetIndexPage(), expected_index_page);
    EXPECT_EQ(result.GetErrorPage(), expected_error_page);
  }

  {
    GetBucketWebsiteResult result;
    result.SetIndexPage(expected_index_page);
    result.SetErrorPage(expected_error_page);

    EXPECT_EQ(result.GetIndexPage(), expected_index_page);
    EXPECT_EQ(result.GetErrorPage(), expected_error_page);
  }
}

TEST(GetBucketWebsiteResult, ParseFailed) {
  GetBucketWebsiteResult result;
  bool parse_ok = true;
  parse_ok = result.DeserializeFromXml("I am invalid xml text");
  EXPECT_FALSE(parse_ok);
  parse_ok = result.DeserializeFromXml(
               "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Test>ab</Test>\n");
  EXPECT_FALSE(parse_ok);
}

}  // namespace oss
