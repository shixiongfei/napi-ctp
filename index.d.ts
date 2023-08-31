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

export * from "./types";
import { MarketDataEvent, TraderEvent, CallbackFunction } from "./types";

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
  reqUserLogin(req?: object): number;

  /**
   * 用户登出请求
   * @param req 用户登出信息
   */
  reqUserLogout(req?: object): number;

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
   * 获取当前交易日
   * @returns 获取到的交易日
   */
  getTradingDay(): string;

  /**
   * 客户端认证请求
   * @param req 客户端认证信息
   */
  reqAuthenticate(req?: object): number;

  /**
   * 用户登录请求
   * @param req 用户登陆信息
   */
  reqUserLogin(req?: object): number;

  /**
   * 用户登出请求
   * @param req 用户登出信息
   */
  reqUserLogout(req?: object): number;

  /**
   * 用户口令更新请求
   * @param req 用户口令信息
   */
  reqUserPasswordUpdate(req?: object): number;

  /**
   * 资金账户口令更新请求
   * @param req 用户口令信息
   */
  reqTradingAccountPasswordUpdate(req?: object): number;

  /**
   * 查询用户当前支持的认证模式
   * @param req 用户信息
   */
  reqUserAuthMethod(req?: object): number;

  /**
   * 用户发出获取图形验证码请求
   * @param req 用户信息
   */
  reqGenUserCaptcha(req?: object): number;

  /**
   * 用户发出获取短信验证码请求
   * @param req 用户信息
   */
  reqGenUserText(req?: object): number;

  /**
   * 用户发出带有图片验证码的登陆请求
   * @param req 用户登陆信息
   */
  reqUserLoginWithCaptcha(req?: object): number;

  /**
   * 用户发出带有短信验证码的登陆请求
   * @param req 用户登陆信息
   */
  reqUserLoginWithText(req?: object): number;

  /**
   * 用户发出带有动态口令的登陆请求
   * @param req 用户登陆信息
   */
  reqUserLoginWithOTP(req?: object): number;

  /**
   * 报单录入请求
   * @param req 报单信息
   */
  reqOrderInsert(req?: object): number;

  /**
   * 预埋单录入请求
   * @param req 预埋单信息
   */
  reqParkedOrderInsert(req?: object): number;

  /**
   * 预埋撤单录入请求
   * @param req 预埋单信息
   */
  reqParkedOrderAction(req?: object): number;

  /**
   * 报单操作请求
   * @param req 报单信息
   */
  reqOrderAction(req?: object): number;

  /**
   * 查询最大报单数量请求
   * @param req 查询最大报单数量
   */
  reqQryMaxOrderVolume(req?: object): number;

  /**
   * 投资者结算结果确认
   * @param req 投资者结算结果确认信息
   */
  reqSettlementInfoConfirm(req?: object): number;

  /**
   * 请求删除预埋单
   * @param req 预埋单信息
   */
  reqRemoveParkedOrder(req?: object): number;

  /**
   * 请求删除预埋撤单
   * @param req 预埋单信息
   */
  reqRemoveParkedOrderAction(req?: object): number;

  /**
   * 执行宣告录入请求
   * @param req 宣告信息
   */
  reqExecOrderInsert(req?: object): number;

  /**
   * 执行宣告操作请求
   * @param req 宣告信息
   */
  reqExecOrderAction(req?: object): number;

  /**
   * 询价录入请求
   * @param req 询价信息
   */
  reqForQuoteInsert(req?: object): number;

  /**
   * 报价录入请求
   * @param req 报价信息
   */
  reqQuoteInsert(req?: object): number;

  /**
   * 报价操作请求
   * @param req 报价信息
   */
  reqQuoteAction(req?: object): number;

  /**
   * 批量报单操作请求
   * @param req 报单请求
   */
  reqBatchOrderAction(req?: object): number;

  /**
   * 期权自对冲录入请求
   * @param req 期权自对冲信息
   */
  reqOptionSelfCloseInsert(req?: object): number;

  /**
   * 期权自对冲操作请求
   * @param req 期权自对冲信息
   */
  reqOptionSelfCloseAction(req?: object): number;

  /**
   * 申请组合录入请求
   * @param req 组合信息
   */
  reqCombActionInsert(req?: object): number;

  /**
   * 请求查询报单
   * @param req 查询信息
   */
  reqQryOrder(req?: object): number;

  /**
   * 请求查询成交
   * @param req 查询信息
   */
  reqQryTrade(req?: object): number;

  /**
   * 请求查询投资者持仓
   * @param req 查询信息
   */
  reqQryInvestorPosition(req?: object): number;

  /**
   * 请求查询资金账户
   * @param req 查询信息
   */
  reqQryTradingAccount(req?: object): number;

  /**
   * 请求查询投资者
   * @param req 查询信息
   */
  reqQryInvestor(req?: object): number;

  /**
   * 请求查询交易编码
   * @param req 查询信息
   */
  reqQryTradingCode(req?: object): number;

  /**
   * 请求查询合约保证金率
   * @param req 查询信息
   */
  reqQryInstrumentMarginRate(req?: object): number;

  /**
   * 请求查询合约手续费率
   * @param req 查询信息
   */
  reqQryInstrumentCommissionRate(req?: object): number;

  /**
   * 请求查询交易所
   * @param req 查询信息
   */
  reqQryExchange(req?: object): number;

  /**
   * 请求查询产品
   * @param req 查询信息
   */
  reqQryProduct(req?: object): number;

  /**
   * 请求查询合约
   * @param req 查询信息
   */
  reqQryInstrument(req?: object): number;

  /**
   * 请求查询行情
   * @param req 查询信息
   */
  reqQryDepthMarketData(req?: object): number;

  /**
   * 请求查询交易员报盘机
   * @param req 查询信息
   */
  reqQryTraderOffer(req?: object): number;

  /**
   * 请求查询投资者结算结果
   * @param req 查询信息
   */
  reqQrySettlementInfo(req?: object): number;

  /**
   * 请求查询转帐银行
   * @param req 转账信息
   */
  reqQryTransferBank(req?: object): number;

  /**
   * 请求查询投资者持仓明细
   * @param req 查询信息
   */
  reqQryInvestorPositionDetail(req?: object): number;

  /**
   * 请求查询客户通知
   * @param req 查询信息
   */
  reqQryNotice(req?: object): number;

  /**
   * 请求查询结算信息确认
   * @param req 查询信息
   */
  reqQrySettlementInfoConfirm(req?: object): number;

  /**
   * 请求查询投资者持仓明细
   * @param req 查询信息
   */
  reqQryInvestorPositionCombineDetail(req?: object): number;

  /**
   * 请求查询保证金监管系统经纪公司资金账户密钥
   * @param req 查询信息
   */
  reqQryCFMMCTradingAccountKey(req?: object): number;

  /**
   * 请求查询仓单折抵信息
   * @param req 查询信息
   */
  reqQryEWarrantOffset(req?: object): number;

  /**
   * 请求查询投资者品种/跨品种保证金
   * @param req 查询信息
   */
  reqQryInvestorProductGroupMargin(req?: object): number;

  /**
   * 请求查询交易所保证金率
   * @param req 查询信息
   */
  reqQryExchangeMarginRate(req?: object): number;

  /**
   * 请求查询交易所调整保证金率
   * @param req 查询信息
   */
  reqQryExchangeMarginRateAdjust(req?: object): number;

  /**
   * 请求查询汇率
   * @param req 查询信息
   */
  reqQryExchangeRate(req?: object): number;

  /**
   * 请求查询二级代理操作员银期权限
   * @param req 查询信息
   */
  reqQrySecAgentACIDMap(req?: object): number;

  /**
   * 请求查询产品报价汇率
   * @param req 查询信息
   */
  reqQryProductExchRate(req?: object): number;

  /**
   * 请求查询产品组
   * @param req 查询信息
   */
  reqQryProductGroup(req?: object): number;

  /**
   * 请求查询做市商合约手续费率
   * @param req 查询信息
   */
  reqQryMMInstrumentCommissionRate(req?: object): number;

  /**
   * 请求查询做市商期权合约手续费
   * @param req 查询信息
   */
  reqQryMMOptionInstrCommRate(req?: object): number;

  /**
   * 请求查询报单手续费
   * @param req 查询信息
   */
  reqQryInstrumentOrderCommRate(req?: object): number;

  /**
   * 请求查询资金账户
   * @param req 查询信息
   */
  reqQrySecAgentTradingAccount(req?: object): number;

  /**
   * 请求查询二级代理商资金校验模式
   * @param req 查询信息
   */
  reqQrySecAgentCheckMode(req?: object): number;

  /**
   * 请求查询二级代理商信息
   * @param req 查询信息
   */
  reqQrySecAgentTradeInfo(req?: object): number;

  /**
   * 请求查询期权交易成本
   * @param req 查询信息
   */
  reqQryOptionInstrTradeCost(req?: object): number;

  /**
   * 请求查询期权合约手续费
   * @param req 查询信息
   */
  reqQryOptionInstrCommRate(req?: object): number;

  /**
   * 请求查询执行宣告
   * @param req 查询信息
   */
  reqQryExecOrder(req?: object): number;

  /**
   * 请求查询询价
   * @param req 查询信息
   */
  reqQryForQuote(req?: object): number;

  /**
   * 请求查询报价
   * @param req 查询信息
   */
  reqQryQuote(req?: object): number;

  /**
   * 请求查询期权自对冲
   * @param req 查询信息
   */
  reqQryOptionSelfClose(req?: object): number;

  /**
   * 请求查询投资单元
   * @param req 查询信息
   */
  reqQryInvestUnit(req?: object): number;

  /**
   * 请求查询组合合约安全系数
   * @param req 查询信息
   */
  reqQryCombInstrumentGuard(req?: object): number;

  /**
   * 请求查询申请组合
   * @param req 查询信息
   */
  reqQryCombAction(req?: object): number;

  /**
   * 请求查询转帐流水
   * @param req 查询信息
   */
  reqQryTransferSerial(req?: object): number;

  /**
   * 请求查询银期签约关系
   * @param req 查询信息
   */
  reqQryAccountregister(req?: object): number;

  /**
   * 请求查询签约银行
   * @param req 查询信息
   */
  reqQryContractBank(req?: object): number;

  /**
   * 请求查询预埋单
   * @param req 查询信息
   */
  reqQryParkedOrder(req?: object): number;

  /**
   * 请求查询预埋撤单
   * @param req 查询信息
   */
  reqQryParkedOrderAction(req?: object): number;

  /**
   * 请求查询交易通知
   * @param req 查询信息
   */
  reqQryTradingNotice(req?: object): number;

  /**
   * 请求查询经纪公司交易参数
   * @param req 查询信息
   */
  reqQryBrokerTradingParams(req?: object): number;

  /**
   * 请求查询经纪公司交易算法
   * @param req 查询信息
   */
  reqQryBrokerTradingAlgos(req?: object): number;

  /**
   * 请求查询监控中心用户令牌
   * @param req 查询信息
   */
  reqQueryCFMMCTradingAccountToken(req?: object): number;

  /**
   * 期货发起银行资金转期货请求
   * @param req 查询信息
   */
  reqFromBankToFutureByFuture(req?: object): number;

  /**
   * 期货发起期货资金转银行请求
   * @param req 查询信息
   */
  reqFromFutureToBankByFuture(req?: object): number;

  /**
   * 期货发起查询银行余额请求
   * @param req 查询信息
   */
  reqQueryBankAccountMoneyByFuture(req?: object): number;

  /**
   * 请求查询分类合约
   * @param req 查询信息
   */
  reqQryClassifiedInstrument(req?: object): number;

  /**
   * 请求组合优惠比例
   * @param req 查询信息
   */
  reqQryCombPromotionParam(req?: object): number;

  /**
   * 投资者风险结算持仓查询
   * @param req 查询信息
   */
  reqQryRiskSettleInvstPosition(req?: object): number;

  /**
   * 风险结算产品查询
   * @param req 查询信息
   */
  reqQryRiskSettleProductStatus(req?: object): number;

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

/**
 * 获取最后请求序列ID
 * @returns 序列ID
 */
export declare function getLastRequestId(): number;
