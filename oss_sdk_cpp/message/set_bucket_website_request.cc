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

#include "oss_sdk_cpp/message/set_bucket_website_request.h"

namespace oss {

SetBucketWebsiteRequest::SetBucketWebsiteRequest() {
}

SetBucketWebsiteRequest::SetBucketWebsiteRequest(
  const std::string& bucket_name,
  const std::string& index_page,
  const std::string& error_page)
  : bucket_name_(bucket_name),
    index_page_(index_page),
    error_page_(error_page) {
}

SetBucketWebsiteRequest::~SetBucketWebsiteRequest() {
}


const std::string& SetBucketWebsiteRequest::GetBucketName() const {
  return bucket_name_;
}

void SetBucketWebsiteRequest::SetBucketName(const std::string& name) {
  bucket_name_ = name;
}


const std::string& SetBucketWebsiteRequest::GetIndexPage() const {
  return index_page_;
}

void SetBucketWebsiteRequest::SetIndexPage(const std::string& page_name) {
  index_page_ = page_name;
}


const std::string& SetBucketWebsiteRequest::GetErrorPage() const {
  return error_page_;
}

void SetBucketWebsiteRequest::SetErrorPage(const std::string& page_name) {
  error_page_ = page_name;
}

std::string SetBucketWebsiteRequest::SerializeToXml() const {
  std::string xml;
  xml.reserve(1024);

  TiXmlDocument doc;
  TiXmlElement* element = NULL;

  TiXmlDeclaration * declaration = new TiXmlDeclaration("1.0", "utf-8", "");
  doc.LinkEndChild(declaration);

  TiXmlElement* root = new TiXmlElement("WebsiteConfiguration");
  doc.LinkEndChild(root);

  element = new TiXmlElement("IndexDocument");
  root->LinkEndChild(element);
  AddChildNode(element, "Suffix", index_page_.c_str());

  element = new TiXmlElement("ErrorDocument");
  root->LinkEndChild(element);
  AddChildNode(element, "Key", error_page_.c_str());

  TiXmlPrinter printer;
  doc.Accept(&printer);
  xml = printer.CStr();

  return xml;
}

}  // namespace oss
