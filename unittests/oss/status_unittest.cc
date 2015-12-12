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
#include "oss_sdk_cpp/oss/oss_status.h"
#include "oss_sdk_cpp/oss/oss_error_code.h"

namespace oss {

TEST(Status, Basic) {
  Status status(oss_error_code::kAccessDenied);
  EXPECT_FALSE(status.Ok());
  EXPECT_EQ(status.GetOssException().GetCode(), "");

  status.SetErrorCode(oss_error_code::kBucketAlreadyExists);
  EXPECT_EQ(status.ErrorCode(), oss_error_code::kBucketAlreadyExists);

  status.SetHttpStausCode(200);
  EXPECT_EQ(status.HttpStausCode(), 200);

  // move constructor.
  Status status2 = std::move(status);
  EXPECT_FALSE(status2.Ok());
  EXPECT_EQ(status2.HttpStausCode(), 200);

  // move assignment.
  status.SetErrorCode(oss_error_code::kBucketAlreadyExists);
  status.SetHttpStausCode(200);

  Status status3;
  status3 = std::move(status);
  EXPECT_FALSE(status3.Ok());
  EXPECT_EQ(status3.HttpStausCode(), 200);
}

}  // namespace oss
