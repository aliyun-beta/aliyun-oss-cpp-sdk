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
#include <algorithm>

#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/utils/xml_utils.h"

#include "oss_sdk_cpp/oss/oss_exception.h"
#include "oss_sdk_cpp/oss/oss_error_code.h"

namespace oss {

OssException::OssException() {
}

OssException::~OssException() {
}

const std::string& OssException::GetCode() const {
  return code_;
}

void OssException::SetCode(const std::string& val) {
  code_ = val;
}

const std::string& OssException::GetMessage() const {
  return message_;
}

void OssException::SetMessage(const std::string& val) {
  message_ = val;
}

const std::string& OssException::GetRequestId() const {
  return request_id_;
}

void OssException::SetRequestId(const std::string& val) {
  request_id_ = val;
}

const std::string& OssException::GetHostId() const {
  return host_id_;
}

void OssException::SetHostId(const std::string& val) {
  host_id_ = val;
}

// move assignment.
OssException& OssException::operator=(OssException&& rhs) {
  code_ = std::move(rhs.code_);
  message_ = std::move(rhs.message_);
  request_id_ = std::move(rhs.request_id_);
  host_id_ = std::move(rhs.host_id_);

  return *this;
}

// move constructor.
OssException::OssException(OssException&& rhs)
  : code_(std::move(rhs.code_)),
    message_(std::move(rhs.message_)),
    request_id_(std::move(rhs.request_id_)),
    host_id_(std::move(rhs.host_id_)) {
}

void OssException::Swap(OssException& right) {
  std::swap(code_, right.code_);
  std::swap(message_, right.message_);
  std::swap(request_id_, right.request_id_);
  std::swap(host_id_, right.host_id_);
}

bool OssException::FromXml(const std::string &response) {
  TiXmlDocument doc;
  if (doc.Parse(response.c_str(), 0, TIXML_ENCODING_UTF8) == NULL) {
    return false;
  }

  // root, error field.
  TiXmlNode* root_node = doc.FirstChild("Error");
  if (root_node == NULL) {
    return false;
  }

  TiXmlNode* node = NULL;
  // Code field.
  node = root_node->FirstChild("Code");
  if (node == NULL) {
    return false;
  }
  code_ = GetXmlNodeText(node);

  // Message field.
  node = root_node->FirstChild("Message");
  if (node == NULL) {
    return false;
  }
  message_ = GetXmlNodeText(node);

  // RequestId field.
  node = root_node->FirstChild("RequestId");
  if (node == NULL) {
    return false;
  }
  request_id_ = GetXmlNodeText(node);

  // HostId field.
  node = root_node->FirstChild("HostId");
  if (node == NULL) {
    return false;
  }
  host_id_ = GetXmlNodeText(node);

  return true;
}

}  // namespace oss
