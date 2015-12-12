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

#include "oss_sdk_cpp/message/set_bucket_logging_request.h"

namespace oss {

SetBucketLoggingRequest::SetBucketLoggingRequest() {
}

SetBucketLoggingRequest::SetBucketLoggingRequest(
  const std::string& target_bucket,
  const std::string& target_prefix,
  const std::string& source_bucket)
  : target_bucket_(target_bucket),
    target_prefix_(target_prefix),
    source_bucket_(source_bucket) {
}

SetBucketLoggingRequest::~SetBucketLoggingRequest() {
}

const std::string& SetBucketLoggingRequest::GetTargetBucket() const {
  return target_bucket_;
}

void SetBucketLoggingRequest::SetTargetBucket(const std::string& name) {
  target_bucket_ = name;
}

const std::string& SetBucketLoggingRequest::GetTargetPrefix() const {
  return target_prefix_;
}

void SetBucketLoggingRequest::SetTargetPrefix(const std::string& prefix) {
  target_prefix_ = prefix;
}

const std::string& SetBucketLoggingRequest::GetSourceBucket() const {
  return source_bucket_;
}

void SetBucketLoggingRequest::SetSourceBucket(const std::string& name) {
  source_bucket_ = name;
}

std::string SetBucketLoggingRequest::SerializeToXml() const {
  std::string xml;
  xml.reserve(1024);

  TiXmlDocument doc;
  TiXmlElement* element = NULL;

  TiXmlDeclaration * declaration = new TiXmlDeclaration("1.0", "utf-8", "");
  doc.LinkEndChild(declaration);

  TiXmlElement* root = new TiXmlElement("BucketLoggingStatus");
  doc.LinkEndChild(root);

  element = new TiXmlElement("LoggingEnabled");
  root->LinkEndChild(element);
  AddChildNode(element, "TargetBucket", target_bucket_.c_str());
  AddChildNode(element, "TargetPrefix", target_prefix_.c_str());

  TiXmlPrinter printer;
  doc.Accept(&printer);
  xml = printer.CStr();

  return xml;
}

}  // namespace oss
