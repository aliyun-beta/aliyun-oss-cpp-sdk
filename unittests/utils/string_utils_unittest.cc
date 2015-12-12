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
#include "oss_sdk_cpp/utils/string_utils.h"

namespace oss {

TEST(StartsWith, Basic) {
  EXPECT_TRUE(StartsWith("http://www.aliyun.com", "http://"));
  EXPECT_FALSE(StartsWith("http://www.aliyun.com", "HTTP://", true));
  EXPECT_TRUE(StartsWith("http://www.aliyun.com", "HTTP://", false));
}

TEST(StartsWith, InvalidInput) {
  EXPECT_FALSE(StartsWith("short text", "llllllong long text"));
}

TEST(EndsWith, Basic) {
  EXPECT_TRUE(EndsWith("http://www.aliyun.com", ".com"));
  EXPECT_FALSE(EndsWith("http://www.aliyun.com", ".COM", true));
  EXPECT_TRUE(EndsWith("http://www.aliyun.com", ".COM", false));
}

TEST(EndsWith, InvalidInput) {
  EXPECT_FALSE(EndsWith("short text", "llllllong long text"));
}

TEST(ToLower, Basic) {
  EXPECT_EQ(ToLower("ALIYUN"), "aliyun");
  EXPECT_EQ(ToLower("aLiYun"), "aliyun");
  EXPECT_EQ(ToLower("Everest"), "everest");
  EXPECT_EQ(ToLower("HIMALAYAS"), "himalayas");
  EXPECT_EQ(ToLower("himalayas"), "himalayas");
}

TEST(ToUpper, Basic) {
  EXPECT_EQ(ToUpper("aliyun"), "ALIYUN");
  EXPECT_EQ(ToUpper("aLiYun"), "ALIYUN");
  EXPECT_EQ(ToUpper("Everest"), "EVEREST");
  EXPECT_EQ(ToUpper("HIMALAYAS"), "HIMALAYAS");
  EXPECT_EQ(ToUpper("himalayas"), "HIMALAYAS");
}

TEST(StringToBool, Basic) {
  EXPECT_TRUE(StringToBool("TRUE"));
  EXPECT_TRUE(StringToBool("true"));
  EXPECT_TRUE(StringToBool("True"));
  EXPECT_TRUE(StringToBool("tRue"));

  EXPECT_FALSE(StringToBool("FLASE"));
  EXPECT_FALSE(StringToBool("false"));
  EXPECT_FALSE(StringToBool("False"));
  EXPECT_FALSE(StringToBool("falsE"));

  EXPECT_FALSE(StringToBool(""));
}

TEST(TrimString, Basic) {
  {
    std::string input = " Everest";
    std::string expected = "Everest";
    std::string output;
    TrimString(input, " ", &output);
    EXPECT_EQ(output, expected);
  }

  {
    std::string input = "######&&&&&Everest******^^^^^^^^";
    std::string expected = "Everest";
    std::string output;
    TrimString(input, "#&*^", &output);
    EXPECT_EQ(output, expected);

    TrimString(input, " ", &output);
    EXPECT_NE(output, expected);

    TrimString(input, "#&*", &output);
    EXPECT_NE(output, expected);
  }
}

TEST(TrimString, TrimToEmpty) {
  {
    std::string input = "abccbabacbcacabaaaabbbb";
    std::string expected = "";
    std::string output;
    TrimString(input, "abc", &output);
    EXPECT_EQ(output, expected);
  }
}

TEST(TrimWhiteSpaces, Basic) {
  {
    std::string input = "   Everest \r\n \t   ";
    std::string expected = "Everest";
    std::string output;
    TrimWhiteSpaces(input, &output);
    EXPECT_EQ(output, expected);
  }

  {
    std::string input = "######&&&&&Everest******^^^^^^^^";
    std::string expected = "Everest";
    std::string output;
    TrimWhiteSpaces(input, &output);
    EXPECT_NE(output, expected);

    TrimWhiteSpaces(input,  &output);
    EXPECT_NE(output, expected);

    TrimWhiteSpaces(input,  &output);
    EXPECT_NE(output, expected);
  }
}

TEST(stricmp, Basic) {
  EXPECT_EQ(stricmp("tRue", "TRUE"), 0);
  EXPECT_EQ(stricmp("TRUE", "TRUE"), 0);
  EXPECT_NE(stricmp("TRUE", "TRUE123"), 0);
  EXPECT_EQ(strnicmp("TRUE", "TRUE123", 4), 0);
}

TEST(ReplaceSubstring, Basic) {
  {
    std::string text = "waterwaterfishneedlewhale";
    std::string expected = "waterwaterfish******whale";
    std::string replacements = "******";
    ReplaceSubstring(&text, "needle", replacements);
    EXPECT_EQ(text, expected);
  }

  {
    std::string text = "waterwaterfishneedlewhale000000needle111111";
    std::string expected = "waterwaterfish******whale000000******111111";
    std::string replacements = "******";
    ReplaceSubstring(&text, "needle", replacements);
    EXPECT_EQ(text, expected);
  }

  {
    std::string text = "waterwaterfishneedlewhale000000needle111111";
    std::string expected = "waterwaterfishwhale000000111111";
    std::string replacements = "";
    ReplaceSubstring(&text, "needle", replacements);
    EXPECT_EQ(text, expected);
  }
}

}  // namespace oss
