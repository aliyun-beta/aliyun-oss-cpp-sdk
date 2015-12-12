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
#include "oss_sdk_cpp/utils/http_utils.h"

namespace oss {

TEST(GmtTime, Basic) {
  const std::string expected = "Sun, 22 Nov 2015 02:29:40 GMT";
  time_t posix_time = 1448159380;
  std::string gmt_time = GmtTime(posix_time);

  EXPECT_EQ(gmt_time, expected);
}

TEST(GmtTimeNow, Basic) {
  while (1) {
    std::string gmt_time1 = GmtTime(time(NULL));
    std::string gmt_time2 = GmtTimeNow();
    std::string gmt_time3 = GmtTime(time(NULL));
    if (gmt_time1[0] == gmt_time2[0] && gmt_time1[0] == gmt_time3[0]) {
      EXPECT_TRUE(gmt_time1 <= gmt_time2);
      EXPECT_TRUE(gmt_time2 <= gmt_time3);

      break;
    }
  }
}

TEST(Iso8601Date, Basic) {
  const std::string expected = "2015-11-22T00:00:00.000Z";
  time_t posix_time = 1448161711;
  std::string iso8601_date = Iso8601Date(posix_time);

  EXPECT_EQ(iso8601_date, expected);
}

TEST(UrlEscape, Basic) {
  const std::string expected =
    "https%3A%2F%2Fexpense.console.aliyun.com"
    "%2F%3Fspm%3D5176.1980653.1909947.21.qPnxrF%23%2Faccount%2Fhome";
  const std::string input =
    "https://expense.console.aliyun.com"
    "/?spm=5176.1980653.1909947.21.qPnxrF#/account/home";

  std::string ouput = UrlEscape(input);
  EXPECT_EQ(ouput, expected);
}

}  // namespace oss
