/*
 * index.d.ts
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

export declare class MarketData {
  getApiVersion(): string
}

export declare class Trader {
  getApiVersion(): string
}

export declare function createMarketData(
  flowMdPath: string,
  frontMdAddr: string
): MarketData

export declare function createTrader(
  flowPath: string,
  frontAddr: string
): Trader
