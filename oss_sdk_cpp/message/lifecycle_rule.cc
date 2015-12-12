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

#include "oss_sdk_cpp/message/lifecycle_rule.h"

namespace oss {

LifeCycleRule::LifeCycleRule()
  : enabled_(true),
    expiration_days_(-1) {
}

const std::string& LifeCycleRule::GetId() const {
  return id_;
}
void LifeCycleRule::SetId(const std::string& id) {
  id_ = id;
}

const std::string& LifeCycleRule::GetPrefix() const {
  return prefix_;
}
void LifeCycleRule::SetPrefix(const std::string& prefix) {
  prefix_ = prefix;
}

bool LifeCycleRule::GetEnabled() const {
  return enabled_;
}
void LifeCycleRule::SetEnabled(bool enabled) {
  enabled_ = enabled;
}

const std::string& LifeCycleRule::GetExpirationDate() const {
  return expiration_date_;
}
void LifeCycleRule::SetExpirationDate(const std::string& date) {
  expiration_date_ = date;
}

int LifeCycleRule::GetExpirationDays() const {
  return expiration_days_;
}
void LifeCycleRule::SetExpirationDays(int days) {
  expiration_days_ = days;
}

}  // namespace oss
