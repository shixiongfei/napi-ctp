/*
 * index.js
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

const binding = require("node-gyp-build")(__dirname);
const types = require("./types");

module.exports = Object.assign(binding, types);
