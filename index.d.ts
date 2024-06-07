/*
 * index.d.ts
 *
 * Copyright (c) 2022-2024 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

import {
  ActionFlagType,
  ActionTypeType,
  BankAccTypeType,
  BizTypeType,
  ClassTypeType,
  ClientIDTypeType,
  CombDirectionType,
  ContingentConditionType,
  CustTypeType,
  DirectionType,
  ExecOrderCloseFlagType,
  FeePayFlagType,
  ForceCloseReasonType,
  HedgeFlagType,
  IdCardTypeType,
  LastFragmentType,
  MessageFields,
  OffsetFlagType,
  OptSelfCloseFlagType,
  OrderPriceTypeType,
  ParkedOrderStatusType,
  PosiDirectionType,
  ProductClassType,
  PwdFlagType,
  TimeConditionType,
  TradingTypeType,
  TransferStatusType,
  UserTypeType,
  VolumeConditionType,
  YesNoIndicatorType,
} from "./types";

/** 行情消息事件 */
export enum MarketDataEvent {
  /** 退出 */
  Quit = "quit",
  /** 当客户端与交易后台建立起通信连接时（还未登录前） */
  FrontConnected = "front-connected",
  /** 当客户端与交易后台通信连接断开时。当发生这个情况后，API会自动重新连接，客户端可不做处理 */
  FrontDisconnected = "front-disconnected",
  /** 心跳超时警告。当长时间未收到报文时 */
  HeartBeatWarning = "heart-beat-warning",
  /** 登录请求响应 */
  RspUserLogin = "rsp-user-login",
  /** 登出请求响应 */
  RspUserLogout = "rsp-user-logout",
  /** 请求查询组播合约响应 */
  RspQryMulticastInstrument = "rsp-qry-multicast-instrument",
  /** 错误应答 */
  RspError = "rsp-error",
  /** 订阅行情应答 */
  RspSubMarketData = "rsp-sub-market-data",
  /** 取消订阅行情应答 */
  RspUnSubMarketData = "rsp-unsub-market-data",
  /** 订阅询价应答 */
  RspSubForQuote = "rsp-sub-for-quote",
  /** 取消订阅询价应答 */
  RspUnSubForQuote = "rsp-unsub-for-quote",
  /** 深度行情通知 */
  RtnDepthMarketData = "rtn-depth-market-data",
  /** 询价通知 */
  RtnForQuote = "rtn-for-quote",
}

