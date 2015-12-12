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

#include "oss_sdk_cpp/message/set_bucket_lifecycle_request.h"

namespace oss {

TEST(SetBucketLifecycleRequest, Basic) {
  std::string bucket_name = "mybucket";
  SetBucketLifecycleRequest request(bucket_name);

  LifeCycleRule rule;
  rule.SetEnabled(true);
  rule.SetId("test1");
  rule.SetPrefix("filter1");
  rule.SetExpirationDays(25);
  request.AddRule(rule);

  LifeCycleRule rule2;
  rule2.SetEnabled(false);
  rule2.SetId("test2");
  rule2.SetPrefix("filter2");
  rule2.SetExpirationDate("2022-10-11T00:00:00.000Z");
  request.AddRule(rule2);

  EXPECT_EQ(request.GetBucketName(), bucket_name);
  request.SetBucketName("123");
  EXPECT_EQ(request.GetBucketName(), "123");

  std::string xml = request.SerializeToXml();
  bool contains;
  contains = xml.find("filter1") != std::string::npos;
  EXPECT_TRUE(contains);

  contains = xml.find("filter2") != std::string::npos;
  EXPECT_TRUE(contains);

  contains = xml.find(rule2.GetExpirationDate()) != std::string::npos;
  EXPECT_TRUE(contains);
}

}  // namespace oss
