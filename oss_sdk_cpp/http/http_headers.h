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

#ifndef OSS_SDK_CPP_HTTP_HTTP_HEADERS_H_
#define OSS_SDK_CPP_HTTP_HTTP_HEADERS_H_

#include <string>
#include <vector>
#include <list>

namespace oss {
namespace http {

extern const char kAuthorization[];
extern const char kContentLength[];
extern const char kContentType[];
extern const char kDate[];
extern const char kHost[];
extern const char kUserAgent[];
extern const char kConnection[];
extern const char kEtag[];
extern const char kServer[];
extern  const char kExpires[];
extern  const char kRange[];
extern const char kLastModified[];
extern  const char kContentMd5[];
extern  const char kCacheControl[];
extern  const char kContentEncoding[];
extern  const char kContentDisposition[];

extern const char kServerSideEncryption[];
extern const char kOssRequestId[];
extern const char kOssCopySource[];
extern const char kOssCopySourceIfMatch[];
extern const char kOssCopySourceIfNoneMatch[];
extern const char kOssCopySourceIfModifiedSince[];
extern const char kOssCopySourceIfUnmodifiedSince[];
extern const char kOssMetadataDirective[];
extern const char kOssCopySourceRange[];

}  // namespace http
}  // namespace oss

#endif  // OSS_SDK_CPP_HTTP_HTTP_HEADERS_H_
