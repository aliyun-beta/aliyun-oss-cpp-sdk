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

#define NOMINMAX

#include <stdint.h>

#include <apr_base64.h>
#include <apr_sha1.h>
#include <apr_md5.h>

#include <fstream>
#include <memory>
#include <algorithm>

#include "oss_sdk_cpp/utils/apr_utils.h"
#include "oss_sdk_cpp/utils/utils.h"

namespace oss {

std::string AprBase64Encode(const unsigned char* input,
                            unsigned int input_size) {
  std::string output;
  if (input == NULL || input_size == 0)
    return output;

  int buffer_length = apr_base64_encode_len(input_size);
  std::unique_ptr<char[]> buffer(new char[buffer_length]);
  buffer_length = apr_base64_encode_binary(buffer.get(), input, input_size);
  // apr_base64_encode_binary always set a null-character ('\0') at the end.
  output.assign(buffer.get());
  (void)buffer_length;
  return output;
}

std::string AprBase64Encode(const std::string& input) {
  auto str = reinterpret_cast<const unsigned char*>(input.c_str());
  int size = static_cast<size_t>(input.size());
  return AprBase64Encode(str, size);
}

void AprHmacSha1(const char *key, int key_length,
                 const char *data, int data_length,
                 char *result, int result_length) {
  const int kBlockSize = 64;
  const unsigned int kDigestSize = 20;
  const char kIpad = 0x36;
  const char kOpad = 0x5c;

  apr_sha1_ctx_t context;
  uint8_t hashed_key[kDigestSize];

  // shorten long key.
  if (key_length > kBlockSize) {
    apr_sha1_init(&context);
    apr_sha1_update(&context, key, key_length);
    apr_sha1_final(hashed_key, &context);
    key = reinterpret_cast<const char*>(hashed_key);
    key_length = kDigestSize;
  }

  char key_ipad[kBlockSize];
  char key_opad[kBlockSize];
  std::fill_n(key_ipad, sizeof(key_ipad), kIpad);
  std::fill_n(key_opad, sizeof(key_opad), kOpad);
  for (int i = 0; i < key_length; ++i) {
    key_ipad[i] = key[i] ^ kIpad;
    key_opad[i] = key[i] ^ kOpad;
  }

  // calculate inner SHA1
  uint8_t sha[kDigestSize];
  apr_sha1_init(&context);
  apr_sha1_update(&context, key_ipad, kBlockSize);
  apr_sha1_update(&context, data, data_length);
  apr_sha1_final(sha, &context);

  // calculate outer HMAC
  apr_sha1_init(&context);
  apr_sha1_update(&context, key_opad, kBlockSize);
  apr_sha1_update(&context, reinterpret_cast<const char*>(sha), kDigestSize);
  apr_sha1_final(sha, &context);

  std::fill_n(result, result_length, 0);
  size_t nbytes = std::min(result_length, static_cast<int>(kDigestSize));
  std::copy(sha, sha + nbytes, result);
}

void AprHmacSha1(const std::string& text,
                 const std::string& key,
                 char output[],
                 int output_length) {
  AprHmacSha1(key.c_str(), key.length(), text.c_str(), text.length(),
              output, output_length);
}

std::string AprComputeMd5(const std::string& text) {
  apr_md5_ctx_t context;
  unsigned char digest[APR_MD5_DIGESTSIZE];
  apr_md5_init(&context);
  apr_md5_update(&context, text.c_str(), text.size());
  apr_md5_final(digest, &context);

  std::string ret;
  ret.resize(APR_MD5_DIGESTSIZE);
  ret.assign(reinterpret_cast<char*>(&digest[0]), APR_MD5_DIGESTSIZE);

  return ret;
}

std::string AprComputeFileMd5(const std::string& file_path) {
  std::ifstream stream;
  OpenStream(&stream, file_path, std::ios::in | std::ios::binary);
  if (!stream)
    return "";
  return AprComputeFileMd5(&stream);
}

// compute md5 of an already opened stream.
std::string AprComputeFileMd5(std::ifstream* stream) {
  // remember original position of stream.
  std::streampos stream_position = stream->tellg();
  std::string result;
  unsigned char digest[APR_MD5_DIGESTSIZE] = "";
  apr_md5_ctx_t context;
  apr_md5_init(&context);

  // 4k read buffer.
  const int kBufferSize = 4096;
  char buffer[kBufferSize];
  while (!stream->eof()) {
    stream->read(buffer, kBufferSize);
    std::streamsize bytes = stream->gcount();
    if (bytes > 0) {
      apr_md5_update(&context, buffer, static_cast<size_t>(bytes));
    }
  }
  apr_md5_final(digest, &context);
  stream->clear();
  stream->seekg(stream_position, std::ios::beg);

  result.resize(APR_MD5_DIGESTSIZE);
  result.assign(reinterpret_cast<char*>(&digest[0]), APR_MD5_DIGESTSIZE);

  return result;
}

std::string AprComputeFileMd5(std::ifstream* stream, int64_t part_size) {
  // remember original position of stream.
  std::streampos stream_position = stream->tellg();
  std::string result;
  unsigned char digest[APR_MD5_DIGESTSIZE] = "";
  apr_md5_ctx_t context;
  apr_md5_init(&context);

  // 4k read buffer.
  const int kBufferSize = 4096;
  char buffer[kBufferSize];
  while (!stream->eof()) {
    int64_t bytes_to_read = kBufferSize;
    if (part_size == 0)
      break;
    if (part_size < bytes_to_read) {
      bytes_to_read = part_size;
    }
    stream->read(buffer, bytes_to_read);
    std::streamsize bytes = stream->gcount();
    if (bytes > 0) {
      part_size -= bytes;
      apr_md5_update(&context, buffer, static_cast<size_t>(bytes));
    }
  }
  apr_md5_final(digest, &context);
  stream->clear();
  stream->seekg(stream_position, std::ios::beg);

  result.resize(APR_MD5_DIGESTSIZE);
  result.assign(reinterpret_cast<char*>(&digest[0]), APR_MD5_DIGESTSIZE);

  return result;
}

}  // namespace oss