/** 交易消息事件 */
export enum TraderEvent {
  /** 退出 */
  Quit = "quit",
  /** 当客户端与交易后台建立起通信连接时（还未登录前） */
  FrontConnected = "front-connected",
  /** 当客户端与交易后台通信连接断开时。当发生这个情况后，API会自动重新连接，客户端可不做处理 */
  FrontDisconnected = "front-disconnected",
  /** 心跳超时警告。当长时间未收到报文时 */
  HeartBeatWarning = "heart-beat-warning",
  /** 客户端认证响应 */
  RspAuthenticate = "rsp-authenticate",
  /** 登录请求响应 */
  RspUserLogin = "rsp-user-login",
  /** 登出请求响应 */
  RspUserLogout = "rsp-user-logout",
  /** 用户口令更新请求响应 */
  RspUserPasswordUpdate = "rsp-user-password-update",
  /** 资金账户口令更新请求响应 */
  RspTradingAccountPasswordUpdate = "rsp-trading-account-password-update",
  /** 查询用户当前支持的认证模式的回复 */
  RspUserAuthMethod = "rsp-user-auth-method",
  /** 获取图形验证码请求的回复 */
  RspGenUserCaptcha = "rsp-gen-user-captcha",
  /** 获取短信验证码请求的回复 */
  RspGenUserText = "rsp-gen-user-text",
  /** 报单录入请求响应 */
  RspOrderInsert = "rsp-order-insert",
  /** 预埋单录入请求响应 */
  RspParkedOrderInsert = "rsp-parked-order-insert",
  /** 预埋撤单录入请求响应 */
  RspParkedOrderAction = "rsp-parked-order-action",
  /** 报单操作请求响应 */
  RspOrderAction = "rsp-order-action",
  /** 查询最大报单数量响应 */
  RspQryMaxOrderVolume = "rsp-qry-max-order-volume",
  /** 投资者结算结果确认响应 */
  RspSettlementInfoConfirm = "rsp-settlement-info-confirm",
  /** 删除预埋单响应 */
  RspRemoveParkedOrder = "rsp-remove-parked-order",
  /** 删除预埋撤单响应 */
  RspRemoveParkedOrderAction = "rsp-remove-parked-order-action",
  /** 执行宣告录入请求响应 */
  RspExecOrderInsert = "rsp-exec-order-insert",
  /** 执行宣告操作请求响应 */
  RspExecOrderAction = "rsp-exec-order-action",
  /** 询价录入请求响应 */
  RspForQuoteInsert = "rsp-for-quote-insert",
  /** 报价录入请求响应 */
  RspQuoteInsert = "rsp-quote-insert",
  /** 报价操作请求响应 */
  RspQuoteAction = "rsp-quote-action",
  /** 批量报单操作请求响应 */
  RspBatchOrderAction = "rsp-batch-order-action",
  /** 期权自对冲录入请求响应 */
  RspOptionSelfCloseInsert = "rsp-option-self-close-insert",
  /** 期权自对冲操作请求响应 */
  RspOptionSelfCloseAction = "rsp-option-self-close-action",
  /** 申请组合录入请求响应 */
  RspCombActionInsert = "rsp-comb-action-insert",
  /** 请求查询报单响应 */
  RspQryOrder = "rsp-qry-order",
  /** 请求查询成交响应 */
  RspQryTrade = "rsp-qry-trade",
  /** 请求查询投资者持仓响应 */
  RspQryInvestorPosition = "rsp-qry-investor-position",
  /** 请求查询资金账户响应 */
  RspQryTradingAccount = "rsp-qry-trading-account",
  /** 请求查询投资者响应 */
  RspQryInvestor = "rsp-qry-investor",
  /** 请求查询交易编码响应 */
  RspQryTradingCode = "rsp-qry-trading-code",
  /** 请求查询合约保证金率响应 */
  RspQryInstrumentMarginRate = "rsp-qry-instrument-margin-rate",
  /** 请求查询合约手续费率响应 */
  RspQryInstrumentCommissionRate = "rsp-qry-instrument-commission-rate",
  /** 请求查询交易所响应 */
  RspQryExchange = "rsp-qry-exchange",
  /** 请求查询产品响应 */
  RspQryProduct = "rsp-qry-product",
  /** 请求查询合约响应 */
  RspQryInstrument = "rsp-qry-instrument",
  /** 请求查询行情响应 */
  RspQryDepthMarketData = "rsp-qry-depth-market-data",
  /** 请求查询交易员报盘机响应 */
  RspQryTraderOffer = "rsp-qry-trader-offer",
  /** 请求查询投资者结算结果响应 */
  RspQrySettlementInfo = "rsp-qry-settlement-info",
  /** 请求查询转帐银行响应 */
  RspQryTransferBank = "rsp-qry-transfer-bank",
  /** 请求查询投资者持仓明细响应 */
  RspQryInvestorPositionDetail = "rsp-qry-investor-position-detail",
  /** 请求查询客户通知响应 */
  RspQryNotice = "rsp-qry-notice",
  /** 请求查询结算信息确认响应 */
  RspQrySettlementInfoConfirm = "rsp-qry-settlement-info-confirm",
  /** 请求查询投资者持仓明细响应 */
  RspQryInvestorPositionCombineDetail = "rsp-qry-investor-position-combine-detail",
  /** 查询保证金监管系统经纪公司资金账户密钥响应 */
  RspQryCFMMCTradingAccountKey = "rsp-qry-cfmmc-trading-account-key",
  /** 请求查询仓单折抵信息响应 */
  RspQryEWarrantOffset = "rsp-qry-e-warrant-offset",
  /** 请求查询投资者品种/跨品种保证金响应 */
  RspQryInvestorProductGroupMargin = "rsp-qry-investor-product-group-margin",
  /** 请求查询交易所保证金率响应 */
  RspQryExchangeMarginRate = "rsp-qry-exchange-margin-rate",
  /** 请求查询交易所调整保证金率响应 */
  RspQryExchangeMarginRateAdjust = "rsp-qry-exchange-margin-rate-adjust",
  /** 请求查询汇率响应 */
  RspQryExchangeRate = "rsp-qry-exchange-rate",
  /** 请求查询二级代理操作员银期权限响应 */
  RspQrySecAgentACIDMap = "rsp-qry-sec-agent-acid-map",
  /** 请求查询产品报价汇率 */
  RspQryProductExchRate = "rsp-qry-product-exch-rate",
  /** 请求查询产品组 */
  RspQryProductGroup = "rsp-qry-product-group",
  /** 请求查询做市商合约手续费率响应 */
  RspQryMMInstrumentCommissionRate = "rsp-qry-mm-instrument-commission-rate",
  /** 请求查询做市商期权合约手续费响应 */
  RspQryMMOptionInstrCommRate = "rsp-qry-mm-option-instr-comm-rate",
  /** 请求查询报单手续费响应 */
  RspQryInstrumentOrderCommRate = "rsp-qry-instrument-order-comm-rate",
  /** 请求查询资金账户响应 */
  RspQrySecAgentTradingAccount = "rsp-qry-sec-agent-trading-account",
  /** 请求查询二级代理商资金校验模式响应 */
  RspQrySecAgentCheckMode = "rsp-qry-sec-agent-check-mode",
  /** 请求查询二级代理商信息响应 */
  RspQrySecAgentTradeInfo = "rsp-qry-sec-agent-trade-info",
  /** 请求查询期权交易成本响应 */
  RspQryOptionInstrTradeCost = "rsp-qry-option-instr-trade-cost",
  /** 请求查询期权合约手续费响应 */
  RspQryOptionInstrCommRate = "rsp-qry-option-instr-comm-rate",
  /** 请求查询执行宣告响应 */
  RspQryExecOrder = "rsp-qry-exec-order",
  /** 请求查询询价响应 */
  RspQryForQuote = "rsp-qry-for-quote",
  /** 请求查询报价响应 */
  RspQryQuote = "rsp-qry-quote",
  /** 请求查询期权自对冲响应 */
  RspQryOptionSelfClose = "rsp-qry-option-self-close",
  /** 请求查询投资单元响应 */
  RspQryInvestUnit = "rsp-qry-invest-unit",
  /** 请求查询组合合约安全系数响应 */
  RspQryCombInstrumentGuard = "rsp-qry-comb-instrument-guard",
  /** 请求查询申请组合响应 */
  RspQryCombAction = "rsp-qry-comb-action",
  /** 请求查询转帐流水响应 */
  RspQryTransferSerial = "rsp-qry-transfer-serial",
  /** 请求查询银期签约关系响应 */
  RspQryAccountRegister = "rsp-qry-account-register",
  /** 错误应答 */
  RspError = "rsp-error",
  /** 报单通知 */
  RtnOrder = "rtn-order",
  /** 成交通知 */
  RtnTrade = "rtn-trade",
  /** 报单录入错误回报 */
  ErrRtnOrderInsert = "err-rtn-order-insert",
  /** 报单操作错误回报 */
  ErrRtnOrderAction = "err-rtn-order-action",
  /** 合约交易状态通知 */
  RtnInstrumentStatus = "rtn-instrument-status",
  /** 交易所公告通知 */
  RtnBulletin = "rtn-bulletin",
  /** 交易通知 */
  RtnTradingNotice = "rtn-trading-notice",
  /** 提示条件单校验错误 */
  RtnErrorConditionalOrder = "rtn-error-conditional-order",
  /** 执行宣告通知 */
  RtnExecOrder = "rtn-exec-order",
  /** 执行宣告录入错误回报 */
  ErrRtnExecOrderInsert = "err-rtn-exec-order-insert",
  /** 执行宣告操作错误回报 */
  ErrRtnExecOrderAction = "err-rtn-exec-order-action",
  /** 询价录入错误回报 */
  ErrRtnForQuoteInsert = "err-rtn-for-quote-insert",
  /** 报价通知 */
  RtnQuote = "rtn-quote",
  /** 报价录入错误回报 */
  ErrRtnQuoteInsert = "err-rtn-quote-insert",
  /** 报价操作错误回报 */
  ErrRtnQuoteAction = "err-rtn-quote-action",
  /** 询价通知 */
  RtnForQuote = "rtn-for-quote",
  /** 保证金监控中心用户令牌 */
  RtnCFMMCTradingAccountToken = "rtn-cfmmc-trading-account-token",
  /** 批量报单操作错误回报 */
  ErrRtnBatchOrderAction = "err-rtn-batch-order-action",
  /** 期权自对冲通知 */
  RtnOptionSelfClose = "rtn-option-self-close",
  /** 期权自对冲录入错误回报 */
  ErrRtnOptionSelfCloseInsert = "err-rtn-option-self-close-insert",
  /** 期权自对冲操作错误回报 */
  ErrRtnOptionSelfCloseAction = "err-rtn-option-self-close-action",
  /** 申请组合通知 */
  RtnCombAction = "rtn-comb-action",
  /** 申请组合录入错误回报 */
  ErrRtnCombActionInsert = "err-rtn-comb-action-insert",
  /** 请求查询签约银行响应 */
  RspQryContractBank = "rsp-qry-contract-bank",
  /** 请求查询预埋单响应 */
  RspQryParkedOrder = "rsp-qry-parked-order",
  /** 请求查询预埋撤单响应 */
  RspQryParkedOrderAction = "rsp-qry-parked-order-action",
  /** 请求查询交易通知响应 */
  RspQryTradingNotice = "rsp-qry-trading-notice",
  /** 请求查询经纪公司交易参数响应 */
  RspQryBrokerTradingParams = "rsp-qry-broker-trading-params",
  /** 请求查询经纪公司交易算法响应 */
  RspQryBrokerTradingAlgos = "rsp-qry-broker-trading-algos",
  /** 银行发起银行资金转期货通知 */
  RtnFromBankToFutureByBank = "rtn-from-bank-to-future-by-bank",
  /** 银行发起期货资金转银行通知 */
  RtnFromFutureToBankByBank = "rtn-from-future-to-bank-by-bank",
  /** 银行发起冲正银行转期货通知 */
  RtnRepealFromBankToFutureByBank = "rtn-repeal-from-bank-to-future-by-bank",
  /** 银行发起冲正期货转银行通知 */
  RtnRepealFromFutureToBankByBank = "rtn-repeal-from-future-to-bank-by-bank",
  /** 期货发起银行资金转期货通知 */
  RtnFromBankToFutureByFuture = "rtn-from-bank-to-future-by-future",
  /** 期货发起期货资金转银行通知 */
  RtnFromFutureToBankByFuture = "rtn-from-future-to-bank-by-future",
  /** 系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知 */
  RtnRepealFromBankToFutureByFutureManual = "rtn-repeal-from-bank-to-future-by-future-manual",
  /** 系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知 */
  RtnRepealFromFutureToBankByFutureManual = "rtn-repeal-from-future-to-bank-by-future-manual",
  /** 期货发起查询银行余额通知 */
  RtnQueryBankBalanceByFuture = "rtn-query-bank-balance-by-future",
  /** 期货发起银行资金转期货错误回报 */
  ErrRtnBankToFutureByFuture = "err-rtn-bank-to-future-by-future",
  /** 期货发起期货资金转银行错误回报 */
  ErrRtnFutureToBankByFuture = "err-rtn-future-to-bank-by-future",
  /** 系统运行时期货端手工发起冲正银行转期货错误回报 */
  ErrRtnRepealBankToFutureByFutureManual = "err-rtn-repeal-bank-to-future-by-future-manual",
  /** 系统运行时期货端手工发起冲正期货转银行错误回报 */
  ErrRtnRepealFutureToBankByFutureManual = "err-rtn-repeal-future-to-bank-by-future-manual",
  /** 期货发起查询银行余额错误回报 */
  ErrRtnQueryBankBalanceByFuture = "err-rtn-query-bank-balance-by-future",
  /** 期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知 */
  RtnRepealFromBankToFutureByFuture = "rtn-repeal-from-bank-to-future-by-future",
  /** 期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知 */
  RtnRepealFromFutureToBankByFuture = "rtn-repeal-from-future-to-bank-by-future",
  /** 期货发起银行资金转期货应答 */
  RspFromBankToFutureByFuture = "rsp-from-bank-to-future-by-future",
  /** 期货发起期货资金转银行应答 */
  RspFromFutureToBankByFuture = "rsp-from-future-to-bank-by-future",
  /** 期货发起查询银行余额应答 */
  RspQueryBankAccountMoneyByFuture = "rsp-query-bank-account-money-by-future",
  /** 银行发起银期开户通知 */
  RtnOpenAccountByBank = "rtn-open-account-by-bank",
  /** 银行发起银期销户通知 */
  RtnCancelAccountByBank = "rtn-cancel-account-by-bank",
  /** 银行发起变更银行账号通知 */
  RtnChangeAccountByBank = "rtn-change-account-by-bank",
  /** 请求查询分类合约响应 */
  RspQryClassifiedInstrument = "rsp-qry-classified-instrument",
  /** 请求组合优惠比例响应 */
  RspQryCombPromotionParam = "rsp-qry-comb-promotion-param",
  /** 投资者风险结算持仓查询响应 */
  RspQryRiskSettleInvstPosition = "rsp-qry-risk-settle-invst-position",
  /** 风险结算产品查询响应 */
  RspQryRiskSettleProductStatus = "rsp-qry-risk-settle-product-status",
}

