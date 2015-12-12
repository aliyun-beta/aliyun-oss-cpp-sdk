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

#include <tinyxml.h>

#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/utils/string_utils.h"
#include "oss_sdk_cpp/utils/xml_utils.h"

#include "oss_sdk_cpp/message/complete_multipart_upload_result.h"

namespace oss {

CompleteMultipartUploadResult::CompleteMultipartUploadResult() {
}

const std::string& CompleteMultipartUploadResult::GetBucketName() const {
  return bucket_name_;
}

const std::string& CompleteMultipartUploadResult::GetKey() const {
  return key_;
}

const std::string& CompleteMultipartUploadResult::GetEtag() const {
  return etag_;
}

const std::string& CompleteMultipartUploadResult::GetLocation() const {
  return location_;
}

bool CompleteMultipartUploadResult::DeserializeFromXml(
  const std::string& content) {
  TiXmlDocument doc;
  if (doc.Parse(content.c_str(), 0, TIXML_ENCODING_UTF8) == NULL)
    return false;

  TiXmlNode* node = NULL;
  TiXmlNode* root_node = doc.FirstChild("CompleteMultipartUploadResult");
  if (root_node == NULL)
    return false;

  node = root_node->FirstChild("Location");
  if (node != NULL) {
    location_ = GetXmlNodeText(node);
  }

  node = root_node->FirstChild("Bucket");
  if (node != NULL) {
    bucket_name_ = GetXmlNodeText(node);
  }

  node = root_node->FirstChild("Key");
  if (node != NULL) {
    key_ = GetXmlNodeText(node);
  }

  node = root_node->FirstChild("ETag");
  if (node != NULL) {
    std::string str = GetXmlNodeText(node);
    TrimString(str, "\"", &etag_);
  }

  return true;
}

}  // namespace oss
