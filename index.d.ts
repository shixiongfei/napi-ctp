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

/** 行情消息事件 */
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

/** 交易消息事件 */
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

/** 交易所属性类型 */
export enum ExchangePropertyType {
  /** 正常 */
  Normal = "0",
  /** 根据成交生成报单 */
  GenOrderByTrade = "1",
}

/** 证件类型类型 */
export enum IdCardType {
  /** 组织机构代码 */
  EID = "0",
  /** 中国公民身份证 */
  IDCard = "1",
  /** 军官证 */
  OfficerIDCard = "2",
  /** 警官证 */
  PoliceIDCard = "3",
  /** 士兵证 */
  SoldierIDCard = "4",
  /** 户口簿 */
  HouseholdRegister = "5",
  /** 护照 */
  Passport = "6",
  /** 台胞证 */
  TaiwanCompatriotIDCard = "7",
  /** 回乡证 */
  HomeComingCard = "8",
  /** 营业执照号 */
  LicenseNo = "9",
  /** 税务登记号/当地纳税ID */
  TaxNo = "A",
  /** 港澳居民来往内地通行证 */
  HMMainlandTravelPermit = "B",
  /** 台湾居民来往大陆通行证 */
  TwMainlandTravelPermit = "C",
  /** 驾照 */
  DrivingLicense = "D",
  /** 当地社保ID */
  SocialID = "F",
  /** 当地身份证 */
  LocalID = "G",
  /** 商业登记证 */
  BusinessRegistration = "H",
  /** 港澳永久性居民身份证 */
  HKMCIDCard = "I",
  /** 人行开户许可证 */
  AccountsPermits = "J",
  /** 外国人永久居留证 */
  FrgPrmtRdCard = "K",
  /** 资管产品备案函 */
  CptMngPrdLetter = "L",
  /** 港澳台居民居住证 */
  HKMCTwResidencePermit = "M",
  /** 统一社会信用代码 */
  UniformSocialCreditCode = "N",
  /** 机构成立证明文件 */
  CorporationCertNo = "O",
  /** 其他证件 */
  OtherCard = "x",
}

/** 投资者范围类型 */
export enum InvestorRangeType {
  /** 所有 */
  All = "1",
  /** 投资者组 */
  Group = "2",
  /** 单一投资者 */
  Single = "3",
}

/** 投资者范围类型 */
export enum DepartmentRangeType {
  /** 所有 */
  All = "1",
  /** 组织架构 */
  Group = "2",
  /** 单一投资者 */
  Single = "3",
}

/** 数据同步状态类型 */
export enum DataSyncStatusType {
  /** 未同步 */
  Asynchronous = "1",
  /** 同步中 */
  Synchronizing = "2",
  /** 已同步 */
  Synchronized = "3",
}

/** 经纪公司数据同步状态类型 */
export enum BrokerDataSyncStatusType {
  /** 已同步 */
  Synchronized = "1",
  /** 同步中 */
  Synchronizing = "2",
}

/** 交易所连接状态类型 */
export enum ExchangeConnectStatusType {
  /** 没有任何连接 */
  NoConnection = "1",
  /** 已经发出合约查询请求 */
  QryInstrumentSent = "2",
  /** 已经获取信息 */
  GotInformation = "9",
}

/** 交易所交易员连接状态类型 */
export enum TraderConnectStatusType {
  /** 没有任何连接 */
  NotConnected = "1",
  /** 已经连接 */
  Connected = "2",
  /** 已经发出合约查询请求 */
  QryInstrumentSent = "3",
  /** 订阅私有流 */
  SubPrivateFlow = "4",
}

/** 功能代码类型 */
export enum FunctionCodeType {
  /** 数据异步化 */
  DataAsync = "1",
  /** 强制用户登出 */
  ForceUserLogout = "2",
  /** 变更管理用户口令 */
  UserPasswordUpdate = "3",
  /** 变更经纪公司口令 */
  BrokerPasswordUpdate = "4",
  /** 变更投资者口令 */
  InvestorPasswordUpdate = "5",
  /** 报单插入 */
  OrderInsert = "6",
  /** 报单操作 */
  OrderAction = "7",
  /** 同步系统数据 */
  SyncSystemData = "8",
  /** 同步经纪公司数据 */
  SyncBrokerData = "9",
  /** 批量同步经纪公司数据 */
  BachSyncBrokerData = "A",
  /** 超级查询 */
  SuperQuery = "B",
  /** 预埋报单插入 */
  ParkedOrderInsert = "C",
  /** 预埋报单操作 */
  ParkedOrderAction = "D",
  /** 同步动态令牌 */
  SyncOTP = "E",
  /** 删除未知单 */
  DeleteOrder = "F",
}

/** 经纪公司功能代码类型 */
export enum BrokerFunctionCodeType {
  /** 强制用户登出 */
  ForceUserLogout = "1",
  /** 变更用户口令 */
  UserPasswordUpdate = "2",
  /** 同步经纪公司数据 */
  SyncBrokerData = "3",
  /** 批量同步经纪公司数据 */
  BachSyncBrokerData = "4",
  /** 报单插入 */
  OrderInsert = "5",
  /** 报单操作 */
  OrderAction = "6",
  /** 全部查询 */
  AllQuery = "7",
  /** 系统功能：登入/登出/修改密码等 */
  log = "a",
  /** 基本查询：查询基础数据，如合约，交易所等常量 */
  BaseQry = "b",
  /** 交易查询：如查成交，委托 */
  TradeQry = "c",
  /** 交易功能：报单，撤单 */
  Trade = "d",
  /** 银期转账 */
  Virement = "e",
  /** 风险监控 */
  Risk = "f",
  /** 查询/管理：查询会话，踢人等 */
  Session = "g",
  /** 风控通知控制 */
  RiskNoticeCtl = "h",
  /** 风控通知发送 */
  RiskNotice = "i",
  /** 察看经纪公司资金权限 */
  BrokerDeposit = "j",
  /** 资金查询 */
  QueryFund = "k",
  /** 报单查询 */
  QueryOrder = "l",
  /** 成交查询 */
  QueryTrade = "m",
  /** 持仓查询 */
  QueryPosition = "n",
  /** 行情查询 */
  QueryMarketData = "o",
  /** 用户事件查询 */
  QueryUserEvent = "p",
  /** 风险通知查询 */
  QueryRiskNotify = "q",
  /** 出入金查询 */
  QueryFundChange = "r",
  /** 投资者信息查询 */
  QueryInvestor = "s",
  /** 交易编码查询 */
  QueryTradingCode = "t",
  /** 强平 */
  ForceClose = "u",
  /** 压力测试 */
  PressTest = "v",
  /** 权益反算 */
  RemainCalc = "w",
  /** 净持仓保证金指标 */
  NetPositionInd = "x",
  /** 风险预算 */
  RiskPredict = "y",
  /** 数据导出 */
  DataExport = "z",
  /** 风控指标设置 */
  RiskTargetSetup = "A",
  /** 行情预警 */
  MarketDataWarn = "B",
  /** 业务通知查询 */
  QryBizNotice = "C",
  /** 业务通知模板设置 */
  CfgBizNotice = "D",
  /** 同步动态令牌 */
  SyncOTP = "E",
  /** 发送业务通知 */
  SendBizNotice = "F",
  /** 风险级别标准设置 */
  CfgRiskLevelStd = "G",
  /** 交易终端应急功能 */
  TbCommand = "H",
  /** 删除未知单 */
  DeleteOrder = "J",
  /** 预埋报单插入 */
  ParkedOrderInsert = "K",
  /** 预埋报单操作 */
  ParkedOrderAction = "L",
  /** 资金不够仍允许行权 */
  ExecOrderNoCheck = "M",
  /** 指定 */
  Designate = "N",
  /** 证券处置 */
  StockDisposal = "O",
  /** 席位资金预警 */
  BrokerDepositWarn = "Q",
  /** 备兑不足预警 */
  CoverWarn = "S",
  /** 行权试算 */
  PreExecOrder = "T",
  /** 行权交收风险 */
  ExecOrderRisk = "P",
  /** 持仓限额预警 */
  PosiLimitWarn = "U",
  /** 持仓限额查询 */
  QryPosiLimit = "V",
  /** 银期签到签退 */
  FBSign = "W",
  /** 银期签约解约 */
  FBAccount = "X",
}

/** 报单操作状态类型 */
export enum OrderActionStatusType {
  /** 已经提交 */
  Submitted = "a",
  /** 已经接受 */
  Accepted = "b",
  /** 已经被拒绝 */
  Rejected = "c",
}

/** 报单状态类型 */
export enum OrderStatusType {
  /** 全部成交 */
  AllTraded = "0",
  /** 部分成交还在队列中 */
  PartTradedQueueing = "1",
  /** 部分成交不在队列中 */
  PartTradedNotQueueing = "2",
  /** 未成交还在队列中 */
  NoTradeQueueing = "3",
  /** 未成交不在队列中 */
  NoTradeNotQueueing = "4",
  /** 撤单 */
  Canceled = "5",
  /** 未知 */
  Unknown = "a",
  /** 尚未触发 */
  NotTouched = "b",
  /** 已触发 */
  Touched = "c",
}

/** 报单提交状态类型 */
export enum OrderSubmitStatusType {
  /** 已经提交 */
  InsertSubmitted = "0",
  /** 撤单已经提交 */
  CancelSubmitted = "1",
  /** 修改已经提交 */
  ModifySubmitted = "2",
  /** 已经接受 */
  Accepted = "3",
  /** 报单已经被拒绝 */
  InsertRejected = "4",
  /** 撤单已经被拒绝 */
  CancelRejected = "5",
  /** 改单已经被拒绝 */
  ModifyRejected = "6",
}

/** 持仓日期类型 */
export enum PositionDateType {
  /** 今日持仓 */
  Today = "1",
  /** 历史持仓 */
  History = "2",
}

/** 持仓日期类型类型 */
export enum PositionDateType {
  /** 使用历史持仓 */
  UseHistory = "1",
  /** 不使用历史持仓 */
  NoUseHistory = "2",
}

/** 交易角色类型 */
export enum TradingRoleType {
  /** 代理 */
  Broker = "1",
  /** 自营 */
  Host = "2",
  /** 做市商 */
  Maker = "3",
}

/** 产品类型类型 */
export enum ProductClassType {
  /** 期货 */
  Futures = "1",
  /** 期货期权 */
  Options = "2",
  /** 组合 */
  Combination = "3",
  /** 即期 */
  Spot = "4",
  /** 期转现 */
  EFP = "5",
  /** 现货期权 */
  SpotOption = "6",
  /** TAS合约 */
  TAS = "7",
  /** 金属指数 */
  MI = "I",
}

/** 产品类型类型 */
export enum APIProductClassType {
  /** 期货单一合约 */
  FutureSingle = "1",
  /** 期权单一合约 */
  OptionSingle = "2",
  /** 可交易期货(含期货组合和期货单一合约) */
  Futures = "3",
  /** 可交易期权(含期权组合和期权单一合约) */
  Options = "4",
  /** 可下单组合（目前包含DCE和ZCE的期货组合） */
  TradingComb = "5",
  /** 可申请的组合（dce可以申请的组合合约 包含dce可以交易的合约） */
  UnTradingComb = "6",
  /** 所有可以交易合约 */
  AllTrading = "7",
  /** 所有合约（包含不能交易合约 慎用） */
  All = "8",
}

/** 合约生命周期状态类型 */
export enum InstLifePhaseType {
  /** 未上市 */
  NotStart = "0",
  /** 上市 */
  Started = "1",
  /** 停牌 */
  Pause = "2",
  /** 到期 */
  Expired = "3",
}

/** 买卖方向类型 */
export enum DirectionType {
  /** 买 */
  Buy = "0",
  /** 卖 */
  Sell = "1",
}

/** 持仓类型类型 */
export enum PositionType {
  /** 净持仓 */
  Net = "1",
  /** 综合持仓 */
  Gross = "2",
}

/** 持仓多空方向类型 */
export enum PosiDirectionType {
  /** 净 */
  Net = "1",
  /** 多头 */
  Long = "2",
  /** 空头 */
  Short = "3",
}

