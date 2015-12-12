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

#include "oss_sdk_cpp/message/set_bucket_website_request.h"

namespace oss {

TEST(SetBucketWebsiteRequest, Basic) {
  std::string bucket_name = "mybucket";
  std::string index_page = "myindex.html";
  std::string not_found_page = "my404.html";

  {
    SetBucketWebsiteRequest request(bucket_name,
                                    index_page,
                                    not_found_page);

    EXPECT_EQ(bucket_name, request.GetBucketName());
    EXPECT_EQ(index_page, request.GetIndexPage());
    EXPECT_EQ(not_found_page, request.GetErrorPage());
  }


  SetBucketWebsiteRequest request;
  request.SetBucketName(bucket_name);
  request.SetIndexPage(index_page);
  request.SetErrorPage(not_found_page);

  EXPECT_EQ(bucket_name, request.GetBucketName());
  EXPECT_EQ(index_page, request.GetIndexPage());
  EXPECT_EQ(not_found_page, request.GetErrorPage());


  std::string xml = request.SerializeToXml();
  EXPECT_TRUE(xml.find("myindex.html") != std::string::npos);
  EXPECT_TRUE(xml.find("my404.html") != std::string::npos);
}

}  // namespace oss
