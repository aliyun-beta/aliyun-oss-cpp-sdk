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

#include "oss_sdk_cpp/message/multipart_upload.h"

namespace oss {

TEST(MultipartUpload, Basic) {
  std::string key = "mykey";
  std::string upload_id = "/home/hello/abc.txt";
  std::string initiated = "0004B999EF518A1FE585B0C9360DC4C8";
  std::string query_string = "mykey?append&position=999";

  {
    MultipartUpload request;
    request.SetKey(key);
    request.SetUploadId(upload_id);
    request.SetInitiated(initiated);

    EXPECT_EQ(key, request.GetKey());
    EXPECT_EQ(upload_id, request.GetUploadId());
    EXPECT_EQ(initiated, request.GetInitiated());
  }
}

}  // namespace oss
