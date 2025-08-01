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
import { dirname, join } from "node:path";
import { fileURLToPath } from "node:url";
import * as types1 from "@napi-ctp/types";
import * as types2 from "./types.js";

const binding = () => {
  const dir = dirname(fileURLToPath(import.meta.url));
  const module = { exports: {} };

  try {
    dlopen(
      module,
      join(dir, "./build/Release/napi_ctp.node"),
      constants.dlopen.RTLD_LAZY
    );
  } catch {
    try {
      dlopen(
        module,
        join(dir, "./build/Debug/napi_ctp.node"),
        constants.dlopen.RTLD_LAZY
      );
    } catch {
      throw new Error("Cannot find module 'napi_ctp.node'");
    }
  }

  return module;
};

const native = binding().exports;

export const Trader = native.Trader;
export const MarketData = native.MarketData;
export const createMarketData = native.createMarketData;
export const createTrader = native.createTrader;
export const getLastRequestId = native.getLastRequestId;
export const resetRequestId = native.resetRequestId;

export default Object.assign(native, types1, types2);
