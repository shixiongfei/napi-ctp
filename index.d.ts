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

export type DisconnectReasonMessage =
  | 0x1001 // 网络读失败
  | 0x1002 // 网络写失败
  | 0x2001 // 接收心跳超时
  | 0x2002 // 发送心跳失败
  | 0x2003; // 收到错误报文

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

export type Message =
  | number
  | DisconnectReasonMessage
  | UserLoginMessage
  | UserLogoutMessage
  | MulticastInstrumentMessage
  | ErrorMessage
  | SpecificInstrumentMessage
  | DepthMarketDataMessage
  | ForQuoteMessage;

export interface CallbackFunction {
  (message?: Message): void;
}

export enum MarketDataEvent {
  // message = code: number
  Quit = "quit",
  // message = undefined
  FrontConnected = "front-connected",
  // message = reason: DisconnectReasonMessage
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

export enum TraderEvent {
  // message = code: number
  Quit = "quit",
  // message = undefined
  FrontConnected = "front-connected",
  // message = reason: DisconnectReasonMessage
  FrontDisconnected = "front-disconnected",
  // message = timeLapse: number
  HeartBeatWarning = "heart-beat-warning",
  // message =
  RspAuthenticate = "rsp-authenticate",
  // message =
  RspUserLogin = "rsp-user-login",
  // message =
  RspUserLogout = "rsp-user-logout",
  // message =
  RspUserPasswordUpdate = "rsp-user-password-update",
  // message =
  RspTradingAccountPasswordUpdate = "rsp-trading-account-password-update",
  // message =
  RspUserAuthMethod = "rsp-user-auth-method",
  // message =
  RspGenUserCaptcha = "rsp-gen-user-captcha",
  // message =
  RspGenUserText = "rsp-gen-user-text",
  // message =
  RspOrderInsert = "rsp-order-insert",
  // message =
  RspParkedOrderInsert = "rsp-parked-order-insert",
  // message =
  RspParkedOrderAction = "rsp-parked-order-action",
  // message =
  RspOrderAction = "rsp-order-action",
  // message =
  RspQryMaxOrderVolume = "rsp-qry-max-order-volume",
  // message =
  RspSettlementInfoConfirm = "rsp-settlement-info-confirm",
  // message =
  RspRemoveParkedOrder = "rsp-remove-parked-order",
  // message =
  RspRemoveParkedOrderAction = "rsp-remove-parked-order-action",
  // message =
  RspExecOrderInsert = "rsp-exec-order-insert",
  // message =
  RspExecOrderAction = "rsp-exec-order-action",
  // message =
  RspForQuoteInsert = "rsp-for-quote-insert",
  // message =
  RspQuoteInsert = "rsp-quote-insert",
  // message =
  RspQuoteAction = "rsp-quote-action",
  // message =
  RspBatchOrderAction = "rsp-batch-order-action",
  // message =
  RspOptionSelfCloseInsert = "rsp-option-self-close-insert",
  // message =
  RspOptionSelfCloseAction = "rsp-option-self-close-action",
  // message =
  RspCombActionInsert = "rsp-comb-action-insert",
  // message =
  RspQryOrder = "rsp-qry-order",
  // message =
  RspQryTrade = "rsp-qry-trade",
  // message =
  RspQryInvestorPosition = "rsp-qry-investor-position",
  // message =
  RspQryTradingAccount = "rsp-qry-trading-account",
  // message =
  RspQryInvestor = "rsp-qry-investor",
  // message =
  RspQryTradingCode = "rsp-qry-trading-code",
  // message =
  RspQryInstrumentMarginRate = "rsp-qry-instrument-margin-rate",
  // message =
  RspQryInstrumentCommissionRate = "rsp-qry-instrument-commission-rate",
  // message =
  RspQryExchange = "rsp-qry-exchange",
  // message =
  RspQryProduct = "rsp-qry-product",
  // message =
  RspQryInstrument = "rsp-qry-instrument",
  // message =
  RspQryDepthMarketData = "rsp-qry-depth-market-data",
  // message =
  RspQryTraderOffer = "rsp-qry-trader-offer",
  // message =
  RspQrySettlementInfo = "rsp-qry-settlement-info",
  // message =
  RspQryTransferBank = "rsp-qry-transfer-bank",
  // message =
  RspQryInvestorPositionDetail = "rsp-qry-investor-position-detail",
  // message =
  RspQryNotice = "rsp-qry-notice",
  // message =
  RspQrySettlementInfoConfirm = "rsp-qry-settlement-info-confirm",
  // message =
  RspQryInvestorPositionCombineDetail = "rsp-qry-investor-position-combine-detail",
  // message =
  RspQryCFMMCTradingAccountKey = "rsp-qry-cfmmc-trading-account-key",
  // message =
  RspQryEWarrantOffset = "rsp-qry-e-warrant-offset",
  // message =
  RspQryInvestorProductGroupMargin = "rsp-qry-investor-product-group-margin",
  // message =
  RspQryExchangeMarginRate = "rsp-qry-exchange-margin-rate",
  // message =
  RspQryExchangeMarginRateAdjust = "rsp-qry-exchange-margin-rate-adjust",
  // message =
  RspQryExchangeRate = "rsp-qry-exchange-rate",
  // message =
  RspQrySecAgentACIDMap = "rsp-qry-sec-agent-acid-map",
  // message =
  RspQryProductExchRate = "rsp-qry-product-exch-rate",
  // message =
  RspQryProductGroup = "rsp-qry-product-group",
  // message =
  RspQryMMInstrumentCommissionRate = "rsp-qry-mm-instrument-commission-rate",
  // message =
  RspQryMMOptionInstrCommRate = "rsp-qry-mm-option-instr-comm-rate",
  // message =
  RspQryInstrumentOrderCommRate = "rsp-qry-instrument-order-comm-rate",
  // message =
  RspQrySecAgentTradingAccount = "rsp-qry-sec-agent-trading-account",
  // message =
  RspQrySecAgentCheckMode = "rsp-qry-sec-agent-check-mode",
  // message =
  RspQrySecAgentTradeInfo = "rsp-qry-sec-agent-trade-info",
  // message =
  RspQryOptionInstrTradeCost = "rsp-qry-option-instr-trade-cost",
  // message =
  RspQryOptionInstrCommRate = "rsp-qry-option-instr-comm-rate",
  // message =
  RspQryExecOrder = "rsp-qry-exec-order",
  // message =
  RspQryForQuote = "rsp-qry-for-quote",
  // message =
  RspQryQuote = "rsp-qry-quote",
  // message =
  RspQryOptionSelfClose = "rsp-qry-option-self-close",
  // message =
  RspQryInvestUnit = "rsp-qry-invest-unit",
  // message =
  RspQryCombInstrumentGuard = "rsp-qry-comb-instrument-guard",
  // message =
  RspQryCombAction = "rsp-qry-comb-action",
  // message =
  RspQryTransferSerial = "rsp-qry-transfer-serial",
  // message =
  RspQryAccountRegister = "rsp-qry-account-register",
  // message =
  RspError = "rsp-error",
  // message =
  RtnOrder = "rtn-order",
  // message =
  RtnTrade = "rtn-trade",
  // message =
  ErrRtnOrderInsert = "err-rtn-order-insert",
  // message =
  ErrRtnOrderAction = "err-rtn-order-action",
  // message =
  RtnInstrumentStatus = "rtn-instrument-status",
  // message =
  RtnBulletin = "rtn-bulletin",
  // message =
  RtnTradingNotice = "rtn-trading-notice",
  // message =
  RtnErrorConditionalOrder = "rtn-error-conditional-order",
  // message =
  RtnExecOrder = "rtn-exec-order",
  // message =
  ErrRtnExecOrderInsert = "err-rtn-exec-order-insert",
  // message =
  ErrRtnExecOrderAction = "err-rtn-exec-order-action",
  // message =
  ErrRtnForQuoteInsert = "err-rtn-for-quote-insert",
  // message =
  RtnQuote = "rtn-quote",
  // message =
  ErrRtnQuoteInsert = "err-rtn-quote-insert",
  // message =
  ErrRtnQuoteAction = "err-rtn-quote-action",
  // message =
  RtnForQuote = "rtn-for-quote",
  // message =
  RtnCFMMCTradingAccountToken = "rtn-cfmmc-trading-account-token",
  // message =
  ErrRtnBatchOrderAction = "err-rtn-batch-order-action",
  // message =
  RtnOptionSelfClose = "rtn-option-self-close",
  // message =
  ErrRtnOptionSelfCloseInsert = "err-rtn-option-self-close-insert",
  // message =
  ErrRtnOptionSelfCloseAction = "err-rtn-option-self-close-action",
  // message =
  RtnCombAction = "rtn-comb-action",
  // message =
  ErrRtnCombActionInsert = "err-rtn-comb-action-insert",
  // message =
  RspQryContractBank = "rsp-qry-contract-bank",
  // message =
  RspQryParkedOrder = "rsp-qry-parked-order",
  // message =
  RspQryParkedOrderAction = "rsp-qry-parked-order-action",
  // message =
  RspQryTradingNotice = "rsp-qry-trading-notice",
  // message =
  RspQryBrokerTradingParams = "rsp-qry-broker-trading-params",
  // message =
  RspQryBrokerTradingAlgos = "rsp-qry-broker-trading-algos",
  // message =
  RspQueryCFMMCTradingAccountToken = "rsp-query-cfmmc-trading-account-token",
  // message =
  RtnFromBankToFutureByBank = "rtn-from-bank-to-future-by-bank",
  // message =
  RtnFromFutureToBankByBank = "rtn-from-future-to-bank-by-bank",
  // message =
  RtnRepealFromBankToFutureByBank = "rtn-repeal-from-bank-to-future-by-bank",
  // message =
  RtnRepealFromFutureToBankByBank = "rtn-repeal-from-future-to-bank-by-bank",
  // message =
  RtnFromBankToFutureByFuture = "rtn-from-bank-to-future-by-future",
  // message =
  RtnFromFutureToBankByFuture = "rtn-from-future-to-bank-by-future",
  // message =
  RtnRepealFromBankToFutureByFutureManual = "rtn-repeal-from-bank-to-future-by-future-manual",
  // message =
  RtnRepealFromFutureToBankByFutureManual = "rtn-repeal-from-future-to-bank-by-future-manual",
  // message =
  RtnQueryBankBalanceByFuture = "rtn-query-bank-balance-by-future",
  // message =
  ErrRtnBankToFutureByFuture = "err-rtn-bank-to-future-by-future",
  // message =
  ErrRtnFutureToBankByFuture = "err-rtn-future-to-bank-by-future",
  // message =
  ErrRtnRepealBankToFutureByFutureManual = "err-rtn-repeal-bank-to-future-by-future-manual",
  // message =
  ErrRtnRepealFutureToBankByFutureManual = "err-rtn-repeal-future-to-bank-by-future-manual",
  // message =
  ErrRtnQueryBankBalanceByFuture = "err-rtn-query-bank-balance-by-future",
  // message =
  RtnRepealFromBankToFutureByFuture = "rtn-repeal-from-bank-to-future-by-future",
  // message =
  RtnRepealFromFutureToBankByFuture = "rtn-repeal-from-future-to-bank-by-future",
  // message =
  RspFromBankToFutureByFuture = "rsp-from-bank-to-future-by-future",
  // message =
  RspFromFutureToBankByFuture = "rsp-from-future-to-bank-by-future",
  // message =
  RspQueryBankAccountMoneyByFuture = "rsp-query-bank-account-money-by-future",
  // message =
  RtnOpenAccountByBank = "rtn-open-account-by-bank",
  // message =
  RtnCancelAccountByBank = "rtn-cancel-account-by-bank",
  // message =
  RtnChangeAccountByBank = "rtn-change-account-by-bank",
  // message =
  RspQryClassifiedInstrument = "rsp-qry-classified-instrument",
  // message =
  RspQryCombPromotionParam = "rsp-qry-comb-promotion-param",
  // message =
  RspQryRiskSettleInvstPosition = "rsp-qry-risk-settle-invst-position",
  // message =
  RspQryRiskSettleProductStatus = "rsp-qry-risk-settle-product-status",
}

export type RequestReturn =
  | 0 // 成功
  | -1 // 网络连接失败
  | -2 // 未处理请求超过许可数
  | -3; // 每秒发送请求数超过许可数

export interface UserLoginRequest {
  BrokerID: string;
  UserID: string;
  Password: string;
}

export interface UserLogoutRequest {
  BrokerID: string;
  UserID: string;
}

export declare class MarketData {
  constructor(flowMdPath: string, frontMdAddr: string);

