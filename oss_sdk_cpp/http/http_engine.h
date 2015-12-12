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

#ifndef OSS_SDK_CPP_HTTP_HTTP_ENGINE_H_
#define OSS_SDK_CPP_HTTP_HTTP_ENGINE_H_

#include <string>
#include <fstream>
#include <mutex>

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/http/curl_warppers.h"
#include "oss_sdk_cpp/http/http_engine_input.h"
#include "oss_sdk_cpp/http/http_engine_output.h"
#include "oss_sdk_cpp/http/http_configuration.h"
#include "oss_sdk_cpp/oss/oss_status.h"

namespace oss {

class HttpEngine {
 public:
  explicit HttpEngine(const std::string& endpoint);

  HttpEngine(const std::string& endpoint,
             const HttpConfiguration& http_config);

  ~HttpEngine();

  HttpEngineOutput Execute(HttpEngineInput* input);

  // for unit test only.
  void SetUnitTestMode();

 private:
  // download, curl needs write data to user.
  static size_t WriteCallback(void *buffer, size_t size, size_t nmemb, void*);

  // upload, curl needs read data from user.
  static size_t ReadCallback(void *buffer, size_t size, size_t nmemb, void*);

  // header received.
  static size_t HeaderCallback(void *buffer, size_t size, size_t nmemb, void*);

 private:
  std::mutex mutex_;
  std::string endpoint_;
  CUrl curl_;
  HttpConfiguration http_config_;
  bool unit_test_mode_;

  friend class HttpEngineTest;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_HTTP_HTTP_ENGINE_H_
