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

export * from "@napi-ctp/types";
export * from "./types.js";

import { dlopen } from "node:process";
import { constants } from "node:os";
import * as types from "@napi-ctp/types";
import { MarketDataEvent, TraderEvent } from "./types.js";

const binding = () => {
  const module = { exports: { MarketDataEvent, TraderEvent, ...types } };

  try {
    dlopen(module, "./build/Release/napi_ctp.node", constants.dlopen.RTLD_LAZY);
  } catch {
    try {
      dlopen(module, "./build/Debug/napi_ctp.node", constants.dlopen.RTLD_LAZY);
    } catch {
      throw new Error("Cannot find module 'napi_ctp.node'");
    }
  }

  return module;
};

export default binding().exports;
