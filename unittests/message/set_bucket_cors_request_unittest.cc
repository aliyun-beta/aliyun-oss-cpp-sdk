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

#include "oss_sdk_cpp/message/set_bucket_cors_request.h"

namespace oss {

TEST(SetBucketCorsRequest, Basic) {
  std::string bucket_name = "mybucket";
  {
    SetBucketCorsRequest request(bucket_name);

    {
      CorsRule rule;
      rule.AddAllowedOrigin("http://www.a.com");
      rule.AddAllowedMethod("POST");
      rule.AddAllowedHeader("*");
      rule.AddExposeHeader("x-oss-test");
      rule.SetMaxAgeSeconds(300);

      request.AddRule(rule);
    }

    {
      CorsRule* rule = request.AddRule();
      rule->AddAllowedOrigin("http://www.google.com");
      rule->AddAllowedOrigin("http://www.facebook.com");
      rule->AddAllowedOrigin("http://www.aliyun.com");

      rule->AddAllowedMethod("POST");
      rule->AddAllowedMethod("GET");
      rule->AddAllowedHeader("a");
      rule->AddAllowedHeader("b");
      rule->AddAllowedHeader("c");

      rule->AddExposeHeader("x-oss-test1");
      rule->AddExposeHeader("x-oss-test2");

      rule->SetMaxAgeSeconds(200);
    }

    EXPECT_EQ(request.GetRules().size(), 2u);
    EXPECT_EQ(request.GetBucketName(), bucket_name);
    request.SetBucketName("123");
    EXPECT_EQ(request.GetBucketName(), "123");

    std::string xml = request.SerializeToXml();
    bool contains = xml.find("http://www.facebook.com") != std::string::npos;
    EXPECT_TRUE(contains);
  }

  {
    SetBucketCorsRequest request(bucket_name);
    CorsRule rule;

    rule.AddAllowedOrigin("http://www.a.com");
    rule.AddAllowedMethod("POST");
    rule.AddAllowedHeader("*");
    rule.AddExposeHeader("x-oss-test");
    rule.SetMaxAgeSeconds(300);

    std::list<CorsRule> rules;
    rules.push_back(rule);
    EXPECT_EQ(request.GetRules().size(), 0u);
    request.SetRules(rules);
    EXPECT_EQ(request.GetRules().size(), 1u);
  }
}

}  // namespace oss