/** 系统结算状态类型 */
export enum SysSettlementStatusType {
  /** 不活跃 */
  NonActive = "1",
  /** 启动 */
  Startup = "2",
  /** 操作 */
  Operating = "3",
  /** 结算 */
  Settlement = "4",
  /** 结算完成 */
  SettlementFinished = "5",
}

/** 费率属性类型 */
export enum RatioAttrType {
  /** 交易费率 */
  Trade = "0",
  /** 结算费率 */
  Settlement = "1",
}

/** 投机套保标志类型 */
export enum HedgeFlagType {
  /** 投机 */
  Speculation = "1",
  /** 套利 */
  Arbitrage = "2",
  /** 套保 */
  Hedge = "3",
  /** 做市商 */
  MarketMaker = "5",
  /** 第一腿投机第二腿套保 大商所专用 */
  SpecHedge = "6",
  /** 第一腿套保第二腿投机  大商所专用 */
  HedgeSpec = "7",
}

/** 投机套保标志类型 */
export enum BillHedgeFlagType {
  /** 投机 */
  Speculation = "1",
  /** 套利 */
  Arbitrage = "2",
  /** 套保 */
  Hedge = "3",
}

/** 交易编码类型类型 */
export enum ClientIDType {
  /** 投机 */
  Speculation = "1",
  /** 套利 */
  Arbitrage = "2",
  /** 套保 */
  Hedge = "3",
  /** 做市商 */
  MarketMaker = "5",
}

/** 报单价格条件类型 */
export enum OrderPriceType {
  /** 任意价 */
  AnyPrice = "1",
  /** 限价 */
  LimitPrice = "2",
  /** 最优价 */
  BestPrice = "3",
  /** 最新价 */
  LastPrice = "4",
  /** 最新价浮动上浮1个ticks */
  LastPricePlusOneTicks = "5",
  /** 最新价浮动上浮2个ticks */
  LastPricePlusTwoTicks = "6",
  /** 最新价浮动上浮3个ticks */
  LastPricePlusThreeTicks = "7",
  /** 卖一价 */
  AskPrice1 = "8",
  /** 卖一价浮动上浮1个ticks */
  AskPrice1PlusOneTicks = "9",
  /** 卖一价浮动上浮2个ticks */
  AskPrice1PlusTwoTicks = "A",
  /** 卖一价浮动上浮3个ticks */
  AskPrice1PlusThreeTicks = "B",
  /** 买一价 */
  BidPrice1 = "C",
  /** 买一价浮动上浮1个ticks */
  BidPrice1PlusOneTicks = "D",
  /** 买一价浮动上浮2个ticks */
  BidPrice1PlusTwoTicks = "E",
  /** 买一价浮动上浮3个ticks */
  BidPrice1PlusThreeTicks = "F",
  /** 五档价 */
  FiveLevelPrice = "G",
}

/** 开平标志类型 */
export enum OffsetFlagType {
  /** 开仓 */
  Open = "0",
  /** 平仓 */
  Close = "1",
  /** 强平 */
  ForceClose = "2",
  /** 平今 */
  CloseToday = "3",
  /** 平昨 */
  CloseYesterday = "4",
  /** 强减 */
  ForceOff = "5",
  /** 本地强平 */
  LocalForceClose = "6",
}

/** 强平原因类型 */
export enum ForceCloseReasonType {
  /** 非强平 */
  NotForceClose = "0",
  /** 资金不足 */
  LackDeposit = "1",
  /** 客户超仓 */
  ClientOverPositionLimit = "2",
  /** 会员超仓 */
  MemberOverPositionLimit = "3",
  /** 持仓非整数倍 */
  NotMultiple = "4",
  /** 违规 */
  Violation = "5",
  /** 其它 */
  Other = "6",
  /** 自然人临近交割 */
  PersonDeliv = "7",
  /** 风控强平不验证资金 */
  Notverifycapital = "8",
}

/** 报单类型类型 */
export enum OrderType {
  /** 正常 */
  Normal = "0",
  /** 报价衍生 */
  DeriveFromQuote = "1",
  /** 组合衍生 */
  DeriveFromCombination = "2",
  /** 组合报单 */
  Combination = "3",
  /** 条件单 */
  ConditionalOrder = "4",
  /** 互换单 */
  Swap = "5",
  /** 大宗交易成交衍生 */
  DeriveFromBlockTrade = "6",
  /** 期转现成交衍生 */
  DeriveFromEFPTrade = "7",
}

/** 有效期类型类型 */
export enum TimeConditionType {
  /** 立即完成，否则撤销 */
  IOC = "1",
  /** 本节有效 */
  GFS = "2",
  /** 当日有效 */
  GFD = "3",
  /** 指定日期前有效 */
  GTD = "4",
  /** 撤销前有效 */
  GTC = "5",
  /** 集合竞价有效 */
  GFA = "6",
}

/** 成交量类型类型 */
export enum VolumeConditionType {
  /** 任何数量 */
  AV = "1",
  /** 最小数量 */
  MV = "2",
  /** 全部数量 */
  CV = "3",
}

/** 触发条件类型 */
export enum ContingentConditionType {
  /** 立即 */
  Immediately = "1",
  /** 止损 */
  Touch = "2",
  /** 止赢 */
  TouchProfit = "3",
  /** 预埋单 */
  ParkedOrder = "4",
  /** 最新价大于条件价 */
  LastPriceGreaterThanStopPrice = "5",
  /** 最新价大于等于条件价 */
  LastPriceGreaterEqualStopPrice = "6",
  /** 最新价小于条件价 */
  LastPriceLesserThanStopPrice = "7",
  /** 最新价小于等于条件价 */
  LastPriceLesserEqualStopPrice = "8",
  /** 卖一价大于条件价 */
  AskPriceGreaterThanStopPrice = "9",
  /** 卖一价大于等于条件价 */
  AskPriceGreaterEqualStopPrice = "A",
  /** 卖一价小于条件价 */
  AskPriceLesserThanStopPrice = "B",
  /** 卖一价小于等于条件价 */
  AskPriceLesserEqualStopPrice = "C",
  /** 买一价大于条件价 */
  BidPriceGreaterThanStopPrice = "D",
  /** 买一价大于等于条件价 */
  BidPriceGreaterEqualStopPrice = "E",
  /** 买一价小于条件价 */
  BidPriceLesserThanStopPrice = "F",
  /** 买一价小于等于条件价 */
  BidPriceLesserEqualStopPrice = "H",
}

/** 操作标志类型 */
export enum ActionFlagType {
  /** 删除 */
  Delete = "0",
  /** 修改 */
  Modify = "3",
}

/** 交易权限类型 */
export enum TradingRightType {
  /** 可以交易 */
  Allow = "0",
  /** 只能平仓 */
  CloseOnly = "1",
  /** 不能交易 */
  Forbidden = "2",
}

/** 报单来源类型 */
export enum OrderSourceType {
  /** 来自参与者 */
  Participant = "0",
  /** 来自管理员 */
  Administrator = "1",
}

/** 成交类型类型 */
export enum TradeType {
  /** 组合持仓拆分为单一持仓,初始化不应包含该类型的持仓 */
  SplitCombination = "#",
  /** 普通成交 */
  Common = "0",
  /** 期权执行 */
  OptionsExecution = "1",
  /** OTC成交 */
  OTC = "2",
  /** 期转现衍生成交 */
  EFPDerived = "3",
  /** 组合衍生成交 */
  CombinationDerived = "4",
  /** 大宗交易成交 */
  BlockTrade = "5",
}

/** 特殊持仓明细标识类型 */
export enum SpecPosiType {
  /** 普通持仓明细 */
  Common = "#",
  /** TAS合约成交产生的标的合约持仓明细 */
  Tas = "0",
}

/** 成交价来源类型 */
export enum PriceSourceType {
  /** 前成交价 */
  LastPrice = "0",
  /** 买委托价 */
  Buy = "1",
  /** 卖委托价 */
  Sell = "2",
  /** 场外成交价 */
  OTC = "3",
}

/** 合约交易状态类型 */
export enum InstrumentStatusType {
  /** 开盘前 */
  BeforeTrading = "0",
  /** 非交易 */
  NoTrading = "1",
  /** 连续交易 */
  Continous = "2",
  /** 集合竞价报单 */
  AuctionOrdering = "3",
  /** 集合竞价价格平衡 */
  AuctionBalance = "4",
  /** 集合竞价撮合 */
  AuctionMatch = "5",
  /** 收盘 */
  Closed = "6",
}

/** 品种进入交易状态原因类型 */
export enum InstStatusEnterReasonType {
  /** 自动切换 */
  Automatic = "1",
  /** 手动切换 */
  Manual = "2",
  /** 熔断 */
  Fuse = "3",
}

/** 处理状态类型 */
export enum BatchStatusType {
  /** 未上传 */
  NoUpload = "1",
  /** 已上传 */
  Uploaded = "2",
  /** 审核失败 */
  Failed = "3",
}

/** 按品种返还方式类型 */
export enum ReturnStyleType {
  /** 按所有品种 */
  All = "1",
  /** 按品种 */
  ByProduct = "2",
}

/** 返还模式类型 */
export enum ReturnPatternType {
  /** 按成交手数 */
  ByVolume = "1",
  /** 按留存手续费 */
  ByFeeOnHand = "2",
}

/** 返还级别类型 */
export enum ReturnLevelType {
  /** 级别1 */
  Level1 = "1",
  /** 级别2 */
  Level2 = "2",
  /** 级别3 */
  Level3 = "3",
  /** 级别4 */
  Level4 = "4",
  /** 级别5 */
  Level5 = "5",
  /** 级别6 */
  Level6 = "6",
  /** 级别7 */
  Level7 = "7",
  /** 级别8 */
  Level8 = "8",
  /** 级别9 */
  Level9 = "9",
}

/** 返还标准类型 */
export enum ReturnStandardType {
  /** 分阶段返还 */
  ByPeriod = "1",
  /** 按某一标准 */
  ByStandard = "2",
}

/** 质押类型类型 */
export enum MortgageType {
  /** 质出 */
  Out = "0",
  /** 质入 */
  In = "1",
}

/** 投资者结算参数代码类型 */
export enum InvestorSettlementParamIDType {
  /** 质押比例 */
  MortgageRatio = "4",
  /** 保证金算法 */
  MarginWay = "5",
  /** 结算单结存是否包含质押 */
  BillDeposit = "9",
}

/** 交易所结算参数代码类型 */
export enum ExchangeSettlementParamIDType {
  /** 质押比例 */
  MortgageRatio = "1",
  /** 分项资金导入项 */
  OtherFundItem = "2",
  /** 分项资金入交易所出入金 */
  OtherFundImport = "3",
  /** 中金所开户最低可用金额 */
  CFFEXMinPrepa = "6",
  /** 郑商所结算方式 */
  CZCESettlementType = "7",
  /** 交易所交割手续费收取方式 */
  ExchDelivFeeMode = "9",
  /** 投资者交割手续费收取方式 */
  DelivFeeMode = "0",
  /** 郑商所组合持仓保证金收取方式 */
  CZCEComMarginType = "A",
  /** 大商所套利保证金是否优惠 */
  DceComMarginType = "B",
  /** 虚值期权保证金优惠比率 */
  OptOutDisCountRate = "a",
  /** 最低保障系数 */
  OptMiniGuarantee = "b",
}