export type CallbackMessage = undefined | number | MessageFields;

export type CallbackOptions = {
  requestId?: number;
  isLast?: boolean;
  timestamp: number;
  elapsed: number;
};

/** 消息事件回调接口 */
export type CallbackFunction = (
  message: CallbackMessage,
  options: CallbackOptions
) => void;

/** 行情对象 */
export declare class MarketData {
  /**
   *
   * @param flowMdPath 存贮订阅信息文件的目录
   * @param frontMdAddr 前置机网络地址
   */
  constructor(flowMdPath: string, frontMdAddr: string);

  /**
   * 获取API的版本信息
   * @returns 获取到的版本号
   */
  getApiVersion(): string;

  /**
   * 获取当前交易日
   * @returns 获取到的交易日
   */
  getTradingDay(): string;

  /**
   * 订阅行情
   * @param instrumentIds 合约ID列表
   */
  subscribeMarketData(instrumentIds: string[]): number;

  /**
   * 退订行情
   * @param instrumentIds 合约ID列表
   */
  unsubscribeMarketData(instrumentIds: string[]): number;

  /**
   * 订阅询价
   * @param instrumentIds 合约ID列表
   */
  subscribeForQuoteRsp(instrumentIds: string[]): number;

  /**
   * 退订询价
   * @param instrumentIds 合约ID列表
   */
  unsubscribeForQuoteRsp(instrumentIds: string[]): number;

  /**
   * 用户登录请求
   * @param req 用户登陆信息
   */
  reqUserLogin(
    req?: Partial<{
      /** 交易日 */
      TradingDay: string;
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
      /** 密码 */
      Password: string;
      /** 用户端产品信息 */
      UserProductInfo: string;
      /** 接口端产品信息 */
      InterfaceProductInfo: string;
      /** 协议信息 */
      ProtocolInfo: string;
      /** Mac地址 */
      MacAddress: string;
      /** 动态密码 */
      OneTimePassword: string;
      /** 登录备注 */
      LoginRemark: string;
      /** 终端IP端口 */
      ClientIPPort: number;
      /** 终端IP地址 */
      ClientIPAddress: string;
    }>
  ): number;

  /**
   * 用户登出请求
   * @param req 用户登出信息
   */
  reqUserLogout(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
    }>
  ): number;

  /**
   * 注册行情消息回调函数
   * @param event 行情消息事件
   * @param func 回调函数
   */
  on(event: MarketDataEvent, func: CallbackFunction): MarketData;

  /**
   * 关闭行情对象
   */
  close(): void;
}

/** 交易对象 */
export declare class Trader {
  /**
   *
   * @param flowPath 存贮订阅信息文件的目录
   * @param frontAddr 前置机网络地址
   */
  constructor(flowPath: string, frontAddr: string);

  /**
   * 获取API的版本信息
   * @returns 获取到的版本号
   */
  getApiVersion(): string;

  /**
   * 获取当前交易日
   * @returns 获取到的交易日
   */
  getTradingDay(): string;

