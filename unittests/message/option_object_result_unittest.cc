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

#include "oss_sdk_cpp/message/option_object_result.h"

namespace oss {

TEST(OptionObjectResult, allinone) {
  OptionObjectResult result;

  std::string expected_allow_origin = "abc";
  std::string expected_methods = "efg";
  std::string expected_expose_headers = "xyz";

  StringMap headers;
  headers["Access-Control-Allow-Origin"] = expected_allow_origin;
  headers["Access-Control-Allow-Methods"] = expected_methods;
  headers["Access-Control-Expose-Headers"] = expected_expose_headers;

  result.ParseFromHeader(headers);

  EXPECT_EQ(result.GetAllowOrigin(), expected_allow_origin);
  EXPECT_EQ(result.GetAllowMethods(), expected_methods);
  EXPECT_EQ(result.GeExposeHeaders(), expected_expose_headers);
}

}  // namespace oss
