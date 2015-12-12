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

#include "oss_sdk_cpp/message/set_bucket_logging_request.h"

namespace oss {

TEST(SetBucketLoggingRequest, Basic) {
  std::string source_bucket = "mybucket";
  std::string log_bucket_name = source_bucket + "log564987";
  std::string log_prefix = "test18";

  {
    SetBucketLoggingRequest request(log_bucket_name,
                                    log_prefix,
                                    source_bucket);
    EXPECT_EQ(source_bucket, request.GetSourceBucket());
    EXPECT_EQ(log_bucket_name, request.GetTargetBucket());
    EXPECT_EQ(log_prefix, request.GetTargetPrefix());
  }

  {
    SetBucketLoggingRequest request;
    request.SetTargetBucket(log_bucket_name);
    request.SetTargetPrefix(log_prefix);
    request.SetSourceBucket(source_bucket);

    EXPECT_EQ(source_bucket, request.GetSourceBucket());
    EXPECT_EQ(log_bucket_name, request.GetTargetBucket());
    EXPECT_EQ(log_prefix, request.GetTargetPrefix());
  }
}

}  // namespace oss
