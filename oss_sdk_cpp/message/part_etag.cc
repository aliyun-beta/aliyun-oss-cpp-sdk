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

#include "oss_sdk_cpp/message/part_etag.h"

namespace oss {

PartEtag::PartEtag() {
}
PartEtag::PartEtag(const std::string& etag, int part_number)
  : etag_(etag), part_number_(part_number) {
}

const std::string& PartEtag::GetEtag() const {
  return etag_;
}

void PartEtag::SetEtag(const std::string& etag) {
  etag_ = etag;
}

int PartEtag::GetPartNumber() const {
  return part_number_;
}

void PartEtag::SetPartNumber(int part_number) {
  part_number_ = part_number;
}

}  // namespace oss
