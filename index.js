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

const binding = () => {
  try {
    return require("./build/Release/napi_ctp.node");
  } catch {
    try {
      return require("./build/Debug/napi_ctp.node");
    } catch {
      throw new Error("Cannot find module 'napi_ctp.node'");
    }
  }
};

module.exports = Object.assign(binding(), Object.assign(napi_ctp_types, types));
