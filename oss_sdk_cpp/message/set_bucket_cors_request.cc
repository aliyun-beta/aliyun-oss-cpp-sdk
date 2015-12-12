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

#include "oss_sdk_cpp/message/set_bucket_cors_request.h"

namespace oss {

SetBucketCorsRequest::SetBucketCorsRequest() {
}

SetBucketCorsRequest::SetBucketCorsRequest(const std::string& bucket_name)
  : bucket_name_(bucket_name) {
}

SetBucketCorsRequest::~SetBucketCorsRequest() {
}

const std::string& SetBucketCorsRequest::GetBucketName() const {
  return bucket_name_;
}

void SetBucketCorsRequest::SetBucketName(const std::string& name) {
  bucket_name_ = name;
}

void SetBucketCorsRequest::AddRule(const CorsRule& rule) {
  rules_.push_back(rule);
}

CorsRule* SetBucketCorsRequest::AddRule() {
  rules_.push_back(CorsRule());
  return &rules_.back();
}

const std::list<CorsRule>& SetBucketCorsRequest::GetRules() const {
  return rules_;
}

void SetBucketCorsRequest::SetRules(const std::list<CorsRule>& rules) {
  rules_ = rules;
}

std::string SetBucketCorsRequest::SerializeToXml() const {
  std::string xml;
  xml.reserve(1024);

  TiXmlDocument doc;
  TiXmlDeclaration * declaration = new TiXmlDeclaration("1.0", "utf-8", "");
  doc.LinkEndChild(declaration);

  TiXmlElement* root = new TiXmlElement("CORSConfiguration");
  doc.LinkEndChild(root);

  for (auto& rule : rules_) {
    TiXmlElement* rule_element = new TiXmlElement("CORSRule");
    root->LinkEndChild(rule_element);
    for (auto& str : rule.GetAllowedOrigins()) {
      AddChildNode(rule_element, "AllowedOrigin", str.c_str());
    }

    for (auto& str : rule.GetAllowedMethods()) {
      AddChildNode(rule_element, "AllowedMethod", str.c_str());
    }

    for (auto& str : rule.GetAllowedHeaders()) {
      AddChildNode(rule_element, "AllowedHeader", str.c_str());
    }

    for (auto& str : rule.GetExposeHeaders()) {
      AddChildNode(rule_element, "ExposeHeader", str.c_str());
    }

    AddChildNode(rule_element, "MaxAgeSeconds",
                 std::to_string(rule.GetMaxAgeSeconds()).c_str());
  }

  TiXmlPrinter printer;
  doc.Accept(&printer);
  xml = printer.CStr();

  return xml;
}

}  // namespace oss
