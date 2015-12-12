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

#include "oss_sdk_cpp/message/upload_part.h"

namespace oss {

TEST(UploadPart, Basic) {
  int part_number = 3;
  std::string last_modified = "2014-07-17T06:27:54.000Z";
  std::string etag = "5B3C1A2E053D763E1B002CC607C5A0FE";
  int64_t size = 1024 * 1024;

  {
    UploadPart part;
    part.SetPartNumber(part_number);
    part.SetEtag(etag);
    part.SetLastModified(last_modified);
    part.SetSize(size);

    EXPECT_EQ(part_number, part.GetPartNumber());
    EXPECT_EQ(last_modified, part.GetLastModified());
    EXPECT_EQ(etag, part.GetEtag());
    EXPECT_EQ(size, part.GetSize());
  }
}

}  // namespace oss
