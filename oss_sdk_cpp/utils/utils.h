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

#ifndef OSS_SDK_CPP_UTILS_UTILS_H_
#define OSS_SDK_CPP_UTILS_UTILS_H_

// unclassified utilities are here.

#include <time.h>
#include <stdint.h>
#include <iosfwd>
#include <fstream>
#include <string>

namespace oss {

int64_t GetFileSize(const std::string& file_path);

std::string ReadWholeFile(const std::string& path);

// assume that file_path is always utf-8 encoded.
void OpenStream(std::ifstream* stream,
                const std::string& file_path,
                std::ios_base::openmode mode);

void OpenStream(std::ofstream* stream,
                const std::string& file_path,
                std::ios_base::openmode mode);

void RemoveStream(const std::string& path);

std::string GetExecutableDirectory();

void NormalizeFilePath(std::string* path);

std::string HexToString(const std::string& input);

struct tm* GmTime(time_t t, struct tm* tm_result);

template <class Collection>
const typename Collection::value_type::second_type&
FindWithDefault(const Collection& collection,
                const typename Collection::value_type::first_type& key,
                const typename Collection::value_type::second_type& value) {
  typename Collection::const_iterator it = collection.find(key);
  if (it == collection.end()) {
    return value;
  }
  return it->second;
}

template <typename CollectionType, typename ValueType>
bool Contains(const CollectionType& collection, const ValueType& value) {
  return std::find(collection.begin(), collection.end(), value) !=
    collection.end();
}

}  // namespace oss

#endif  // OSS_SDK_CPP_UTILS_UTILS_H_
