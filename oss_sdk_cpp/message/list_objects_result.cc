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

#include "oss_sdk_cpp/message/list_objects_result.h"

namespace oss {

ListObjectsResult::ListObjectsResult()
  : is_truncated_(false),
    max_keys_(0) {
}

ListObjectsResult::~ListObjectsResult() {
}

const std::list<ObjectContent>& ListObjectsResult::GetContents() const {
  return contents_;
}

bool ListObjectsResult::GetIsTruncated() const {
  return is_truncated_;
}

int ListObjectsResult::GetMaxKeys() const {
  return max_keys_;
}

const std::string& ListObjectsResult::GetMarker() const {
  return marker_;
}

const std::string& ListObjectsResult::GetPrefix() const {
  return prefix_;
}

const std::string& ListObjectsResult::GetDelimiter() const {
  return delimiter_;
}

const std::string& ListObjectsResult::GetBucketName() const {
  return bucket_name_;
}

const std::string& ListObjectsResult::GetNextMarker() const {
  return marker_;
}

std::list<ObjectContent>& ListObjectsResult::MutableContents() {
  return contents_;
}

const StringList& ListObjectsResult::GetCommonPrefixes() const {
  return common_prefixes_;
}

bool ListObjectsResult::DeserializeFromXml(const std::string& text) {
  TiXmlDocument doc;
  if (doc.Parse(text.c_str(), 0, TIXML_ENCODING_UTF8) == NULL)
    return false;

  TiXmlNode* root_node = doc.FirstChild("ListBucketResult");
  if (root_node == NULL)
    return false;

  bucket_name_ = GetXmlChildNodeText(root_node, "Name");
  is_truncated_ = StringToBool(GetXmlChildNodeText(root_node, "IsTruncated"));
  prefix_ = GetXmlChildNodeText(root_node, "Prefix");
  marker_ = GetXmlChildNodeText(root_node, "Marker");
  max_keys_ = atoi(GetXmlChildNodeText(root_node, "MaxKeys"));
  marker_ = GetXmlChildNodeText(root_node, "Delimiter");
  marker_ = GetXmlChildNodeText(root_node, "NextMarker");

  TiXmlNode* contents_node = root_node->FirstChild("Contents");
  while (contents_node != NULL) {
    ObjectContent content;

    content.SetKey(GetXmlChildNodeText(contents_node, "Key"));
    content.SetLastModified(GetXmlChildNodeText(contents_node, "LastModified"));
    content.SetEtag(GetXmlChildNodeText(contents_node, "ETag"));
    content.SetType(GetXmlChildNodeText(contents_node, "Type"));
    content.SetSize(atoi(GetXmlChildNodeText(contents_node, "Size")));
    content.SetStorageClass(GetXmlChildNodeText(contents_node, "StorageClass"));

    // Owner
    TiXmlNode* owner_node = contents_node->FirstChild("Owner");
    if (owner_node != NULL) {
      content.SetOwnerId(GetXmlChildNodeText(owner_node, "ID"));
      content.SetOwnerDisplayName(
        GetXmlChildNodeText(owner_node, "DisplayName"));
    }

    contents_.push_back(content);
    contents_node = contents_node->NextSibling("Contents");
  }

  TiXmlNode* common_prefixes_node = root_node->FirstChild("CommonPrefixes");
  while (common_prefixes_node != NULL) {
    std::string str = GetXmlChildNodeText(common_prefixes_node, "Prefix");
    common_prefixes_.push_back(str);
    common_prefixes_node = common_prefixes_node->NextSibling("CommonPrefixes");
  }

  return true;
}

}  // namespace oss