/** 系统参数代码类型 */
export enum SystemParamIDType {
  /** 投资者代码最小长度 */
  InvestorIDMinLength = "1",
  /** 投资者帐号代码最小长度 */
  AccountIDMinLength = "2",
  /** 投资者开户默认登录权限 */
  UserRightLogon = "3",
  /** 投资者交易结算单成交汇总方式 */
  SettlementBillTrade = "4",
  /** 统一开户更新交易编码方式 */
  TradingCode = "5",
  /** 结算是否判断存在未复核的出入金和分项资金 */
  CheckFund = "6",
  /** 是否启用手续费模板数据权限 */
  CommModelRight = "7",
  /** 是否启用保证金率模板数据权限 */
  MarginModelRight = "9",
  /** 是否规范用户才能激活 */
  IsStandardActive = "8",
  /** 上传的交易所结算文件路径 */
  UploadSettlementFile = "U",
  /** 上报保证金监控中心文件路径 */
  DownloadCSRCFile = "D",
  /** 生成的结算单文件路径 */
  SettlementBillFile = "S",
  /** 证监会文件标识 */
  CSRCOthersFile = "C",
  /** 投资者照片路径 */
  InvestorPhoto = "P",
  /** 全结经纪公司上传文件路径 */
  CSRCData = "R",
  /** 开户密码录入方式 */
  InvestorPwdModel = "I",
  /** 投资者中金所结算文件下载路径 */
  CFFEXInvestorSettleFile = "F",
  /** 投资者代码编码方式 */
  InvestorIDType = "a",
  /** 休眠户最高权益 */
  FreezeMaxReMain = "r",
  /** 手续费相关操作实时上场开关 */
  IsSync = "A",
  /** 解除开仓权限限制 */
  RelieveOpenLimit = "O",
  /** 是否规范用户才能休眠 */
  IsStandardFreeze = "X",
  /** 郑商所是否开放所有品种套保交易 */
  CZCENormalProductHedge = "B",
}

/** 交易系统参数代码类型 */
export enum TradeParamIDType {
  /** 系统加密算法 */
  EncryptionStandard = "E",
  /** 系统风险算法 */
  RiskMode = "R",
  /** 系统风险算法是否全局 0-否 1-是 */
  RiskModeGlobal = "G",
  /** 密码加密算法 */
  modeEncode = "P",
  /** 价格小数位数参数 */
  tickMode = "T",
  /** 用户最大会话数 */
  SingleUserSessionMaxNum = "S",
  /** 最大连续登录失败数 */
  LoginFailMaxNum = "L",
  /** 是否强制认证 */
  IsAuthForce = "A",
  /** 是否冻结证券持仓 */
  IsPosiFreeze = "F",
  /** 是否限仓 */
  IsPosiLimit = "M",
  /** 郑商所询价时间间隔 */
  ForQuoteTimeInterval = "Q",
  /** 是否期货限仓 */
  IsFuturePosiLimit = "B",
  /** 是否期货下单频率限制 */
  IsFutureOrderFreq = "C",
  /** 行权冻结是否计算盈利 */
  IsExecOrderProfit = "H",
  /** 银期开户是否验证开户银行卡号是否是预留银行账户 */
  IsCheckBankAcc = "I",
  /** 弱密码最后修改日期 */
  PasswordDeadLine = "J",
  /** 强密码校验 */
  IsStrongPassword = "K",
  /** 自有资金质押比 */
  BalanceMorgage = "a",
  /** 最小密码长度 */
  MinPwdLen = "O",
  /** IP当日最大登陆失败次数 */
  LoginFailMaxNumForIP = "U",
  /** 密码有效期 */
  PasswordPeriod = "V",
}

/** 文件标识类型 */
export enum FileIDType {
  /** 资金数据 */
  SettlementFund = "F",
  /** 成交数据 */
  Trade = "T",
  /** 投资者持仓数据 */
  InvestorPosition = "P",
  /** 投资者分项资金数据 */
  SubEntryFund = "O",
  /** 组合持仓数据 */
  CZCECombinationPos = "C",
  /** 上报保证金监控中心数据 */
  CSRCData = "R",
  /** 郑商所平仓了结数据 */
  CZCEClose = "L",
  /** 郑商所非平仓了结数据 */
  CZCENoClose = "N",
  /** 持仓明细数据 */
  PositionDtl = "D",
  /** 期权执行文件 */
  OptionStrike = "S",
  /** 结算价比对文件 */
  SettlementPriceComparison = "M",
  /** 上期所非持仓变动明细 */
  NonTradePosChange = "B",
}

/** 文件上传类型类型 */
export enum FileType {
  /** 结算 */
  Settlement = "0",
  /** 核对 */
  Check = "1",
}

/** 文件格式类型 */
export enum FileFormatType {
  /** 文本文件(.txt) */
  Txt = "0",
  /** 压缩文件(.zip) */
  Zip = "1",
  /** DBF文件(.dbf) */
  DBF = "2",
}

/** 文件状态类型 */
export enum FileUploadStatusType {
  /** 上传成功 */
  SucceedUpload = "1",
  /** 上传失败 */
  FailedUpload = "2",
  /** 导入成功 */
  SucceedLoad = "3",
  /** 导入部分成功 */
  PartSucceedLoad = "4",
  /** 导入失败 */
  FailedLoad = "5",
}

/** 移仓方向类型 */
export enum TransferDirectionType {
  /** 移出 */
  Out = "0",
  /** 移入 */
  In = "1",
}

/** 特殊的创建规则类型 */
export enum SpecialCreateRuleType {
  /** 没有特殊创建规则 */
  NoSpecialRule = "0",
  /** 不包含春节 */
  NoSpringFestival = "1",
}

/** 挂牌基准价类型类型 */
export enum BasisPriceType {
  /** 上一合约结算价 */
  LastSettlement = "1",
  /** 上一合约收盘价 */
  LaseClose = "2",
}

/** 产品生命周期状态类型 */
export enum ProductLifePhaseType {
  /** 活跃 */
  Active = "1",
  /** 不活跃 */
  NonActive = "2",
  /** 注销 */
  Canceled = "3",
}

/** 交割方式类型 */
export enum DeliveryModeType {
  /** 现金交割 */
  CashDeliv = "1",
  /** 实物交割 */
  CommodityDeliv = "2",
}

/** 出入金类型类型 */
export enum FundIOType {
  /** 出入金 */
  FundIO = "1",
  /** 银期转帐 */
  Transfer = "2",
  /** 银期换汇 */
  SwapCurrency = "3",
}

/** 资金类型类型 */
export enum FundType {
  /** 银行存款 */
  Deposite = "1",
  /** 分项资金 */
  ItemFund = "2",
  /** 公司调整 */
  Company = "3",
  /** 资金内转 */
  InnerTransfer = "4",
}

/** 出入金方向类型 */
export enum FundDirectionType {
  /** 入金 */
  In = "1",
  /** 出金 */
  Out = "2",
}

/** 资金状态类型 */
export enum FundStatusType {
  /** 已录入 */
  Record = "1",
  /** 已复核 */
  Check = "2",
  /** 已冲销 */
  Charge = "3",
}

/** 发布状态类型 */
export enum PublishStatusType {
  /** 未发布 */
  None = "1",
  /** 正在发布 */
  Publishing = "2",
  /** 已发布 */
  Published = "3",
}

/** 系统状态类型 */
export enum SystemStatusType {
  /** 不活跃 */
  NonActive = "1",
  /** 启动 */
  Startup = "2",
  /** 交易开始初始化 */
  Initialize = "3",
  /** 交易完成初始化 */
  Initialized = "4",
  /** 收市开始 */
  Close = "5",
  /** 收市完成 */
  Closed = "6",
  /** 结算 */
  Settlement = "7",
}

/** 结算状态类型 */
export enum SettlementStatusType {
  /** 初始 */
  Initialize = "0",
  /** 结算中 */
  Settlementing = "1",
  /** 已结算 */
  Settlemented = "2",
  /** 结算完成 */
  Finished = "3",
}

/** 投资者类型类型 */
export enum InvestorType {
  /** 自然人 */
  Person = "0",
  /** 法人 */
  Company = "1",
  /** 投资基金 */
  Fund = "2",
  /** 特殊法人 */
  SpecialOrgan = "3",
  /** 资管户 */
  Asset = "4",
}

/** 经纪公司类型类型 */
export enum BrokerType {
  /** 交易会员 */
  Trade = "0",
  /** 交易结算会员 */
  TradeSettle = "1",
}

/** 风险等级类型 */
export enum RiskLevelType {
  /** 低风险客户 */
  Low = "1",
  /** 普通客户 */
  Normal = "2",
  /** 关注客户 */
  Focus = "3",
  /** 风险客户 */
  Risk = "4",
}

/** 手续费收取方式类型 */
export enum FeeAcceptStyleType {
  /** 按交易收取 */
  ByTrade = "1",
  /** 按交割收取 */
  ByDeliv = "2",
  /** 不收 */
  None = "3",
  /** 按指定手续费收取 */
  FixFee = "4",
}

/** 密码类型类型 */
export enum PasswordType {
  /** 交易密码 */
  Trade = "1",
  /** 资金密码 */
  Account = "2",
}

/** 盈亏算法类型 */
export enum AlgorithmType {
  /** 浮盈浮亏都计算 */
  All = "1",
  /** 浮盈不计，浮亏计 */
  OnlyLost = "2",
  /** 浮盈计，浮亏不计 */
  OnlyGain = "3",
  /** 浮盈浮亏都不计算 */
  None = "4",
}

/** 是否包含平仓盈利类型 */
export enum IncludeCloseProfitType {
  /** 包含平仓盈利 */
  Include = "0",
  /** 不包含平仓盈利 */
  NotInclude = "2",
}

/** 是否受可提比例限制类型 */
export enum AllWithoutTradeType {
  /** 无仓无成交不受可提比例限制 */
  Enable = "0",
  /** 受可提比例限制 */
  Disable = "2",
  /** 无仓不受可提比例限制 */
  NoHoldEnable = "3",
}

/** 资金密码核对标志类型 */
export enum FuturePwdFlagType {
  /** 不核对 */
  UnCheck = "0",
  /** 核对 */
  Check = "1",
}

/** 银期转账类型类型 */
export enum TransferType {
  /** 银行转期货 */
  BankToFuture = "0",
  /** 期货转银行 */
  FutureToBank = "1",
}

/** 转账有效标志类型 */
export enum TransferValidFlagType {
  /** 无效或失败 */
  Invalid = "0",
  /** 有效 */
  Valid = "1",
  /** 冲正 */
  Reverse = "2",
}

/** 事由类型 */
export enum ReasonType {
  /** 错单 */
  CD = "0",
  /** 资金在途 */
  ZT = "1",
  /** 其它 */
  QT = "2",
}

/** 性别类型 */
export enum SexType {
  /** 未知 */
  None = "0",
  /** 男 */
  Man = "1",
  /** 女 */
  Woman = "2",
}

/** 用户类型类型 */
export enum UserType {
  /** 投资者 */
  Investor = "0",
  /** 操作员 */
  Operator = "1",
  /** 管理员 */
  SuperUser = "2",
}

/** 费率类型类型 */
export enum RateType {
  /** 保证金率 */
  MarginRate = "2",
}

/** 通知类型类型 */
export enum NoteType {
  /** 交易结算单 */
  TradeSettleBill = "1",
  /** 交易结算月报 */
  TradeSettleMonth = "2",
  /** 追加保证金通知书 */
  CallMarginNotes = "3",
  /** 强行平仓通知书 */
  ForceCloseNotes = "4",
  /** 成交通知书 */
  TradeNotes = "5",
  /** 交割通知书 */
  DelivNotes = "6",
}

/** 结算单方式类型 */
export enum SettlementStyleType {
  /** 逐日盯市 */
  Day = "1",
  /** 逐笔对冲 */
  Volume = "2",
}

/** 结算单类型类型 */
export enum SettlementBillType {
  /** 日报 */
  Day = "0",
  /** 月报 */
  Month = "1",
}

/** 客户权限类型类型 */
export enum UserRightType {
  /** 登录 */
  Logon = "1",
  /** 银期转帐 */
  Transfer = "2",
  /** 邮寄结算单 */
  EMail = "3",
  /** 传真结算单 */
  Fax = "4",
  /** 条件单 */
  ConditionOrder = "5",
}

/** 保证金价格类型类型 */
export enum MarginPriceType {
  /** 昨结算价 */
  PreSettlementPrice = "1",
  /** 最新价 */
  SettlementPrice = "2",
  /** 成交均价 */
  AveragePrice = "3",
  /** 开仓价 */
  OpenPrice = "4",
}

/** 结算单生成状态类型 */
export enum BillGenStatusType {
  /** 未生成 */
  None = "0",
  /** 生成中 */
  NoGenerated = "1",
  /** 已生成 */
  Generated = "2",
}

