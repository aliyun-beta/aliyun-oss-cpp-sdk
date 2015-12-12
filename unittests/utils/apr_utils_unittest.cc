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

#include "gtest/gtest.h"

#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/utils/apr_utils.h"
#include "oss_sdk_cpp/utils/utils.h"

namespace oss {

const char* md5_file1 = "md5_1.dll";
const char* md5_file2 = "md5_2.dll";

const char* md5_file1_digest = "c933986546b4e7339de244c472bb3855";
const char* md5_file2_digest = "7101137a1c333cbe07efcc5b5cf5b876";

TEST(Base64Test, Basic) {
  const std::string kText = "hello world";
  const std::string kBase64Text = "aGVsbG8gd29ybGQ=";

  std::string encoded = AprBase64Encode(kText);
  EXPECT_EQ(kBase64Text, encoded);
}

TEST(Base64Test, InvalidArguments) {
  std::string encoded = AprBase64Encode(NULL, 0);
  EXPECT_TRUE(encoded.empty());
}

TEST(MD5, Basic) {
  const std::string input = "hello world";
  const std::string expected = "5eb63bbbe01eeed093cb22bb8f5acdc3";

  std::string digest = AprComputeMd5(input);
  std::string b16 = HexToString(digest);
  EXPECT_EQ(b16, expected);
}

TEST(MD5, File) {
  const std::string expected = md5_file1_digest;
  std::string file_path = GetExecutableDirectory() +
                          kPathSlash + std::string("test_files") +
                          kPathSlash + md5_file1;

  std::string digest = AprComputeFileMd5(file_path);
  std::string b16 = HexToString(digest);
  EXPECT_EQ(b16, expected);
}

TEST(MD5, FilePathInvalid) {
  std::string digest = AprComputeFileMd5("/root/invalid_file_path20151124");
  EXPECT_TRUE(digest.empty());
}

TEST(MD5, FileStream) {
  const std::string expected = md5_file1_digest;
  std::string file_path = GetExecutableDirectory() +
                          kPathSlash + std::string("test_files") +
                          kPathSlash + md5_file1;

  std::ifstream stream;
  OpenStream(&stream, file_path, std::ios::in | std::ios::binary);
  std::string digest = AprComputeFileMd5(file_path);
  std::string b16 = HexToString(digest);
  EXPECT_EQ(b16, expected);
}

TEST(MD5, FileStreamPart) {
  const std::string expected = "93b93997aa95f9894752a4f139deb252";
  std::string file_path1 = GetExecutableDirectory() +
                           kPathSlash + std::string("test_files") +
                           kPathSlash + md5_file1;

  int64_t file1_size = 1024;
  std::ifstream stream;
  OpenStream(&stream, file_path1, std::ios::in | std::ios::binary);
  std::string digest = AprComputeFileMd5(&stream, file1_size);
  std::string b16 = HexToString(digest);
  EXPECT_EQ(b16, expected);
}

TEST(AprHmacSha1, basic) {
  const std::string text = "hello world";
  const std::string key = "everest";
  const std::string expected = "37a68fcfdb7dcd2b94350ad5d7578cdc5ad48d30";

  unsigned char digest[20] = { 0 };
  AprHmacSha1(text, key, reinterpret_cast<char*>(digest), 20);
  std::string b16 = HexToString(
                      std::string(reinterpret_cast<char*>(&digest[0]), 20));
  EXPECT_EQ(b16, expected);
}

TEST(AprHmacSha1, LongKey) {
  const std::string text = "hello world";
  std::string key(100, 'a');
  const std::string expected = "138f4646cb8c5aeb9c5f733bf8ae69da008a4dda";

  unsigned char digest[20] = { 0 };
  AprHmacSha1(text, key, reinterpret_cast<char*>(digest), 20);
  std::string b16 = HexToString(
                      std::string(reinterpret_cast<char*>(&digest[0]), 20));
  EXPECT_EQ(b16, expected);
}

}  // namespace oss
