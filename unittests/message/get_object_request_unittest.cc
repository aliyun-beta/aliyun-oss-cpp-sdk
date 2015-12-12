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

#include <fstream>
#include "gtest/gtest.h"

#include "oss_sdk_cpp/message/get_object_request.h"

namespace oss {

TEST(GetObjectRequest, Basic) {
  std::string bucket_name = "mybucket";
  std::string key = "mykey";
  std::ofstream output_stream;
  std::string output_file = "/root/abc.txt";
  OptionalRange range = Range(200, 300);

  GetObjectRequest request;
  request.SetBucket(bucket_name);
  request.SetKey(key);
  request.SetRange(range);
  request.SetFilePath(output_file);
  request.SetOutputStream(&output_stream);


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
    { "2C0FC53DB041AB32EC663867DF02EDE3" },
    { "24196B4D8EAB6F08A4B141D3D594531C" },
    { "4ADAD0363F0B0F612FD28B15A51DDD80" }
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

  EXPECT_EQ(request.GetBucket(), bucket_name);
  EXPECT_EQ(request.GetKey(), key);
  EXPECT_EQ(request.GetOutputStream(), &output_stream);
  EXPECT_EQ(request.GetFilePath(), output_file);
  EXPECT_EQ(request.GetRange().Value(), range.Value());


  EXPECT_EQ(headers["foo"], "bar");
  EXPECT_EQ(headers["hello"], "world");
  EXPECT_EQ(headers["highest"], "everest");

  EXPECT_EQ(modified_since_time, request.GetModifiedSinceConstraint());
  EXPECT_EQ(unmodified_since_time, request.GetUnmodifiedSinceConstraint());

  EXPECT_EQ(matching_etag_list, request.GetMatchingETagConstraints());
  EXPECT_EQ(unmatching_etag_list, request.GetNonmatchingEtagConstraints());

  {
    GetObjectRequest req(bucket_name, key, output_file);
    EXPECT_EQ(req.GetFilePath(), output_file);
  }

  {
    GetObjectRequest req(bucket_name, key, &output_stream);
    EXPECT_EQ(req.GetOutputStream(), &output_stream);
  }
}

}  // namespace oss
