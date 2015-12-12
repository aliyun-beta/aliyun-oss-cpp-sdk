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

#include "oss_sdk_cpp/message/get_bucket_referer_result.h"

namespace oss {

GetBucketRefererResult::GetBucketRefererResult()
  : allow_empty_(true) {
}

GetBucketRefererResult::~GetBucketRefererResult() {
}

const StringList& GetBucketRefererResult::GetBucketReferer() const {
  return referers_;
}

bool GetBucketRefererResult::GetAllowEmpty() const {
  return allow_empty_;
}

bool GetBucketRefererResult::DeserializeFromXml(const std::string& content) {
  TiXmlDocument doc;
  if (doc.Parse(content.c_str(), 0, TIXML_ENCODING_UTF8) == NULL)
    return false;

  TiXmlNode* node = NULL;
  TiXmlNode* root_node = doc.FirstChild("RefererConfiguration");
  // RefererConfiguration is required.
  if (root_node == NULL)
    return false;

  node = root_node->FirstChild("AllowEmptyReferer");
  // AllowEmptyReferer is required
  if (node == NULL)
    return false;
  allow_empty_ = StringToBool(GetXmlNodeText(node));

  TiXmlNode* list_node = root_node->FirstChild("RefererList");
  // RefererList is required.
  if (list_node == NULL)
    return false;

  TiXmlNode* referer_node = list_node->FirstChild("Referer");
  while (referer_node != NULL) {
    std::string referer = GetXmlNodeText(referer_node);
    referers_.push_back(referer);
    referer_node = referer_node->NextSibling("Referer");
  }

  return true;
}

}  // namespace oss
