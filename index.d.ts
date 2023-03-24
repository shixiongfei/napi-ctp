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

export interface UserLoginMessage {
  TradingDay: string;
  LoginTime: string;
  BrokerID: string;
  UserID: string;
  SystemName: string;
  FrontID: number;
  SessionID: number;
  MaxOrderRef: string;
  SHFETime: string;
  DCETime: string;
  CZCETime: string;
  FFEXTime: string;
  INETime: string;
  SysVersion: string;
}

export interface UserLogoutMessage {
  BrokerID: string;
  UserID: string;
}

export interface MulticastInstrumentMessage {
  TopicID: number;
  reserve1: string;
  InstrumentNo: number;
  CodePrice: number;
  VolumeMultiple: number;
  PriceTick: number;
  InstrumentID: string;
}

export interface ErrorMessage {
  ErrorID: number;
  ErrorMsg: string;
}

export interface SpecificInstrumentMessage {
  reserve1: string;
  InstrumentID: string;
}

export interface DepthMarketDataMessage {
  TradingDay: string;
  reserve1: string;
  ExchangeID: string;
  reserve2: string;
  LastPrice: number;
  PreSettlementPrice: number;
  PreClosePrice: number;
  PreOpenInterest: number;
  OpenPrice: number;
  HighestPrice: number;
  LowestPrice: number;
  Volume: number;
  Turnover: number;
  OpenInterest: number;
  ClosePrice: number;
  SettlementPrice: number;
  UpperLimitPrice: number;
  LowerLimitPrice: number;
  PreDelta: number;
  CurrDelta: number;
  UpdateTime: string;
  UpdateMillisec: number;
  BidPrice1: number;
  BidVolume1: number;
  AskPrice1: number;
  AskVolume1: number;
  BidPrice2: number;
  BidVolume2: number;
  AskPrice2: number;
  AskVolume2: number;
  BidPrice3: number;
  BidVolume3: number;
  AskPrice3: number;
  AskVolume3: number;
  BidPrice4: number;
  BidVolume4: number;
  AskPrice4: number;
  AskVolume4: number;
  BidPrice5: number;
  BidVolume5: number;
  AskPrice5: number;
  AskVolume5: number;
  AveragePrice: number;
  ActionDay: string;
  InstrumentID: string;
  ExchangeInstID: string;
  BandingUpperPrice: number;
  BandingLowerPrice: number;
}

export interface ForQuoteMessage {
  TradingDay: string;
  reserve1: string;
  ForQuoteSysID: string;
  ForQuoteTime: string;
  ActionDay: string;
  ExchangeID: string;
  InstrumentID: string;
}

export enum MarketDataEvent {
  // message = code: number
  Quit = "quit",
  // message = undefined
  FrontConnected = "front-connected",
  // message = reason: number
  FrontDisconnected = "front-disconnected",
  // message = timeLapse: number
  HeartBeatWarning = "heart-beat-warning",
  // message = userLogin: UserLoginMessage
  RspUserLogin = "rsp-user-login",
  // message = userLogout: UserLogoutMessage
  RspUserLogout = "rsp-user-logout",
  // message = multicastInstrument: MulticastInstrumentMessage
  RspQryMulticastInstrument = "rsp-qry-multicast-instrument",
  // message = error: ErrorMessage
  RspError = "rsp-error",
  // message = specificInstrument: SpecificInstrumentMessage
  RspSubMarketData = "rsp-sub-market-data",
  // message = specificInstrument: SpecificInstrumentMessage
  RspUnSubMarketData = "rsp-unsub-market-data",
  // message = specificInstrument: SpecificInstrumentMessage
  RspSubForQuote = "rsp-sub-for-quote",
  // message = specificInstrument: SpecificInstrumentMessage
  RspUnSubForQuote = "rsp-unsub-for-quote",
  // message = depthMarketData: DepthMarketDataMessage
  RtnDepthMarketData = "rtn-depth-market-data",
  // message = forQuote: ForQuoteMessage
  RtnForQuote = "rtn-for-quote",
}

export type MarketDataMessage =
  | number
  | UserLoginMessage
  | UserLogoutMessage
  | MulticastInstrumentMessage
  | ErrorMessage
  | SpecificInstrumentMessage
  | DepthMarketDataMessage
  | ForQuoteMessage;

export interface MarketDataFunction {
  (message?: MarketDataMessage): void;
}

export declare class MarketData {
  constructor(flowMdPath: string, frontMdAddr: string);
  getApiVersion(): string;
  subscribeMarketData(instrumentIds: string[]): number;
  unsubscribeMarketData(instrumentIds: string[]): number;
  subscribeForQuoteRsp(instrumentIds: string[]): number;
  unsubscribeForQuoteRsp(instrumentIds: string[]): number;
  userLogin(brokerId: string, userId: string, password: string): number;
  userLogout(brokerId: string, userId: string): number;
  on(event: MarketDataEvent, func: MarketDataFunction): MarketData;
}

export enum TraderEvent {
  // message = code: number
  Quit = "quit",
  // message = undefined
  FrontConnected = "front-connected",
  // message = reason: number
  FrontDisconnected = "front-disconnected",
  // message = timeLapse: number
  HeartBeatWarning = "heart-beat-warning",
}

export type TraderMessage = number;

export interface TraderFunction {
  (message?: TraderMessage): void;
}

export declare class Trader {
  constructor(flowPath: string, frontAddr: string);
  getApiVersion(): string;
  on(event: TraderEvent, func: TraderFunction): Trader;
}

export declare function createMarketData(
  flowMdPath: string,
  frontMdAddr: string
): MarketData;

export declare function createTrader(
  flowPath: string,
  frontAddr: string
): Trader;
