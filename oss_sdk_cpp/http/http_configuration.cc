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

#include <string>
#include "oss_sdk_cpp/http/http_configuration.h"

namespace oss {

const char kDefaultHttpUserAgent[] = "aliyun-sdk-cpp 1.0";

HttpConfiguration::HttpConfiguration()
  : reuse_(true),
    proxy_port_(808),
    response_buffer_size_(kMaxResponseBufferSize),
    timeout_ms_(-1) {
  user_agent_ = kDefaultHttpUserAgent;
}

HttpConfiguration::HttpConfiguration(bool reuse,
                                     const std::string& proxy_host,
                                     int16_t proxy_port,
                                     const std::string& proxy_username,
                                     const std::string& proxy_password,
                                     const std::string& proxy_domain,
                                     int response_buffer_size,
                                     int64_t timeout_ms)
  : reuse_(reuse),
    proxy_host_(proxy_host),
    proxy_port_(proxy_port),
    proxy_username_(proxy_username),
    proxy_password_(proxy_password),
    proxy_domain_(proxy_domain),
    response_buffer_size_(response_buffer_size) {
  user_agent_ = kDefaultHttpUserAgent;
}

bool HttpConfiguration::GetReuse() const {
  return reuse_;
}

void HttpConfiguration::SetReuse(bool reuse) {
  reuse_ = reuse;
}

const std::string& HttpConfiguration::GetProxyHost() const {
  return proxy_host_;
}

void HttpConfiguration::SetProxyHost(const std::string& proxy_host) {
  proxy_host_ = proxy_host;
}

int16_t HttpConfiguration::GetProxyPort() const {
  return proxy_port_;
}

void HttpConfiguration::SetProxyPort(int16_t proxy_port) {
  proxy_port_ = proxy_port;
}

const std::string& HttpConfiguration::GetProxyUsername() const {
  return proxy_username_;
}

void HttpConfiguration::SetProxyUsername(const std::string& proxy_username) {
  proxy_username_ = proxy_username;
}

const std::string& HttpConfiguration::GetProxyPassword() const {
  return proxy_password_;
}

void HttpConfiguration::SetProxyPassword(const std::string& proxy_password) {
  proxy_password_ = proxy_password;
}

const std::string& HttpConfiguration::GetProxyDomain() const {
  return proxy_domain_;
}

void HttpConfiguration::SetProxyDomain(const std::string& proxy_domain) {
  proxy_domain_ = proxy_domain;
}

int HttpConfiguration::GetResponseBufferSize() const {
  return response_buffer_size_;
}

void HttpConfiguration::SetResponseBufferSize(int response_buffer_size) {
  response_buffer_size_ = response_buffer_size;
}

void HttpConfiguration::SetUserAgent(const std::string& user_agent) {
  user_agent_ = user_agent;
}

const std::string& HttpConfiguration::GetUserAgent() const {
  return user_agent_;
}

int64_t HttpConfiguration::GetTimeoutMs() const {
  return timeout_ms_;
}
void HttpConfiguration::SetTimeoutMs(int64_t timeout) {
  timeout_ms_ = timeout;
}

}  // namespace oss
