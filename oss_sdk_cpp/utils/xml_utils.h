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

#ifndef OSS_SDK_CPP_UTILS_XML_UTILS_H_
#define OSS_SDK_CPP_UTILS_XML_UTILS_H_

class TiXmlNode;
class TiXmlElement;
class fstream;

namespace oss {

const char* GetXmlNodeText(TiXmlNode* node);

const char* GetXmlChildNodeText(TiXmlNode* node, const char* name);

TiXmlElement* CreateXmlNode(const char* name, const char* value);

void AddChildNode(TiXmlElement* parent, const char* name, const char* value);

}  // namespace oss

#endif  // OSS_SDK_CPP_UTILS_XML_UTILS_H_
