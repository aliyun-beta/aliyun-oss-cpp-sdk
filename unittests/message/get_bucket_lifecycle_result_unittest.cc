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

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/message/get_bucket_lifecycle_result.h"

namespace oss {

static const char* kXmlContent =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<LifecycleConfiguration>\n"
  "  <Rule>\n"
  "    <ID>test1</ID>\n"
  "    <Prefix>filter1</Prefix>\n"
  "    <Status>Enabled</Status>\n"
  "    <Expiration>\n"
  "      <Days>25</Days>\n"
  "    </Expiration>\n"
  "  </Rule>\n"
  "  <Rule>\n"
  "    <ID>test2</ID>\n"
  "    <Prefix>filter2</Prefix>\n"
  "    <Status>Disabled</Status>\n"
  "    <Expiration>\n"
  "      <Date>2015-12-03T00:00:00.000Z</Date>\n"
  "    </Expiration>\n"
  "  </Rule>\n"
  "</LifecycleConfiguration>\n"
  "";

TEST(GetBucketLifecycleResult, Normal) {
  GetBucketLifecycleResult result;
  bool parse_ok = result.DeserializeFromXml(kXmlContent);
  EXPECT_TRUE(parse_ok);
  EXPECT_EQ(result.GetBucketLifecycle().size(), 2u);

  auto lifecycles = result.GetBucketLifecycle();
  {
    auto& lifecycle = lifecycles.front();
    EXPECT_EQ(lifecycle.GetEnabled(), true);
    EXPECT_EQ(lifecycle.GetExpirationDays(), 25);
    EXPECT_EQ(lifecycle.GetId(), "test1");
    EXPECT_EQ(lifecycle.GetPrefix(), "filter1");
  }

  {
    auto& lifecycle = lifecycles.back();
    EXPECT_EQ(lifecycle.GetEnabled(), false);
    EXPECT_EQ(lifecycle.GetExpirationDate(), "2015-12-03T00:00:00.000Z");
    EXPECT_EQ(lifecycle.GetId(), "test2");
    EXPECT_EQ(lifecycle.GetPrefix(), "filter2");
  }
}

TEST(GetBucketLifecycleResult, ParseFailed) {
  GetBucketLifecycleResult result;
  bool parse_ok = result.DeserializeFromXml("I am invalid xml text");
  EXPECT_FALSE(parse_ok);
}

TEST(GetBucketLifecycleResult, XmlNoRoot) {
  const char* kNoRootXml =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<Test>abc</Test>\n";
  GetBucketLifecycleResult result;
  bool parse_ok = result.DeserializeFromXml(kNoRootXml);
  EXPECT_FALSE(parse_ok);
}

}  // namespace oss
