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

#include "oss_sdk_cpp/http/http_engine_output.h"

namespace oss {

HttpEngineOutput::HttpEngineOutput()
  : http_status_code(0) {
}

HttpEngineOutput::~HttpEngineOutput() {
}

// move assignment
HttpEngineOutput& HttpEngineOutput::operator=(HttpEngineOutput&& rhs) {
  oss_exception = std::move(rhs.oss_exception);
  code = std::move(rhs.code);
  response = std::move(rhs.response);
  headers = std::move(rhs.headers);
  http_status_code = rhs.http_status_code;
  rhs.http_status_code = 0;

  return *this;
}

// move constructor.
HttpEngineOutput::HttpEngineOutput(HttpEngineOutput&& rhs)
  : response(std::move(rhs.response)),
    http_status_code(rhs.http_status_code),
    oss_exception(std::move(rhs.oss_exception)),
    code(std::move(rhs.code)),
    headers(std::move(rhs.headers)) {
  rhs.http_status_code = 0;
}

Status HttpEngineOutput::ToStatus() {
  Status status;
  status.MutableErrorCode().swap(code);
  status.MutableOssException().Swap(oss_exception);
  status.SetHttpStausCode(http_status_code);

  return status;
}

}  // namespace oss
