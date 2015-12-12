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

#ifndef OSS_SDK_CPP_HTTP_HTTP_ENGINE_INPUT_H_
#define OSS_SDK_CPP_HTTP_HTTP_ENGINE_INPUT_H_

#include <string>
#include <fstream>

#include "oss_sdk_cpp/base/base.h"

namespace oss {

class HttpEngineInput {
  HttpEngineInput();

 private:
  // http method for this request.
  std::string method;

  // http content type.
  std::string content_type;

  // date time in GMT format.
  std::string gmt_datetime;

  // the full url used in curl.
  std::string url;

  // http headers in request.
  StringMap headers;

  // upload data from this buffer.
  const std::string* input_buffer;

  // upload data from this file.
  std::string input_filename;

  // upload data from this stream.
  std::ifstream* input_stream;

  // how many bytes should read from stream, if -1, read to eof,
  // otherwise read stream_bytes exactly.
  int64_t stream_bytes;

  // limit response size to avoid "out of memory"
  int response_size_limit;

  // response buffer.
  std::string response;

  // download to this file.
  std::string output_path;

  // download to this stream.
  std::ofstream* output_stream;

  friend class HttpEngine;
  friend class OssClient;
  friend class HttpEngineTest;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_HTTP_HTTP_ENGINE_INPUT_H_
