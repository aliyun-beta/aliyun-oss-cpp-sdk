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

#include "oss_sdk_cpp/message/complete_multipart_upload_request.h"

namespace oss {

CompleteMultipartUploadrequest::CompleteMultipartUploadrequest() {
}

CompleteMultipartUploadrequest::CompleteMultipartUploadrequest(
  const std::string& bucket_name,
  const std::string& key,
  const std::string& upload_id)
  : bucket_name_(bucket_name),
    key_(key),
    upload_id_(upload_id) {
}

CompleteMultipartUploadrequest::CompleteMultipartUploadrequest(
  const std::string& bucket_name,
  const std::string& key,
  const std::string& upload_id,
  const PartEtagList& etags)
  : bucket_name_(bucket_name),
    key_(key),
    upload_id_(upload_id),
    part_etags_(etags) {
}

PartEtagList& CompleteMultipartUploadrequest::MutableEtagList() {
  return part_etags_;
}

void CompleteMultipartUploadrequest::SetEtagList(const PartEtagList& etags) {
  part_etags_ = etags;
}

const PartEtagList& CompleteMultipartUploadrequest::GetEtagList() const {
  return part_etags_;
}

const std::string& CompleteMultipartUploadrequest::GetBucketName() const {
  return bucket_name_;
}

void CompleteMultipartUploadrequest::SetBucketName(const std::string& name) {
  bucket_name_ = name;
}

const std::string& CompleteMultipartUploadrequest::GetUploadId() const {
  return upload_id_;
}

void CompleteMultipartUploadrequest::SetUploadId(const std::string& upload_id) {
  upload_id_ = upload_id;
}

const std::string& CompleteMultipartUploadrequest::GetKey() const {
  return key_;
}

void CompleteMultipartUploadrequest::SetKey(const std::string& key) {
  key_ = key;
}

std::string CompleteMultipartUploadrequest::BuildQueryString() const {
  return key_ + "?uploadId=" + upload_id_;
}

std::string CompleteMultipartUploadrequest::SerializeToXml() const {
  std::string xml;
  xml.reserve(1024);

  TiXmlDocument doc;

  TiXmlDeclaration * declaration = new TiXmlDeclaration("1.0", "", "");
  doc.LinkEndChild(declaration);

  TiXmlElement* root = new TiXmlElement("CompleteMultipartUpload");
  doc.LinkEndChild(root);

  for (auto& part_etag : part_etags_) {
    TiXmlElement* rule_element = new TiXmlElement("Part");
    root->LinkEndChild(rule_element);

    rule_element->LinkEndChild(
      CreateXmlNode("PartNumber",
                    std::to_string(part_etag.GetPartNumber()).c_str()));

    rule_element->LinkEndChild(
      CreateXmlNode("ETag", ("\"" + part_etag.GetEtag() + "\"").c_str()));
  }

  TiXmlPrinter printer;
  doc.Accept(&printer);
  xml = printer.CStr();

  // avoid escape of quote.
  ReplaceSubstring(&xml, "&quot;", "\"");

  return xml;
}

}  // namespace oss
