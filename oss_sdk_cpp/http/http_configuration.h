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

#ifndef OSS_SDK_CPP_HTTP_HTTP_CONFIGURATION_H_
#define OSS_SDK_CPP_HTTP_HTTP_CONFIGURATION_H_

#include <stdint.h>
#include <string>

namespace oss {

const int kMaxResponseBufferSize = 1024 * 1024;

struct HttpConfiguration {
  HttpConfiguration();

  HttpConfiguration(bool reuse,
                    const std::string& proxy_host,
                    int16_t proxy_port,
                    const std::string& proxy_username,
                    const std::string& proxy_password,
                    const std::string& proxy_domain,
                    int response_buffer_size = kMaxResponseBufferSize,
                    int64_t timeout_ms = -1);

 public:
  bool GetReuse() const;

  void SetReuse(bool reuse);

  const std::string& GetProxyHost() const;

  void SetProxyHost(const std::string& proxy_host);

  int16_t GetProxyPort() const;

  void SetProxyPort(int16_t proxy_port);

  const std::string& GetProxyUsername() const;

  void SetProxyUsername(const std::string& proxy_username);

  const std::string& GetProxyPassword() const;

  void SetProxyPassword(const std::string& proxy_password);

  const std::string& GetProxyDomain() const;

  void SetProxyDomain(const std::string& proxy_domain);

  int GetResponseBufferSize() const;

  void SetResponseBufferSize(int response_buffer_size);

  const std::string& GetUserAgent() const;

  void SetUserAgent(const std::string& user_agent);

  int64_t GetTimeoutMs() const;

  void SetTimeoutMs(int64_t timeout);

 private:
  bool reuse_;
  std::string proxy_host_;
  int16_t proxy_port_;
  std::string proxy_username_;
  std::string proxy_password_;
  std::string proxy_domain_;
  int response_buffer_size_;
  std::string user_agent_;
  // total time limit for request, including connection phase and data phase.
  // in milliseconds.
  int64_t timeout_ms_;
};

}  // namespace oss

#endif  // OSS_SDK_CPP_HTTP_HTTP_CONFIGURATION_H__
