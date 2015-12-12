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

#include "oss_sdk_cpp/message/bucket_cors.h"

namespace oss {

TEST(CorsRule, Basic) {
  if (1) {
    CorsRule rule;

    StringList allowed_origins;
    allowed_origins.push_back("http://www.google.com");
    allowed_origins.push_back("http://www.facebook.com");
    allowed_origins.push_back("http://www.aliyun.com");
    for (auto& str : allowed_origins) {
      rule.AddAllowedOrigin(str);
    }

    StringList allowed_methods;
    allowed_methods.push_back("POST");
    allowed_methods.push_back("GET");
    for (auto& str : allowed_methods) {
      rule.AddAllowedMethod(str);
    }

    StringList allowed_headers;
    allowed_headers.push_back("a");
    allowed_headers.push_back("b");
    allowed_headers.push_back("c");

    for (auto& str : allowed_headers) {
      rule.AddAllowedHeader(str);
    }

    StringList expose_headers;
    expose_headers.push_back("x-oss-test1");
    expose_headers.push_back("x-oss-test2");
    for (auto& str : expose_headers) {
      rule.AddExposeHeader(str);
    }

    int seconds = 200;
    rule.SetMaxAgeSeconds(seconds);

    EXPECT_EQ(allowed_origins, rule.GetAllowedOrigins());
    EXPECT_EQ(allowed_methods, rule.GetAllowedMethods());
    EXPECT_EQ(allowed_headers, rule.GetAllowedHeaders());
    EXPECT_EQ(expose_headers, rule.GetExposeHeaders());
    EXPECT_EQ(seconds, rule.GetMaxAgeSeconds());
  }
}

}  // namespace oss
