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

#include "oss_sdk_cpp/message/set_bucket_referer_request.h"

namespace oss {

SetBucketRefererRequest::SetBucketRefererRequest()
  : allow_empty_(true) {
}

SetBucketRefererRequest::SetBucketRefererRequest(
  const std::string& bucket_name,
  bool allow_empty)
  : bucket_name_(bucket_name),
    allow_empty_(allow_empty) {
}

SetBucketRefererRequest::~SetBucketRefererRequest() {
}

const std::string& SetBucketRefererRequest::GetBucketName() const {
  return bucket_name_;
}

void SetBucketRefererRequest::SetBucketName(const std::string& name) {
  bucket_name_ = name;
}

const StringList& SetBucketRefererRequest::GetBucketReferer() const {
  return referers_;
}

void SetBucketRefererRequest::SetBucketReferer(
  const std::list<std::string>& referers) {
  referers_ = referers;
}

bool SetBucketRefererRequest::GetAllowEmpty() const {
  return allow_empty_;
}

void SetBucketRefererRequest::SetAllowEmpty(bool allow) {
  allow_empty_ = allow;
}

void SetBucketRefererRequest::AddReferer(const std::string& referer) {
  referers_.push_back(referer);
}

std::string SetBucketRefererRequest::SerializeToXml() const {
  std::string xml;
  xml.reserve(1024);

  TiXmlDocument doc;
  TiXmlElement* element = NULL;
  TiXmlText * text = NULL;

  TiXmlDeclaration * declaration = new TiXmlDeclaration("1.0", "utf-8", "");
  doc.LinkEndChild(declaration);

  TiXmlElement* root = new TiXmlElement("RefererConfiguration");
  doc.LinkEndChild(root);

  element = new TiXmlElement("AllowEmptyReferer");
  text = new TiXmlText(allow_empty_ ? "true" : "false");
  element->LinkEndChild(text);
  root->LinkEndChild(element);

  TiXmlElement* list_element = new TiXmlElement("RefererList");
  root->LinkEndChild(list_element);

  for (auto& referer : referers_) {
    element = new TiXmlElement("Referer");
    text = new TiXmlText(referer.c_str());
    element->LinkEndChild(text);
    list_element->LinkEndChild(element);
  }

  TiXmlPrinter printer;
  doc.Accept(&printer);

  xml = printer.CStr();

  return xml;
}

}  // namespace oss