/** 算法类型类型 */
export enum AlgoType {
  /** 持仓处理算法 */
  HandlePositionAlgo = "1",
  /** 寻找保证金率算法 */
  FindMarginRateAlgo = "2",
}

/** 持仓处理算法编号类型 */
export enum HandlePositionAlgoIDType {
  /** 基本 */
  Base = "1",
  /** 大连商品交易所 */
  DCE = "2",
  /** 郑州商品交易所 */
  CZCE = "3",
}

/** 寻找保证金率算法编号类型 */
export enum FindMarginRateAlgoIDType {
  /** 基本 */
  Base = "1",
  /** 大连商品交易所 */
  DCE = "2",
  /** 郑州商品交易所 */
  CZCE = "3",
}

/** 资金处理算法编号类型 */
export enum HandleTradingAccountAlgoIDType {
  /** 基本 */
  Base = "1",
  /** 大连商品交易所 */
  DCE = "2",
  /** 郑州商品交易所 */
  CZCE = "3",
}

/** 联系人类型类型 */
export enum PersonType {
  /** 指定下单人 */
  Order = "1",
  /** 开户授权人 */
  Open = "2",
  /** 资金调拨人 */
  Fund = "3",
  /** 结算单确认人 */
  Settlement = "4",
  /** 法人 */
  Company = "5",
  /** 法人代表 */
  Corporation = "6",
  /** 投资者联系人 */
  LinkMan = "7",
  /** 分户管理资产负责人 */
  Ledger = "8",
  /** 托（保）管人 */
  Trustee = "9",
  /** 托（保）管机构法人代表 */
  TrusteeCorporation = "A",
  /** 托（保）管机构开户授权人 */
  TrusteeOpen = "B",
  /** 托（保）管机构联系人 */
  TrusteeContact = "C",
  /** 境外自然人参考证件 */
  ForeignerRefer = "D",
  /** 法人代表参考证件 */
  CorporationRefer = "E",
}

/** 查询范围类型 */
export enum QueryInvestorRangeType {
  /** 所有 */
  All = "1",
  /** 查询分类 */
  Group = "2",
  /** 单一投资者 */
  Single = "3",
}

/** 投资者风险状态类型 */
export enum InvestorRiskStatusType {
  /** 正常 */
  Normal = "1",
  /** 警告 */
  Warn = "2",
  /** 追保 */
  Call = "3",
  /** 强平 */
  Force = "4",
  /** 异常 */
  Exception = "5",
}

/** 用户事件类型类型 */
export enum UserEventType {
  /** 登录 */
  Login = "1",
  /** 登出 */
  Logout = "2",
  /** 交易成功 */
  Trading = "3",
  /** 交易失败 */
  TradingError = "4",
  /** 修改密码 */
  UpdatePassword = "5",
  /** 客户端认证 */
  Authenticate = "6",
  /** 终端信息上报 */
  SubmitSysInfo = "7",
  /** 转账 */
  Transfer = "8",
  /** 其他 */
  Other = "9",
}

/** 平仓方式类型 */
export enum CloseStyleType {
  /** 先开先平 */
  Close = "0",
  /** 先平今再平昨 */
  CloseToday = "1",
}

/** 统计方式类型 */
export enum StatModeType {
  /** ---- */
  Non = "0",
  /** 按合约统计 */
  Instrument = "1",
  /** 按产品统计 */
  Product = "2",
  /** 按投资者统计 */
  Investor = "3",
}

/** 预埋单状态类型 */
export enum ParkedOrderStatusType {
  /** 未发送 */
  NotSend = "1",
  /** 已发送 */
  Send = "2",
  /** 已删除 */
  Deleted = "3",
}

/** 处理状态类型 */
export enum VirDealStatusType {
  /** 正在处理 */
  Dealing = "1",
  /** 处理成功 */
  DeaclSucceed = "2",
}

/** 原有系统代码类型 */
export enum OrgSystemIDType {
  /** 综合交易平台 */
  Standard = "0",
  /** 易盛系统 */
  ESunny = "1",
  /** 金仕达V6系统 */
  KingStarV6 = "2",
}

/** 交易状态类型 */
export enum VirTradeStatusType {
  /** 正常处理中 */
  NaturalDeal = "0",
  /** 成功结束 */
  SucceedEnd = "1",
  /** 失败结束 */
  FailedEND = "2",
  /** 异常中 */
  Exception = "3",
  /** 已人工异常处理 */
  ManualDeal = "4",
  /** 通讯异常 ，请人工处理 */
  MesException = "5",
  /** 系统出错，请人工处理 */
  SysException = "6",
}

/** 银行帐户类型类型 */
export enum VirBankAccType {
  /** 存折 */
  BankBook = "1",
  /** 储蓄卡 */
  BankCard = "2",
  /** 信用卡 */
  CreditCard = "3",
}

/** 银行帐户类型类型 */
export enum VirementStatusType {
  /** 正常 */
  Natural = "0",
  /** 销户 */
  Canceled = "9",
}

/** 有效标志类型 */
export enum VirementAvailAbilityType {
  /** 未确认 */
  NoAvailAbility = "0",
  /** 有效 */
  AvailAbility = "1",
  /** 冲正 */
  Repeal = "2",
}

/** 交易代码类型 */
export enum VirementTradeCodeType {
  /** 银行发起银行资金转期货 */
  BankBankToFuture = "\u8E71",
  /** 银行发起期货资金转银行 */
  BankFutureToBank = "\u8E72",
  /** 期货发起银行资金转期货 */
  FutureBankToFuture = "\u1511",
  /** 期货发起期货资金转银行 */
  FutureFutureToBank = "\u1512",
}

/** Aml生成方式类型 */
export enum AMLGenStatusType {
  /** 程序生成 */
  Program = "0",
  /** 人工生成 */
  HandWork = "1",
}

/** 动态密钥类别(保证金监管)类型 */
export enum CFMMCKeyKindType {
  /** 主动请求更新 */
  REQUEST = "R",
  /** CFMMC自动更新 */
  AUTO = "A",
  /** CFMMC手动更新 */
  MANUAL = "M",
}

/** 证件类型类型 */
export enum CertificationType {
  /** 身份证 */
  IDCard = "0",
  /** 护照 */
  Passport = "1",
  /** 军官证 */
  OfficerIDCard = "2",
  /** 士兵证 */
  SoldierIDCard = "3",
  /** 回乡证 */
  HomeComingCard = "4",
  /** 户口簿 */
  HouseholdRegister = "5",
  /** 营业执照号 */
  LicenseNo = "6",
  /** 组织机构代码证 */
  InstitutionCodeCard = "7",
  /** 临时营业执照号 */
  TempLicenseNo = "8",
  /** 民办非企业登记证书 */
  NoEnterpriseLicenseNo = "9",
  /** 其他证件 */
  OtherCard = "x",
  /** 主管部门批文 */
  SuperDepAgree = "a",
}

/** 文件业务功能类型 */
export enum FileBusinessCodeType {
  /** 其他 */
  Others = "0",
  /** 转账交易明细对账 */
  TransferDetails = "1",
  /** 客户账户状态对账 */
  CustAccStatus = "2",
  /** 账户类交易明细对账 */
  AccountTradeDetails = "3",
  /** 期货账户信息变更明细对账 */
  FutureAccountChangeInfoDetails = "4",
  /** 客户资金台账余额明细对账 */
  CustMoneyDetail = "5",
  /** 客户销户结息明细对账 */
  CustCancelAccountInfo = "6",
  /** 客户资金余额对账结果 */
  CustMoneyResult = "7",
  /** 其它对账异常结果文件 */
  OthersExceptionResult = "8",
  /** 客户结息净额明细 */
  CustInterestNetMoneyDetails = "9",
  /** 客户资金交收明细 */
  CustMoneySendAndReceiveDetails = "a",
  /** 法人存管银行资金交收汇总 */
  CorporationMoneyTotal = "b",
  /** 主体间资金交收汇总 */
  MainbodyMoneyTotal = "c",
  /** 总分平衡监管数据 */
  MainPartMonitorData = "d",
  /** 存管银行备付金余额 */
  PreparationMoney = "e",
  /** 协办存管银行资金监管数据 */
  BankMoneyMonitorData = "f",
}

/** 汇钞标志类型 */
export enum CashExchangeCodeType {
  /** 汇 */
  Exchange = "1",
  /** 钞 */
  Cash = "2",
}

/** 是或否标识类型 */
export enum YesNoIndicatorType {
  /** 是 */
  Yes = "0",
  /** 否 */
  No = "1",
}

/** 余额类型类型 */
export enum BanlanceType {
  /** 当前余额 */
  CurrentMoney = "0",
  /** 可用余额 */
  UsableMoney = "1",
  /** 可取余额 */
  FetchableMoney = "2",
  /** 冻结余额 */
  FreezeMoney = "3",
}

/** 性别类型 */
export enum GenderType {
  /** 未知状态 */
  Unknown = "0",
  /** 男 */
  Male = "1",
  /** 女 */
  Female = "2",
}

/** 费用支付标志类型 */
export enum FeePayFlagType {
  /** 由受益方支付费用 */
  BEN = "0",
  /** 由发送方支付费用 */
  OUR = "1",
  /** 由发送方支付发起的费用，受益方支付接受的费用 */
  SHA = "2",
}

/** 密钥类型类型 */
export enum PassWordKeyType {
  /** 交换密钥 */
  ExchangeKey = "0",
  /** 密码密钥 */
  PassWordKey = "1",
  /** MAC密钥 */
  MACKey = "2",
  /** 报文密钥 */
  MessageKey = "3",
}

/** 密码类型类型 */
export enum FBTPassWordType {
  /** 查询 */
  Query = "0",
  /** 取款 */
  Fetch = "1",
  /** 转帐 */
  Transfer = "2",
  /** 交易 */
  Trade = "3",
}

/** 加密方式类型 */
export enum FBTEncryModeType {
  /** 不加密 */
  NoEncry = "0",
  /** DES */
  DES = "1",
  /** 3DES */
  DES3 = "2",
}

/** 银行冲正标志类型 */
export enum BankRepealFlagType {
  /** 银行无需自动冲正 */
  BankNotNeedRepeal = "0",
  /** 银行待自动冲正 */
  BankWaitingRepeal = "1",
  /** 银行已自动冲正 */
  BankBeenRepealed = "2",
}

/** 期商冲正标志类型 */
export enum BrokerRepealFlagType {
  /** 期商无需自动冲正 */
  BrokerNotNeedRepeal = "0",
  /** 期商待自动冲正 */
  BrokerWaitingRepeal = "1",
  /** 期商已自动冲正 */
  BrokerBeenRepealed = "2",
}

/** 机构类别类型 */
export enum InstitutionType {
  /** 银行 */
  Bank = "0",
  /** 期商 */
  Future = "1",
  /** 券商 */
  Store = "2",
}

/** 最后分片标志类型 */
export enum LastFragmentType {
  /** 是最后分片 */
  Yes = "0",
  /** 不是最后分片 */
  No = "1",
}

/** 银行账户状态类型 */
export enum BankAccStatusType {
  /** 正常 */
  Normal = "0",
  /** 冻结 */
  Freeze = "1",
  /** 挂失 */
  ReportLoss = "2",
}

/** 资金账户状态类型 */
export enum MoneyAccountStatusType {
  /** 正常 */
  Normal = "0",
  /** 销户 */
  Cancel = "1",
}

/** 存管状态类型 */
export enum ManageStatusType {
  /** 指定存管 */
  Point = "0",
  /** 预指定 */
  PrePoint = "1",
  /** 撤销指定 */
  CancelPoint = "2",
}

/** 应用系统类型类型 */
export enum SystemType {
  /** 银期转帐 */
  FutureBankTransfer = "0",
  /** 银证转帐 */
  StockBankTransfer = "1",
  /** 第三方存管 */
  TheThirdPartStore = "2",
}

