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

#ifndef OSS_SDK_CPP_BASE_BASE_H_
#define OSS_SDK_CPP_BASE_BASE_H_

#include <stdint.h>
#include <time.h>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include "oss_sdk_cpp/base/range.h"
#include "oss_sdk_cpp/base/nullable.h"

namespace oss {

typedef Nullable<time_t> OptionalDateTime;
typedef Nullable<Range> OptionalRange;
typedef Nullable<std::string> OptionalString;
typedef Nullable<int64_t> OptionalInt64;

typedef std::map<std::string, std::string> StringMap;
typedef std::vector<std::string> StringArray;
typedef std::list<std::string> StringList;

typedef long HttpTimeoutType;  //NOLINT
typedef long HttpStatusType;  //NOLINT

extern const  char kHttpPut[];
extern const  char kHttpGet[];
extern const  char kHttpPost[];
extern const  char kHttpDelete[];
extern const  char kHttpHead[];
extern const char kHttpOptions[];

extern const  char kHttps[];
extern const  char kHttp[];

extern const  char kPathSlash;
extern const  char kPathSlashStr[];

}  // namespace oss

#endif  // OSS_SDK_CPP_BASE_BASE_H_
