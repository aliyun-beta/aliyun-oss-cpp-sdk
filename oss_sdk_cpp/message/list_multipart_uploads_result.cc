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

#include "oss_sdk_cpp/message/list_multipart_uploads_result.h"

namespace oss {

ListMultipartUploadsResult::ListMultipartUploadsResult()
  : is_truncated_(false) {
}

ListMultipartUploadsResult::~ListMultipartUploadsResult() {
}

const MultipartList& ListMultipartUploadsResult::GetMultipartUpload() const {
  return uploads_;
}

const std::string& ListMultipartUploadsResult::GetBucketName() const {
  return bucket_name_;
}

const std::string& ListMultipartUploadsResult::GetKeyMarker() const {
  return key_marker_;
}

const std::string& ListMultipartUploadsResult::GetUploadIdMarker() const {
  return upload_id_marker_;
}

const std::string& ListMultipartUploadsResult::GetNextKeyMarker() const {
  return next_key_marker_;
}

const std::string& ListMultipartUploadsResult::GetNextUploadIdMarker() const {
  return next_upload_id_marker_;
}

int ListMultipartUploadsResult::GetMaxUploads() const {
  return max_uploads_;
}

const std::string& ListMultipartUploadsResult::GetPrefix() const {
  return prefix_;
}

const std::string& ListMultipartUploadsResult::GetDelimiter() const {
  return delimiter_;
}

bool ListMultipartUploadsResult::GetIsTruncated() const {
  return is_truncated_;
}

bool ListMultipartUploadsResult::DeserializeFromXml(const std::string&
    content) {
  TiXmlDocument doc;
  if (doc.Parse(content.c_str(), 0, TIXML_ENCODING_UTF8) == NULL)
    return false;

  TiXmlNode* root_node = doc.FirstChild("ListMultipartUploadsResult");
  if (root_node == NULL)
    return false;

  bucket_name_ = GetXmlChildNodeText(root_node, "Bucket");
  prefix_ = GetXmlChildNodeText(root_node, "Prefix");
  key_marker_ = GetXmlChildNodeText(root_node, "KeyMarker");
  upload_id_marker_ = GetXmlChildNodeText(root_node, "UploadIdMarker");
  next_key_marker_ = GetXmlChildNodeText(root_node, "NextKeyMarker");
  next_upload_id_marker_ = GetXmlChildNodeText(root_node, "NextUploadIdMarker");
  delimiter_ = GetXmlChildNodeText(root_node, "Delimiter");
  prefix_ = GetXmlChildNodeText(root_node, "Prefix");
  max_uploads_ = atoi(GetXmlChildNodeText(root_node, "MaxUploads"));
  is_truncated_ = StringToBool(GetXmlChildNodeText(root_node, "IsTruncated"));

  TiXmlNode* upload_node = root_node->FirstChild("Upload");
  while (upload_node != NULL) {
    MultipartUpload upload;

    upload.SetKey(GetXmlChildNodeText(upload_node, "Key"));
    upload.SetUploadId(GetXmlChildNodeText(upload_node, "UploadId"));
    upload.SetInitiated(GetXmlChildNodeText(upload_node, "Initiated"));
    uploads_.push_back(upload);
    upload_node = upload_node->NextSibling("Upload");
  }

  return true;
}

}  // namespace oss
