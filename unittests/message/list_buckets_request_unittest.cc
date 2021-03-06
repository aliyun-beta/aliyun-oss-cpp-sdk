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

#include "oss_sdk_cpp/message/list_buckets_request.h"

namespace oss {

TEST(ListBucketsRequest, Basic) {
  std::string prefix = "abc";
  std::string marker = "foo";
  int max_keys = 100;

  {
    ListBucketsRequest request;
    request.SetPrefix(prefix);
    request.SetMarker(marker);
    request.SetMaxKeys(max_keys);

    StringMap headers;
    request.AddToParameterList(&headers);

    EXPECT_EQ(headers["prefix"], prefix);
    EXPECT_EQ(headers["marker"], marker);
    EXPECT_EQ(headers["max-keys"], std::to_string(max_keys));
  }

  {
    ListBucketsRequest request(prefix, marker, max_keys);

    StringMap headers;
    request.AddToParameterList(&headers);

    EXPECT_EQ(headers["prefix"], prefix);
    EXPECT_EQ(headers["marker"], marker);
    EXPECT_EQ(headers["max-keys"], std::to_string(max_keys));
  }

  {
    ListBucketsRequest request;
    request.SetMaxKeys(-1);

    StringMap headers;
    request.AddToParameterList(&headers);

    EXPECT_EQ(headers["max-keys"], std::to_string(0));
  }
}

}  // namespace oss
