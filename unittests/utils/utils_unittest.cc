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
#include "oss_sdk_cpp/utils/utils.h"

namespace oss {

const uint64_t kExampleFileSize = 139341;

class FileTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    file_path_ = GetExecutableDirectory() +
                 kPathSlash + std::string("test_files") +
                 kPathSlash + "md5_1.dll";

    output_file_path_ = GetExecutableDirectory() +
                        kPathSlash + std::string("test_files") +
                        kPathSlash + "output_unittest.txt";

    file_size_ = kExampleFileSize;
  }
  int64_t file_size_;
  std::string file_path_;
  std::string output_file_path_;
};

TEST_F(FileTest, GetFileSize) {
  int64_t file_size = GetFileSize(file_path_);
  EXPECT_EQ(file_size, file_size_);
}

TEST_F(FileTest, ReadWholeFile) {
  std::string file_content = ReadWholeFile(file_path_);
  EXPECT_EQ(file_content.size(), kExampleFileSize);
}

TEST_F(FileTest, OpenStream) {
  {
    std::ifstream stream;
    OpenStream(&stream, file_path_, std::ios::in | std::ios::binary);
    EXPECT_TRUE(stream);
  }

  {
    std::ofstream stream;
    OpenStream(&stream, output_file_path_, std::ios::out | std::ios::binary);
    EXPECT_TRUE(stream);
    RemoveStream(output_file_path_);
  }
}

TEST_F(FileTest, GetExecutableDirectory) {
  std::string dir = GetExecutableDirectory();
  EXPECT_FALSE(dir.empty());
}

TEST_F(FileTest, NormalizeFilePath) {
  std::string path = "/root/test\\abc\\foo.txt";
  std::string expected_win = "\\root\\test\\abc\\foo.txt";
  std::string expected_other = "/root/test/abc/foo.txt";

  NormalizeFilePath(&path);
#ifdef _MSC_VER
  EXPECT_EQ(path, expected_win);
#else
  EXPECT_EQ(path, expected_other);
#endif
}

TEST_F(FileTest, GetFileSizeFailed) {
  int64_t file_size = GetFileSize("/ghost/nosuchfilenosuchfile123.txt");
  EXPECT_EQ(file_size, -1);
}

}  // namespace oss
