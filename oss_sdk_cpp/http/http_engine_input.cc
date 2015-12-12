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

#include "oss_sdk_cpp/http/http_engine_input.h"
#include "oss_sdk_cpp/utils/http_utils.h"

namespace oss {

HttpEngineInput::HttpEngineInput()
  : input_buffer(NULL),
    input_stream(NULL),
    stream_bytes(-1),
    response_size_limit(-1),
    output_stream(NULL) {
  gmt_datetime = GmtTimeNow();
}

}  // namespace oss
