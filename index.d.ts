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

/**
 * 行情消息事件
 */
export enum MarketDataEvent {
  Quit = "quit",
  FrontConnected = "front-connected",
  FrontDisconnected = "front-disconnected",
  HeartBeatWarning = "heart-beat-warning",
  RspUserLogin = "rsp-user-login",
  RspUserLogout = "rsp-user-logout",
  RspQryMulticastInstrument = "rsp-qry-multicast-instrument",
  RspError = "rsp-error",
  RspSubMarketData = "rsp-sub-market-data",
  RspUnSubMarketData = "rsp-unsub-market-data",
  RspSubForQuote = "rsp-sub-for-quote",
  RspUnSubForQuote = "rsp-unsub-for-quote",
  RtnDepthMarketData = "rtn-depth-market-data",
  RtnForQuote = "rtn-for-quote",
}

/**
 * 交易消息事件
 */
export enum TraderEvent {
  Quit = "quit",
  FrontConnected = "front-connected",
  FrontDisconnected = "front-disconnected",
  HeartBeatWarning = "heart-beat-warning",
  RspAuthenticate = "rsp-authenticate",
  RspUserLogin = "rsp-user-login",
  RspUserLogout = "rsp-user-logout",
  RspUserPasswordUpdate = "rsp-user-password-update",
  RspTradingAccountPasswordUpdate = "rsp-trading-account-password-update",
  RspUserAuthMethod = "rsp-user-auth-method",
  RspGenUserCaptcha = "rsp-gen-user-captcha",
  RspGenUserText = "rsp-gen-user-text",
  RspOrderInsert = "rsp-order-insert",
  RspParkedOrderInsert = "rsp-parked-order-insert",
  RspParkedOrderAction = "rsp-parked-order-action",
  RspOrderAction = "rsp-order-action",
  RspQryMaxOrderVolume = "rsp-qry-max-order-volume",
  RspSettlementInfoConfirm = "rsp-settlement-info-confirm",
  RspRemoveParkedOrder = "rsp-remove-parked-order",
  RspRemoveParkedOrderAction = "rsp-remove-parked-order-action",
  RspExecOrderInsert = "rsp-exec-order-insert",
  RspExecOrderAction = "rsp-exec-order-action",
  RspForQuoteInsert = "rsp-for-quote-insert",
  RspQuoteInsert = "rsp-quote-insert",
  RspQuoteAction = "rsp-quote-action",
  RspBatchOrderAction = "rsp-batch-order-action",
  RspOptionSelfCloseInsert = "rsp-option-self-close-insert",
  RspOptionSelfCloseAction = "rsp-option-self-close-action",
  RspCombActionInsert = "rsp-comb-action-insert",
  RspQryOrder = "rsp-qry-order",
  RspQryTrade = "rsp-qry-trade",
  RspQryInvestorPosition = "rsp-qry-investor-position",
  RspQryTradingAccount = "rsp-qry-trading-account",
  RspQryInvestor = "rsp-qry-investor",
  RspQryTradingCode = "rsp-qry-trading-code",
  RspQryInstrumentMarginRate = "rsp-qry-instrument-margin-rate",
  RspQryInstrumentCommissionRate = "rsp-qry-instrument-commission-rate",
  RspQryExchange = "rsp-qry-exchange",
  RspQryProduct = "rsp-qry-product",
  RspQryInstrument = "rsp-qry-instrument",
  RspQryDepthMarketData = "rsp-qry-depth-market-data",
  RspQryTraderOffer = "rsp-qry-trader-offer",
  RspQrySettlementInfo = "rsp-qry-settlement-info",
  RspQryTransferBank = "rsp-qry-transfer-bank",
  RspQryInvestorPositionDetail = "rsp-qry-investor-position-detail",
  RspQryNotice = "rsp-qry-notice",
  RspQrySettlementInfoConfirm = "rsp-qry-settlement-info-confirm",
  RspQryInvestorPositionCombineDetail = "rsp-qry-investor-position-combine-detail",
  RspQryCFMMCTradingAccountKey = "rsp-qry-cfmmc-trading-account-key",
  RspQryEWarrantOffset = "rsp-qry-e-warrant-offset",
  RspQryInvestorProductGroupMargin = "rsp-qry-investor-product-group-margin",
  RspQryExchangeMarginRate = "rsp-qry-exchange-margin-rate",
  RspQryExchangeMarginRateAdjust = "rsp-qry-exchange-margin-rate-adjust",
  RspQryExchangeRate = "rsp-qry-exchange-rate",
  RspQrySecAgentACIDMap = "rsp-qry-sec-agent-acid-map",
  RspQryProductExchRate = "rsp-qry-product-exch-rate",
  RspQryProductGroup = "rsp-qry-product-group",
  RspQryMMInstrumentCommissionRate = "rsp-qry-mm-instrument-commission-rate",
  RspQryMMOptionInstrCommRate = "rsp-qry-mm-option-instr-comm-rate",
  RspQryInstrumentOrderCommRate = "rsp-qry-instrument-order-comm-rate",
  RspQrySecAgentTradingAccount = "rsp-qry-sec-agent-trading-account",
  RspQrySecAgentCheckMode = "rsp-qry-sec-agent-check-mode",
  RspQrySecAgentTradeInfo = "rsp-qry-sec-agent-trade-info",
  RspQryOptionInstrTradeCost = "rsp-qry-option-instr-trade-cost",
  RspQryOptionInstrCommRate = "rsp-qry-option-instr-comm-rate",
  RspQryExecOrder = "rsp-qry-exec-order",
  RspQryForQuote = "rsp-qry-for-quote",
  RspQryQuote = "rsp-qry-quote",
  RspQryOptionSelfClose = "rsp-qry-option-self-close",
  RspQryInvestUnit = "rsp-qry-invest-unit",
  RspQryCombInstrumentGuard = "rsp-qry-comb-instrument-guard",
  RspQryCombAction = "rsp-qry-comb-action",
  RspQryTransferSerial = "rsp-qry-transfer-serial",
  RspQryAccountRegister = "rsp-qry-account-register",
  RspError = "rsp-error",
  RtnOrder = "rtn-order",
  RtnTrade = "rtn-trade",
  ErrRtnOrderInsert = "err-rtn-order-insert",
  ErrRtnOrderAction = "err-rtn-order-action",
  RtnInstrumentStatus = "rtn-instrument-status",
  RtnBulletin = "rtn-bulletin",
  RtnTradingNotice = "rtn-trading-notice",
  RtnErrorConditionalOrder = "rtn-error-conditional-order",
  RtnExecOrder = "rtn-exec-order",
  ErrRtnExecOrderInsert = "err-rtn-exec-order-insert",
  ErrRtnExecOrderAction = "err-rtn-exec-order-action",
  ErrRtnForQuoteInsert = "err-rtn-for-quote-insert",
  RtnQuote = "rtn-quote",
  ErrRtnQuoteInsert = "err-rtn-quote-insert",
  ErrRtnQuoteAction = "err-rtn-quote-action",
  RtnForQuote = "rtn-for-quote",
  RtnCFMMCTradingAccountToken = "rtn-cfmmc-trading-account-token",
  ErrRtnBatchOrderAction = "err-rtn-batch-order-action",
  RtnOptionSelfClose = "rtn-option-self-close",
  ErrRtnOptionSelfCloseInsert = "err-rtn-option-self-close-insert",
  ErrRtnOptionSelfCloseAction = "err-rtn-option-self-close-action",
  RtnCombAction = "rtn-comb-action",
  ErrRtnCombActionInsert = "err-rtn-comb-action-insert",
  RspQryContractBank = "rsp-qry-contract-bank",
  RspQryParkedOrder = "rsp-qry-parked-order",
  RspQryParkedOrderAction = "rsp-qry-parked-order-action",
  RspQryTradingNotice = "rsp-qry-trading-notice",
  RspQryBrokerTradingParams = "rsp-qry-broker-trading-params",
  RspQryBrokerTradingAlgos = "rsp-qry-broker-trading-algos",
  RtnFromBankToFutureByBank = "rtn-from-bank-to-future-by-bank",
  RtnFromFutureToBankByBank = "rtn-from-future-to-bank-by-bank",
  RtnRepealFromBankToFutureByBank = "rtn-repeal-from-bank-to-future-by-bank",
  RtnRepealFromFutureToBankByBank = "rtn-repeal-from-future-to-bank-by-bank",
  RtnFromBankToFutureByFuture = "rtn-from-bank-to-future-by-future",
  RtnFromFutureToBankByFuture = "rtn-from-future-to-bank-by-future",
  RtnRepealFromBankToFutureByFutureManual = "rtn-repeal-from-bank-to-future-by-future-manual",
  RtnRepealFromFutureToBankByFutureManual = "rtn-repeal-from-future-to-bank-by-future-manual",
  RtnQueryBankBalanceByFuture = "rtn-query-bank-balance-by-future",
  ErrRtnBankToFutureByFuture = "err-rtn-bank-to-future-by-future",
  ErrRtnFutureToBankByFuture = "err-rtn-future-to-bank-by-future",
  ErrRtnRepealBankToFutureByFutureManual = "err-rtn-repeal-bank-to-future-by-future-manual",
  ErrRtnRepealFutureToBankByFutureManual = "err-rtn-repeal-future-to-bank-by-future-manual",
  ErrRtnQueryBankBalanceByFuture = "err-rtn-query-bank-balance-by-future",
  RtnRepealFromBankToFutureByFuture = "rtn-repeal-from-bank-to-future-by-future",
  RtnRepealFromFutureToBankByFuture = "rtn-repeal-from-future-to-bank-by-future",
  RspFromBankToFutureByFuture = "rsp-from-bank-to-future-by-future",
  RspFromFutureToBankByFuture = "rsp-from-future-to-bank-by-future",
  RspQueryBankAccountMoneyByFuture = "rsp-query-bank-account-money-by-future",
  RtnOpenAccountByBank = "rtn-open-account-by-bank",
  RtnCancelAccountByBank = "rtn-cancel-account-by-bank",
  RtnChangeAccountByBank = "rtn-change-account-by-bank",
  RspQryClassifiedInstrument = "rsp-qry-classified-instrument",
  RspQryCombPromotionParam = "rsp-qry-comb-promotion-param",
  RspQryRiskSettleInvstPosition = "rsp-qry-risk-settle-invst-position",
  RspQryRiskSettleProductStatus = "rsp-qry-risk-settle-product-status",
}

