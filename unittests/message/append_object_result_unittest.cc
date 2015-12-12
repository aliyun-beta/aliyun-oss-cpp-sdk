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

#include "oss_sdk_cpp/message/append_object_result.h"

namespace oss {

TEST(AppendObjectResult, allinone) {
  StringMap headers;
  std::string next_append_position = "1717";
  std::string oss_hash_crc64ecma = "14741617095266562575";
  std::string etag = "0F7230CAA4BE94CCBDC99C5500000000";

  headers["x-oss-next-append-position"] = next_append_position;
  headers["x-oss-hash-crc64ecma"] = oss_hash_crc64ecma;
  headers["ETag"] = etag;

  AppendObjectResult result;
  result.ParseFromHeader(headers);

  EXPECT_EQ(next_append_position,
            std::to_string(result.GetNextAppendPosition()));
  EXPECT_EQ(oss_hash_crc64ecma, result.GetCrc64Ecma());
  EXPECT_EQ(etag, result.GetEtag());
}

}  // namespace oss
