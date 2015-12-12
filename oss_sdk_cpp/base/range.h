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

#ifndef OSS_SDK_CPP_BASE_RANGE_H_
#define OSS_SDK_CPP_BASE_RANGE_H_

namespace oss {

struct Range {
  Range() {
    start = -1;
    end = -1;
  }

  Range(size_t s, size_t e) : start(s), end(e) {
  }
  size_t start;
  size_t end;
};

// equality test
inline bool operator==(const Range& lhs, const Range& rhs) {
  return (lhs.start == rhs.start && lhs.end == rhs.end);
}

}  // namespace oss

#endif  // OSS_SDK_CPP_BASE_RANGE_H_
