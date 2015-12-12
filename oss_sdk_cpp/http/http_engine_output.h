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

#ifndef OSS_SDK_CPP_HTTP_HTTP_ENGINE_OUTPUT_H_
#define OSS_SDK_CPP_HTTP_HTTP_ENGINE_OUTPUT_H_

#include <string>
#include <fstream>

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/oss/oss_status.h"

namespace oss {

class HttpEngineOutput {
  HttpEngineOutput();

  ~HttpEngineOutput();

  // move assignment
  HttpEngineOutput& operator=(HttpEngineOutput&& rhs);

  // move constructor.
  HttpEngineOutput(HttpEngineOutput&& rhs);

  Status ToStatus();

 private:
  // response buffer.
  std::string response;

  // http status code from server.
  HttpStatusType http_status_code;

  // oss exception.
  OssException oss_exception;

  // error code.
  std::string  code;

  // header received from server.
  StringMap headers;

  friend class HttpEngine;
  friend class OssClient;
  friend class HttpEngineTest;
};

}  // namespace oss
#endif  // OSS_SDK_CPP_HTTP_HTTP_ENGINE_OUTPUT_H_
