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

#ifndef OSS_SDK_CPP_UTILS_APR_UTILS_H_
#define OSS_SDK_CPP_UTILS_APR_UTILS_H_

#include <stdint.h>
#include <string>
#include <fstream>

namespace oss {

std::string AprBase64Encode(unsigned char const*, unsigned int len);

std::string AprBase64Encode(const std::string& input);

std::string AprComputeMd5(const std::string& text);

std::string AprComputeFileMd5(const std::string& file_path);

std::string AprComputeFileMd5(std::ifstream* stream);

std::string AprComputeFileMd5(std::ifstream* stream, int64_t part_size);

void AprHmacSha1(const std::string& text,
                 const std::string& key,
                 char output[], int output_length);

void AprHmacSha1(const char *key, int key_length,
                 const char *data, int data_length,
                 char *result, int result_length);

}  // namespace oss

#endif  // OSS_SDK_CPP_UTILS_APR_UTILS_H_