/** 银期转帐划转结果标志类型 */
export enum TxnEndFlagType {
  /** 正常处理中 */
  NormalProcessing = "0",
  /** 成功结束 */
  Success = "1",
  /** 失败结束 */
  Failed = "2",
  /** 异常中 */
  Abnormal = "3",
  /** 已人工异常处理 */
  ManualProcessedForException = "4",
  /** 通讯异常 ，请人工处理 */
  CommuFailedNeedManualProcess = "5",
  /** 系统出错，请人工处理 */
  SysErrorNeedManualProcess = "6",
}

/** 银期转帐服务处理状态类型 */
export enum ProcessStatusType {
  /** 未处理 */
  NotProcess = "0",
  /** 开始处理 */
  StartProcess = "1",
  /** 处理完成 */
  Finished = "2",
}

/** 客户类型类型 */
export enum CustType {
  /** 自然人 */
  Person = "0",
  /** 机构户 */
  Institution = "1",
}

/** 银期转帐方向类型 */
export enum FBTTransferDirectionType {
  /** 入金，银行转期货 */
  FromBankToFuture = "1",
  /** 出金，期货转银行 */
  FromFutureToBank = "2",
}

/** 开销户类别类型 */
export enum OpenOrDestroyType {
  /** 开户 */
  Open = "1",
  /** 销户 */
  Destroy = "0",
}

/** 有效标志类型 */
export enum AvailabilityFlagType {
  /** 未确认 */
  Invalid = "0",
  /** 有效 */
  Valid = "1",
  /** 冲正 */
  Repeal = "2",
}

/** 机构类型类型 */
export enum OrganType {
  /** 银行代理 */
  Bank = "1",
  /** 交易前置 */
  Future = "2",
  /** 银期转帐平台管理 */
  PlateForm = "9",
}

/** 机构级别类型 */
export enum OrganLevelType {
  /** 银行总行或期商总部 */
  HeadQuarters = "1",
  /** 银行分中心或期货公司营业部 */
  Branch = "2",
}

/** 协议类型类型 */
export enum ProtocalIDType {
  /** 期商协议 */
  FutureProtocal = "0",
  /** 工行协议 */
  ICBCProtocal = "1",
  /** 农行协议 */
  ABCProtocal = "2",
  /** 中国银行协议 */
  CBCProtocal = "3",
  /** 建行协议 */
  CCBProtocal = "4",
  /** 交行协议 */
  BOCOMProtocal = "5",
  /** 银期转帐平台协议 */
  FBTPlateFormProtocal = "X",
}

/** 套接字连接方式类型 */
export enum ConnectModeType {
  /** 短连接 */
  ShortConnect = "0",
  /** 长连接 */
  LongConnect = "1",
}

/** 套接字通信方式类型 */
export enum SyncModeType {
  /** 异步 */
  ASync = "0",
  /** 同步 */
  Sync = "1",
}

/** 银行帐号类型类型 */
export enum BankAccType {
  /** 银行存折 */
  BankBook = "1",
  /** 储蓄卡 */
  SavingCard = "2",
  /** 信用卡 */
  CreditCard = "3",
}

/** 期货公司帐号类型类型 */
export enum FutureAccType {
  /** 银行存折 */
  BankBook = "1",
  /** 储蓄卡 */
  SavingCard = "2",
  /** 信用卡 */
  CreditCard = "3",
}

/** 接入机构状态类型 */
export enum OrganStatusType {
  /** 启用 */
  Ready = "0",
  /** 签到 */
  CheckIn = "1",
  /** 签退 */
  CheckOut = "2",
  /** 对帐文件到达 */
  CheckFileArrived = "3",
  /** 对帐 */
  CheckDetail = "4",
  /** 日终清理 */
  DayEndClean = "5",
  /** 注销 */
  Invalid = "9",
}

/** 建行收费模式类型 */
export enum CCBFeeModeType {
  /** 按金额扣收 */
  ByAmount = "1",
  /** 按月扣收 */
  ByMonth = "2",
}

/** 通讯API类型类型 */
export enum CommApiType {
  /** 客户端 */
  Client = "1",
  /** 服务端 */
  Server = "2",
  /** 交易系统的UserApi */
  UserApi = "3",
}

/** 连接状态类型 */
export enum LinkStatusType {
  /** 已经连接 */
  Connected = "1",
  /** 没有连接 */
  Disconnected = "2",
}

/** 密码核对标志类型 */
export enum PwdFlagType {
  /** 不核对 */
  NoCheck = "0",
  /** 明文核对 */
  BlankCheck = "1",
  /** 密文核对 */
  EncryptCheck = "2",
}

/** 期货帐号类型类型 */
export enum SecuAccType {
  /** 资金帐号 */
  AccountID = "1",
  /** 资金卡号 */
  CardID = "2",
  /** 上海股东帐号 */
  SHStockholderID = "3",
  /** 深圳股东帐号 */
  SZStockholderID = "4",
}

/** 转账交易状态类型 */
export enum TransferStatusType {
  /** 正常 */
  Normal = "0",
  /** 被冲正 */
  Repealed = "1",
}

/** 发起方类型 */
export enum SponsorType {
  /** 期商 */
  Broker = "0",
  /** 银行 */
  Bank = "1",
}

/** 请求响应类别类型 */
export enum ReqRspType {
  /** 请求 */
  Request = "0",
  /** 响应 */
  Response = "1",
}

/** 银期转帐用户事件类型类型 */
export enum FBTUserEventType {
  /** 签到 */
  SignIn = "0",
  /** 银行转期货 */
  FromBankToFuture = "1",
  /** 期货转银行 */
  FromFutureToBank = "2",
  /** 开户 */
  OpenAccount = "3",
  /** 销户 */
  CancelAccount = "4",
  /** 变更银行账户 */
  ChangeAccount = "5",
  /** 冲正银行转期货 */
  RepealFromBankToFuture = "6",
  /** 冲正期货转银行 */
  RepealFromFutureToBank = "7",
  /** 查询银行账户 */
  QueryBankAccount = "8",
  /** 查询期货账户 */
  QueryFutureAccount = "9",
  /** 签退 */
  SignOut = "A",
  /** 密钥同步 */
  SyncKey = "B",
  /** 预约开户 */
  ReserveOpenAccount = "C",
  /** 撤销预约开户 */
  CancelReserveOpenAccount = "D",
  /** 预约开户确认 */
  ReserveOpenAccountConfirm = "E",
  /** 其他 */
  Other = "Z",
}

/** 记录操作类型类型 */
export enum DBOperationType {
  /** 插入 */
  Insert = "0",
  /** 更新 */
  Update = "1",
  /** 删除 */
  Delete = "2",
}

/** 同步标记类型 */
export enum SyncFlagType {
  /** 已同步 */
  Yes = "0",
  /** 未同步 */
  No = "1",
}

/** 同步类型类型 */
export enum SyncType {
  /** 一次同步 */
  OneOffSync = "0",
  /** 定时同步 */
  TimerSync = "1",
  /** 定时完全同步 */
  TimerFullSync = "2",
}

/** 换汇方向类型 */
export enum ExDirectionType {
  /** 结汇 */
  Settlement = "0",
  /** 售汇 */
  Sale = "1",
}

/** 换汇成功标志类型 */
export enum FBEResultFlagType {
  /** 成功 */
  Success = "0",
  /** 账户余额不足 */
  InsufficientBalance = "1",
  /** 交易结果未知 */
  UnknownTrading = "8",
  /** 失败 */
  Fail = "x",
}

/** 换汇交易状态类型 */
export enum FBEExchStatusType {
  /** 正常 */
  Normal = "0",
  /** 交易重发 */
  ReExchange = "1",
}

/** 换汇文件标志类型 */
export enum FBEFileFlagType {
  /** 数据包 */
  DataPackage = "0",
  /** 文件 */
  File = "1",
}

/** 换汇已交易标志类型 */
export enum FBEAlreadyTradeType {
  /** 未交易 */
  NotTrade = "0",
  /** 已交易 */
  Trade = "1",
}

/** 银期换汇用户事件类型类型 */
export enum FBEUserEventType {
  /** 签到 */
  SignIn = "0",
  /** 换汇 */
  Exchange = "1",
  /** 换汇重发 */
  ReExchange = "2",
  /** 银行账户查询 */
  QueryBankAccount = "3",
  /** 换汇明细查询 */
  QueryExchDetial = "4",
  /** 换汇汇总查询 */
  QueryExchSummary = "5",
  /** 换汇汇率查询 */
  QueryExchRate = "6",
  /** 对账文件通知 */
  CheckBankAccount = "7",
  /** 签退 */
  SignOut = "8",
  /** 其他 */
  Other = "Z",
}

/** 换汇发送标志类型 */
export enum FBEReqFlagType {
  /** 未处理 */
  UnProcessed = "0",
  /** 等待发送 */
  WaitSend = "1",
  /** 发送成功 */
  SendSuccess = "2",
  /** 发送失败 */
  SendFailed = "3",
  /** 等待重发 */
  WaitReSend = "4",
}

/** 风险通知类型类型 */
export enum NotifyClassType {
  /** 正常 */
  NOERROR = "0",
  /** 警示 */
  Warn = "1",
  /** 追保 */
  Call = "2",
  /** 强平 */
  Force = "3",
  /** 穿仓 */
  CHUANCANG = "4",
  /** 异常 */
  Exception = "5",
}

/** 强平单类型类型 */
export enum ForceCloseType {
  /** 手工强平 */
  Manual = "0",
  /** 单一投资者辅助强平 */
  Single = "1",
  /** 批量投资者辅助强平 */
  Group = "2",
}

/** 风险通知途径类型 */
export enum RiskNotifyMethodType {
  /** 系统通知 */
  System = "0",
  /** 短信通知 */
  SMS = "1",
  /** 邮件通知 */
  EMail = "2",
  /** 人工通知 */
  Manual = "3",
}

/** 风险通知状态类型 */
export enum RiskNotifyStatusType {
  /** 未生成 */
  NotGen = "0",
  /** 已生成未发送 */
  Generated = "1",
  /** 发送失败 */
  SendError = "2",
  /** 已发送未接收 */
  SendOk = "3",
  /** 已接收未确认 */
  Received = "4",
  /** 已确认 */
  Confirmed = "5",
}

/** 风控用户操作事件类型 */
export enum RiskUserEventType {
  /** 导出数据 */
  ExportData = "0",
}

/** 条件单索引条件类型 */
export enum ConditionalOrderSortType {
  /** 使用最新价升序 */
  LastPriceAsc = "0",
  /** 使用最新价降序 */
  LastPriceDesc = "1",
  /** 使用卖价升序 */
  AskPriceAsc = "2",
  /** 使用卖价降序 */
  AskPriceDesc = "3",
  /** 使用买价升序 */
  BidPriceAsc = "4",
  /** 使用买价降序 */
  BidPriceDesc = "5",
}

/** 报送状态类型 */
export enum SendType {
  /** 未发送 */
  NoSend = "0",
  /** 已发送 */
  Sended = "1",
  /** 已生成 */
  Generated = "2",
  /** 报送失败 */
  SendFail = "3",
  /** 接收成功 */
  Success = "4",
  /** 接收失败 */
  Fail = "5",
  /** 取消报送 */
  Cancel = "6",
}

/** 交易编码状态类型 */
export enum ClientIDStatusType {
  /** 未申请 */
  NoApply = "1",
  /** 已提交申请 */
  Submited = "2",
  /** 已发送申请 */
  Sended = "3",
  /** 完成 */
  Success = "4",
  /** 拒绝 */
  Refuse = "5",
  /** 已撤销编码 */
  Cancel = "6",
}

/** 特有信息类型类型 */
export enum QuestionType {
  /** 单选 */
  Radio = "1",
  /** 多选 */
  Option = "2",
  /** 填空 */
  Blank = "3",
}

/** 业务类型类型 */
export enum BusinessType {
  /** 请求 */
  Request = "1",
  /** 应答 */
  Response = "2",
  /** 通知 */
  Notice = "3",
}

/** 监控中心返回码类型 */
export enum CfmmcReturnCodeType {
  /** 成功 */
  Success = "0",
  /** 该客户已经有流程在处理中 */
  Working = "1",
  /** 监控中客户资料检查失败 */
  InfoFail = "2",
  /** 监控中实名制检查失败 */
  IDCardFail = "3",
  /** 其他错误 */
  OtherFail = "4",
}

