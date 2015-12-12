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

#include <curl/curl.h>
#include <algorithm>

#include "oss_sdk_cpp/base/defer.h"
#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/utils/string_utils.h"
#include "oss_sdk_cpp/http/http_headers.h"

#include "oss_sdk_cpp/http/http_engine.h"

namespace oss {

HttpEngine::HttpEngine(const std::string& endpoint)
  : endpoint_(endpoint) {
  unit_test_mode_ = false;
}

HttpEngine::HttpEngine(const std::string& endpoint,
                       const HttpConfiguration& http_config)
  : endpoint_(endpoint), http_config_(http_config) {
  unit_test_mode_ = false;
}

HttpEngine::~HttpEngine() {
}

HttpEngineOutput HttpEngine::Execute(HttpEngineInput* input) {
  std::lock_guard<std::mutex> lock(mutex_);
  Defer([this]() {
    if (http_config_.GetReuse()) {
      curl_.ResetState();
    } else {
      curl_.Close();
    }
  });

  input->response_size_limit = http_config_.GetResponseBufferSize();

  HttpEngineOutput output;
  CUrlSlist header_list;
  for (auto& kv : input->headers) {
    header_list.AddHeader(kv.first, kv.second);
  }
  header_list.AddHeader(http::kUserAgent, http_config_.GetUserAgent());
  header_list.AddHeader(http::kContentType, input->content_type);
  header_list.AddHeader(http::kDate, input->gmt_datetime);

  if (curl_.Get() == NULL && curl_.Create() == NULL) {
    output.code = "CurlCreateInstanceFailed";
    return output;
  }

  // upload data from buffer or file stream.
  bool upload = false;
  std::ifstream input_stream;
  if (input->input_buffer != NULL) {
    // data is in a buffer.
    curl_easy_setopt(curl_.Get(), CURLOPT_POSTFIELDSIZE,
                     input->input_buffer->length());

    curl_easy_setopt(curl_.Get(), CURLOPT_POSTFIELDS,
                     input->input_buffer->c_str());
  } else {
    // data is in a file.
    if (input->input_stream == NULL && !input->input_filename.empty()) {
      // use filename.
      OpenStream(&input_stream,
                 input->input_filename,
                 std::ios::in | std::ios::binary);
      if (!input_stream) {
        output.code = "OpenFileFailed";
        return output;
      }
      input->input_stream = &input_stream;
    }

    std::ifstream* stream = input->input_stream;
    if (stream != NULL) {
      curl_easy_setopt(curl_.Get(), CURLOPT_READFUNCTION, ReadCallback);
      curl_easy_setopt(curl_.Get(), CURLOPT_READDATA, input);
      int64_t file_size = input->stream_bytes;
      if (input->stream_bytes == -1) {
        std::streampos orignal_pos = stream->tellg();
        stream->seekg(0, std::ios::end);
        file_size = static_cast<int64_t>(stream->tellg() - orignal_pos);
        stream->clear();
        stream->seekg(orignal_pos, std::ios::beg);
      }
      curl_easy_setopt(curl_.Get(),
                       CURLOPT_INFILESIZE_LARGE,
                       static_cast<curl_off_t>(file_size));
      upload = true;
    }
  }
  header_list.AddHeader("Expect", "");

  // download to stream
  std::ofstream output_stream;
  if (input->output_stream == NULL && !input->output_path.empty()) {
    OpenStream(&output_stream,
               input->output_path,
               std::ios::out | std::ios::binary);
    if (!output_stream) {
      output.code = "OpenFileFailed";
      return output;
    }
    input->output_stream = &output_stream;
  }

  curl_easy_setopt(curl_.Get(), CURLOPT_URL, input->url.c_str());
  curl_easy_setopt(curl_.Get(), CURLOPT_CUSTOMREQUEST, input->method.c_str());
  curl_easy_setopt(curl_.Get(), CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl_.Get(), CURLOPT_WRITEDATA, input);
  curl_easy_setopt(curl_.Get(), CURLOPT_HTTPHEADER, header_list.Get());
  curl_easy_setopt(curl_.Get(), CURLOPT_HEADERFUNCTION, HeaderCallback);
  curl_easy_setopt(curl_.Get(), CURLOPT_WRITEHEADER, &output.headers);

  HttpTimeoutType timeout =
    static_cast<HttpTimeoutType>(http_config_.GetTimeoutMs());
  if (timeout != -1) {
    curl_easy_setopt(curl_.Get(), CURLOPT_CONNECTTIMEOUT_MS, timeout);
    curl_easy_setopt(curl_.Get(), CURLOPT_TIMEOUT_MS, timeout);
  }

  // Http Proxy config.
  if (!http_config_.GetProxyHost().empty()) {
    std::string proxy = http_config_.GetProxyHost() + ":" +
                        std::to_string(http_config_.GetProxyPort());
    curl_easy_setopt(curl_.Get(), CURLOPT_PROXY, proxy.c_str());
  }

  // disable signal is useful for multi-threaded applications.
  curl_easy_setopt(curl_.Get(), CURLOPT_NOSIGNAL, 1);

  // do not verify the peer
  curl_easy_setopt(curl_.Get(), CURLOPT_SSL_VERIFYPEER, 0);

  if (upload)
    curl_easy_setopt(curl_.Get(), CURLOPT_UPLOAD, 1L);

  if (input->method == kHttpHead) {
    curl_easy_setopt(curl_.Get(), CURLOPT_NOBODY, 1L);
  }

  if (unit_test_mode_) {
    return output;
  }

  HttpStatusType http_code = 0;
  CURLcode curl_result = curl_easy_perform(curl_.Get());
  if (curl_result != CURLE_OK) {
    output.code = "Curl ";
    output.code += curl_easy_strerror(curl_result);
    curl_.Close();
    return output;
  }
  std::swap(input->response, output.response);
  // http query succeed

  curl_easy_getinfo(curl_.Get(), CURLINFO_RESPONSE_CODE, &http_code);
  output.http_status_code = http_code;

  return output;
}

size_t HttpEngine::WriteCallback(void* buffer,
                                 size_t size,
                                 size_t nmemb,
                                 void* userdata) {
  HttpEngineInput* receiver = static_cast<HttpEngineInput*>(userdata);
  if (receiver == NULL)
    return 0;

  size_t bytes = size * nmemb;
  size_t left = receiver->response_size_limit - receiver->response.size();
  size_t allowed = std::min<size_t>(left, bytes);
  receiver->response.append(static_cast<char*>(buffer), allowed);

  if (receiver->output_stream != NULL) {
    receiver->output_stream->write(static_cast<char*>(buffer), bytes);
  }

  return bytes;
}

size_t HttpEngine::ReadCallback(void* buffer,
                                size_t size,
                                size_t nmemb,
                                void* userdata) {
  HttpEngineInput* input = static_cast<HttpEngineInput*>(userdata);
  if (input->stream_bytes == 0)
    return 0;

  std::ifstream* stream = input->input_stream;
  if (stream == NULL)
    return 0;
  if (stream->eof())
    return 0;

  int64_t bytes = static_cast<int64_t>(size * nmemb);
  if (bytes == 0)
    return 0;
  if (input->stream_bytes != -1) {
    if (input->stream_bytes < bytes)
      bytes = input->stream_bytes;
  }

  stream->read(static_cast<char*>(buffer), static_cast<std::streamsize>(bytes));
  int64_t bytes_read = static_cast<int64_t>(stream->gcount());

  if (input->stream_bytes != -1) {
    input->stream_bytes -= bytes_read;
  }

  return static_cast<size_t>(bytes_read);
}

size_t HttpEngine::HeaderCallback(void* buffer,
                                  size_t size,
                                  size_t nmemb,
                                  void* userdata) {
  size_t bytes = size * nmemb;
  if (bytes == 0)
    return 0;

  std::string str(reinterpret_cast<char*>(buffer), bytes);
  size_t colon_pos = str.find(':', 0);
  if (colon_pos == std::string::npos) {
    // discard texts like "HTTP/1.1 200 OK" etc.
    return bytes;
  }

  int name_len = colon_pos;
  int value_len = str.size() - colon_pos - 1;

  std::string sub = str.substr(0, name_len);
  std::string name, value;
  TrimWhiteSpaces(sub, &name);
  if (value_len != 0) {
    sub = str.substr(colon_pos + 1, value_len);
    TrimWhiteSpaces(sub, &value);
  }

  StringMap* headers = static_cast<StringMap*>(userdata);
  (*headers)[name] = value;

  return bytes;
}

void HttpEngine::SetUnitTestMode() {
  unit_test_mode_ = true;
}

}  // namespace oss
