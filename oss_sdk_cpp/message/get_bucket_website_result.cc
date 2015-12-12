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

#include "oss_sdk_cpp/message/get_bucket_website_result.h"

namespace oss {

const std::string& GetBucketWebsiteResult::GetIndexPage() const {
  return index_page_;
}

void GetBucketWebsiteResult::SetIndexPage(const std::string& page_name) {
  index_page_ = page_name;
}

const std::string& GetBucketWebsiteResult::GetErrorPage() const {
  return error_page_;
}

void GetBucketWebsiteResult::SetErrorPage(const std::string& page_name) {
  error_page_ = page_name;
}

bool GetBucketWebsiteResult::DeserializeFromXml(const std::string& content) {
  TiXmlDocument doc;
  if (doc.Parse(content.c_str(), 0, TIXML_ENCODING_UTF8) == NULL)
    return false;

  TiXmlNode* node = NULL;
  TiXmlNode* root_node = doc.FirstChild("WebsiteConfiguration");
  if (root_node == NULL)
    return false;

  TiXmlNode* index_node = root_node->FirstChild("IndexDocument");
  if (index_node != NULL) {
    node = index_node->FirstChild("Suffix");
    if (node != NULL) {
      index_page_ = GetXmlNodeText(node);
    }
  }

  TiXmlNode* error_node = root_node->FirstChild("ErrorDocument");
  if (error_node != NULL) {
    node = error_node->FirstChild("Key");
    if (node != NULL) {
      error_page_ = GetXmlNodeText(node);
    }
  }

  return true;
}

}  // namespace oss