/** 客户类型类型 */
export enum ClientType {
  /** 所有 */
  All = "0",
  /** 个人 */
  Person = "1",
  /** 单位 */
  Company = "2",
  /** 其他 */
  Other = "3",
  /** 特殊法人 */
  SpecialOrgan = "4",
  /** 资管户 */
  Asset = "5",
}

/** 交易所编号类型 */
export enum ExchangeIDType {
  /** 上海期货交易所 */
  SHFE = "S",
  /** 郑州商品交易所 */
  CZCE = "Z",
  /** 大连商品交易所 */
  DCE = "D",
  /** 中国金融期货交易所 */
  CFFEX = "J",
  /** 上海国际能源交易中心股份有限公司 */
  INE = "N",
}

/** 交易编码类型类型 */
export enum ExClientIDType {
  /** 套保 */
  Hedge = "1",
  /** 套利 */
  Arbitrage = "2",
  /** 投机 */
  Speculation = "3",
}

/** 更新状态类型 */
export enum UpdateFlagType {
  /** 未更新 */
  NoUpdate = "0",
  /** 更新全部信息成功 */
  Success = "1",
  /** 更新全部信息失败 */
  Fail = "2",
  /** 更新交易编码成功 */
  TCSuccess = "3",
  /** 更新交易编码失败 */
  TCFail = "4",
  /** 已丢弃 */
  Cancel = "5",
}

/** 申请动作类型 */
export enum ApplyOperateIDType {
  /** 开户 */
  OpenInvestor = "1",
  /** 修改身份信息 */
  ModifyIDCard = "2",
  /** 修改一般信息 */
  ModifyNoIDCard = "3",
  /** 申请交易编码 */
  ApplyTradingCode = "4",
  /** 撤销交易编码 */
  CancelTradingCode = "5",
  /** 销户 */
  CancelInvestor = "6",
  /** 账户休眠 */
  FreezeAccount = "8",
  /** 激活休眠账户 */
  ActiveFreezeAccount = "9",
}

/** 申请状态类型 */
export enum ApplyStatusIDType {
  /** 未补全 */
  NoComplete = "1",
  /** 已提交 */
  Submited = "2",
  /** 已审核 */
  Checked = "3",
  /** 已拒绝 */
  Refused = "4",
  /** 已删除 */
  Deleted = "5",
}

/** 发送方式类型 */
export enum SendMethodType {
  /** 文件发送 */
  ByAPI = "1",
  /** 电子发送 */
  ByFile = "2",
}

/** 操作方法类型 */
export enum EventModeType {
  /** 增加 */
  ADD = "1",
  /** 修改 */
  UPDATE = "2",
  /** 删除 */
  DELETE = "3",
  /** 复核 */
  CHECK = "4",
  /** 复制 */
  COPY = "5",
  /** 注销 */
  CANCEL = "6",
  /** 冲销 */
  Reverse = "7",
}

/** 统一开户申请自动发送类型 */
export enum UOAAutoSendType {
  /** 自动发送并接收 */
  ASR = "1",
  /** 自动发送，不自动接收 */
  ASNR = "2",
  /** 不自动发送，自动接收 */
  NSAR = "3",
  /** 不自动发送，也不自动接收 */
  NSR = "4",
}

/** 流程ID类型 */
export enum FlowIDType {
  /** 投资者对应投资者组设置 */
  InvestorGroupFlow = "1",
  /** 投资者手续费率设置 */
  InvestorRate = "2",
  /** 投资者手续费率模板关系设置 */
  InvestorCommRateModel = "3",
}

/** 复核级别类型 */
export enum CheckLevelType {
  /** 零级复核 */
  Zero = "0",
  /** 一级复核 */
  One = "1",
  /** 二级复核 */
  Two = "2",
}

/** 复核级别类型 */
export enum CheckStatusType {
  /** 未复核 */
  Init = "0",
  /** 复核中 */
  Checking = "1",
  /** 已复核 */
  Checked = "2",
  /** 拒绝 */
  Refuse = "3",
  /** 作废 */
  Cancel = "4",
}

/** 生效状态类型 */
export enum UsedStatusType {
  /** 未生效 */
  Unused = "0",
  /** 已生效 */
  Used = "1",
  /** 生效失败 */
  Fail = "2",
}

/** 账户来源类型 */
export enum BankAcountOriginType {
  /** 手工录入 */
  ByAccProperty = "0",
  /** 银期转账 */
  ByFBTransfer = "1",
}

/** 结算单月报成交汇总方式类型 */
export enum MonthBillTradeSumType {
  /** 同日同合约 */
  ByInstrument = "0",
  /** 同日同合约同价格 */
  ByDayInsPrc = "1",
  /** 同合约 */
  ByDayIns = "2",
}

/** 银期交易代码枚举类型 */
export enum FBTTradeCodeEnumType {
  /** 银行发起银行转期货 */
  BankLaunchBankToBroker = "\u8E71",
  /** 期货发起银行转期货 */
  BrokerLaunchBankToBroker = "\u1511",
  /** 银行发起期货转银行 */
  BankLaunchBrokerToBank = "\u8E72",
  /** 期货发起期货转银行 */
  BrokerLaunchBrokerToBank = "\u1512",
}

/** 动态令牌类型类型 */
export enum OTPType {
  /** 无动态令牌 */
  NONE = "0",
  /** 时间令牌 */
  TOTP = "1",
}

/** 动态令牌状态类型 */
export enum OTPStatusType {
  /** 未使用 */
  Unused = "0",
  /** 已使用 */
  Used = "1",
  /** 注销 */
  Disuse = "2",
}

/** 经济公司用户类型类型 */
export enum BrokerUserType {
  /** 投资者 */
  Investor = "1",
  /** 操作员 */
  BrokerUser = "2",
}

/** 期货类型类型 */
export enum FutureType {
  /** 商品期货 */
  Commodity = "1",
  /** 金融期货 */
  Financial = "2",
}

/** 资金管理操作类型类型 */
export enum FundEventType {
  /** 转账限额 */
  Restriction = "0",
  /** 当日转账限额 */
  TodayRestriction = "1",
  /** 期商流水 */
  Transfer = "2",
  /** 资金冻结 */
  Credit = "3",
  /** 投资者可提资金比例 */
  InvestorWithdrawAlm = "4",
  /** 单个银行帐户转账限额 */
  BankRestriction = "5",
  /** 银期签约账户 */
  Accountregister = "6",
  /** 交易所出入金 */
  ExchangeFundIO = "7",
  /** 投资者出入金 */
  InvestorFundIO = "8",
}

/**  资金账户来源类型*/
export enum AccountSourceType {
  /** 银期同步 */
  FBTransfer = "0",
  /** 手工录入 */
  ManualEntry = "1",
}

/** 交易编码来源类型 */
export enum CodeSourceType {
  /** 统一开户(已规范) */
  UnifyAccount = "0",
  /** 手工录入(未规范) */
  ManualEntry = "1",
}

/** 操作员范围类型 */
export enum UserRangeType {
  /** 所有 */
  All = "0",
  /** 单一操作员 */
  Single = "1",
}

/** 交易统计表按客户统计方式类型 */
export enum ByGroupType {
  /** 按投资者统计 */
  Investor = "2",
  /** 按类统计 */
  Group = "1",
}

/** 交易统计表按范围统计方式类型 */
export enum TradeSumStatModeType {
  /** 按合约统计 */
  Instrument = "1",
  /** 按产品统计 */
  Product = "2",
  /** 按交易所统计 */
  Exchange = "3",
}

/** 日期表达式设置类型类型 */
export enum ExprSetModeType {
  /** 相对已有规则设置 */
  Relative = "1",
  /** 典型设置 */
  Typical = "2",
}

/** 投资者范围类型 */
export enum RateInvestorRangeType {
  /** 公司标准 */
  All = "1",
  /** 模板 */
  Model = "2",
  /** 单一投资者 */
  Single = "3",
}

/** 主次用系统数据同步状态类型 */
export enum SyncDataStatusType {
  /** 未同步 */
  Initialize = "0",
  /** 同步中 */
  Settlementing = "1",
  /** 已同步 */
  Settlemented = "2",
}

/** 成交来源类型 */
export enum TradeSourceType {
  /** 来自交易所普通回报 */
  NORMAL = "0",
  /** 来自查询 */
  QUERY = "1",
}

/** 产品合约统计方式类型 */
export enum FlexStatModeType {
  /** 产品统计 */
  Product = "1",
  /** 交易所统计 */
  Exchange = "2",
  /** 统计所有 */
  All = "3",
}

/** 投资者范围统计方式类型 */
export enum ByInvestorRangeType {
  /** 属性统计 */
  Property = "1",
  /** 统计所有 */
  All = "2",
}

/** 投资者范围类型 */
export enum PropertyInvestorRangeType {
  /** 所有 */
  All = "1",
  /** 投资者属性 */
  Property = "2",
  /** 单一投资者 */
  Single = "3",
}

/** 文件状态类型 */
export enum FileStatusType {
  /** 未生成 */
  NoCreate = "0",
  /** 已生成 */
  Created = "1",
  /** 生成失败 */
  Failed = "2",
}

/** 文件生成方式类型 */
export enum FileGenStyleType {
  /** 下发 */
  FileTransmit = "0",
  /** 生成 */
  FileGen = "1",
}

/** 系统日志操作方法类型 */
export enum SysOperModeType {
  /** 增加 */
  Add = "1",
  /** 修改 */
  Update = "2",
  /** 删除 */
  Delete = "3",
  /** 复制 */
  Copy = "4",
  /** 激活 */
  AcTive = "5",
  /** 注销 */
  CanCel = "6",
  /** 重置 */
  ReSet = "7",
}

/** 系统日志操作类型类型 */
export enum SysOperType {
  /** 修改操作员密码 */
  UpdatePassword = "0",
  /** 操作员组织架构关系 */
  UserDepartment = "1",
  /** 角色管理 */
  RoleManager = "2",
  /** 角色功能设置 */
  RoleFunction = "3",
  /** 基础参数设置 */
  BaseParam = "4",
  /** 设置操作员 */
  SetUserID = "5",
  /** 用户角色设置 */
  SetUserRole = "6",
  /** 用户IP限制 */
  UserIpRestriction = "7",
  /** 组织架构管理 */
  DepartmentManager = "8",
  /** 组织架构向查询分类复制 */
  DepartmentCopy = "9",
  /** 交易编码管理 */
  Tradingcode = "A",
  /** 投资者状态维护 */
  InvestorStatus = "B",
  /** 投资者权限管理 */
  InvestorAuthority = "C",
  /** 属性设置 */
  PropertySet = "D",
  /** 重置投资者密码 */
  ReSetInvestorPasswd = "E",
  /** 投资者个性信息维护 */
  InvestorPersonalityInfo = "F",
}

/** 上报数据查询类型类型 */
export enum CSRCDataQueyType {
  /** 查询当前交易日报送的数据 */
  Current = "0",
  /** 查询历史报送的代理经纪公司的数据 */
  History = "1",
}

/** 休眠状态类型 */
export enum FreezeStatusType {
  /** 活跃 */
  Normal = "1",
  /** 休眠 */
  Freeze = "0",
}

/** 规范状态类型 */
export enum StandardStatusType {
  /** 已规范 */
  Standard = "0",
  /** 未规范 */
  NonStandard = "1",
}

/** 配置类型类型 */
export enum RightParamType {
  /** 休眠户 */
  Freeze = "1",
  /** 激活休眠户 */
  FreezeActive = "2",
  /** 开仓权限限制 */
  OpenLimit = "3",
  /** 解除开仓权限限制 */
  RelieveOpenLimit = "4",
}

/** 反洗钱审核表数据状态类型 */
export enum DataStatusType {
  /** 正常 */
  Normal = "0",
  /** 已删除 */
  Deleted = "1",
}

/** 审核状态类型 */
export enum AMLCheckStatusType {
  /** 未复核 */
  Init = "0",
  /** 复核中 */
  Checking = "1",
  /** 已复核 */
  Checked = "2",
  /** 拒绝上报 */
  RefuseReport = "3",
}

