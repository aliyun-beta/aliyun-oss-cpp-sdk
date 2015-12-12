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

#include "oss_sdk_cpp/message/lifecycle_rule.h"

namespace oss {

TEST(LifeCycleRule, Basic) {
  LifeCycleRule rule;
  rule.SetEnabled(true);
  rule.SetId("test1");
  rule.SetPrefix("filter1");
  rule.SetExpirationDays(25);
  rule.SetExpirationDate("2015-12-03T00:00:00.000Z");

  EXPECT_TRUE(rule.GetEnabled());
  EXPECT_EQ(rule.GetId(), "test1");
  EXPECT_EQ(rule.GetPrefix(), "filter1");
  EXPECT_EQ(rule.GetExpirationDays(), 25);
  EXPECT_EQ(rule.GetExpirationDate(), "2015-12-03T00:00:00.000Z");
}

}  // namespace oss
