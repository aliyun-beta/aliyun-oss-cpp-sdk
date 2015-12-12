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

#include <apr_strings.h>
#include <tinyxml.h>

#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/utils/string_utils.h"
#include "oss_sdk_cpp/utils/xml_utils.h"

#include "oss_sdk_cpp/message/list_parts_result.h"

namespace oss {

ListPartsResult::ListPartsResult()
  : part_number_marker_(0),
    next_part_number_marker_(0),
    max_parts(0),
    is_truncated_(false) {
}

ListPartsResult::~ListPartsResult() {
}

const std::list<UploadPart>& ListPartsResult::GetParts() const {
  return parts_;
}

const std::string& ListPartsResult::GetBucketName() const {
  return bucket_name_;
}

const std::string& ListPartsResult::GetKey() const {
  return key_;
}

const std::string& ListPartsResult::GetUploadId() const {
  return upload_id_;
}

const std::string& ListPartsResult::GetStorageClass() const {
  return storage_class_;
}

int ListPartsResult::GetPartNumberMarker() const {
  return part_number_marker_;
}

int ListPartsResult::GetNextPartNumberMarker() const {
  return next_part_number_marker_;
}

int ListPartsResult::GetMaxParts() const {
  return max_parts;
}

bool ListPartsResult::GetIsTruncated() const {
  return is_truncated_;
}

bool ListPartsResult::DeserializeFromXml(const std::string& content) {
  TiXmlDocument doc;
  if (doc.Parse(content.c_str(), 0, TIXML_ENCODING_UTF8) == NULL)
    return false;

  TiXmlNode* root_node = doc.FirstChild("ListPartsResult");
  if (root_node == NULL)
    return false;

  bucket_name_ = GetXmlChildNodeText(root_node, "Bucket");
  key_ = GetXmlChildNodeText(root_node, "Key");
  upload_id_ = GetXmlChildNodeText(root_node, "UploadId");
  storage_class_ = GetXmlChildNodeText(root_node, "StorageClass");
  part_number_marker_ =
    atoi(GetXmlChildNodeText(root_node, "PartNumberMarker"));
  next_part_number_marker_ =
    atoi(GetXmlChildNodeText(root_node, "NextPartNumberMarker"));
  max_parts = atoi(GetXmlChildNodeText(root_node, "MaxParts"));
  is_truncated_ = StringToBool(GetXmlChildNodeText(root_node, "IsTruncated"));

  TiXmlNode* part_node = root_node->FirstChild("Part");
  while (part_node != NULL) {
    UploadPart part;

    part.SetPartNumber(atoi(GetXmlChildNodeText(part_node, "PartNumber")));
    part.SetEtag(GetXmlChildNodeText(part_node, "ETag"));
    part.SetLastModified(GetXmlChildNodeText(part_node, "LastModified"));
    part.SetSize(apr_atoi64(GetXmlChildNodeText(part_node, "Size")));
    parts_.push_back(part);
    part_node = part_node->NextSibling("Part");
  }

  return true;
}

}  // namespace oss
