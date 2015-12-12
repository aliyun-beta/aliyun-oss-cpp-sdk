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

#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/base/string_piece.h"
#include "oss_sdk_cpp/base/sys_string_conversions.h"

#include "oss_sdk_cpp/utils/sign_utils.h"
#include "oss_sdk_cpp/utils/http_utils.h"
#include "oss_sdk_cpp/utils/apr_utils.h"
#include "oss_sdk_cpp/utils/string_utils.h"
#include "oss_sdk_cpp/utils/utils.h"

#include "oss_sdk_cpp/http/http_engine.h"
#include "oss_sdk_cpp/http/http_engine_input.h"
#include "oss_sdk_cpp/http/http_engine_output.h"
#include "oss_sdk_cpp/http/http_headers.h"

#include "oss_sdk_cpp/oss/oss_exception.h"
#include "oss_sdk_cpp/oss/oss_error_code.h"
#include "oss_sdk_cpp/oss/oss_client.h"

namespace oss {

OssClient::~OssClient() {
}

OssClient::OssClient(const std::string& access_key_id,
                     const std::string& access_key_secret)
  : access_key_id_(access_key_id),
    access_key_secret_(access_key_secret) {
  unit_test_mode_ = false;
}

OssClient::OssClient(const std::string& endpoint,
                     const std::string& access_key_id,
                     const std::string& access_key_secret,
                     const ClientConfiguration& config)
  : access_key_id_(access_key_id),
    access_key_secret_(access_key_secret),
    endpoint_(endpoint),
    client_config_(config) {
  ParseEndpoint(endpoint_);
  engine_.reset(new HttpEngine(endpoint, config.http_config));
  unit_test_mode_ = false;
}

Status OssClient::CreateBucket(const std::string& bucket_name,
                               const std::string& acl) {
  HttpEngineInput engine_input;
  engine_input.method = kHttpPut;
  engine_input.url = bucket_name + "." + endpoint_;
  engine_input.headers[kOssAcl] = acl;
  auto resource = "/" + bucket_name + "/";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::DeleteBucket(const std::string& bucket_name) {
  HttpEngineInput engine_input;
  engine_input.method = kHttpDelete;
  engine_input.url = bucket_name + "." + endpoint_;
  auto resource = "/" + bucket_name + "/";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::SetBucketAcl(const std::string& bucket_name,
                               const std::string& acl) {
  HttpEngineInput engine_input;
  engine_input.method = kHttpPut;
  engine_input.url = bucket_name + "." + endpoint_  + "/" + "?acl";
  engine_input.headers[kOssAcl] = acl;
  auto resource = "/" + bucket_name + "/" + "?acl";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::GetBucketAcl(const std::string& bucket_name,
                               GetBucketAclResult* result) {
  HttpEngineInput engine_input;
  engine_input.method = kHttpGet;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + "?acl";
  auto resource = "/" + bucket_name + "/" + "?acl";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::GetBucketAcl(const std::string& bucket_name,
                               std::string* acl) {
  GetBucketAclResult result;
  auto status = GetBucketAcl(bucket_name, &result);
  if (status.Ok()) {
    *acl = result.GetAcl();
  }

  return status;
}

Status OssClient::BucketExists(const std::string& bucket_name,
                               bool* exist) {
  std::string acl;
  auto status = GetBucketAcl(bucket_name, &acl);
  if (!status.Ok()) {
    if (status.ErrorCode() == oss_error_code::kNoSuchBucket) {
      *exist = false;
      status.SetErrorCode("");
    }
  } else {
    *exist = true;
  }

  return status;
}

Status OssClient::GetBucketLocation(const std::string& bucket_name,
                                    std::string* location) {
  HttpEngineInput engine_input;
  engine_input.method = kHttpGet;
  engine_input.url = bucket_name + "." + endpoint_ + "/?location";
  auto resource = "/" + bucket_name + "/?location";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    GetBucketLocationResult result;
    if (!result.DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    } else {
      *location = result.GetLocation();
    }
  }

  return status;
}

Status OssClient::GetBucketLogging(const std::string& bucket_name,
                                   GetBucketLoggingResult* result) {
  HttpEngineInput engine_input;
  engine_input.method = kHttpGet;
  engine_input.url = bucket_name + "." + endpoint_ + "/?logging";
  auto resource = "/" + bucket_name + "/?logging";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::SetBucketLogging(const SetBucketLoggingRequest& request) {
  auto& bucket_name = request.GetSourceBucket();

  HttpEngineInput engine_input;
  auto body = request.SerializeToXml();
  engine_input.input_buffer = &body;
  engine_input.method = kHttpPut;
  engine_input.url = bucket_name + "." + endpoint_ + "/?logging";
  auto resource = "/" + bucket_name + "/?logging";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::DeleteBucketLogging(const std::string& bucket_name) {
  return DeleteBucketConfig(bucket_name, "logging");
}

Status OssClient::GetBucketWebsite(const std::string& bucket_name,
                                   GetBucketWebsiteResult* result) {
  HttpEngineInput engine_input;
  engine_input.method = kHttpGet;
  engine_input.url = bucket_name + "." + endpoint_ + "/?website";
  auto resource = "/" + bucket_name + "/?website";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  Status status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::SetBucketWebsite(const SetBucketWebsiteRequest& request) {
  auto& bucket_name = request.GetBucketName();

  HttpEngineInput engine_input;
  auto body = request.SerializeToXml();
  engine_input.input_buffer = &body;
  engine_input.method = kHttpPut;
  engine_input.url = bucket_name + "." + endpoint_ + "/?website";
  auto resource = "/" + bucket_name + "/?website";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::SetBucketWebsite(const std::string& bucket_name,
                                   const std::string& index_page,
                                   const std::string& error_page) {
  SetBucketWebsiteRequest request(bucket_name, index_page, error_page);
  return SetBucketWebsite(request);
}

Status OssClient::DeleteBucketWebsite(const std::string& bucket_name) {
  return DeleteBucketConfig(bucket_name, "website");
}

Status OssClient::GetBucketCors(const std::string& bucket_name,
                                GetBucketCorsResult* result) {
  HttpEngineInput engine_input;
  engine_input.method = kHttpGet;
  engine_input.url = bucket_name + "." + endpoint_ + "/?cors";
  auto resource = "/" + bucket_name + "/?cors";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  Status status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::SetBucketCors(const SetBucketCorsRequest& request) {
  auto& bucket_name = request.GetBucketName();

  HttpEngineInput engine_input;
  auto body = request.SerializeToXml();
  engine_input.input_buffer = &body;
  engine_input.method = kHttpPut;
  engine_input.url = bucket_name + "." + endpoint_ + "/?cors";
  auto resource = "/" + bucket_name + "/?cors";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::DeleteBucketCors(const std::string& bucket_name) {
  return DeleteBucketConfig(bucket_name, "cors");
}

Status OssClient::GetBucketReferer(const std::string& bucket_name,
                                   GetBucketRefererResult* result) {
  HttpEngineInput engine_input;
  engine_input.method = kHttpGet;
  engine_input.url = bucket_name + "." + endpoint_ + "/?referer";
  auto resource = "/" + bucket_name + "/?referer";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::SetBucketReferer(const SetBucketRefererRequest& request) {
  auto& bucket_name = request.GetBucketName();

  HttpEngineInput engine_input;
  auto body = request.SerializeToXml();
  engine_input.input_buffer = &body;
  engine_input.method = kHttpPut;
  engine_input.url = bucket_name + "." + endpoint_ + "/?referer";
  auto resource = "/" + bucket_name + "/?referer";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::GetBucketLifecycle(const std::string& bucket_name,
                                     GetBucketLifecycleResult* result) {
  HttpEngineInput engine_input;
  engine_input.method = kHttpGet;
  engine_input.url = bucket_name + "." + endpoint_ + "/?lifecycle";
  auto resource = "/" + bucket_name + "/?lifecycle";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::SetBucketLifecycle(const SetBucketLifecycleRequest &request) {
  auto& bucket_name = request.GetBucketName();

  HttpEngineInput engine_input;
  auto body = request.SerializeToXml();
  engine_input.input_buffer = &body;
  engine_input.method = kHttpPut;
  engine_input.url = bucket_name + "." + endpoint_ + "/?lifecycle";
  auto resource = "/" + bucket_name + "/?lifecycle";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::DeleteBucketLifecycle(const std::string& bucket_name) {
  return DeleteBucketConfig(bucket_name, "lifecycle");
}

Status OssClient::CreateFolder(const std::string& bucket_name,
                               const std::string& folder_name) {
  auto new_folder_name = folder_name;
  if (!EndsWith(folder_name, "/")) {
    new_folder_name += "/";
  }
  return PutString(bucket_name, new_folder_name, "");
}

Status OssClient::ObjectExists(const std::string& bucket_name,
                               const std::string& key,
                               bool* exist) {
  std::unique_ptr<ObjectMetadata> object_meta_data;
  auto status = GetObjectMetadata(bucket_name, key, &object_meta_data);
  if (!status.Ok()) {
    if (status.ErrorCode() == oss_error_code::kNoSuchKey ||
        status.ErrorCode() == oss_error_code::kNoSuchBucket) {
      *exist = false;
      status.SetErrorCode("");
    } else {
      if (status.HttpStausCode() == 404) {
        *exist = false;
        status.SetErrorCode("");
      }
    }
  } else {
    *exist = true;
  }

  return status;
}

Status OssClient::PutString(const std::string& bucket_name,
                            const std::string& key,
                            const std::string& str,
                            const ObjectMetadata* object_metadata) {
  HttpEngineInput engine_input;
  engine_input.headers[oss::http::kContentType] = kObjectDefaultContentType;
  engine_input.method = kHttpPut;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + UrlEscape(key);
  engine_input.input_buffer = &str;
  if (object_metadata != NULL)
    object_metadata->AddToParameterList(&engine_input.headers);
  auto resource = "/" + bucket_name + "/" + key;

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::PutObject(const std::string& bucket_name,
                            const std::string& key,
                            const std::string& file_path,
                            const ObjectMetadata* object_metadata) {
  return PutObject(bucket_name, key, file_path, -1, object_metadata);
}

Status OssClient::PutObject(const std::string& bucket_name,
                            const std::string& key,
                            const std::string& file_path,
                            int64_t stream_bytes,
                            const ObjectMetadata* object_metadata) {
  HttpEngineInput engine_input;
  engine_input.headers[oss::http::kContentType] = kObjectDefaultContentType;
  engine_input.method = kHttpPut;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + UrlEscape(key);
  engine_input.input_filename = file_path;
  engine_input.stream_bytes = stream_bytes;
  if (object_metadata != NULL)
    object_metadata->AddToParameterList(&engine_input.headers);
  auto resource = "/" + bucket_name + "/" + key;

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::PutObject(const std::string& bucket_name,
                            const std::string& key,
                            std::ifstream* stream,
                            const ObjectMetadata* object_metadata) {
  return PutObject(bucket_name, key, stream, -1, object_metadata);
}

Status OssClient::PutObject(const std::string& bucket_name,
                            const std::string& key,
                            std::ifstream* stream,
                            int64_t stream_bytes,
                            const ObjectMetadata* object_metadata) {
  HttpEngineInput engine_input;
  engine_input.headers[oss::http::kContentType] = kObjectDefaultContentType;
  engine_input.method = kHttpPut;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + UrlEscape(key);
  engine_input.input_stream = stream;
  engine_input.stream_bytes = stream_bytes;
  if (object_metadata != NULL)
    object_metadata->AddToParameterList(&engine_input.headers);
  auto resource = "/" + bucket_name + "/" + key;

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::DeleteObject(const std::string& bucket_name,
                               const std::string& key) {
  HttpEngineInput engine_input;
  engine_input.method = kHttpDelete;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + UrlEscape(key);
  auto resource = "/" + bucket_name + "/" + key;

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::DeleteMultipleObjects(
  const DeleteMultipleObjectsRequest& request,
  DeleteMultipleObjectsResult* result) {
  auto& bucket_name = request.GetBucketName();
  auto body = request.SerializeToXml();
  auto digest = AprBase64Encode(AprComputeMd5(body));

  HttpEngineInput engine_input;
  engine_input.headers[http::kContentMd5] = digest;
  engine_input.input_buffer = &body;
  engine_input.method = kHttpPost;
  engine_input.url = bucket_name + "." + endpoint_ + "/?delete";
  auto resource = "/" + bucket_name + "/?delete";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  Status status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::OptionObject(const OptionObjectRequest& request,
                               OptionObjectResult* result) {
  auto& bucket_name = request.GetBucketName();

  HttpEngineInput engine_input;
  engine_input.headers["Origin"] = request.GetOrigin();
  engine_input.headers["Access-Control-Request-Method"]
    = request.GetRequestMethod();
  engine_input.headers["Access-Control-Request-Headers"]
    = request.GetRequestHeaders();

  engine_input.method = kHttpOptions;
  engine_input.url = bucket_name + "." + endpoint_ + "/" +
                     UrlEscape(request.GetKey());
  auto resource = "/" + request.GetKey();

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    result->ParseFromHeader(engine_output.headers);
  }

  return status;
}

Status OssClient::CopyObject(const CopyObjectRequest& request,
                             CopyObjectResult* result) {
  auto& bucket_name = request.GetTargetBucket();
  auto& key = request.GetTargetKey();

  HttpEngineInput engine_input;
  request.AddToParameterList(&engine_input.headers);
  engine_input.method = kHttpPut;
  engine_input.content_type = kObjectDefaultContentType;
  // resource should be target.
  engine_input.url = bucket_name + "." + endpoint_ + "/" +  UrlEscape(key);
  auto resource = "/" + bucket_name + "/" + key;

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::GetObject(const GetObjectRequest & request) {
  auto& bucket_name = request.GetBucket();
  auto& key = request.GetKey();

  HttpEngineInput engine_input;
  request.AddToParameterList(&engine_input.headers);
  engine_input.method = kHttpGet;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + UrlEscape(key);
  auto resource = "/" + bucket_name + "/" + key;

  engine_input.output_path = request.GetFilePath();
  engine_input.output_stream = request.GetOutputStream();

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::ListBuckets(const ListBucketsRequest& request,
                              ListBucketsResult* result) {
  HttpEngineInput engine_input;
  request.AddToParameterList(&engine_input.headers);
  engine_input.method = kHttpGet;
  engine_input.url = endpoint_;
  auto resource = "/";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::ListBuckets(std::vector<Bucket>* buckets) {
  ListBucketsRequest request;
  ListBucketsResult result;
  auto status = ListBuckets(request, &result);
  if (status.Ok()) {
    result.MutableBuckets().swap(*buckets);
  }

  return status;
}

Status OssClient::DeleteBucketConfig(const std::string& bucket_name,
                                     const std::string& config_name) {
  HttpEngineInput engine_input;
  engine_input.method = kHttpDelete;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + "?" + config_name;
  auto resource = "/" + bucket_name + "/" + "?" + config_name;

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::ListObjects(const ListObjectsRequest& request,
                              ListObjectsResult* result) {
  auto& bucket_name = request.GetBucketName();
  // do not sign for this request.
  auto query_string = request.BuildQueryString();

  HttpEngineInput engine_input;
  engine_input.method = kHttpGet;
  engine_input.url = bucket_name + "." + endpoint_ + "/?" + query_string;
  auto resource = "/" + bucket_name + "/";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::InitiateMultipartUpload(
  const InitiateMultipartUploadRequest& request,
  InitiateMultipartUploadResult* result) {
  auto& bucket_name = request.GetBucketName();
  // must sign query parameters for this request.
  auto query_string = request.BuildQueryString();

  HttpEngineInput engine_input;
  engine_input.method = kHttpPost;
  // add query_string to resource to sign.
  engine_input.url = bucket_name + "." + endpoint_ + "/" + query_string;
  auto resource = "/" + bucket_name + "/" + query_string;

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::UploadPart(const UploadPartRequest& request,
                             UploadPartResult* result) {
  auto& bucket_name = request.GetBucketName();
  // must sign for this request.
  auto query_string = request.BuildQueryString();

  HttpEngineInput engine_input;
  if (!request.GetMd5Digest().empty()) {
    engine_input.headers[http::kContentMd5] = request.GetMd5Digest();
  }

  engine_input.method = kHttpPut;
  engine_input.headers[oss::http::kContentType] = kObjectDefaultContentType;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + query_string;
  auto resource = "/" + bucket_name + "/" + query_string;

  engine_input.input_stream = request.GetInputStream();
  engine_input.stream_bytes = request.GetPartSize();

  auto engine_output =  ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    result->ParseFromHeader(engine_output.headers);
  }

  return status;
}

Status OssClient::AppendObject(const AppendObjectRequest& request) {
  auto& bucket_name = request.GetBucketName();
  // must sign for this request.
  auto query_string = request.BuildQueryString();
  HttpEngineInput engine_input;
  engine_input.method = kHttpPost;
  engine_input.headers[oss::http::kContentType] = kObjectDefaultContentType;
  engine_input.content_type = kObjectDefaultContentType;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + query_string;
  auto resource = "/" + bucket_name + "/" + query_string;
  engine_input.input_filename = request.GetFilePath();

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::AppendObject(const AppendObjectRequest& request,
                               const ObjectMetadata* object_metadata) {
  AppendObjectResult result;
  return AppendObject(request, object_metadata, &result);
}

Status OssClient::AppendObject(const AppendObjectRequest& request,
                               const ObjectMetadata* object_metadata,
                               AppendObjectResult* result) {
  auto& bucket_name = request.GetBucketName();
  // must sign for this request.
  std::string query_string = request.BuildQueryString();
  HttpEngineInput engine_input;
  engine_input.method = kHttpPost;
  engine_input.headers[oss::http::kContentType] = kObjectDefaultContentType;
  engine_input.content_type = kObjectDefaultContentType;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + query_string;
  if (object_metadata != NULL)
    object_metadata->AddToParameterList(&engine_input.headers);
  auto resource = "/" + bucket_name + "/" + query_string;
  engine_input.input_filename = request.GetFilePath();

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    result->ParseFromHeader(engine_output.headers);
  }

  return engine_output.ToStatus();
}

Status OssClient::UploadPartCopy(const UploadPartCopyRequest& request,
                                 UploadPartCopyResult* result) {
  auto& bucket_name = request.GetTargetBucket();
  auto query_string = request.BuildQueryString();

  HttpEngineInput engine_input;
  request.AddToParameterList(&engine_input.headers);
  engine_input.method = kHttpPut;
  engine_input.headers[oss::http::kContentType] = kObjectDefaultContentType;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + query_string;
  auto resource = "/" + bucket_name + "/" + query_string;

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::CompleteMultipartUpload(
  const CompleteMultipartUploadrequest& request,
  CompleteMultipartUploadResult* result) {
  auto& bucket_name = request.GetBucketName();
  // must sign for this request.
  auto query_string = request.BuildQueryString();
  auto body = request.SerializeToXml();

  HttpEngineInput engine_input;
  engine_input.input_buffer = &body;
  engine_input.method = kHttpPost;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + query_string;
  auto resource = "/" + bucket_name + "/" + query_string;

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::AbortMultipartUpload(const std::string& bucket_name,
                                       const std::string& key,
                                       const std::string& upload_id) {
  auto query_string = key + "?uploadId=" + upload_id;

  HttpEngineInput engine_input;
  engine_input.method = kHttpDelete;
  engine_input.url = bucket_name + "." + endpoint_ + "/" + query_string;
  auto resource = "/" + bucket_name + "/" + query_string;

  auto engine_output = ExecuteHttp(&engine_input, resource);
  return engine_output.ToStatus();
}

Status OssClient::ListMultipartUploads(
  const ListMultipartUploadsRequest& request,
  ListMultipartUploadsResult* result) {
  auto& bucket_name = request.GetBucketName();
  HttpEngineInput engine_input;

  request.AddToParameterList(&engine_input.headers);
  engine_input.method = kHttpGet;
  engine_input.url = bucket_name + "." + endpoint_ + "/?uploads";
  auto resource = "/" + bucket_name + "/?uploads";

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::ListParts(const ListPartsRequest& request,
                            ListPartsResult* result) {
  auto& bucket_name = request.GetBucketName();
  auto& key = request.GetKey();
  const auto upload_id = request.GetUploaId();
  auto url_parameters = key + "?uploadId=" + upload_id;

  HttpEngineInput engine_input;
  engine_input.method = kHttpGet;
  auto resource = "/" + bucket_name + "/" + url_parameters;
  engine_input.url = bucket_name + "." + endpoint_ + "/"
                     + UrlEscape(key) + "?" + request.BuildQueryString();

  auto engine_output = ExecuteHttp(&engine_input, resource);
  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    if (!result->DeserializeFromXml(engine_output.response)) {
      status.SetErrorCode(oss_error_code::kParseXmlFailed);
    }
  }

  return status;
}

Status OssClient::GetObjectMetadata(
  const std::string& bucket_name,
  const std::string& key,
  std::unique_ptr<ObjectMetadata>* object_meta_data) {
  HttpEngineInput engine_input;
  engine_input.method = "HEAD";
  engine_input.url = bucket_name + "." + endpoint_ + "/" + UrlEscape(key);
  auto resource = "/" + bucket_name + "/" + key;

  auto engine_output = ExecuteHttp(&engine_input, resource);

  auto status = engine_output.ToStatus();
  if (status.Ok()) {
    (*object_meta_data).reset(new ObjectMetadata);
    (*object_meta_data)->SetMetadata(engine_output.headers);
  }

  return status;
}

std::string OssClient::CalculateAuthorization(const std::string& resource,
    const HttpEngineInput& input) {

  auto authorizatoin =
    BuildOssAuthorization(access_key_secret_,
                          access_key_id_,
                          input.method,
                          input.gmt_datetime,
                          resource,
                          input.headers);

  return authorizatoin;
}

HttpEngineOutput OssClient::ExecuteHttp(HttpEngineInput* input,
                                        const std::string& resource) {
  // prepend protocol to url.
  input->url.insert(0, protocol_);
  std::string authorization = CalculateAuthorization(resource, *input);
  input->headers[http::kAuthorization] = authorization;

  auto output = engine_->Execute(input);
  if (output.http_status_code == 0) {
    // error happened before http query.
    return output;
  }

  // http query succeed.
  if (output.http_status_code == 200 ||
      output.http_status_code == 201 ||
      output.http_status_code == 204 ||
      output.http_status_code == 206) {
    return output;
  }

  // http query failed.
  if (output.response.empty()) {
    // failed, but no error message.
  }

  // parse error message.
  if (!output.oss_exception.FromXml(output.response)) {
    output.code = oss_error_code::kParseXmlFailed;
  } else {
    output.code = output.oss_exception.GetCode();
  }

  if (unit_test_mode_) {
    output.code = "";
  }

  return output;
}

void OssClient::ParseEndpoint(const std::string& endpoint) {
  std::string new_endpoint;
  TrimWhiteSpaces(endpoint, &new_endpoint);
  if (StartsWith(new_endpoint, kHttps)) {
    protocol_ = kHttps;
    endpoint_ = new_endpoint.substr(strlen(kHttps));
  } else if (StartsWith(new_endpoint, kHttp)) {
    protocol_ = kHttp;
    endpoint_ = new_endpoint.substr(strlen(kHttp));
  } else {
    protocol_ = kHttp;
    endpoint_ = new_endpoint;
  }
}

void OssClient::SetEndpoint(const std::string& endpoint) {
  ParseEndpoint(endpoint);
}

void OssClient::SetUnitTestMode() {
  unit_test_mode_ = true;
  if (engine_) {
    engine_->SetUnitTestMode();
  }
}

}  // namespace oss
