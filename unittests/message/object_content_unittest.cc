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

#include "oss_sdk_cpp/message/object_content.h"

namespace oss {

TEST(ObjectContent, Basic) {
  std::string key = "fun/movie/001.avi";
  std::string last_modified = "2012-02-24T08:43:07.000Z";
  std::string etag = "5B3C1A2E053D763E1B002CC607C5A0FE";
  std::string type = "Normal";
  size_t size = 344606;
  std::string storage_class = "Standard";
  std::string owner_id = "00220120222";
  std::string owner_display_name = "user-example";

  {
    ObjectContent request;
    request.SetKey(key);
    request.SetLastModified(last_modified);
    request.SetEtag(etag);
    request.SetType(type);
    request.SetSize(size);
    request.SetStorageClass(storage_class);
    request.SetOwnerId(owner_id);
    request.SetOwnerDisplayName(owner_display_name);

    EXPECT_EQ(key, request.GetKey());
    EXPECT_EQ(last_modified, request.GetLastModified());
    EXPECT_EQ(etag, request.GetEtag());
    EXPECT_EQ(type, request.GetType());
    EXPECT_EQ(size, request.GetSize());
    EXPECT_EQ(storage_class, request.GetStorageClass());
    EXPECT_EQ(owner_id, request.GetOwnerId());
    EXPECT_EQ(owner_display_name, request.GetOwnerDisplayName());
  }

  {
    ObjectContent request(
      key,
      last_modified,
      etag,
      type,
      size,
      storage_class,
      owner_id,
      owner_display_name);

    EXPECT_EQ(key, request.GetKey());
    EXPECT_EQ(last_modified, request.GetLastModified());
    EXPECT_EQ(etag, request.GetEtag());
    EXPECT_EQ(type, request.GetType());
    EXPECT_EQ(size, request.GetSize());
    EXPECT_EQ(storage_class, request.GetStorageClass());
    EXPECT_EQ(owner_id, request.GetOwnerId());
    EXPECT_EQ(owner_display_name, request.GetOwnerDisplayName());
  }
}

}  // namespace oss
