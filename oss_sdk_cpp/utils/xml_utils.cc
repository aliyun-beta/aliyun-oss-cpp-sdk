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
#include "oss_sdk_cpp/utils/xml_utils.h"

namespace oss {

const char* GetXmlNodeText(TiXmlNode* node) {
  if (node != NULL) {
    TiXmlElement* element = node->ToElement();
    if (element != NULL) {
      const char* text = element->GetText();
      if (text != NULL) {
        return text;
      }
    }
  }
  // return empty string instead of NULL pointer
  // to prevent program from crashing.
  return "";
}

const char* GetXmlChildNodeText(TiXmlNode* parent_node, const char* name) {
  const char* text = "";
  TiXmlNode* child_node = parent_node->FirstChild(name);
  if (child_node != NULL) {
    text = GetXmlNodeText(child_node);
  }
  return text;
}

TiXmlElement* CreateXmlNode(const char* name, const char* value) {
  TiXmlElement* element = new TiXmlElement(name);
  TiXmlText* text = new TiXmlText(value);
  element->LinkEndChild(text);

  return element;
}

void AddChildNode(TiXmlElement* parent, const char* name, const char* value) {
  TiXmlElement* element = new TiXmlElement(name);
  TiXmlText* text = new TiXmlText(value);
  element->LinkEndChild(text);
  parent->LinkEndChild(element);
}

}  // namespace oss
