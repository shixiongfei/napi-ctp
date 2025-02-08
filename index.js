/*
 * index.js
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

const napi_ctp_types = require("@napi-ctp/types");
const types = require("./types.js");

try {
  const binding = require("./build/Release/napi_ctp.node");
  module.exports = Object.assign(binding, Object.assign(napi_ctp_types, types));
} catch {
  const binding = require("./build/Debug/napi_ctp.node");
  module.exports = Object.assign(binding, Object.assign(napi_ctp_types, types));
}
