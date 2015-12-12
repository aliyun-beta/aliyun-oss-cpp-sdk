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

const char* kXmlText =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<Error>\n"
  "  <Code>NoSuchBucket</Code>\n"
  "  <Message>bucket not exist, bucket: wuhawukawuha1567</Message>\n"
  "  <RequestId>5653F85050A11BC338F8E2D6</RequestId>\n"
  "  <HostId>wuhawukawuha1567.oss-cn-hangzhou.aliyuncs.com</HostId>\n"
  "</Error>\n"
  "";

namespace oss {

TEST(OssException, Basic) {
  const std::string code = "NoSuchBucket";
  const std::string message = "bucket not exist, bucket: wuhawukawuha1567";
  const std::string request_id = "5653F85050A11BC338F8E2D6";
  const std::string host_id = "wuhawukawuha1567.oss-cn-hangzhou.aliyuncs.com";

  {
    OssException exp;
    EXPECT_TRUE(exp.FromXml(kXmlText));
    EXPECT_EQ(exp.GetCode(), code);
    EXPECT_EQ(exp.GetMessage(), message);
    EXPECT_EQ(exp.GetRequestId(), request_id);
    EXPECT_EQ(exp.GetHostId(), host_id);
  }

  {
    OssException exp;
    exp.SetCode(code);
    exp.SetMessage(message);
    exp.SetRequestId(request_id);
    exp.SetHostId(host_id);

    EXPECT_EQ(exp.GetCode(), code);
    EXPECT_EQ(exp.GetMessage(), message);
    EXPECT_EQ(exp.GetRequestId(), request_id);
    EXPECT_EQ(exp.GetHostId(), host_id);
  }
}

TEST(OssException, NoCode) {
  const char* kXml =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<Error>\n"
    "  123\n"
    "</Error>\n"
    "";
  OssException exp;
  EXPECT_FALSE(exp.FromXml(kXml));
}

TEST(OssException, NoMessage) {
  const char* kXml =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<Error>\n"
    "  <Code>NoSuchBucket</Code>\n"
    "</Error>\n"
    "";
  OssException exp;
  EXPECT_FALSE(exp.FromXml(kXml));
}

TEST(OssException, NoRequestId) {
  const char* kXml =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<Error>\n"
    "  <Code>NoSuchBucket</Code>\n"
    "  <Message>bucket not exist, bucket: wuhawukawuha1567</Message>\n"
    "</Error>\n"
    "";
  OssException exp;
  EXPECT_FALSE(exp.FromXml(kXml));
}

TEST(OssException, NoHostId) {
  const char* kXml =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<Error>\n"
    "  <Code>NoSuchBucket</Code>\n"
    "  <Message>bucket not exist, bucket: wuhawukawuha1567</Message>\n"
    "  <RequestId>5653F85050A11BC338F8E2D6</RequestId>\n"
    "</Error>\n"
    "";
  OssException exp;
  EXPECT_FALSE(exp.FromXml(kXml));
}

}  // namespace oss
