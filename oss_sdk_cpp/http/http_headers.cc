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

#include "oss_sdk_cpp/http/http_headers.h"

namespace oss {
namespace http {

const char kAuthorization[] = "Authorization";
const char kContentLength[] = "Content-Length";
const char kContentType[] = "Content-Type";
const char kDate[] = "Date";
const char kHost[] = "Host";
const char kUserAgent[] = "User-Agent";
const char kConnection[] = "Connection";
const char kEtag[] = "ETag";
const char kServer[] = "Server";
const char kLastModified[] = "Last-Modified";
const char kCacheControl[] = "Cache-Control";
const char kExpires[] = "Expires";
const char kRange[] = "Range";
const char kContentEncoding[] = "Content-Encoding";
const char kContentDisposition[] = "Content-Disposition";
const char kContentMd5[] = "Content-MD5";

const char kServerSideEncryption[] = "x-oss-server-side-encryption";
const char kOssRequestId[] = "x-oss-request-id";
const char kOssCopySource[] = "x-oss-copy-source";
const char kOssCopySourceIfMatch[] = "x-oss-copy-source-if-match";
const char kOssCopySourceIfNoneMatch[] = "x-oss-copy-source-if-none-match";
const char kOssCopySourceIfModifiedSince[] =
  "x-oss-copy-source-if-modified-since";
const char kOssCopySourceIfUnmodifiedSince[] =
  "x-oss-copy-source-if-unmodified-since";
const char kOssCopySourceRange[] = "x-oss-copy-source-range";
const char kOssMetadataDirective[] = "x-oss-metadata-directive";

}  // namespace http
}  // namespace oss
