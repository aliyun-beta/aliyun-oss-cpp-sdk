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

#include "oss_sdk_cpp/message/delete_multiple_objects_request.h"

namespace oss {

TEST(DeleteMultipleObjectsRequest, Basic) {
  // Himalayas in Chinese.
  char kUtf8Text1[] =
    "\xE5\x96\x9C\xE9\xA9\xAC\xE6\x8B\x89\xE9\x9B\x85\xE5\xB1\xB1";
  std::string bucket_name = "mybucket";

  {
    DeleteMultipleObjectsRequest request{
      bucket_name,
      true
    };

    EXPECT_EQ(bucket_name, request.GetBucketName());
    EXPECT_EQ(true, request.GetQuiet());
    EXPECT_TRUE(request.GetKeyList().empty());

    StringList keys;
    keys.push_back("abc");
    request.AddKey("abc");
    EXPECT_EQ(keys, request.GetKeyList());
  }

  StringList keys;
  keys.push_back(kUtf8Text1);
  keys.push_back("foo");
  keys.push_back("bar");

  bool quiet = false;

  {
    DeleteMultipleObjectsRequest request;
    request.SetBucketName(bucket_name);
    request.SetKeyList(keys);
    request.SetQuiet(quiet);

    EXPECT_EQ(bucket_name, request.GetBucketName());
    EXPECT_EQ(keys, request.GetKeyList());
    EXPECT_EQ(quiet, request.GetQuiet());

    keys.push_back("abc");
    request.AddKey("abc");
    EXPECT_EQ(keys, request.GetKeyList());

    std::string xml = request.SerializeToXml();
    EXPECT_TRUE(xml.find("foo") != std::string::npos);
  }

  {
    DeleteMultipleObjectsRequest request{
      bucket_name,
      keys,
      false,
    };

    EXPECT_EQ(bucket_name, request.GetBucketName());
    EXPECT_FALSE(request.GetQuiet());

    keys.push_back("abc");
    request.AddKey("abc");
    EXPECT_EQ(keys, request.GetKeyList());
  }
}

}  // namespace oss
