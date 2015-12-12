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

#ifndef OSS_SDK_CPP_OSS_OSS_ERROR_CODE_H_
#define OSS_SDK_CPP_OSS_OSS_ERROR_CODE_H_

namespace oss {

namespace oss_error_code {

extern const char kCurlCreateInstanceFailed[];

extern const char kOpenFileFailed[];

extern const char kParseXmlFailed[];

extern const char kAccessDenied[];

extern const char kBucketAlreadyExists[];

extern const char kBucketNotEmtpy[];

extern const char kEntityTooLarge[];

extern const char kEntityTooSmall[];

extern const char kFileGroupTooLarge[];

extern const char kInvalidLinkName[];

extern const char kLinkPartNotExist[];

extern const char kObjectLinkTooLarge[];

extern const char kFieldItemTooLong[];

extern const char kFilePartInterity[];

extern const char kFilePartNotExist[];

extern const char kFilePartStale[];

extern const char kIncorrectNumberOfFilesInPOSTRequest[];

extern const char kInvalidArgument[];

extern const char kInvalidAccessKeyId[];

extern const char kInvalidBucketName[];

extern const char kInvalidDigest[];

extern const char kInvalidTargetBucketForLogging[];

extern const char kInvalidObjectName[];

extern const char kInvalidPart[];

extern const char kInvalidPartOrder[];

extern const char kInvalidPolicyDocument[];

extern const char kInternalError[];

extern const char kMalformedXML[];

extern const char kMalformedPostRequest[];

extern const char kMaxPostPreDataLengthExceededError[];

extern const char kMethodNotAllowed[];

extern const char kMissingArgument[];

extern const char kMissingContentLength[];
//
extern const char kNoSuchBucket[];

extern const char kNoSuchKey[];

extern const char kNoSuchUpload[];

extern const char kNotImplemented[];

extern const char kPreconditionFailed[];

extern const char kRequestTimeTooSkewed[];

extern const char kRequestTimeout[];

extern const char kRequestIsNotMultiPartContent[];

extern const char kSignatureDoesNotMatch[];

extern const char kTooManyBuckets[];

extern const char kInvalidEncryptionAlgorithmError[];

extern const char kNoSuchWebsiteConfiguration[];

extern const char kNoSuchCorsConfiguration[];

extern const char kNotModified[];
}  // namespace oss_error_code

}  // namespace oss

#endif  // OSS_SDK_CPP_OSS_OSS_ERROR_CODE_H_