/** 日期类型类型 */
export enum AmlDateType {
  /** 检查日期 */
  DrawDay = "0",
  /** 发生日期 */
  TouchDay = "1",
}

/** 审核级别类型 */
export enum AmlCheckLevelType {
  /** 零级审核 */
  CheckLevel0 = "0",
  /** 一级审核 */
  CheckLevel1 = "1",
  /** 二级审核 */
  CheckLevel2 = "2",
  /** 三级审核 */
  CheckLevel3 = "3",
}

/** 导出文件类型类型 */
export enum ExportFileType {
  /** CSV */
  CSV = "0",
  /** Excel */
  EXCEL = "1",
  /** DBF */
  DBF = "2",
}

/** 结算配置类型类型 */
export enum SettleManagerType {
  /** 结算前准备 */
  Before = "1",
  /** 结算 */
  Settlement = "2",
  /** 结算后核对 */
  After = "3",
  /** 结算后处理 */
  Settlemented = "4",
}

/** 结算配置等级类型 */
export enum SettleManagerLevelType {
  /** 必要 */
  Must = "1",
  /** 警告 */
  Alarm = "2",
  /** 提示 */
  Prompt = "3",
  /** 不检查 */
  Ignore = "4",
}

/** 模块分组类型 */
export enum SettleManagerGroupType {
  /** 交易所核对 */
  Exhcange = "1",
  /** 内部核对 */
  ASP = "2",
  /** 上报数据核对 */
  CSRC = "3",
}

/** 保值额度使用类型类型 */
export enum LimitUseType {
  /** 可重复使用 */
  Repeatable = "1",
  /** 不可重复使用 */
  Unrepeatable = "2",
}

/** 数据来源类型 */
export enum DataResourceType {
  /** 本系统 */
  Settle = "1",
  /** 交易所 */
  Exchange = "2",
  /** 报送数据 */
  CSRC = "3",
}

/** 保证金类型类型 */
export enum MarginType {
  /** 交易所保证金率 */
  ExchMarginRate = "0",
  /** 投资者保证金率 */
  InstrMarginRate = "1",
  /** 投资者交易保证金率 */
  InstrMarginRateTrade = "2",
}

/** 生效类型类型 */
export enum ActiveType {
  /** 仅当日生效 */
  Intraday = "1",
  /** 长期生效 */
  Long = "2",
}

/** 冲突保证金率类型类型 */
export enum MarginRateType {
  /** 交易所保证金率 */
  Exchange = "1",
  /** 投资者保证金率 */
  Investor = "2",
  /** 投资者交易保证金率 */
  InvestorTrade = "3",
}

/** 备份数据状态类型 */
export enum BackUpStatusType {
  /** 未生成备份数据 */
  UnBak = "0",
  /** 备份数据生成中 */
  BakUp = "1",
  /** 已生成备份数据 */
  BakUped = "2",
  /** 备份数据失败 */
  BakFail = "3",
}

/** 结算初始化状态类型 */
export enum InitSettlementType {
  /** 结算初始化未开始 */
  UnInitialize = "0",
  /** 结算初始化中 */
  Initialize = "1",
  /** 结算初始化完成 */
  Initialized = "2",
}

/** 报表数据生成状态类型 */
export enum ReportStatusType {
  /** 未生成报表数据 */
  NoCreate = "0",
  /** 报表数据生成中 */
  Create = "1",
  /** 已生成报表数据 */
  Created = "2",
  /** 生成报表数据失败 */
  CreateFail = "3",
}

/** 数据归档状态类型 */
export enum SaveStatusType {
  /** 归档未完成 */
  UnSaveData = "0",
  /** 归档完成 */
  SaveDatad = "1",
}

/** 结算确认数据归档状态类型 */
export enum SettArchiveStatusType {
  /** 未归档数据 */
  UnArchived = "0",
  /** 数据归档中 */
  Archiving = "1",
  /** 已归档数据 */
  Archived = "2",
  /** 归档数据失败 */
  ArchiveFail = "3",
}

/** CTP交易系统类型类型 */
export enum CTPType {
  /** 未知类型 */
  Unkown = "0",
  /** 主中心 */
  MainCenter = "1",
  /** 备中心 */
  BackUp = "2",
}

/** 平仓处理类型类型 */
export enum CloseDealType {
  /** 正常 */
  Normal = "0",
  /** 投机平仓优先 */
  SpecFirst = "1",
}

/** 货币质押资金可用范围类型 */
export enum MortgageFundUseRangeType {
  /** 不能使用 */
  None = "0",
  /** 用于保证金 */
  Margin = "1",
  /** 用于手续费、盈亏、保证金 */
  All = "2",
  /** 人民币方案3 */
  CNY3 = "3",
}

/** 特殊产品类型类型 */
export enum SpecProductType {
  /** 郑商所套保产品 */
  CzceHedge = "1",
  /** 货币质押产品 */
  IneForeignCurrency = "2",
  /** 大连短线开平仓产品 */
  DceOpenClose = "3",
}

/** 货币质押类型类型 */
export enum FundMortgageType {
  /** 质押 */
  Mortgage = "1",
  /** 解质 */
  Redemption = "2",
}

/** 投资者账户结算参数代码类型 */
export enum AccountSettlementParamIDType {
  /** 基础保证金 */
  BaseMargin = "1",
  /** 最低权益标准 */
  LowestInterest = "2",
}

/** 货币质押方向类型 */
export enum FundMortDirectionType {
  /** 货币质入 */
  In = "1",
  /** 货币质出 */
  Out = "2",
}

/** 换汇类别类型 */
export enum BusinessClassType {
  /** 盈利 */
  Profit = "0",
  /** 亏损 */
  Loss = "1",
  /** 其他 */
  Other = "Z",
}

/** 换汇数据来源类型 */
export enum SwapSourceType {
  /** 手工 */
  Manual = "0",
  /** 自动生成 */
  Automatic = "1",
}

/** 换汇类型类型 */
export enum CurrExDirectionType {
  /** 结汇 */
  Settlement = "0",
  /** 售汇 */
  Sale = "1",
}

/** 申请状态类型 */
export enum CurrencySwapStatusType {
  /** 已录入 */
  Entry = "1",
  /** 已审核 */
  Approve = "2",
  /** 已拒绝 */
  Refuse = "3",
  /** 已撤销 */
  Revoke = "4",
  /** 已发送 */
  Send = "5",
  /** 换汇成功 */
  Success = "6",
  /** 换汇失败 */
  Failure = "7",
}

/** 换汇发送标志类型 */
export enum ReqFlagType {
  /** 未发送 */
  NoSend = "0",
  /** 发送成功 */
  SendSuccess = "1",
  /** 发送失败 */
  SendFailed = "2",
  /** 等待重发 */
  WaitReSend = "3",
}

/** 换汇返回成功标志类型 */
export enum ResFlagType {
  /** 成功 */
  Success = "0",
  /** 账户余额不足 */
  InsuffiCient = "1",
  /** 交易结果未知 */
  UnKnown = "8",
}

/** 修改状态类型 */
export enum ExStatusType {
  /** 修改前 */
  Before = "0",
  /** 修改后 */
  After = "1",
}

/** 开户客户地域类型 */
export enum ClientRegionType {
  /** 国内客户 */
  Domestic = "1",
  /** 港澳台客户 */
  GMT = "2",
  /** 国外客户 */
  Foreign = "3",
}

/** 是否有董事会类型 */
export enum HasBoardType {
  /** 没有 */
  No = "0",
  /** 有 */
  Yes = "1",
}

/** 启动模式类型 */
export enum StartModeType {
  /** 正常 */
  Normal = "1",
  /** 应急 */
  Emerge = "2",
  /** 恢复 */
  Restore = "3",
}

/** 模型类型类型 */
export enum TemplateType {
  /** 全量 */
  Full = "1",
  /** 增量 */
  Increment = "2",
  /** 备份 */
  BackUp = "3",
}

/** 登录模式类型 */
export enum LoginModeType {
  /** 交易 */
  Trade = "0",
  /** 转账 */
  Transfer = "1",
}

/** 日历提示类型类型 */
export enum PromptType {
  /** 合约上下市 */
  Instrument = "1",
  /** 保证金分段生效 */
  Margin = "2",
}

/** 是否有托管人类型 */
export enum HasTrusteeType {
  /** 有 */
  Yes = "1",
  /** 没有 */
  No = "0",
}

/** 机构类型类型 */
export enum AmType {
  /** 银行 */
  Bank = "1",
  /** 证券公司 */
  Securities = "2",
  /** 基金公司 */
  Fund = "3",
  /** 保险公司 */
  Insurance = "4",
  /** 信托公司 */
  Trust = "5",
  /** 其他 */
  Other = "9",
}

/** 出入金类型类型 */
export enum CSRCFundIOType {
  /** 出入金 */
  FundIO = "0",
  /** 银期换汇 */
  SwapCurrency = "1",
}

/** 结算账户类型类型 */
export enum CusAccountType {
  /** 期货结算账户 */
  Futures = "1",
  /** 纯期货资管业务下的资管结算账户 */
  AssetmgrFuture = "2",
  /** 综合类资管业务下的期货资管托管账户 */
  AssetmgrTrustee = "3",
  /** 综合类资管业务下的资金中转账户 */
  AssetmgrTransfer = "4",
}

/** 通知语言类型类型 */
export enum LanguageType {
  /** 中文 */
  Chinese = "1",
  /** 英文 */
  English = "2",
}

/** 资产管理客户类型类型 */
export enum AssetmgrClientType {
  /** 个人资管客户 */
  Person = "1",
  /** 单位资管客户 */
  Organ = "2",
  /** 特殊单位资管客户 */
  SpecialOrgan = "4",
}

/** 投资类型类型 */
export enum AssetmgrType {
  /** 期货类 */
  Futures = "3",
  /** 综合类 */
  SpecialOrgan = "4",
}

/** 合约比较类型类型 */
export enum CheckInstrType {
  /** 合约交易所不存在 */
  HasExch = "0",
  /** 合约本系统不存在 */
  HasATP = "1",
  /** 合约比较不一致 */
  HasDiff = "2",
}

/** 交割类型类型 */
export enum DeliveryType {
  /** 手工交割 */
  HandDeliv = "1",
  /** 到期交割 */
  PersonDeliv = "2",
}

/** 大额单边保证金算法类型 */
export enum MaxMarginSideAlgorithmType {
  /** 不使用大额单边保证金算法 */
  NO = "0",
  /** 使用大额单边保证金算法 */
  YES = "1",
}

/** 资产管理客户类型类型 */
export enum DAClientType {
  /** 自然人 */
  Person = "0",
  /** 法人 */
  Company = "1",
  /** 其他 */
  Other = "2",
}

/** 投资类型类型 */
export enum UOAAssetmgrType {
  /** 期货类 */
  Futures = "1",
  /** 综合类 */
  SpecialOrgan = "2",
}

/** 买卖方向类型 */
export enum DirectionEnType {
  /** Buy */
  Buy = "0",
  /** Sell */
  Sell = "1",
}

/** 开平标志类型 */
export enum OffsetFlagEnType {
  /** Position Opening */
  Open = "0",
  /** Position Close */
  Close = "1",
  /** Forced Liquidation */
  ForceClose = "2",
  /** Close Today */
  CloseToday = "3",
  /** Close Prev. */
  CloseYesterday = "4",
  /** Forced Reduction */
  ForceOff = "5",
  /** Local Forced Liquidation */
  LocalForceClose = "6",
}

/** 投机套保标志类型 */
export enum HedgeFlagEnType {
  /** Speculation */
  Speculation = "1",
  /** Arbitrage */
  Arbitrage = "2",
  /** Hedge */
  Hedge = "3",
}

/** 出入金类型类型 */
export enum FundIOTypeEnType {
  /** Deposit/Withdrawal */
  FundIO = "1",
  /** Bank-Futures Transfer */
  Transfer = "2",
  /** Bank-Futures FX Exchange */
  SwapCurrency = "3",
}

