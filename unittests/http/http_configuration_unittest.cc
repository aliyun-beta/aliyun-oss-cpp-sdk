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

#include <stdint.h>
#include <string>
#include <ostream>

#include "gtest/gtest.h"

#include "oss_sdk_cpp/base/nullable.h"
#include "oss_sdk_cpp/http/http_configuration.h"

namespace oss {

class HttpConfigurationTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    reuse_ = true;
    proxy_host_ = "www.proxy.com";
    proxy_port_ = 8080;
    proxy_username_ = "myuser";
    proxy_password_ = "mypassword";
    proxy_password_ = "mydomain";
    response_buffer_size_ = 1024 * 1024;
  }
  bool reuse_;
  std::string proxy_host_;
  int16_t proxy_port_;
  std::string proxy_username_;
  std::string proxy_password_;
  std::string proxy_domain_;
  int response_buffer_size_;
};

TEST_F(HttpConfigurationTest, Constructor1) {
  HttpConfiguration config(reuse_,
                           proxy_host_,
                           proxy_port_,
                           proxy_username_,
                           proxy_password_,
                           proxy_domain_,
                           response_buffer_size_);

  EXPECT_EQ(reuse_, config.GetReuse());
  EXPECT_EQ(proxy_host_, config.GetProxyHost());
  EXPECT_EQ(proxy_port_, config.GetProxyPort());
  EXPECT_EQ(proxy_username_, config.GetProxyUsername());
  EXPECT_EQ(proxy_password_, config.GetProxyPassword());
  EXPECT_EQ(proxy_domain_, config.GetProxyDomain());
  EXPECT_EQ(response_buffer_size_, config.GetResponseBufferSize());
}

TEST_F(HttpConfigurationTest, Constructor2) {
  HttpConfiguration config;

  config.SetReuse(reuse_);
  config.SetProxyHost(proxy_host_);
  config.SetProxyPort(proxy_port_);
  config.SetProxyUsername(proxy_username_);
  config.SetProxyPassword(proxy_password_);
  config.SetProxyDomain(proxy_domain_);
  config.SetResponseBufferSize(response_buffer_size_);
  config.SetUserAgent("test user agent");
  config.SetTimeoutMs(1000);

  EXPECT_EQ(reuse_, config.GetReuse());
  EXPECT_EQ(proxy_host_, config.GetProxyHost());
  EXPECT_EQ(proxy_port_, config.GetProxyPort());
  EXPECT_EQ(proxy_username_, config.GetProxyUsername());
  EXPECT_EQ(proxy_password_, config.GetProxyPassword());
  EXPECT_EQ(proxy_domain_, config.GetProxyDomain());
  EXPECT_EQ(response_buffer_size_, config.GetResponseBufferSize());
  EXPECT_EQ("test user agent", config.GetUserAgent());
  EXPECT_EQ(1000, config.GetTimeoutMs());
}

}  // namespace oss
