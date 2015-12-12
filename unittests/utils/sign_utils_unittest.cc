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
#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/utils/sign_utils.h"

namespace oss {

TEST(BuildOssAuthorization, Basic) {
  const std::string access_key_secret = "mykey";
  const std::string access_key_id = "myid";
  const std::string http_method = "POST";
  const std::string gmt_datetime = "Sun, 22 Nov 2015 02:29:40 GMT";
  const std::string resource = "/mybucket2365/?website";
  StringMap headers;
  headers["Content-MD5"] = "OWI5NzIwNTM5NzhkNWM4MDFlOTkxN2Q2YWNkYmE1ZDE=";
  const std::string expected = "OSS myid:7fe00XhirYEuEHUZLLas7saQmLM=";
  std::string auth =
    BuildOssAuthorization(access_key_secret,
                          access_key_id,
                          http_method,
                          gmt_datetime,
                          resource,
                          headers);

  EXPECT_EQ(auth, expected);
}

}  // namespace oss
