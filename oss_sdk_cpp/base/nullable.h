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

#ifndef OSS_SDK_CPP_BASE_NULLABLE_H_
#define OSS_SDK_CPP_BASE_NULLABLE_H_

#include <cassert>
#include <algorithm>
#include <iostream>

namespace oss {

template <typename T>
class Nullable {
 public:
  Nullable()
    : value_(),
      is_null_(true) {
  }

  Nullable(const T& value)    // NOLINT(runtime/explicit)
    : value_(value),
      is_null_(false) {
  }

  Nullable(const Nullable& rhs)
    : value_(rhs.value_),
      is_null_(rhs.is_null_) {
  }

  // move constructor.
  Nullable(Nullable&& rhs)
    : value_(std::move(rhs.value_)),
      is_null_(rhs.is_null_) {
    rhs.is_null_ = true;
  }

  // move assignment.
  Nullable& operator=(Nullable&& rhs) {
    value_ = std::move(rhs.Value);
    is_null_ = rhs.is_null_;
    rhs->is_null_ = true;

    return *this;
  }

  ~Nullable() {
  }

  bool IsNull() const {
    return is_null_;
  }

  void Clear() {
    is_null_ = true;
  }

  Nullable& Set(const T& value) {
    value_  = value;
    is_null_ = false;
    return *this;
  }

  Nullable& Set(const Nullable& rhs) {
    value_ = rhs.value_;
    is_null_ = rhs.is_null_;
    return *this;
  }

  T* operator->() {
    assert(!is_null_);
    return &value_;
  }

  Nullable& operator = (const T& rhs) {
    return Set(rhs);
  }

  Nullable& operator = (const Nullable& rhs) {
    return Set(rhs);
  }

  T& Value() {
    assert(!is_null_);
    return value_;
  }

  const T& Value() const {
    assert(!is_null_);
    return value_;
  }

  const T& Value(const T& default_value) const {
    return is_null_ ? default_value : value_;
  }

  operator T& () {
    return Value();
  }

  operator const T& () const {
    return Value();
  }

  void swap(Nullable& rhs) {
    std::swap(value_, rhs.value_);
    std::swap(is_null_, rhs.is_null_);
  }

  // operators.
  bool operator == (const T& value) const {
    return (!is_null_ && value_ == value);
  }

  bool operator == (const Nullable<T>& rhs) const {
    return (is_null_ && rhs.is_null_) ||
           (is_null_ == rhs.is_null_ && value_ == rhs.value_);
  }

  bool operator != (const Nullable<T>& rhs) const {
    return !(*this == rhs);
  }

  bool operator != (const T& value) const {
    return !(*this == value);
  }

 private:
  T        value_;
  bool     is_null_;
};

// test equality of value type and Nullable type.
template <typename T>
bool operator==(const T& lhs, const Nullable<T>& rhs) {
  return (rhs == lhs);
}

// test inequality of value type and Nullable type.
template <typename T>
bool operator!=(const T& lhs, const Nullable<T>& rhs) {
  return !(rhs == lhs);
}

}  // namespace oss

// output to stream.
template <typename T>
std::ostream& operator<<(std::ostream& stream, const oss::Nullable<T>& rhs) {
  if (!rhs.IsNull()) {
    stream << rhs.Value();
  }
  return stream;
}

namespace std {
// swap two Nullable type.
template <typename T>
inline void swap(oss::Nullable<T>& lhs, oss::Nullable<T>& rhs) {
  lhs.swap(rhs);
}
}

#endif  // OSS_SDK_CPP_BASE_NULLABLE_H_
