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

export type MarketDataEvent = 'quit'

export type MarketDataMessage = number

export interface MarketDataFunction {
  (message?: MarketDataMessage): void
}

export declare class MarketData {
  constructor(flowMdPath: string, frontMdAddr: string)
  getApiVersion(): string
  subscribeMarketData(instrumentIds: string[]): number
  unsubscribeMarketData(instrumentIds: string[]): number
  subscribeForQuoteRsp(instrumentIds: string[]): number
  unsubscribeForQuoteRsp(instrumentIds: string[]): number
  userLogin(brokerId: string, userId: string, password: string): number
  userLogout(brokerId: string, userId: string): number
  on(event: MarketDataEvent, func: MarketDataFunction): MarketData
}

export type TraderEvent = 'quit'

export type TraderMessage = number

export interface TraderFunction {
  (message?: TraderMessage): void
}

export declare class Trader {
  constructor(flowPath: string, frontAddr: string)
  getApiVersion(): string
  on(event: TraderEvent, func: TraderFunction): Trader
}

export declare function createMarketData(
  flowMdPath: string,
  frontMdAddr: string
): MarketData

export declare function createTrader(
  flowPath: string,
  frontAddr: string
): Trader
