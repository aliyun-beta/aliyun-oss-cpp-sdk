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

#ifndef OSS_SDK_CPP_MESSAGE_DELETE_MULTIPLE_OBJECTS_REQUEST_H_
#define OSS_SDK_CPP_MESSAGE_DELETE_MULTIPLE_OBJECTS_REQUEST_H_

#include <string>

#include "oss_sdk_cpp/base/base.h"

namespace oss {

class DeleteMultipleObjectsRequest {
 public:
  DeleteMultipleObjectsRequest();

  DeleteMultipleObjectsRequest(const std::string& bucket_name,
                               bool quiet = false);

  DeleteMultipleObjectsRequest(const std::string& bucket_name,
                               const StringList& keys,
                               bool quiet = false);

  ~DeleteMultipleObjectsRequest();

  const std::string& GetBucketName() const;

  void SetBucketName(const std::string& name);

  const StringList& GetKeyList() const;

  void SetKeyList(const StringList& keys);

  void AddKey(const std::string& key);

  bool GetQuiet() const;

  void SetQuiet(bool quiet);

  std::string SerializeToXml() const;

 private:
  std::string bucket_name_;
  StringList keys_;
  bool quiet_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_MESSAGE_DELETE_MULTIPLE_OBJECTS_REQUEST_H_