  /**
   * 获取API的版本信息
   * @returns 获取到的版本号
   */
  getApiVersion(): string;

  /**
   * 订阅行情
   * @param instrumentIds 合约ID列表
   */
  subscribeMarketData(instrumentIds: string[]): RequestReturn;

  /**
   * 退订行情
   * @param instrumentIds 合约ID列表
   */
  unsubscribeMarketData(instrumentIds: string[]): RequestReturn;

  /**
   * 订阅询价
   * @param instrumentIds 合约ID列表
   */
  subscribeForQuoteRsp(instrumentIds: string[]): RequestReturn;

  /**
   * 退订询价
   * @param instrumentIds 合约ID列表
   */
  unsubscribeForQuoteRsp(instrumentIds: string[]): RequestReturn;

  /**
   * 用户登录请求
   * @param reqUserLogin 用户登陆信息
   */
  userLogin(reqUserLogin: UserLoginRequest): RequestReturn;

  /**
   * 用户登出请求
   * @param reqUserLogout 用户登出信息
   */
  userLogout(reqUserLogout: UserLogoutRequest): RequestReturn;

  /**
   * 注册行情消息回调函数
   * @param event 行情消息事件
   * @param func 回调函数
   */
  on(event: MarketDataEvent, func: CallbackFunction): MarketData;
}

export declare class Trader {
  constructor(flowPath: string, frontAddr: string);

  /**
   * 获取API的版本信息
   * @returns 获取到的版本号
   */
  getApiVersion(): string;

  /**
   * 注册交易消息回调函数
   * @param event 交易消息事件
   * @param func 回调函数
   */
  on(event: TraderEvent, func: CallbackFunction): Trader;
}

export declare function createMarketData(
  flowMdPath: string,
  frontMdAddr: string
): MarketData;

export declare function createTrader(
  flowPath: string,
  frontAddr: string
): Trader;
