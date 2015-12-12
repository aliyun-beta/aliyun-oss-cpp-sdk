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

#include <string>
#include <ostream>

#include "gtest/gtest.h"
#include "oss_sdk_cpp/base/base.h"
#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/http/http_engine.h"
#include "oss_sdk_cpp/http/http_engine_input.h"

namespace oss {

class HttpEngineTest {
 public:
  static void TestHeaderCallback() {
    char data[] = "Server: AliyunOSS\r\n";
    int input_length = strlen(data);
    {
      StringMap headers;
      HttpEngine::HeaderCallback(data, 1, input_length, &headers);
      std::string server = headers["Server"];
      EXPECT_EQ(headers["Server"], "AliyunOSS");
    }

    {
      HttpEngine engine("");
      int ret = engine.HeaderCallback(data, 0, 0, NULL);
      EXPECT_EQ(ret, 0);
    }

    {
      char nocolon_text[] = "HTTP/1.1 200 OK";
      int text_length = strlen(nocolon_text);
      StringMap headers;
      int ret = HttpEngine::HeaderCallback(nocolon_text,
                                           1,
                                           text_length,
                                           &headers);
      EXPECT_EQ(ret, text_length);
      EXPECT_EQ(headers.size(), 0u);
    }
  }

  static void TestReadCallback() {
    {
      char data[64] = "";
      HttpEngineInput http_input;
      http_input.stream_bytes = 0;
      int ret = HttpEngine::ReadCallback(data, 1, sizeof(data), &http_input);
      EXPECT_EQ(ret, 0);
    }

    {
      char data[64] = "";
      HttpEngineInput http_input;
      http_input.stream_bytes = 100;
      int ret = HttpEngine::ReadCallback(data, 1, sizeof(data), &http_input);
      EXPECT_EQ(ret, 0);
    }

    {
      char data[256] = "";
      HttpEngineInput http_input;
      http_input.stream_bytes = 100;
      int ret = 0;
      std::string file_path = GetExecutableDirectory() +
                              kPathSlash + std::string("test_files") +
                              kPathSlash + "md5_1.cc";
      std::ifstream input_stream;
      OpenStream(&input_stream, file_path, std::ios::in | std::ios::binary);
      http_input.input_stream = &input_stream;
      ASSERT_TRUE(input_stream);

      const int kReadBufferSize = 1024 * 1024;
      std::unique_ptr<char[]> read_buffer(new char[kReadBufferSize]);
      while (1) {
        input_stream.read(read_buffer.get(), kReadBufferSize);
        if (input_stream.eof())
          break;
      }
      char testdata[] = "hello world";
      ret = HttpEngine::ReadCallback(&testdata[0], 1, 4, &http_input);
      EXPECT_EQ(ret, 0);

      input_stream.clear();
      input_stream.seekg(0, std::ios::beg);
      ret = HttpEngine::ReadCallback(&testdata[0], 0, 0, &http_input);
      EXPECT_EQ(ret, 0);

      ret = HttpEngine::ReadCallback(data, 1, 4, &http_input);
      EXPECT_EQ(ret, 4);

      ret = HttpEngine::ReadCallback(data, 1, 100, &http_input);
      EXPECT_EQ(ret, 96);
    }
  }

  static void TestWriteCallback() {
    {
      char testdata[] = "hello world";
      int ret;
      ret = HttpEngine::WriteCallback(NULL, 0, 0, NULL);
      EXPECT_EQ(ret, 0);

      std::string output_file_path = GetExecutableDirectory() +
                                     kPathSlash + std::string("test_files") +
                                     kPathSlash + "output_unittest.txt";
      std::ofstream stream;
      OpenStream(&stream, output_file_path, std::ios::out | std::ios::binary);
      HttpEngineInput http_input;
      http_input.output_stream = &stream;
      ret = HttpEngine::WriteCallback(&testdata[0], 1, 5, &http_input);
      EXPECT_EQ(ret, 5);
      RemoveStream(output_file_path);
    }
  }
};

TEST(HttpEngine, TestHeaderCallback) {
  HttpEngineTest::TestHeaderCallback();
}

TEST(HttpEngine, TestReadCallback) {
  HttpEngineTest::TestReadCallback();
}

TEST(HttpEngine, TestWriteCallback) {
  HttpEngineTest::TestWriteCallback();
}

}  // namespace oss
