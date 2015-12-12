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

#ifndef OSS_SDK_CPP_MESSAGE_SET_BUCKET_WEBSITE_REQUEST_H_
#define OSS_SDK_CPP_MESSAGE_SET_BUCKET_WEBSITE_REQUEST_H_

#include <string>
#include <list>

#include "oss_sdk_cpp/base/base.h"

namespace oss {

class SetBucketWebsiteRequest {
 public:
  SetBucketWebsiteRequest();

  SetBucketWebsiteRequest(const std::string& bucket_name,
                          const std::string& index_page,
                          const std::string& error_page);

  ~SetBucketWebsiteRequest();

  const std::string& GetBucketName() const;

  void SetBucketName(const std::string& name);

  const std::string& GetIndexPage() const;

  void SetIndexPage(const std::string& page_name);

  const std::string& GetErrorPage() const;

  void SetErrorPage(const std::string& page_name);

  std::string SerializeToXml() const;

 private:
  std::string bucket_name_;
  std::string index_page_;
  std::string error_page_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_SET_BUCKET_WEBSITE_REQUEST_H_
