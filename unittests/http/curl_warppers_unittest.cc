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

#include <string>
#include <ostream>

#include "gtest/gtest.h"

#include "oss_sdk_cpp/base/nullable.h"
#include "oss_sdk_cpp/http/curl_warppers.h"

namespace oss {

TEST(CUrlSlist, basic) {
  CUrlSlist slist;
  curl_slist* raw_slist = slist.Get();
  slist.AddHeader("hello", "world");
  EXPECT_NE(raw_slist, slist.Get());
  raw_slist = slist.Get();
  slist.AddHeader("foo", "bar");
  EXPECT_EQ(raw_slist, slist.Get());
}

TEST(CUrl, basic) {
  CUrl curl;

  EXPECT_NE(curl.Get(), nullptr);
  curl.Close();
  EXPECT_EQ(curl.Get(), nullptr);
  curl.ReCreate();
  EXPECT_NE(curl.Get(), nullptr);
  curl.Close();
  EXPECT_EQ(curl.Get(), nullptr);
  curl.Create();
  EXPECT_NE(curl.Get(), nullptr);

  void* raw_curl = curl.Get();
  curl.ResetState();
  EXPECT_EQ(curl.Get(), raw_curl);
}

}  // namespace oss
