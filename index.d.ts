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

export enum MarketDataEvent {
  // message = code: number
  Quit = 'quit',
  // message = undefined
  FrontConnected = 'front-connected',
  // message = reason: number
  FrontDisconnected = 'front-disconnected',
  // message = timeLapse: number
  HeartBeatWarning = 'heart-beat-warning',
  UserLogin = 'user-login',
  UserLogout = 'user-logout',
  QryMulticastInstrument = 'qry-multicast-instrument',
  Error = 'error',
  SubMarketData = 'sub-market-data',
  UnSubMarketData = 'unsub-market-data',
  SubForQuote = 'sub-for-quote',
  UnSubForQuote = 'unsub-for-quote',
  DepthMarketData = 'depth-market-data',
  ForQuote = 'for-quote'
}

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

export enum TraderEvent {
  // message = code: number
  Quit = 'quit',
  // message = undefined
  FrontConnected = 'front-connected',
  // message = reason: number
  FrontDisconnected = 'front-disconnected',
  // message = timeLapse: number
  HeartBeatWarning = 'heart-beat-warning'
}

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
