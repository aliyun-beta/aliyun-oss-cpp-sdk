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

#include "oss_sdk_cpp/message/set_bucket_lifecycle_request.h"

namespace oss {

SetBucketLifecycleRequest::SetBucketLifecycleRequest() {
}

SetBucketLifecycleRequest::SetBucketLifecycleRequest(
  const std::string& bucket_name)
  : bucket_name_(bucket_name) {
}

SetBucketLifecycleRequest::~SetBucketLifecycleRequest() {
}

void SetBucketLifecycleRequest::AddRule(const LifeCycleRule& rule) {
  rules_.push_back(rule);
}

const std::string& SetBucketLifecycleRequest::GetBucketName() const {
  return bucket_name_;
}

void SetBucketLifecycleRequest::SetBucketName(const std::string& name) {
  bucket_name_ = name;
}

std::string SetBucketLifecycleRequest::SerializeToXml() const {
  std::string xml;
  xml.reserve(1024);

  TiXmlDocument doc;

  TiXmlDeclaration * declaration = new TiXmlDeclaration("1.0", "utf-8", "");
  doc.LinkEndChild(declaration);

  TiXmlElement* root = new TiXmlElement("LifecycleConfiguration");
  doc.LinkEndChild(root);

  for (auto& rule : rules_) {
    TiXmlElement* rule_element = new TiXmlElement("Rule");
    root->LinkEndChild(rule_element);

    rule_element->LinkEndChild(
      CreateXmlNode("ID", rule.GetId().c_str()));
    rule_element->LinkEndChild(
      CreateXmlNode("Prefix", rule.GetPrefix().c_str()));
    rule_element->LinkEndChild(
      CreateXmlNode("Status", rule.GetEnabled() ? "Enabled" : "Disabled"));

    TiXmlElement* expiration_element = new TiXmlElement("Expiration");
    rule_element->LinkEndChild(expiration_element);
    if (rule.GetExpirationDate().empty()) {
      expiration_element->LinkEndChild(
        CreateXmlNode("Days",
                      std::to_string(rule.GetExpirationDays()).c_str()));
    } else {
      expiration_element->LinkEndChild(
        CreateXmlNode("Date", rule.GetExpirationDate().c_str()));
    }
  }

  TiXmlPrinter printer;
  doc.Accept(&printer);
  xml = printer.CStr();

  return xml;
}

}  // namespace oss
