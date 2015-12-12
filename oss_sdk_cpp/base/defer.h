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

#ifndef OSS_SDK_CPP_BASE_DEFER_H_
#define OSS_SDK_CPP_BASE_DEFER_H_

#include <functional>

namespace oss {

class DeferredCall {
 public:
  ~DeferredCall() {
    if (func_) {
      // do deferred call.
      func_();
    }
  }

  DeferredCall(DeferredCall&& call) :
    func_(std::forward<std::function<void()>>(call.func_)) {
    call.func_ = nullptr;
  }

  // make object non-copyable.
  DeferredCall(DeferredCall const&) = delete;
  DeferredCall& operator=(DeferredCall const&) = delete;
  DeferredCall& operator=(DeferredCall&&) = delete;

 private:
  std::function<void()> func_;

  template <typename... Params>
  DeferredCall(Params&&... params) :  // NOLINT(runtime/explicit)
    func_(std::bind(std::forward<Params>(params)...)) {
  }

  // make DeferredCall only accessible by DoDefer.
  template < typename... Params>
  friend DeferredCall DoDefer(Params&&... params);
};

template<typename... Params>
DeferredCall DoDefer(Params&&... params) {
  return DeferredCall(std::forward<Params>(params)...);
}

#define MAKE_UNIQUE_VAR(prefix, lineno)  CONCATENATE_TWO(prefix, lineno)
#define CONCATENATE_TWO(x, y)   x ## y

#define Defer \
  auto MAKE_UNIQUE_VAR(defer_var_, __LINE__) = \
  DoDefer

#define defer(...)            \
  auto MAKE_UNIQUE_VAR(defer_var_, __LINE__) = \
  DoDefer([&]{ __VA_ARGS__; });  // NOLINT, special case.

}  // namespace oss

#endif  // OSS_SDK_CPP_BASE_DEFER_H_
