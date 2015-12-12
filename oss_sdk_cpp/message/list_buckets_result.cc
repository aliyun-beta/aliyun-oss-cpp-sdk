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

#include "oss_sdk_cpp/message/list_buckets_result.h"

namespace oss {

ListBucketsResult::ListBucketsResult()
  : is_truncated_(false),
    max_keys_(0) {
}

ListBucketsResult::~ListBucketsResult() {
}

const std::vector<Bucket>& ListBucketsResult::GetBuckets() const {
  return buckets_;
}

const std::string& ListBucketsResult::GetOwnerId() const {
  return owner_id_;
}

const std::string& ListBucketsResult::GetOwnerDisplayName() const {
  return owner_display_name_;
}

bool ListBucketsResult::GetIsTruncated() const {
  return is_truncated_;
}

int ListBucketsResult::GetMaxKeys() const {
  return max_keys_;
}

const std::string& ListBucketsResult::GetMarker() const {
  return marker_;
}

const std::string& ListBucketsResult::GetNextMarker() const {
  return next_marker_;
}

const std::string& ListBucketsResult::GetPrefix() const {
  return prefix_;
}

std::vector<Bucket>& ListBucketsResult::MutableBuckets() {
  return buckets_;
}

bool ListBucketsResult::DeserializeFromXml(const std::string& content) {
  TiXmlDocument doc;
  if (doc.Parse(content.c_str(), 0, TIXML_ENCODING_UTF8) == NULL)
    return false;

  TiXmlNode* node = NULL;
  TiXmlNode* root_node = doc.FirstChild("ListAllMyBucketsResult");
  if (root_node == NULL)
    return false;

  // IsTruncated field is optional.
  node = root_node->FirstChild("IsTruncated");
  if (node != NULL) {
    is_truncated_ = StringToBool(node->ToElement()->GetText());
  }

  // Prefix field is optional.
  node = root_node->FirstChild("Prefix");
  if (node != NULL) {
    prefix_ = GetXmlNodeText(node);
  }

  // Marker field is optional.
  node = root_node->FirstChild("Marker");
  if (node != NULL) {
    marker_ = GetXmlNodeText(node);
  }

  // NextMarker field is optional.
  node = root_node->FirstChild("NextMarker");
  if (node != NULL) {
    next_marker_ = GetXmlNodeText(node);
  }

  // MaxKeys field is optional.
  node = root_node->FirstChild("MaxKeys");
  if (node != NULL) {
    max_keys_ = atoi(GetXmlNodeText(node));
  }

  // Owner
  TiXmlNode* owner_node = root_node->FirstChild("Owner");
  if (owner_node == NULL)
    return false;

  owner_id_ = GetXmlChildNodeText(owner_node, "ID");
  owner_display_name_ = GetXmlChildNodeText(owner_node, "DisplayName");

  TiXmlNode* buckets_node = root_node->FirstChild("Buckets");
  if (buckets_node == NULL)
    return false;

  TiXmlNode* bucket_node = buckets_node->FirstChild("Bucket");
  while (bucket_node != NULL) {
    Bucket bucket;

    bucket.SetName(GetXmlChildNodeText(bucket_node, "Name"));
    bucket.SetLocation(GetXmlChildNodeText(bucket_node, "Location"));
    bucket.SetCreationDate(GetXmlChildNodeText(bucket_node, "CreationDate"));

    buckets_.push_back(bucket);
    bucket_node = bucket_node->NextSibling("Bucket");
  }

  return true;
}

}  // namespace oss
