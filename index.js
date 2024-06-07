/*
 * index.js
 *
 * Copyright (c) 2022-2024 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

try {
  const binding = require("./build/Release/napi_ctp.node");
  module.exports = binding;
} catch {
  const binding = require("./build/Debug/napi_ctp.node");
  module.exports = binding;
}
