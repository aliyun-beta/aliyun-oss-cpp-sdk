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

#include "oss_sdk_cpp/message/copy_object_request.h"

namespace oss {

TEST(CopyObjectRequest, Basic) {
  std::string source_bucket = "mysourcetest123";
  std::string source_key = "mysource.txt";
  std::string target_bucket = "mytargettest123";
  std::string target_key = "mytarget.txt";

  CopyObjectRequest request;
  request.SetSourceBucket(source_bucket);
  request.SetSourceKey(source_key);
  request.SetTargetBucket(target_bucket);
  request.SetTargetKey(target_key);

  std::unique_ptr<ObjectMetadata> object_metadata(new ObjectMetadata);
  object_metadata->AddHeader("foo", "bar");
  object_metadata->AddHeader("hello", "world");
  object_metadata->AddHeader("highest", "everest");
  request.SetNewObjectMetaData(object_metadata.release());

  time_t modified_since_time = time(NULL);
  time_t unmodified_since_time = time(NULL) + 1000;

  request.SetModifiedSinceConstraint(modified_since_time);
  request.SetUnmodifiedSinceConstraint(unmodified_since_time);

  StringList matching_etag_list = {
    { "2C0FC53DB041AB32EC663867DF02EDE3"},
    { "24196B4D8EAB6F08A4B141D3D594531C"},
    { "4ADAD0363F0B0F612FD28B15A51DDD80"}
  };

  StringList unmatching_etag_list = {
    { "9C0FC53DB041AB32EC663867DF02EDE3" },
    { "84196B4D8EAB6F08A4B141D3D594531C" },
    { "7ADAD0363F0B0F612FD28B15A51DDD80" }
  };

  request.SetMatchingETagConstraints(matching_etag_list);
  request.SetNonmatchingEtagConstraints(unmatching_etag_list);

  StringMap headers;
  request.AddToParameterList(&headers);

  EXPECT_EQ(request.GetSourceBucket(), source_bucket);
  EXPECT_EQ(request.GetSourceKey(), source_key);
  EXPECT_EQ(request.GetTargetBucket(), target_bucket);
  EXPECT_EQ(request.GetTargetKey(), target_key);

  EXPECT_EQ(headers["foo"], "bar");
  EXPECT_EQ(headers["hello"], "world");
  EXPECT_EQ(headers["highest"], "everest");

  EXPECT_EQ(modified_since_time, request.GetModifiedSinceConstraint());
  EXPECT_EQ(unmodified_since_time, request.GetUnmodifiedSinceConstraint());

  EXPECT_EQ(matching_etag_list, request.GetMatchingETagConstraints());
  EXPECT_EQ(unmatching_etag_list, request.GetNonmatchingEtagConstraints());

  {
    CopyObjectRequest req;
    EXPECT_TRUE(req.GetModifiedSinceConstraint().IsNull());
    EXPECT_TRUE(req.GetUnmodifiedSinceConstraint().IsNull());
  }
}

}  // namespace oss
