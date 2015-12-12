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

#include "oss_sdk_cpp/message/set_bucket_referer_request.h"

namespace oss {

TEST(SetBucketRefererRequest, Basic) {
  std::string bucket_name = "mybucket";

  StringList referers;
  referers.push_back("http://www.yahoo.com");
  referers.push_back("http://www.microsoft.com");
  referers.push_back("http://www.msn.com");
  referers.push_back("http://www.aliyun.com");
  referers.push_back("http://www.*.com");
  referers.push_back("http://www.?.aliyuncs.com");

  SetBucketRefererRequest request(bucket_name);
  for (auto& referer : referers) {
    request.AddReferer(referer);
  }

  EXPECT_EQ(referers, request.GetBucketReferer());
  EXPECT_EQ(bucket_name, request.GetBucketName());
  EXPECT_EQ(true, request.GetAllowEmpty());
  request.SetAllowEmpty(false);
  EXPECT_FALSE(request.GetAllowEmpty());

  std::string xml = request.SerializeToXml();
  EXPECT_TRUE(xml.find("www.yahoo.com") != std::string::npos);
  EXPECT_TRUE(xml.find("www.msn.com") != std::string::npos);
  EXPECT_TRUE(xml.find("www.aliyun.com") != std::string::npos);

  {
    SetBucketRefererRequest req;
    EXPECT_TRUE(req.GetBucketName().empty());
    EXPECT_TRUE(req.GetAllowEmpty());
  }

  {
    SetBucketRefererRequest req;
    req.SetBucketName(bucket_name);
    req.SetBucketReferer(referers);

    EXPECT_EQ(bucket_name, req.GetBucketName());
    EXPECT_EQ(referers, req.GetBucketReferer());
  }
}

}  // namespace oss