  /**
   * 客户端认证请求
   * @param req 客户端认证信息
   */
  reqAuthenticate(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
      /** 用户端产品信息 */
      UserProductInfo: string;
      /** 认证码 */
      AuthCode: string;
      /** App代码 */
      AppID: string;
    }>
  ): number;

  /**
   * 用户登录请求
   * @param req 用户登陆信息
   */
  reqUserLogin(
    req?: Partial<{
      /** 交易日 */
      TradingDay: string;
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
      /** 密码 */
      Password: string;
      /** 用户端产品信息 */
      UserProductInfo: string;
      /** 接口端产品信息 */
      InterfaceProductInfo: string;
      /** 协议信息 */
      ProtocolInfo: string;
      /** Mac地址 */
      MacAddress: string;
      /** 动态密码 */
      OneTimePassword: string;
      /** 登录备注 */
      LoginRemark: string;
      /** 终端IP端口 */
      ClientIPPort: number;
      /** 终端IP地址 */
      ClientIPAddress: string;
    }>
  ): number;

  /**
   * 用户登出请求
   * @param req 用户登出信息
   */
  reqUserLogout(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
    }>
  ): number;

  /**
   * 用户口令更新请求
   * @param req 用户口令信息
   */
  reqUserPasswordUpdate(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
      /** 原来的口令 */
      OldPassword: string;
      /** 新的口令 */
      NewPassword: string;
    }>
  ): number;

  /**
   * 资金账户口令更新请求
   * @param req 用户口令信息
   */
  reqTradingAccountPasswordUpdate(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者帐号 */
      AccountID: string;
      /** 原来的口令 */
      OldPassword: string;
      /** 新的口令 */
      NewPassword: string;
      /** 币种代码 */
      CurrencyID: string;
    }>
  ): number;

  /**
   * 查询用户当前支持的认证模式
   * @param req 用户信息
   */
  reqUserAuthMethod(
    req?: Partial<{
      /** 交易日 */
      TradingDay: string;
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
    }>
  ): number;

  /**
   * 用户发出获取图形验证码请求
   * @param req 用户信息
   */
  reqGenUserCaptcha(
    req?: Partial<{
      /** 交易日 */
      TradingDay: string;
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
    }>
  ): number;

  /**
   * 用户发出获取短信验证码请求
   * @param req 用户信息
   */
  reqGenUserText(
    req?: Partial<{
      /** 交易日 */
      TradingDay: string;
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
    }>
  ): number;

  /**
   * 用户发出带有图片验证码的登陆请求
   * @param req 用户登陆信息
   */
  reqUserLoginWithCaptcha(
    req?: Partial<{
      /** 交易日 */
      TradingDay: string;
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
      /** 密码 */
      Password: string;
      /** 用户端产品信息 */
      UserProductInfo: string;
      /** 接口端产品信息 */
      InterfaceProductInfo: string;
      /** 协议信息 */
      ProtocolInfo: string;
      /** Mac地址 */
      MacAddress: string;
      /** 登录备注 */
      LoginRemark: string;
      /** 图形验证码的文字内容 */
      Captcha: string;
      /** 终端IP端口 */
      ClientIPPort: number;
      /** 终端IP地址 */
      ClientIPAddress: string;
    }>
  ): number;

  /**
   * 用户发出带有短信验证码的登陆请求
   * @param req 用户登陆信息
   */
  reqUserLoginWithText(
    req?: Partial<{
      /** 交易日 */
      TradingDay: string;
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
      /** 密码 */
      Password: string;
      /** 用户端产品信息 */
      UserProductInfo: string;
      /** 接口端产品信息 */
      InterfaceProductInfo: string;
      /** 协议信息 */
      ProtocolInfo: string;
      /** Mac地址 */
      MacAddress: string;
      /** 登录备注 */
      LoginRemark: string;
      /** 短信验证码文字内容 */
      Text: string;
      /** 终端IP端口 */
      ClientIPPort: number;
      /** 终端IP地址 */
      ClientIPAddress: string;
    }>
  ): number;

  /**
   * 用户发出带有动态口令的登陆请求
   * @param req 用户登陆信息
   */
  reqUserLoginWithOTP(
    req?: Partial<{
      /** 交易日 */
      TradingDay: string;
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
      /** 密码 */
      Password: string;
      /** 用户端产品信息 */
      UserProductInfo: string;
      /** 接口端产品信息 */
      InterfaceProductInfo: string;
      /** 协议信息 */
      ProtocolInfo: string;
      /** Mac地址 */
      MacAddress: string;
      /** 登录备注 */
      LoginRemark: string;
      /** OTP密码 */
      OTPPassword: string;
      /** 终端IP端口 */
      ClientIPPort: number;
      /** 终端IP地址 */
      ClientIPAddress: string;
    }>
  ): number;

  /**
   * 报单录入请求
   * @param req 报单信息
   */
  reqOrderInsert(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 报单引用 */
      OrderRef: string;
      /** 用户代码 */
      UserID: string;
      /** 报单价格条件 */
      OrderPriceType: OrderPriceTypeType;
      /** 买卖方向 */
      Direction: DirectionType;
      /** 组合开平标志 @type [OffsetFlagType].join("") */
      CombOffsetFlag: string;
      /** 组合投机套保标志 @type [HedgeFlagType].join("") */
      CombHedgeFlag: string;
      /** 价格 */
      LimitPrice: number;
      /** 数量 */
      VolumeTotalOriginal: number;
      /** 有效期类型 */
      TimeCondition: TimeConditionType;
      /** GTD日期 */
      GTDDate: string;
      /** 成交量类型 */
      VolumeCondition: VolumeConditionType;
      /** 最小成交量 */
      MinVolume: number;
      /** 触发条件 */
      ContingentCondition: ContingentConditionType;
      /** 止损价 */
      StopPrice: number;
      /** 强平原因 */
      ForceCloseReason: ForceCloseReasonType;
      /** 自动挂起标志 */
      IsAutoSuspend: number;
      /** 业务单元 */
      BusinessUnit: string;
      /** 请求编号 */
      RequestID: number;
      /** 用户强评标志 */
      UserForceClose: number;
      /** 互换单标志 */
      IsSwapOrder: number;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 资金账号 */
      AccountID: string;
      /** 币种代码 */
      CurrencyID: string;
      /** 交易编码 */
      ClientID: string;
      /** Mac地址 */
      MacAddress: string;
      /** 合约代码 */
      InstrumentID: string;
      /** IP地址 */
      IPAddress: string;
    }>
  ): number;

  /**
   * 预埋单录入请求
   * @param req 预埋单信息
   */
  reqParkedOrderInsert(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 报单引用 */
      OrderRef: string;
      /** 用户代码 */
      UserID: string;
      /** 报单价格条件 */
      OrderPriceType: OrderPriceTypeType;
      /** 买卖方向 */
      Direction: DirectionType;
      /** 组合开平标志 @type [OffsetFlagType].join("") */
      CombOffsetFlag: string;
      /** 组合投机套保标志 @type [HedgeFlagType].join("") */
      CombHedgeFlag: string;
      /** 价格 */
      LimitPrice: number;
      /** 数量 */
      VolumeTotalOriginal: number;
      /** 有效期类型 */
      TimeCondition: TimeConditionType;
      /** GTD日期 */
      GTDDate: string;
      /** 成交量类型 */
      VolumeCondition: VolumeConditionType;
      /** 最小成交量 */
      MinVolume: number;
      /** 触发条件 */
      ContingentCondition: ContingentConditionType;
      /** 止损价 */
      StopPrice: number;
      /** 强平原因 */
      ForceCloseReason: ForceCloseReasonType;
      /** 自动挂起标志 */
      IsAutoSuspend: number;
      /** 业务单元 */
      BusinessUnit: string;
      /** 请求编号 */
      RequestID: number;
      /** 用户强评标志 */
      UserForceClose: number;
      /** 交易所代码 */
      ExchangeID: string;
      /** 预埋报单编号 */
      ParkedOrderID: string;
      /** 用户类型 */
      UserType: UserTypeType;
      /** 预埋单状态 */
      Status: ParkedOrderStatusType;
      /** 错误代码 */
      ErrorID: number;
      /** 错误信息 */
      ErrorMsg: string;
      /** 互换单标志 */
      IsSwapOrder: number;
      /** 资金账号 */
      AccountID: string;
      /** 币种代码 */
      CurrencyID: string;
      /** 交易编码 */
      ClientID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** Mac地址 */
      MacAddress: string;
      /** 合约代码 */
      InstrumentID: string;
      /** IP地址 */
      IPAddress: string;
    }>
  ): number;

  /**
   * 预埋撤单录入请求
   * @param req 预埋单信息
   */
  reqParkedOrderAction(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 报单操作引用 */
      OrderActionRef: number;
      /** 报单引用 */
      OrderRef: string;
      /** 请求编号 */
      RequestID: number;
      /** 前置编号 */
      FrontID: number;
      /** 会话编号 */
      SessionID: number;
      /** 交易所代码 */
      ExchangeID: string;
      /** 报单编号 */
      OrderSysID: string;
      /** 操作标志 */
      ActionFlag: ActionFlagType;
      /** 价格 */
      LimitPrice: number;
      /** 数量变化 */
      VolumeChange: number;
      /** 用户代码 */
      UserID: string;
      /** 预埋撤单单编号 */
      ParkedOrderActionID: string;
      /** 用户类型 */
      UserType: UserTypeType;
      /** 预埋撤单状态 */
      Status: ParkedOrderStatusType;
      /** 错误代码 */
      ErrorID: number;
      /** 错误信息 */
      ErrorMsg: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** Mac地址 */
      MacAddress: string;
      /** 合约代码 */
      InstrumentID: string;
      /** IP地址 */
      IPAddress: string;
    }>
  ): number;

  /**
   * 报单操作请求
   * @param req 报单信息
   */
  reqOrderAction(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 报单操作引用 */
      OrderActionRef: number;
      /** 报单引用 */
      OrderRef: string;
      /** 请求编号 */
      RequestID: number;
      /** 前置编号 */
      FrontID: number;
      /** 会话编号 */
      SessionID: number;
      /** 交易所代码 */
      ExchangeID: string;
      /** 报单编号 */
      OrderSysID: string;
      /** 操作标志 */
      ActionFlag: ActionFlagType;
      /** 价格 */
      LimitPrice: number;
      /** 数量变化 */
      VolumeChange: number;
      /** 用户代码 */
      UserID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** Mac地址 */
      MacAddress: string;
      /** 合约代码 */
      InstrumentID: string;
      /** IP地址 */
      IPAddress: string;
    }>
  ): number;

  /**
   * 查询最大报单数量请求
   * @param req 查询最大报单数量
   */
  reqQryMaxOrderVolume(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 买卖方向 */
      Direction: DirectionType;
      /** 开平标志 */
      OffsetFlag: OffsetFlagType;
      /** 投机套保标志 */
      HedgeFlag: HedgeFlagType;
      /** 最大允许报单数量 */
      MaxVolume: number;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 投资者结算结果确认
   * @param req 投资者结算结果确认信息
   */
  reqSettlementInfoConfirm(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 确认日期 */
      ConfirmDate: string;
      /** 确认时间 */
      ConfirmTime: string;
      /** 结算编号 */
      SettlementID: number;
      /** 投资者帐号 */
      AccountID: string;
      /** 币种代码 */
      CurrencyID: string;
    }>
  ): number;

  /**
   * 请求删除预埋单
   * @param req 预埋单信息
   */
  reqRemoveParkedOrder(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 预埋报单编号 */
      ParkedOrderID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
    }>
  ): number;

  /**
   * 请求删除预埋撤单
   * @param req 预埋单信息
   */
  reqRemoveParkedOrderAction(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 预埋撤单编号 */
      ParkedOrderActionID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
    }>
  ): number;

  /**
   * 执行宣告录入请求
   * @param req 宣告信息
   */
  reqExecOrderInsert(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 执行宣告引用 */
      ExecOrderRef: string;
      /** 用户代码 */
      UserID: string;
      /** 数量 */
      Volume: number;
      /** 请求编号 */
      RequestID: number;
      /** 业务单元 */
      BusinessUnit: string;
      /** 开平标志 */
      OffsetFlag: OffsetFlagType;
      /** 投机套保标志 */
      HedgeFlag: HedgeFlagType;
      /** 执行类型 */
      ActionType: ActionTypeType;
      /** 保留头寸申请的持仓方向 */
      PosiDirection: PosiDirectionType;
      /** 期权行权后生成的头寸是否自动平仓 */
      CloseFlag: ExecOrderCloseFlagType;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 资金账号 */
      AccountID: string;
      /** 币种代码 */
      CurrencyID: string;
      /** 客户代码 */
      ClientID: string;
      /** Mac地址 */
      MacAddress: string;
      /** 合约代码 */
      InstrumentID: string;
      /** IP地址 */
      IPAddress: string;
    }>
  ): number;

  /**
   * 执行宣告操作请求
   * @param req 宣告信息
   */
  reqExecOrderAction(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 执行宣告操作引用 */
      ExecOrderActionRef: number;
      /** 执行宣告引用 */
      ExecOrderRef: string;
      /** 请求编号 */
      RequestID: number;
      /** 前置编号 */
      FrontID: number;
      /** 会话编号 */
      SessionID: number;
      /** 交易所代码 */
      ExchangeID: string;
      /** 执行宣告编号 */
      ExecOrderSysID: number;
      /** 操作标志 */
      ActionFlag: ActionFlagType;
      /** 用户代码 */
      UserID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** Mac地址 */
      MacAddress: string;
      /** 合约代码 */
      InstrumentID: string;
      /** IP地址 */
      IPAddress: string;
    }>
  ): number;

  /**
   * 询价录入请求
   * @param req 询价信息
   */
  reqForQuoteInsert(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 询价引用 */
      ForQuoteRef: string;
      /** 用户代码 */
      UserID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** Mac地址 */
      MacAddress: string;
      /** 合约代码 */
      InstrumentID: string;
      /** IP地址 */
      IPAddress: string;
    }>
  ): number;

  /**
   * 报价录入请求
   * @param req 报价信息
   */
  reqQuoteInsert(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 报价引用 */
      QuoteRef: string;
      /** 用户代码 */
      UserID: string;
      /** 卖价格 */
      AskPrice: number;
      /** 买价格 */
      BidPrice: number;
      /** 卖数量 */
      AskVolume: number;
      /** 买数量 */
      BidVolume: number;
      /** 请求编号 */
      RequestID: number;
      /** 业务单元 */
      BusinessUnit: string;
      /** 卖开平标志 */
      AskOffsetFlag: OffsetFlagType;
      /** 买开平标志 */
      BidOffsetFlag: OffsetFlagType;
      /** 卖投机套保标志 */
      AskHedgeFlag: HedgeFlagType;
      /** 买投机套保标志 */
      BidHedgeFlag: HedgeFlagType;
      /** 衍生卖报单引用 */
      AskOrderRef: string;
      /** 衍生买报单引用 */
      BidOrderRef: string;
      /** 应价编号 */
      ForQuoteSysID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 客户代码 */
      ClientID: string;
      /** Mac地址 */
      MacAddress: string;
      /** 合约代码 */
      InstrumentID: string;
      /** IP地址 */
      IPAddress: string;
      /** 被顶单编号 */
      ReplaceSysID: string;
    }>
  ): number;

  /**
   * 报价操作请求
   * @param req 报价信息
   */
  reqQuoteAction(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 报价操作引用 */
      QuoteActionRef: number;
      /** 报价引用 */
      QuoteRef: string;
      /** 请求编号 */
      RequestID: number;
      /** 前置编号 */
      FrontID: number;
      /** 会话编号 */
      SessionID: number;
      /** 交易所代码 */
      ExchangeID: string;
      /** 报价操作编号 */
      QuoteSysID: string;
      /** 操作标志 */
      ActionFlag: ActionFlagType;
      /** 用户代码 */
      UserID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 客户代码 */
      ClientID: string;
      /** Mac地址 */
      MacAddress: string;
      /** 合约代码 */
      InstrumentID: string;
      /** IP地址 */
      IPAddress: string;
    }>
  ): number;

  /**
   * 批量报单操作请求
   * @param req 报单请求
   */
  reqBatchOrderAction(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 报单操作引用 */
      OrderActionRef: number;
      /** 请求编号 */
      RequestID: number;
      /** 前置编号 */
      FrontID: number;
      /** 会话编号 */
      SessionID: number;
      /** 交易所代码 */
      ExchangeID: string;
      /** 用户代码 */
      UserID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** Mac地址 */
      MacAddress: string;
      /** IP地址 */
      IPAddress: string;
    }>
  ): number;

  /**
   * 期权自对冲录入请求
   * @param req 期权自对冲信息
   */
  reqOptionSelfCloseInsert(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 期权自对冲引用 */
      OptionSelfCloseRef: string;
      /** 用户代码 */
      UserID: string;
      /** 数量 */
      Volume: number;
      /** 请求编号 */
      RequestID: number;
      /** 业务单元 */
      BusinessUnit: string;
      /** 投机套保标志 */
      HedgeFlag: HedgeFlagType;
      /** 期权行权的头寸是否自对冲 */
      OptSelfCloseFlag: OptSelfCloseFlagType;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 资金账号 */
      AccountID: string;
      /** 币种代码 */
      CurrencyID: string;
      /** 客户代码 */
      ClientID: string;
      /** Mac地址 */
      MacAddress: string;
      /** 合约代码 */
      InstrumentID: string;
      /** IP地址 */
      IPAddress: string;
    }>
  ): number;

  /**
   * 期权自对冲操作请求
   * @param req 期权自对冲信息
   */
  reqOptionSelfCloseAction(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 期权自对冲操作引用 */
      OptionSelfCloseActionRef: number;
      /** 期权自对冲引用 */
      OptionSelfCloseRef: string;
      /** 请求编号 */
      RequestID: number;
      /** 前置编号 */
      FrontID: number;
      /** 会话编号 */
      SessionID: number;
      /** 交易所代码 */
      ExchangeID: string;
      /** 期权自对冲操作编号 */
      OptionSelfCloseSysID: string;
      /** 操作标志 */
      ActionFlag: ActionFlagType;
      /** 用户代码 */
      UserID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** Mac地址 */
      MacAddress: string;
      /** 合约代码 */
      InstrumentID: string;
      /** IP地址 */
      IPAddress: string;
    }>
  ): number;

  /**
   * 申请组合录入请求
   * @param req 组合信息
   */
  reqCombActionInsert(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 组合引用 */
      CombActionRef: string;
      /** 用户代码 */
      UserID: string;
      /** 买卖方向 */
      Direction: DirectionType;
      /** 数量 */
      Volume: number;
      /** 组合指令方向 */
      CombDirection: CombDirectionType;
      /** 投机套保标志 */
      HedgeFlag: HedgeFlagType;
      /** 交易所代码 */
      ExchangeID: string;
      /** Mac地址 */
      MacAddress: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 前置编号 */
      FrontID: number;
      /** 会话编号 */
      SessionID: number;
      /** 合约代码 */
      InstrumentID: string;
      /** IP地址 */
      IPAddress: string;
    }>
  ): number;

  /**
   * 请求查询报单
   * @param req 查询信息
   */
  reqQryOrder(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 报单编号 */
      OrderSysID: string;
      /** 开始时间 */
      InsertTimeStart: string;
      /** 结束时间 */
      InsertTimeEnd: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询成交
   * @param req 查询信息
   */
  reqQryTrade(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 成交编号 */
      TradeID: string;
      /** 开始时间 */
      TradeTimeStart: string;
      /** 结束时间 */
      TradeTimeEnd: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询投资者持仓
   * @param req 查询信息
   */
  reqQryInvestorPosition(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询资金账户
   * @param req 查询信息
   */
  reqQryTradingAccount(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 币种代码 */
      CurrencyID: string;
      /** 业务类型 */
      BizType: BizTypeType;
      /** 资金账号 */
      AccountID: string;
    }>
  ): number;

  /**
   * 请求查询投资者
   * @param req 查询信息
   */
  reqQryInvestor(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
    }>
  ): number;

  /**
   * 请求查询交易编码
   * @param req 查询信息
   */
  reqQryTradingCode(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 客户代码 */
      ClientID: string;
      /** 交易编码类型 */
      ClientIDType: ClientIDTypeType;
      /** 投资单元代码 */
      InvestUnitID: string;
    }>
  ): number;

  /**
   * 请求查询合约保证金率
   * @param req 查询信息
   */
  reqQryInstrumentMarginRate(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 投机套保标志 */
      HedgeFlag: HedgeFlagType;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询合约手续费率
   * @param req 查询信息
   */
  reqQryInstrumentCommissionRate(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询交易所
   * @param req 查询信息
   */
  reqQryExchange(
    req?: Partial<{
      /** 交易所代码 */
      ExchangeID: string;
    }>
  ): number;

  /**
   * 请求查询产品
   * @param req 查询信息
   */
  reqQryProduct(
    req?: Partial<{
      /** 产品类型 */
      ProductClass: ProductClassType;
      /** 交易所代码 */
      ExchangeID: string;
      /** 产品代码 */
      ProductID: string;
    }>
  ): number;

  /**
   * 请求查询合约
   * @param req 查询信息
   */
  reqQryInstrument(
    req?: Partial<{
      /** 交易所代码 */
      ExchangeID: string;
      /** 合约代码 */
      InstrumentID: string;
      /** 合约在交易所的代码 */
      ExchangeInstID: string;
      /** 产品代码 */
      ProductID: string;
    }>
  ): number;

  /**
   * 请求查询行情
   * @param req 查询信息
   */
  reqQryDepthMarketData(
    req?: Partial<{
      /** 交易所代码 */
      ExchangeID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询交易员报盘机
   * @param req 查询信息
   */
  reqQryTraderOffer(
    req?: Partial<{
      /** 交易所代码 */
      ExchangeID: string;
      /** 会员代码 */
      ParticipantID: string;
      /** 交易所交易员代码 */
      TraderID: string;
    }>
  ): number;

  /**
   * 请求查询投资者结算结果
   * @param req 查询信息
   */
  reqQrySettlementInfo(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易日 */
      TradingDay: string;
      /** 资金账号 */
      AccountID: string;
      /** 币种代码 */
      CurrencyID: string;
    }>
  ): number;

  /**
   * 请求查询转帐银行
   * @param req 转账信息
   */
  reqQryTransferBank(
    req?: Partial<{
      /** 银行代码 */
      BankID: string;
      /** 银行分中心代码 */
      BankBrchID: string;
    }>
  ): number;

  /**
   * 请求查询投资者持仓明细
   * @param req 查询信息
   */
  reqQryInvestorPositionDetail(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询客户通知
   * @param req 查询信息
   */
  reqQryNotice(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
    }>
  ): number;

  /**
   * 请求查询结算信息确认
   * @param req 查询信息
   */
  reqQrySettlementInfoConfirm(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 资金账号 */
      AccountID: string;
      /** 币种代码 */
      CurrencyID: string;
    }>
  ): number;

  /**
   * 请求查询投资者持仓明细
   * @param req 查询信息
   */
  reqQryInvestorPositionCombineDetail(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 组合持仓合约编码 */
      CombInstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询保证金监管系统经纪公司资金账户密钥
   * @param req 查询信息
   */
  reqQryCFMMCTradingAccountKey(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
    }>
  ): number;

  /**
   * 请求查询仓单折抵信息
   * @param req 查询信息
   */
  reqQryEWarrantOffset(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询投资者品种/跨品种保证金
   * @param req 查询信息
   */
  reqQryInvestorProductGroupMargin(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 投机套保标志 */
      HedgeFlag: HedgeFlagType;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 品种/跨品种标示 */
      ProductGroupID: string;
    }>
  ): number;

  /**
   * 请求查询交易所保证金率
   * @param req 查询信息
   */
  reqQryExchangeMarginRate(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投机套保标志 */
      HedgeFlag: HedgeFlagType;
      /** 交易所代码 */
      ExchangeID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询交易所调整保证金率
   * @param req 查询信息
   */
  reqQryExchangeMarginRateAdjust(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投机套保标志 */
      HedgeFlag: HedgeFlagType;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询汇率
   * @param req 查询信息
   */
  reqQryExchangeRate(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 源币种 */
      FromCurrencyID: string;
      /** 目标币种 */
      ToCurrencyID: string;
    }>
  ): number;

  /**
   * 请求查询二级代理操作员银期权限
   * @param req 查询信息
   */
  reqQrySecAgentACIDMap(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 用户代码 */
      UserID: string;
      /** 资金账号 */
      AccountID: string;
      /** 币种代码 */
      CurrencyID: string;
    }>
  ): number;

  /**
   * 请求查询产品报价汇率
   * @param req 查询信息
   */
  reqQryProductExchRate(
    req?: Partial<{
      /** 交易所代码 */
      ExchangeID: string;
      /** 产品代码 */
      ProductID: string;
    }>
  ): number;

  /**
   * 请求查询产品组
   * @param req 查询信息
   */
  reqQryProductGroup(
    req?: Partial<{
      /** 交易所代码 */
      ExchangeID: string;
      /** 产品代码 */
      ProductID: string;
    }>
  ): number;

  /**
   * 请求查询做市商合约手续费率
   * @param req 查询信息
   */
  reqQryMMInstrumentCommissionRate(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询做市商期权合约手续费
   * @param req 查询信息
   */
  reqQryMMOptionInstrCommRate(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询报单手续费
   * @param req 查询信息
   */
  reqQryInstrumentOrderCommRate(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询资金账户
   * @param req 查询信息
   */
  reqQrySecAgentTradingAccount(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 币种代码 */
      CurrencyID: string;
      /** 业务类型 */
      BizType: BizTypeType;
      /** 资金账号 */
      AccountID: string;
    }>
  ): number;

  /**
   * 请求查询二级代理商资金校验模式
   * @param req 查询信息
   */
  reqQrySecAgentCheckMode(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
    }>
  ): number;

  /**
   * 请求查询二级代理商信息
   * @param req 查询信息
   */
  reqQrySecAgentTradeInfo(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 境外中介机构资金帐号 */
      BrokerSecAgentID: string;
    }>
  ): number;

  /**
   * 请求查询期权交易成本
   * @param req 查询信息
   */
  reqQryOptionInstrTradeCost(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 投机套保标志 */
      HedgeFlag: HedgeFlagType;
      /** 期权合约报价 */
      InputPrice: number;
      /** 标的价格,填0则用昨结算价 */
      UnderlyingPrice: number;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询期权合约手续费
   * @param req 查询信息
   */
  reqQryOptionInstrCommRate(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询执行宣告
   * @param req 查询信息
   */
  reqQryExecOrder(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 执行宣告编号 */
      ExecOrderSysID: number;
      /** 开始时间 */
      InsertTimeStart: string;
      /** 结束时间 */
      InsertTimeEnd: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询询价
   * @param req 查询信息
   */
  reqQryForQuote(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 开始时间 */
      InsertTimeStart: string;
      /** 结束时间 */
      InsertTimeEnd: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询报价
   * @param req 查询信息
   */
  reqQryQuote(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 报价操作编号 */
      QuoteSysID: string;
      /** 开始时间 */
      InsertTimeStart: string;
      /** 结束时间 */
      InsertTimeEnd: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询期权自对冲
   * @param req 查询信息
   */
  reqQryOptionSelfClose(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 期权自对冲操作编号 */
      OptionSelfCloseSysID: string;
      /** 开始时间 */
      InsertTimeStart: string;
      /** 结束时间 */
      InsertTimeEnd: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询投资单元
   * @param req 查询信息
   */
  reqQryInvestUnit(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
    }>
  ): number;

  /**
   * 请求查询组合合约安全系数
   * @param req 查询信息
   */
  reqQryCombInstrumentGuard(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询申请组合
   * @param req 查询信息
   */
  reqQryCombAction(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询转帐流水
   * @param req 查询信息
   */
  reqQryTransferSerial(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 资金账号 */
      AccountID: string;
      /** 银行代码 */
      BankID: string;
      /** 币种代码 */
      CurrencyID: string;
    }>
  ): number;

  /**
   * 请求查询银期签约关系
   * @param req 查询信息
   */
  reqQryAccountregister(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 资金账号 */
      AccountID: string;
      /** 银行代码 */
      BankID: string;
      /** 银行分支机构代码 */
      BankBranchID: string;
      /** 币种代码 */
      CurrencyID: string;
    }>
  ): number;

  /**
   * 请求查询签约银行
   * @param req 查询信息
   */
  reqQryContractBank(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 银行代码 */
      BankID: string;
      /** 银行分中心代码 */
      BankBrchID: string;
    }>
  ): number;

  /**
   * 请求查询预埋单
   * @param req 查询信息
   */
  reqQryParkedOrder(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询预埋撤单
   * @param req 查询信息
   */
  reqQryParkedOrderAction(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询交易通知
   * @param req 查询信息
   */
  reqQryTradingNotice(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
    }>
  ): number;

  /**
   * 请求查询经纪公司交易参数
   * @param req 查询信息
   */
  reqQryBrokerTradingParams(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 币种代码 */
      CurrencyID: string;
      /** 资金账号 */
      AccountID: string;
    }>
  ): number;

  /**
   * 请求查询经纪公司交易算法
   * @param req 查询信息
   */
  reqQryBrokerTradingAlgos(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 请求查询监控中心用户令牌
   * @param req 查询信息
   */
  reqQueryCFMMCTradingAccountToken(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 投资单元代码 */
      InvestUnitID: string;
    }>
  ): number;

  /**
   * 期货发起银行资金转期货请求
   * @param req 查询信息
   */
  reqFromBankToFutureByFuture(
    req?: Partial<{
      /** 业务功能码 */
      TradeCode: string;
      /** 银行代码 */
      BankID: string;
      /** 银行分支机构代码 */
      BankBranchID: string;
      /** 经纪公司代码 */
      BrokerID: string;
      /** 期商分支机构代码 */
      BrokerBranchID: string;
      /** 交易日期 */
      TradeDate: string;
      /** 交易时间 */
      TradeTime: string;
      /** 银行流水号 */
      BankSerial: string;
      /** 交易日 */
      TradingDay: string;
      /** 期平台消息流水号 */
      PlateSerial: number;
      /** 最后分片标志 */
      LastFragment: LastFragmentType;
      /** 会话编号 */
      SessionID: number;
      /** 客户姓名 */
      CustomerName: string;
      /** 证件类型 */
      IdCardType: IdCardTypeType;
      /** 证件号码 */
      IdentifiedCardNo: string;
      /** 客户类型 */
      CustType: CustTypeType;
      /** 银行帐号 */
      BankAccount: string;
      /** 银行密码 */
      BankPassWord: string;
      /** 资金账号 */
      AccountID: string;
      /** 期货密码 */
      Password: string;
      /** 安装编号 */
      InstallID: number;
      /** 期货公司流水号 */
      FutureSerial: number;
      /** 用户代码 */
      UserID: string;
      /** 验证客户证件号码标志 */
      VerifyCertNoFlag: YesNoIndicatorType;
      /** 币种代码 */
      CurrencyID: string;
      /** 转帐金额 */
      TradeAmount: number;
      /** 期货可取金额 */
      FutureFetchAmount: number;
      /** 费用支付标志 */
      FeePayFlag: FeePayFlagType;
      /** 应收客户费用 */
      CustFee: number;
      /** 应收期货公司费用 */
      BrokerFee: number;
      /** 发送方给接收方的消息 */
      Message: string;
      /** 摘要 */
      Digest: string;
      /** 银行帐号类型 */
      BankAccType: BankAccTypeType;
      /** 渠道标志 */
      DeviceID: string;
      /** 期货单位帐号类型 */
      BankSecuAccType: BankAccTypeType;
      /** 期货公司银行编码 */
      BrokerIDByBank: string;
      /** 期货单位帐号 */
      BankSecuAcc: string;
      /** 银行密码标志 */
      BankPwdFlag: PwdFlagType;
      /** 期货资金密码核对标志 */
      SecuPwdFlag: PwdFlagType;
      /** 交易柜员 */
      OperNo: string;
      /** 请求编号 */
      RequestID: number;
      /** 交易ID */
      TID: number;
      /** 转账交易状态 */
      TransferStatus: TransferStatusType;
      /** 长客户姓名 */
      LongCustomerName: string;
    }>
  ): number;

  /**
   * 期货发起期货资金转银行请求
   * @param req 查询信息
   */
  reqFromFutureToBankByFuture(
    req?: Partial<{
      /** 业务功能码 */
      TradeCode: string;
      /** 银行代码 */
      BankID: string;
      /** 银行分支机构代码 */
      BankBranchID: string;
      /** 经纪公司代码 */
      BrokerID: string;
      /** 期商分支机构代码 */
      BrokerBranchID: string;
      /** 交易日期 */
      TradeDate: string;
      /** 交易时间 */
      TradeTime: string;
      /** 银行流水号 */
      BankSerial: string;
      /** 交易日 */
      TradingDay: string;
      /** 期平台消息流水号 */
      PlateSerial: number;
      /** 最后分片标志 */
      LastFragment: LastFragmentType;
      /** 会话编号 */
      SessionID: number;
      /** 客户姓名 */
      CustomerName: string;
      /** 证件类型 */
      IdCardType: IdCardTypeType;
      /** 证件号码 */
      IdentifiedCardNo: string;
      /** 客户类型 */
      CustType: CustTypeType;
      /** 银行帐号 */
      BankAccount: string;
      /** 银行密码 */
      BankPassWord: string;
      /** 资金账号 */
      AccountID: string;
      /** 期货密码 */
      Password: string;
      /** 安装编号 */
      InstallID: number;
      /** 期货公司流水号 */
      FutureSerial: number;
      /** 用户代码 */
      UserID: string;
      /** 验证客户证件号码标志 */
      VerifyCertNoFlag: YesNoIndicatorType;
      /** 币种代码 */
      CurrencyID: string;
      /** 转帐金额 */
      TradeAmount: number;
      /** 期货可取金额 */
      FutureFetchAmount: number;
      /** 费用支付标志 */
      FeePayFlag: FeePayFlagType;
      /** 应收客户费用 */
      CustFee: number;
      /** 应收期货公司费用 */
      BrokerFee: number;
      /** 发送方给接收方的消息 */
      Message: string;
      /** 摘要 */
      Digest: string;
      /** 银行帐号类型 */
      BankAccType: BankAccTypeType;
      /** 渠道标志 */
      DeviceID: string;
      /** 期货单位帐号类型 */
      BankSecuAccType: BankAccTypeType;
      /** 期货公司银行编码 */
      BrokerIDByBank: string;
      /** 期货单位帐号 */
      BankSecuAcc: string;
      /** 银行密码标志 */
      BankPwdFlag: PwdFlagType;
      /** 期货资金密码核对标志 */
      SecuPwdFlag: PwdFlagType;
      /** 交易柜员 */
      OperNo: string;
      /** 请求编号 */
      RequestID: number;
      /** 交易ID */
      TID: number;
      /** 转账交易状态 */
      TransferStatus: TransferStatusType;
      /** 长客户姓名 */
      LongCustomerName: string;
    }>
  ): number;

  /**
   * 期货发起查询银行余额请求
   * @param req 查询信息
   */
  reqQueryBankAccountMoneyByFuture(
    req?: Partial<{
      /** 业务功能码 */
      TradeCode: string;
      /** 银行代码 */
      BankID: string;
      /** 银行分支机构代码 */
      BankBranchID: string;
      /** 经纪公司代码 */
      BrokerID: string;
      /** 期商分支机构代码 */
      BrokerBranchID: string;
      /** 交易日期 */
      TradeDate: string;
      /** 交易时间 */
      TradeTime: string;
      /** 银行流水号 */
      BankSerial: string;
      /** 交易日 */
      TradingDay: string;
      /** 期平台消息流水号 */
      PlateSerial: number;
      /** 最后分片标志 */
      LastFragment: LastFragmentType;
      /** 会话编号 */
      SessionID: number;
      /** 客户姓名 */
      CustomerName: string;
      /** 证件类型 */
      IdCardType: IdCardTypeType;
      /** 证件号码 */
      IdentifiedCardNo: string;
      /** 客户类型 */
      CustType: CustTypeType;
      /** 银行帐号 */
      BankAccount: string;
      /** 银行密码 */
      BankPassWord: string;
      /** 资金账号 */
      AccountID: string;
      /** 期货密码 */
      Password: string;
      /** 期货公司流水号 */
      FutureSerial: number;
      /** 安装编号 */
      InstallID: number;
      /** 用户代码 */
      UserID: string;
      /** 验证客户证件号码标志 */
      VerifyCertNoFlag: YesNoIndicatorType;
      /** 币种代码 */
      CurrencyID: string;
      /** 摘要 */
      Digest: string;
      /** 银行帐号类型 */
      BankAccType: BankAccTypeType;
      /** 渠道标志 */
      DeviceID: string;
      /** 期货单位帐号类型 */
      BankSecuAccType: BankAccTypeType;
      /** 期货公司银行编码 */
      BrokerIDByBank: string;
      /** 期货单位帐号 */
      BankSecuAcc: string;
      /** 银行密码标志 */
      BankPwdFlag: PwdFlagType;
      /** 期货资金密码核对标志 */
      SecuPwdFlag: PwdFlagType;
      /** 交易柜员 */
      OperNo: string;
      /** 请求编号 */
      RequestID: number;
      /** 交易ID */
      TID: number;
      /** 长客户姓名 */
      LongCustomerName: string;
    }>
  ): number;

  /**
   * 请求查询分类合约
   * @param req 查询信息
   */
  reqQryClassifiedInstrument(
    req?: Partial<{
      /** 合约代码 */
      InstrumentID: string;
      /** 交易所代码 */
      ExchangeID: string;
      /** 合约在交易所的代码 */
      ExchangeInstID: string;
      /** 产品代码 */
      ProductID: string;
      /** 合约交易状态 */
      TradingType: TradingTypeType;
      /** 合约分类类型 */
      ClassType: ClassTypeType;
    }>
  ): number;

  /**
   * 请求组合优惠比例
   * @param req 查询信息
   */
  reqQryCombPromotionParam(
    req?: Partial<{
      /** 交易所代码 */
      ExchangeID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 投资者风险结算持仓查询
   * @param req 查询信息
   */
  reqQryRiskSettleInvstPosition(
    req?: Partial<{
      /** 经纪公司代码 */
      BrokerID: string;
      /** 投资者代码 */
      InvestorID: string;
      /** 合约代码 */
      InstrumentID: string;
    }>
  ): number;

  /**
   * 风险结算产品查询
   * @param req 查询信息
   */
  reqQryRiskSettleProductStatus(
    req?: Partial<{
      /** 产品代码 */
      ProductID: string;
    }>
  ): number;

  /**
   * 注册交易消息回调函数
   * @param event 交易消息事件
   * @param func 回调函数
   */
  on(event: TraderEvent, func: CallbackFunction): Trader;

  /**
   * 关闭交易对象
   */
  close(): void;
}

/**
 * 创建行情对象
 * @param flowMdPath 存贮订阅信息文件的目录
 * @param frontMdAddr 前置机网络地址
 * @returns 行情对象
 */
export declare function createMarketData(
  flowMdPath: string,
  frontMdAddr: string
): MarketData;

/**
 * 创建交易对象
 * @param flowPath 存贮订阅信息文件的目录
 * @param frontAddr 前置机网络地址
 * @returns 交易对象
 */
export declare function createTrader(
  flowPath: string,
  frontAddr: string
): Trader;

/**
 * 获取最后请求序列ID
 * @returns 序列ID
 */
export declare function getLastRequestId(): number;