/** 资金类型类型 */
export enum FundTypeEnType {
  /** Bank Deposit */
  Deposite = "1",
  /** Payment/Fee */
  ItemFund = "2",
  /** Brokerage Adj */
  Company = "3",
  /** Internal Transfer */
  InnerTransfer = "4",
}

/** 出入金方向类型 */
export enum FundDirectionEnType {
  /** Deposit */
  In = "1",
  /** Withdrawal */
  Out = "2",
}

/** 货币质押方向类型 */
export enum FundMortDirectionEnType {
  /** Pledge */
  In = "1",
  /** Redemption */
  Out = "2",
}

/** 期权类型类型 */
export enum OptionsType {
  /** 看涨 */
  CallOptions = "1",
  /** 看跌 */
  PutOptions = "2",
}

/** 执行方式类型 */
export enum StrikeModeType {
  /** 欧式 */
  Continental = "0",
  /** 美式 */
  American = "1",
  /** 百慕大 */
  Bermuda = "2",
}

/** 执行类型类型 */
export enum StrikeType {
  /** 自身对冲 */
  Hedge = "0",
  /** 匹配执行 */
  Match = "1",
}

/** 中金所期权放弃执行申请类型类型 */
export enum ApplyType {
  /** 不执行数量 */
  NotStrikeNum = "4",
}

/** 放弃执行申请数据来源类型 */
export enum GiveUpDataSourceType {
  /** 系统生成 */
  Gen = "0",
  /** 手工添加 */
  Hand = "1",
}

/** 执行结果类型 */
export enum ExecResultType {
  /** 没有执行 */
  NoExec = "n",
  /** 已经取消 */
  Canceled = "c",
  /** 执行成功 */
  OK = "0",
  /** 期权持仓不够 */
  NoPosition = "1",
  /** 资金不够 */
  NoDeposit = "2",
  /** 会员不存在 */
  NoParticipant = "3",
  /** 客户不存在 */
  NoClient = "4",
  /** 合约不存在 */
  NoInstrument = "6",
  /** 没有执行权限 */
  NoRight = "7",
  /** 不合理的数量 */
  InvalidVolume = "8",
  /** 没有足够的历史成交 */
  NoEnoughHistoryTrade = "9",
  /** 未知 */
  Unknown = "a",
}

/** 组合类型类型 */
export enum CombinationType {
  /** 期货组合 */
  Future = "0",
  /** 垂直价差BUL */
  BUL = "1",
  /** 垂直价差BER */
  BER = "2",
  /** 跨式组合 */
  STD = "3",
  /** 宽跨式组合 */
  STG = "4",
  /** 备兑组合 */
  PRT = "5",
  /** 时间价差组合 */
  CAS = "6",
  /** 期权对锁组合 */
  OPL = "7",
  /** 买备兑组合 */
  BFO = "8",
  /** 买入期权垂直价差组合 */
  BLS = "9",
  /** 卖出期权垂直价差组合 */
  BES = "a",
}

/** 组合类型类型 */
export enum DceCombinationType {
  /** 期货对锁组合 */
  SPL = "0",
  /** 期权对锁组合 */
  OPL = "1",
  /** 期货跨期组合 */
  SP = "2",
  /** 期货跨品种组合 */
  SPC = "3",
  /** 买入期权垂直价差组合 */
  BLS = "4",
  /** 卖出期权垂直价差组合 */
  BES = "5",
  /** 期权日历价差组合 */
  CAS = "6",
  /** 期权跨式组合 */
  STD = "7",
  /** 期权宽跨式组合 */
  STG = "8",
  /** 买入期货期权组合 */
  BFO = "9",
  /** 卖出期货期权组合 */
  SFO = "a",
}

/** 期权权利金价格类型类型 */
export enum OptionRoyaltyPriceType {
  /** 昨结算价 */
  PreSettlementPrice = "1",
  /** 开仓价 */
  OpenPrice = "4",
  /** 最新价与昨结算价较大值 */
  MaxPreSettlementPrice = "5",
}

/** 权益算法类型 */
export enum BalanceAlgorithmType {
  /** 不计算期权市值盈亏 */
  Default = "1",
  /** 计算期权市值亏损 */
  IncludeOptValLost = "2",
}

/** 执行类型类型 */
export enum ActionType {
  /** 执行 */
  Exec = "1",
  /** 放弃 */
  Abandon = "2",
}

/** 询价状态类型 */
export enum ForQuoteStatusType {
  /** 已经提交 */
  Submitted = "a",
  /** 已经接受 */
  Accepted = "b",
  /** 已经被拒绝 */
  Rejected = "c",
}

/** 取值方式类型 */
export enum ValueMethodType {
  /** 按绝对值 */
  Absolute = "0",
  /** 按比率 */
  Ratio = "1",
}

/** 期权行权后是否保留期货头寸的标记类型 */
export enum ExecOrderPositionFlagType {
  /** 保留 */
  Reserve = "0",
  /** 不保留 */
  UnReserve = "1",
}

/** 期权行权后生成的头寸是否自动平仓类型 */
export enum ExecOrderCloseFlagType {
  /** 自动平仓 */
  AutoClose = "0",
  /** 免于自动平仓 */
  NotToClose = "1",
}

/** 产品类型类型 */
export enum ProductType {
  /** 期货 */
  Futures = "1",
  /** 期权 */
  Options = "2",
}

/** 郑商所结算文件名类型 */
export enum CZCEUploadFileNameType {
  /** ^\d{8}_zz_\d{4} */
  O = "O",
  /** ^\d{8}成交表 */
  T = "T",
  /** ^\d{8}单腿持仓表new */
  P = "P",
  /** ^\d{8}非平仓了结表 */
  N = "N",
  /** ^\d{8}平仓表 */
  L = "L",
  /** ^\d{8}资金表 */
  F = "F",
  /** ^\d{8}组合持仓表 */
  C = "C",
  /** ^\d{8}保证金参数表 */
  M = "M",
}

/** 大商所结算文件名类型 */
export enum DCEUploadFileNameType {
  /** ^\d{8}_dl_\d{3} */
  O = "O",
  /** ^\d{8}_成交表 */
  T = "T",
  /** ^\d{8}_持仓表 */
  P = "P",
  /** ^\d{8}_资金结算表 */
  F = "F",
  /** ^\d{8}_优惠组合持仓明细表 */
  C = "C",
  /** ^\d{8}_持仓明细表 */
  D = "D",
  /** ^\d{8}_保证金参数表 */
  M = "M",
  /** ^\d{8}_期权执行表 */
  S = "S",
}

/** 上期所结算文件名类型 */
export enum SHFEUploadFileNameType {
  /** ^\d{4}_\d{8}_\d{8}_DailyFundChg */
  O = "O",
  /** ^\d{4}_\d{8}_\d{8}_Trade */
  T = "T",
  /** ^\d{4}_\d{8}_\d{8}_SettlementDetail */
  P = "P",
  /** ^\d{4}_\d{8}_\d{8}_Capital */
  F = "F",
}

/** 中金所结算文件名类型 */
export enum CFFEXUploadFileNameType {
  /** ^\d{4}_SG\d{1}_\d{8}_\d{1}_Trade */
  T = "T",
  /** ^\d{4}_SG\d{1}_\d{8}_\d{1}_SettlementDetail */
  P = "P",
  /** ^\d{4}_SG\d{1}_\d{8}_\d{1}_Capital */
  F = "F",
  /** ^\d{4}_SG\d{1}_\d{8}_\d{1}_OptionExec */
  S = "S",
}

/** 组合指令方向类型 */
export enum CombDirectionType {
  /** 申请组合 */
  Comb = "0",
  /** 申请拆分 */
  UnComb = "1",
  /** 操作员删组合单 */
  DelComb = "2",
}

/** 行权偏移类型类型 */
export enum StrikeOffsetType {
  /** 实值额 */
  RealValue = "1",
  /** 盈利额 */
  ProfitValue = "2",
  /** 实值比例 */
  RealRatio = "3",
  /** 盈利比例 */
  ProfitRatio = "4",
}

/** 预约开户状态类型 */
export enum ReserveOpenAccStasType {
  /** 等待处理中 */
  Processing = "0",
  /** 已撤销 */
  Cancelled = "1",
  /** 已开户 */
  Opened = "2",
  /** 无效请求 */
  Invalid = "3",
}

/** 弱密码来源类型 */
export enum WeakPasswordSourceType {
  /** 弱密码库 */
  Lib = "1",
  /** 手工录入 */
  Manual = "2",
}

/** 期权行权的头寸是否自对冲类型 */
export enum OptSelfCloseFlagType {
  /** 自对冲期权仓位 */
  CloseSelfOptionPosition = "1",
  /** 保留期权仓位 */
  ReserveOptionPosition = "2",
  /** 自对冲卖方履约后的期货仓位 */
  SellCloseSelfFuturePosition = "3",
  /** 保留卖方履约后的期货仓位 */
  ReserveFuturePosition = "4",
}

/** 业务类型类型 */
export enum BizType {
  /** 期货 */
  Future = "1",
  /** 证券 */
  Stock = "2",
}

/** 用户App类型类型 */
export enum AppType {
  /** 直连的投资者 */
  Investor = "1",
  /** 为每个投资者都创建连接的中继 */
  InvestorRelay = "2",
  /** 所有投资者共享一个操作员连接的中继 */
  OperatorRelay = "3",
  /** 未知 */
  UnKnown = "4",
}

/** 应答类型类型 */
export enum ResponseValueType {
  /** 检查成功 */
  Right = "0",
  /** 检查失败 */
  Refuse = "1",
}

/** OTC成交类型类型 */
export enum OTCTradeType {
  /** 大宗交易 */
  Block = "0",
  /** 期转现 */
  EFP = "1",
}

/** 期现风险匹配方式类型 */
export enum MatchType {
  /** 基点价值 */
  DV01 = "1",
  /** 面值 */
  ParValue = "2",
}

/** 用户终端认证方式类型 */
export enum AuthType {
  /** 白名单校验 */
  WHITE = "0",
  /** 黑名单校验 */
  BLACK = "1",
}

/** 合约分类方式类型 */
export enum ClassType {
  /** 所有合约 */
  ALL = "0",
  /** 期货、即期、期转现、Tas、金属指数合约 */
  FUTURE = "1",
  /** 期货、现货期权合约 */
  OPTION = "2",
  /** 组合合约 */
  COMB = "3",
}

/** 合约交易状态分类方式类型 */
export enum TradingType {
  /** 所有状态 */
  ALL = "0",
  /** 交易 */
  TRADE = "1",
  /** 非交易 */
  UNTRADE = "2",
}

/** 产品状态类型 */
export enum ProductStatusType {
  /** 可交易 */
  tradeable = "1",
  /** 不可交易 */
  untradeable = "2",
}

/** 追平状态类型 */
export enum SyncDeltaStatusType {
  /** 交易可读 */
  Readable = "1",
  /** 交易在读 */
  Reading = "2",
  /** 交易读取完成 */
  Readend = "3",
  /** 追平失败 交易本地状态结算不存在 */
  OptErr = "e",
}

/** 操作标志类型 */
export enum ActionDirectionType {
  /** 增加 */
  Add = "1",
  /** 删除 */
  Del = "2",
  /** 更新 */
  Upd = "3",
}

/** 撤单时选择席位算法类型 */
export enum OrderCancelAlgType {
  /** 轮询席位撤单 */
  Balance = "1",
  /** 优先原报单席位撤单 */
  OrigFirst = "2",
}

/** 开仓量限制粒度类型 */
export enum OpenLimitControlLevelType {
  /** 不控制 */
  None = "0",
  /** 产品级别 */
  Product = "1",
  /** 合约级别 */
  Inst = "2",
}

/** 报单频率控制粒度类型 */
export enum OrderFreqControlLevelType {
  /** 不控制 */
  None = "0",
  /** 产品级别 */
  Product = "1",
  /** 合约级别 */
  Inst = "2",
}

/** 枚举bool类型类型 */
export enum EnumBoolType {
  /** false */
  False = "0",
  /** true */
  True = "1",
}

/** 消息事件回调接口 */
export interface CallbackFunction {
  /** 消息对象(不同消息事件，相应的对象也不同) */
  (message?: number | object): void;
}

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
