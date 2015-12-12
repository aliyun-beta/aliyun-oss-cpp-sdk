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

#include "oss_sdk_cpp/utils/sign_utils.h"
#include "oss_sdk_cpp/utils/apr_utils.h"
#include "oss_sdk_cpp/utils/string_utils.h"
#include "oss_sdk_cpp/utils/utils.h"

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/oss/oss.h"

namespace oss {

std::string ComputeOssSignature(const std::string& access_key_secret,
                                const std::string& canonical_string) {
  unsigned char digest[20] = { 0 };
  AprHmacSha1(canonical_string, access_key_secret,
              reinterpret_cast<char*>(digest),
              sizeof(digest));
  std::string signature = AprBase64Encode(digest, sizeof(digest));
  return signature;
}

std::string BuildOssAuthorization(const std::string& access_key_secret,
                                  const std::string& access_key_id,
                                  const std::string& http_method,
                                  const std::string& gmt_datetime,
                                  const std::string& resource,
                                  const StringMap& headers) {
  std::string canonical_string =
    BuildCanonicalString(http_method,
                         gmt_datetime,
                         resource,
                         headers);

  std::string signature =
    ComputeOssSignature(access_key_secret, canonical_string);

  std::string output;
  output.reserve(1024);
  output.append("OSS ");
  output.append(access_key_id);
  output.append(":");
  output.append(signature);

  return output;
}

std::string BuildCanonicalString(const std::string& method,
                                 const std::string& gmt_date,
                                 const std::string& resource,
                                 const StringMap& headers) {
  std::string content_md5 = FindWithDefault(headers, "Content-MD5", "");
  std::string content_type = FindWithDefault(headers, "Content-Type", "");

  StringMap lower_headers;
  for (auto& kv : headers) {
    if (StartsWith(kv.first, kOssPrefix, false)) {
      lower_headers[ToLower(kv.first)] = kv.second;
    }
  }
  // std::map has a default predicate std::less, so the iteration is ascending.
  std::string canonicalized_headers;
  canonicalized_headers.reserve(1024);
  for (auto& kv : lower_headers) {
    canonicalized_headers.append(ToLower(kv.first));
    canonicalized_headers.append(":");
    canonicalized_headers.append(kv.second);
    canonicalized_headers.append("\n");
  }

  std::string result;
  result.reserve(1024);
  result.append(method).append("\n")
  .append(content_md5).append("\n")
  .append(content_type).append("\n")
  .append(gmt_date).append("\n")
  .append(canonicalized_headers)
  .append(resource);

  return result;
}

}  // namespace oss
