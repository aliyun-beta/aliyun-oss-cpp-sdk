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

#include "oss_sdk_cpp/message/delete_multiple_objects_result.h"

namespace oss {

bool DeleteMultipleObjectsResult::DeserializeFromXml(
  const std::string& content) {
  TiXmlDocument doc;
  if (doc.Parse(content.c_str(), 0, TIXML_ENCODING_UTF8) == NULL)
    return false;

  TiXmlNode* root_node = doc.FirstChild("DeleteResult");
  // RefererConfiguration is required.
  if (root_node == NULL)
    return false;

  TiXmlNode* deleted_node = root_node->FirstChild("Deleted");
  while (deleted_node != NULL) {
    TiXmlNode* key_node = deleted_node->FirstChild("Key");
    if (key_node != NULL) {
      std::string key = GetXmlNodeText(key_node);
      keys_.push_back(key);
    }
    deleted_node = deleted_node->NextSibling("Deleted");
  }

  return true;
}

const StringList& DeleteMultipleObjectsResult::GetKeyList() const {
  return keys_;
}

}  // namespace oss
