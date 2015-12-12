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

#include "oss_sdk_cpp/message/get_bucket_cors_result.h"

namespace oss {

const std::list<CorsRule>& GetBucketCorsResult::GetRules() const {
  return rules_;
}

bool GetBucketCorsResult::DeserializeFromXml(const std::string& content) {
  TiXmlDocument doc;
  if (doc.Parse(content.c_str(), 0, TIXML_ENCODING_UTF8) == NULL)
    return false;

  TiXmlNode* node = NULL;
  TiXmlNode* root_node = doc.FirstChild("CORSConfiguration");
  // RefererConfiguration is required.
  if (root_node == NULL)
    return false;

  TiXmlNode* rule_node = root_node->FirstChild("CORSRule");
  while (rule_node != NULL) {
    CorsRule rule;

    node = rule_node->FirstChild("AllowedOrigin");
    while (node != NULL) {
      rule.AddAllowedOrigin(GetXmlNodeText(node));
      node = node->NextSibling("AllowedOrigin");
    }

    node = rule_node->FirstChild("AllowedMethod");
    while (node != NULL) {
      rule.AddAllowedMethod(GetXmlNodeText(node));
      node = node->NextSibling("AllowedMethod");
    }

    node = rule_node->FirstChild("AllowedHeader");
    while (node != NULL) {
      rule.AddAllowedHeader(GetXmlNodeText(node));
      node = node->NextSibling("AllowedHeader");
    }

    node = rule_node->FirstChild("ExposeHeader");
    while (node != NULL) {
      rule.AddExposeHeader(GetXmlNodeText(node));
      node = node->NextSibling("ExposeHeader");
    }

    node = rule_node->FirstChild("MaxAgeSeconds");
    if (node != NULL) {
      rule.SetMaxAgeSeconds(atoi(GetXmlNodeText(node)));
    }

    rules_.push_back(rule);
    rule_node = rule_node->NextSibling("CORSRule");
  }

  return true;
}

}  // namespace oss