/**
 * 消息事件回调接口
 */
export interface CallbackFunction {
  /**
   * 消息对象(不同消息事件，相应的对象也不同)
   */
  (message?: number | object): void;
}

/**
 * 行情对象
 */
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
  userLogin(req: object): number;

  /**
   * 用户登出请求
   * @param req 用户登出信息
   */
  userLogout(req: object): number;

  /**
   * 注册行情消息回调函数
   * @param event 行情消息事件
   * @param func 回调函数
   */
  on(event: MarketDataEvent, func: CallbackFunction): MarketData;
}

/**
 * 交易对象
 */
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
   * 客户端认证请求
   * @param req 客户端认证信息
   */
  authenticate(req: object): number;

  /**
   * 用户登录请求
   * @param req 用户登陆信息
   */
  userLogin(req: object): number;

  /**
   * 用户登出请求
   * @param req 用户登出信息
   */
  userLogout(req: object): number;

  /**
   * 用户口令更新请求
   * @param req 用户口令信息
   */
  userPasswordUpdate(req: object): number;

  /**
   * 资金账户口令更新请求
   * @param req 用户口令信息
   */
  tradingAccountPasswordUpdate(req: object): number;

  /**
   * 查询用户当前支持的认证模式
   * @param req 用户信息
   */
  userAuthMethod(req: object): number;

  /**
   * 用户发出获取图形验证码请求
   * @param req 用户信息
   */
  genUserCaptcha(req: object): number;

  /**
   * 用户发出获取短信验证码请求
   * @param req 用户信息
   */
  genUserText(req: object): number;

  /**
   * 用户发出带有图片验证码的登陆请求
   * @param req 用户登陆信息
   */
  userLoginWithCaptcha(req: object): number;

  /**
   * 用户发出带有短信验证码的登陆请求
   * @param req 用户登陆信息
   */
  userLoginWithText(req: object): number;

  /**
   * 用户发出带有动态口令的登陆请求
   * @param req 用户登陆信息
   */
  userLoginWithOTP(req: object): number;

  /**
   * 报单录入请求
   * @param req 报单信息
   */
  orderInsert(req: object): number;

  /**
   * 预埋单录入请求
   * @param req 预埋单信息
   */
  parkedOrderInsert(req: object): number;

  /**
   * 预埋撤单录入请求
   * @param req 预埋单信息
   */
  parkedOrderAction(req: object): number;

  /**
   * 报单操作请求
   * @param req 报单信息
   */
  orderAction(req: object): number;

  /**
   * 查询最大报单数量请求
   * @param req 查询最大报单数量
   */
  qryMaxOrderVolume(req: object): number;

  /**
   * 投资者结算结果确认
   * @param req 投资者结算结果确认信息
   */
  settlementInfoConfirm(req: object): number;

  /**
   * 请求删除预埋单
   * @param req 预埋单信息
   */
  removeParkedOrder(req: object): number;

  /**
   * 请求删除预埋撤单
   * @param req 预埋单信息
   */
  removeParkedOrderAction(req: object): number;

  /**
   * 执行宣告录入请求
   * @param req 宣告信息
   */
  execOrderInsert(req: object): number;

  /**
   * 执行宣告操作请求
   * @param req 宣告信息
   */
  execOrderAction(req: object): number;

  /**
   * 询价录入请求
   * @param req 询价信息
   */
  forQuoteInsert(req: object): number;

  /**
   * 报价录入请求
   * @param req 报价信息
   */
  quoteInsert(req: object): number;

  /**
   * 报价操作请求
   * @param req 报价信息
   */
  quoteAction(req: object): number;

  /**
   * 批量报单操作请求
   * @param req 报单请求
   */
  batchOrderAction(req: object): number;

  /**
   * 期权自对冲录入请求
   * @param req 期权自对冲信息
   */
  optionSelfCloseInsert(req: object): number;

  /**
   * 期权自对冲操作请求
   * @param req 期权自对冲信息
   */
  optionSelfCloseAction(req: object): number;

  /**
   * 申请组合录入请求
   * @param req 组合信息
   */
  combActionInsert(req: object): number;

  /**
   * 请求查询报单
   * @param req 查询信息
   */
  qryOrder(req: object): number;

  /**
   * 请求查询成交
   * @param req 查询信息
   */
  qryTrade(req: object): number;

  /**
   * 请求查询投资者持仓
   * @param req 查询信息
   */
  qryInvestorPosition(req: object): number;

  /**
   * 请求查询资金账户
   * @param req 查询信息
   */
  qryTradingAccount(req: object): number;

  /**
   * 请求查询投资者
   * @param req 查询信息
   */
  qryInvestor(req: object): number;

  /**
   * 请求查询交易编码
   * @param req 查询信息
   */
  qryTradingCode(req: object): number;

  /**
   * 请求查询合约保证金率
   * @param req 查询信息
   */
  qryInstrumentMarginRate(req: object): number;

  /**
   * 请求查询合约手续费率
   * @param req 查询信息
   */
  qryInstrumentCommissionRate(req: object): number;

  /**
   * 请求查询交易所
   * @param req 查询信息
   */
  qryExchange(req: object): number;

  /**
   * 请求查询产品
   * @param req 查询信息
   */
  qryProduct(req: object): number;

  /**
   * 请求查询合约
   * @param req 查询信息
   */
  qryInstrument(req: object): number;

  /**
   * 请求查询行情
   * @param req 查询信息
   */
  qryDepthMarketData(req: object): number;

  /**
   * 请求查询交易员报盘机
   * @param req 查询信息
   */
  qryTraderOffer(req: object): number;

  /**
   * 请求查询投资者结算结果
   * @param req 查询信息
   */
  qrySettlementInfo(req: object): number;

  /**
   * 请求查询转帐银行
   * @param req 转账信息
   */
  qryTransferBank(req: object): number;

  /**
   * 请求查询投资者持仓明细
   * @param req 查询信息
   */
  qryInvestorPositionDetail(req: object): number;

  /**
   * 请求查询客户通知
   * @param req 查询信息
   */
  qryNotice(req: object): number;

  /**
   * 请求查询结算信息确认
   * @param req 查询信息
   */
  qrySettlementInfoConfirm(req: object): number;

  /**
   * 请求查询投资者持仓明细
   * @param req 查询信息
   */
  qryInvestorPositionCombineDetail(req: object): number;

  /**
   * 请求查询保证金监管系统经纪公司资金账户密钥
   * @param req 查询信息
   */
  qryCFMMCTradingAccountKey(req: object): number;

  /**
   * 请求查询仓单折抵信息
   * @param req 查询信息
   */
  qryEWarrantOffset(req: object): number;

  /**
   * 请求查询投资者品种/跨品种保证金
   * @param req 查询信息
   */
  qryInvestorProductGroupMargin(req: object): number;

  /**
   * 请求查询交易所保证金率
   * @param req 查询信息
   */
  qryExchangeMarginRate(req: object): number;

  /**
   * 请求查询交易所调整保证金率
   * @param req 查询信息
   */
  qryExchangeMarginRateAdjust(req: object): number;

  /**
   * 请求查询汇率
   * @param req 查询信息
   */
  qryExchangeRate(req: object): number;

  /**
   * 请求查询二级代理操作员银期权限
   * @param req 查询信息
   */
  qrySecAgentACIDMap(req: object): number;

  /**
   * 请求查询产品报价汇率
   * @param req 查询信息
   */
  qryProductExchRate(req: object): number;

  /**
   * 请求查询产品组
   * @param req 查询信息
   */
  qryProductGroup(req: object): number;

  /**
   * 请求查询做市商合约手续费率
   * @param req 查询信息
   */
  qryMMInstrumentCommissionRate(req: object): number;

  /**
   * 请求查询做市商期权合约手续费
   * @param req 查询信息
   */
  qryMMOptionInstrCommRate(req: object): number;

  /**
   * 请求查询报单手续费
   * @param req 查询信息
   */
  qryInstrumentOrderCommRate(req: object): number;

  /**
   * 请求查询资金账户
   * @param req 查询信息
   */
  qrySecAgentTradingAccount(req: object): number;

  /**
   * 请求查询二级代理商资金校验模式
   * @param req 查询信息
   */
  qrySecAgentCheckMode(req: object): number;

  /**
   * 请求查询二级代理商信息
   * @param req 查询信息
   */
  qrySecAgentTradeInfo(req: object): number;

  /**
   * 请求查询期权交易成本
   * @param req 查询信息
   */
  qryOptionInstrTradeCost(req: object): number;

  /**
   * 请求查询期权合约手续费
   * @param req 查询信息
   */
  qryOptionInstrCommRate(req: object): number;

  /**
   * 请求查询执行宣告
   * @param req 查询信息
   */
  qryExecOrder(req: object): number;

  /**
   * 请求查询询价
   * @param req 查询信息
   */
  qryForQuote(req: object): number;

  /**
   * 请求查询报价
   * @param req 查询信息
   */
  qryQuote(req: object): number;

  /**
   * 请求查询期权自对冲
   * @param req 查询信息
   */
  qryOptionSelfClose(req: object): number;

  /**
   * 请求查询投资单元
   * @param req 查询信息
   */
  qryInvestUnit(req: object): number;

  /**
   * 请求查询组合合约安全系数
   * @param req 查询信息
   */
  qryCombInstrumentGuard(req: object): number;

  /**
   * 请求查询申请组合
   * @param req 查询信息
   */
  qryCombAction(req: object): number;

  /**
   * 请求查询转帐流水
   * @param req 查询信息
   */
  qryTransferSerial(req: object): number;

  /**
   * 请求查询银期签约关系
   * @param req 查询信息
   */
  qryAccountregister(req: object): number;

  /**
   * 请求查询签约银行
   * @param req 查询信息
   */
  qryContractBank(req: object): number;

  /**
   * 请求查询预埋单
   * @param req 查询信息
   */
  qryParkedOrder(req: object): number;

  /**
   * 请求查询预埋撤单
   * @param req 查询信息
   */
  qryParkedOrderAction(req: object): number;

  /**
   * 请求查询交易通知
   * @param req 查询信息
   */
  qryTradingNotice(req: object): number;

  /**
   * 请求查询经纪公司交易参数
   * @param req 查询信息
   */
  qryBrokerTradingParams(req: object): number;

  /**
   * 请求查询经纪公司交易算法
   * @param req 查询信息
   */
  qryBrokerTradingAlgos(req: object): number;

  /**
   * 请求查询监控中心用户令牌
   * @param req 查询信息
   */
  queryCFMMCTradingAccountToken(req: object): number;

  /**
   * 期货发起银行资金转期货请求
   * @param req 查询信息
   */
  fromBankToFutureByFuture(req: object): number;

  /**
   * 期货发起期货资金转银行请求
   * @param req 查询信息
   */
  fromFutureToBankByFuture(req: object): number;

  /**
   * 期货发起查询银行余额请求
   * @param req 查询信息
   */
  queryBankAccountMoneyByFuture(req: object): number;

  /**
   * 请求查询分类合约
   * @param req 查询信息
   */
  qryClassifiedInstrument(req: object): number;

  /**
   * 请求组合优惠比例
   * @param req 查询信息
   */
  qryCombPromotionParam(req: object): number;

  /**
   * 投资者风险结算持仓查询
   * @param req 查询信息
   */
  qryRiskSettleInvstPosition(req: object): number;

  /**
   * 风险结算产品查询
   * @param req 查询信息
   */
  qryRiskSettleProductStatus(req: object): number;

  /**
   * 注册交易消息回调函数
   * @param event 交易消息事件
   * @param func 回调函数
   */
  on(event: TraderEvent, func: CallbackFunction): Trader;
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
