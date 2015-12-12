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

#include "oss_sdk_cpp/message/bucket.h"

namespace oss {

TEST(Bucket, Basic) {
  std::string bucket_name = "mybucket";
  std::string location = "mykey";
  std::string creation_date = "2015-11-11T12:01:02.000Z";

  {
    Bucket bucket;
    EXPECT_TRUE(bucket.GetName().empty());
    EXPECT_TRUE(bucket.GetLocation().empty());
    EXPECT_TRUE(bucket.GetCreationDate().empty());
  }

  {
    Bucket bucket;

    bucket.SetName(bucket_name);
    EXPECT_EQ(bucket_name, bucket.GetName());

    bucket.SetLocation(location);
    EXPECT_EQ(location, bucket.GetLocation());

    bucket.SetCreationDate(creation_date);
    EXPECT_EQ(creation_date, bucket.GetCreationDate());
  }
}

}  // namespace oss
