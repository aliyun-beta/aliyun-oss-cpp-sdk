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

#include "oss_sdk_cpp/message/get_bucket_lifecycle_result.h"

namespace oss {

const LifeCycleList& GetBucketLifecycleResult::GetBucketLifecycle() const {
  return rules_;
}

bool GetBucketLifecycleResult::DeserializeFromXml(const std::string& content) {
  TiXmlDocument doc;
  if (doc.Parse(content.c_str(), 0, TIXML_ENCODING_UTF8) == NULL)
    return false;

  TiXmlNode* node = NULL;
  TiXmlNode* root_node = doc.FirstChild("LifecycleConfiguration");
  // RefererConfiguration is required.
  if (root_node == NULL)
    return false;

  TiXmlNode* rule_node = root_node->FirstChild("Rule");
  while (rule_node != NULL) {
    LifeCycleRule rule;

    node = rule_node->FirstChild("ID");
    if (node != NULL) {
      rule.SetId(GetXmlNodeText(node));
    }

    node = rule_node->FirstChild("Prefix");
    if (node != NULL) {
      rule.SetPrefix(GetXmlNodeText(node));
    }

    node = rule_node->FirstChild("Status");
    if (node != NULL) {
      const char* status = GetXmlNodeText(node);
      rule.SetEnabled(stricmp(status, "Enabled") == 0);
    }

    TiXmlNode* expiration_node = rule_node->FirstChild("Expiration");
    if (expiration_node != NULL) {
      node = expiration_node->FirstChild("Days");
      if (node != NULL) {
        // use Days.
        rule.SetExpirationDays(atoi(GetXmlNodeText(node)));
      } else {
        node = expiration_node->FirstChild("Date");
        if (node != NULL) {
          // use Date.
          rule.SetExpirationDate(GetXmlNodeText(node));
        }
      }
      rules_.push_back(rule);
    }

    rule_node = rule_node->NextSibling("Rule");
  }

  return true;
}

}  // namespace oss
