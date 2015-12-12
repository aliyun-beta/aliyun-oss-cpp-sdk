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

#include "oss_sdk_cpp/base/nullable.h"

namespace oss {

TEST(Nullable, Int) {
  Nullable<int> myint1(100);
  EXPECT_FALSE(myint1.IsNull());

  Nullable<int> myint2 = 100;
  EXPECT_EQ(myint1, myint2);

  myint1.Set(77);
  EXPECT_NE(myint1, myint2);

  myint1.Clear();
  EXPECT_TRUE(myint1.IsNull());

  myint1.Set(myint2);
  EXPECT_EQ(myint1, 100);

  myint1.Clear();
  EXPECT_EQ(-1, myint1.Value(-1));
  EXPECT_NE(-1, myint1.Value(20));
}

TEST(Nullable, String) {
  std::string str1 = "123";
  Nullable<std::string> var1(str1);
  EXPECT_EQ(str1, var1->c_str());
  EXPECT_EQ(str1, var1.Value());

  Nullable<std::string> var2;
  var2.swap(var1);
  EXPECT_EQ(str1, var2->c_str());
  EXPECT_EQ(str1, var2);
  EXPECT_EQ(str1, var2.Value());
  EXPECT_NE(var1, var2);

  std::swap(var1, var2);
  EXPECT_EQ(str1, var1->c_str());
  EXPECT_EQ(str1, var1);
  EXPECT_EQ(str1, var1.Value());
  EXPECT_NE(var1, var2);

  std::ostringstream stream;
  stream << var1;
  std::string str2 = stream.str();
  EXPECT_EQ(var1, str2);

  Nullable<std::string> var3("123");
  std::string str3 = "456";
  EXPECT_TRUE(str3 != var3);
  EXPECT_FALSE(str3 == var3);

  EXPECT_TRUE(var3 != str3);
  EXPECT_FALSE(var3 == str3);

  Nullable<std::string> var4("123");
  EXPECT_TRUE(var4 == var3);
  EXPECT_FALSE(var4 != var3);
}

}  // namespace oss
