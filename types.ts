/*
 * types.ts
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

import type { MessageFields, RspInfoField } from "@napi-ctp/types";

/** 行情消息事件 */
export type MarketDataEvent =
  /** 当客户端与交易后台建立起通信连接时（还未登录前） */
  | "front-connected"
  /** 当客户端与交易后台通信连接断开时。当发生这个情况后，API会自动重新连接，客户端可不做处理 */
  | "front-disconnected"
  /** 心跳超时警告。当长时间未收到报文时 */
  | "heart-beat-warning"
  /** 登录请求响应 */
  | "rsp-user-login"
  /** 登出请求响应 */
  | "rsp-user-logout"
  /** 请求查询组播合约响应 */
  | "rsp-qry-multicast-instrument"
  /** 错误应答 */
  | "rsp-error"
  /** 订阅行情应答 */
  | "rsp-sub-market-data"
  /** 取消订阅行情应答 */
  | "rsp-unsub-market-data"
  /** 订阅询价应答 */
  | "rsp-sub-for-quote"
  /** 取消订阅询价应答 */
  | "rsp-unsub-for-quote"
  /** 深度行情通知 */
  | "rtn-depth-market-data"
  /** 询价通知 */
  | "rtn-for-quote";

/** 交易消息事件 */
export type TraderEvent =
  /** 当客户端与交易后台建立起通信连接时（还未登录前） */
  | "front-connected"
  /** 当客户端与交易后台通信连接断开时。当发生这个情况后，API会自动重新连接，客户端可不做处理 */
  | "front-disconnected"
  /** 心跳超时警告。当长时间未收到报文时 */
  | "heart-beat-warning"
  /** 客户端认证响应 */
  | "rsp-authenticate"
  /** 登录请求响应 */
  | "rsp-user-login"
  /** 登出请求响应 */
  | "rsp-user-logout"
  /** 用户口令更新请求响应 */
  | "rsp-user-password-update"
  /** 资金账户口令更新请求响应 */
  | "rsp-trading-account-password-update"
  /** 查询用户当前支持的认证模式的回复 */
  | "rsp-user-auth-method"
  /** 获取图形验证码请求的回复 */
  | "rsp-gen-user-captcha"
  /** 获取短信验证码请求的回复 */
  | "rsp-gen-user-text"
  /** 报单录入请求响应 */
  | "rsp-order-insert"
  /** 预埋单录入请求响应 */
  | "rsp-parked-order-insert"
  /** 预埋撤单录入请求响应 */
  | "rsp-parked-order-action"
  /** 报单操作请求响应 */
  | "rsp-order-action"
  /** 查询最大报单数量响应 */
  | "rsp-qry-max-order-volume"
  /** 投资者结算结果确认响应 */
  | "rsp-settlement-info-confirm"
  /** 删除预埋单响应 */
  | "rsp-remove-parked-order"
  /** 删除预埋撤单响应 */
  | "rsp-remove-parked-order-action"
  /** 执行宣告录入请求响应 */
  | "rsp-exec-order-insert"
  /** 执行宣告操作请求响应 */
  | "rsp-exec-order-action"
  /** 询价录入请求响应 */
  | "rsp-for-quote-insert"
  /** 报价录入请求响应 */
  | "rsp-quote-insert"
  /** 报价操作请求响应 */
  | "rsp-quote-action"
  /** 批量报单操作请求响应 */
  | "rsp-batch-order-action"
  /** 期权自对冲录入请求响应 */
  | "rsp-option-self-close-insert"
  /** 期权自对冲操作请求响应 */
  | "rsp-option-self-close-action"
  /** 申请组合录入请求响应 */
  | "rsp-comb-action-insert"
  /** 请求查询报单响应 */
  | "rsp-qry-order"
  /** 请求查询成交响应 */
  | "rsp-qry-trade"
  /** 请求查询投资者持仓响应 */
  | "rsp-qry-investor-position"
  /** 请求查询资金账户响应 */
  | "rsp-qry-trading-account"
  /** 请求查询投资者响应 */
  | "rsp-qry-investor"
  /** 请求查询交易编码响应 */
  | "rsp-qry-trading-code"
  /** 请求查询合约保证金率响应 */
  | "rsp-qry-instrument-margin-rate"
  /** 请求查询合约手续费率响应 */
  | "rsp-qry-instrument-commission-rate"
  /** 请求查询交易所响应 */
  | "rsp-qry-exchange"
  /** 请求查询产品响应 */
  | "rsp-qry-product"
  /** 请求查询合约响应 */
  | "rsp-qry-instrument"
  /** 请求查询行情响应 */
  | "rsp-qry-depth-market-data"
  /** 请求查询交易员报盘机响应 */
  | "rsp-qry-trader-offer"
  /** 请求查询投资者结算结果响应 */
  | "rsp-qry-settlement-info"
  /** 请求查询转帐银行响应 */
  | "rsp-qry-transfer-bank"
  /** 请求查询投资者持仓明细响应 */
  | "rsp-qry-investor-position-detail"
  /** 请求查询客户通知响应 */
  | "rsp-qry-notice"
  /** 请求查询结算信息确认响应 */
  | "rsp-qry-settlement-info-confirm"
  /** 请求查询投资者持仓明细响应 */
  | "rsp-qry-investor-position-combine-detail"
  /** 查询保证金监管系统经纪公司资金账户密钥响应 */
  | "rsp-qry-cfmmc-trading-account-key"
  /** 请求查询仓单折抵信息响应 */
  | "rsp-qry-e-warrant-offset"
  /** 请求查询投资者品种/跨品种保证金响应 */
  | "rsp-qry-investor-product-group-margin"
  /** 请求查询交易所保证金率响应 */
  | "rsp-qry-exchange-margin-rate"
  /** 请求查询交易所调整保证金率响应 */
  | "rsp-qry-exchange-margin-rate-adjust"
  /** 请求查询汇率响应 */
  | "rsp-qry-exchange-rate"
  /** 请求查询二级代理操作员银期权限响应 */
  | "rsp-qry-sec-agent-acid-map"
  /** 请求查询产品报价汇率 */
  | "rsp-qry-product-exch-rate"
  /** 请求查询产品组 */
  | "rsp-qry-product-group"
  /** 请求查询做市商合约手续费率响应 */
  | "rsp-qry-mm-instrument-commission-rate"
  /** 请求查询做市商期权合约手续费响应 */
  | "rsp-qry-mm-option-instr-comm-rate"
  /** 请求查询报单手续费响应 */
  | "rsp-qry-instrument-order-comm-rate"
  /** 请求查询资金账户响应 */
  | "rsp-qry-sec-agent-trading-account"
  /** 请求查询二级代理商资金校验模式响应 */
  | "rsp-qry-sec-agent-check-mode"
  /** 请求查询二级代理商信息响应 */
  | "rsp-qry-sec-agent-trade-info"
  /** 请求查询期权交易成本响应 */
  | "rsp-qry-option-instr-trade-cost"
  /** 请求查询期权合约手续费响应 */
  | "rsp-qry-option-instr-comm-rate"
  /** 请求查询执行宣告响应 */
  | "rsp-qry-exec-order"
  /** 请求查询询价响应 */
  | "rsp-qry-for-quote"
  /** 请求查询报价响应 */
  | "rsp-qry-quote"
  /** 请求查询期权自对冲响应 */
  | "rsp-qry-option-self-close"
  /** 请求查询投资单元响应 */
  | "rsp-qry-invest-unit"
  /** 请求查询组合合约安全系数响应 */
  | "rsp-qry-comb-instrument-guard"
  /** 请求查询申请组合响应 */
  | "rsp-qry-comb-action"
  /** 请求查询转帐流水响应 */
  | "rsp-qry-transfer-serial"
  /** 请求查询银期签约关系响应 */
  | "rsp-qry-account-register"
  /** 错误应答 */
  | "rsp-error"
  /** 报单通知 */
  | "rtn-order"
  /** 成交通知 */
  | "rtn-trade"
  /** 报单录入错误回报 */
  | "err-rtn-order-insert"
  /** 报单操作错误回报 */
  | "err-rtn-order-action"
  /** 合约交易状态通知 */
  | "rtn-instrument-status"
  /** 交易所公告通知 */
  | "rtn-bulletin"
  /** 交易通知 */
  | "rtn-trading-notice"
  /** 提示条件单校验错误 */
  | "rtn-error-conditional-order"
  /** 执行宣告通知 */
  | "rtn-exec-order"
  /** 执行宣告录入错误回报 */
  | "err-rtn-exec-order-insert"
  /** 执行宣告操作错误回报 */
  | "err-rtn-exec-order-action"
  /** 询价录入错误回报 */
  | "err-rtn-for-quote-insert"
  /** 报价通知 */
  | "rtn-quote"
  /** 报价录入错误回报 */
  | "err-rtn-quote-insert"
  /** 报价操作错误回报 */
  | "err-rtn-quote-action"
  /** 询价通知 */
  | "rtn-for-quote"
  /** 保证金监控中心用户令牌 */
  | "rtn-cfmmc-trading-account-token"
  /** 批量报单操作错误回报 */
  | "err-rtn-batch-order-action"
  /** 期权自对冲通知 */
  | "rtn-option-self-close"
  /** 期权自对冲录入错误回报 */
  | "err-rtn-option-self-close-insert"
  /** 期权自对冲操作错误回报 */
  | "err-rtn-option-self-close-action"
  /** 申请组合通知 */
  | "rtn-comb-action"
  /** 申请组合录入错误回报 */
  | "err-rtn-comb-action-insert"
  /** 请求查询签约银行响应 */
  | "rsp-qry-contract-bank"
  /** 请求查询预埋单响应 */
  | "rsp-qry-parked-order"
  /** 请求查询预埋撤单响应 */
  | "rsp-qry-parked-order-action"
  /** 请求查询交易通知响应 */
  | "rsp-qry-trading-notice"
  /** 请求查询经纪公司交易参数响应 */
  | "rsp-qry-broker-trading-params"
  /** 请求查询经纪公司交易算法响应 */
  | "rsp-qry-broker-trading-algos"
  /** 银行发起银行资金转期货通知 */
  | "rtn-from-bank-to-future-by-bank"
  /** 银行发起期货资金转银行通知 */
  | "rtn-from-future-to-bank-by-bank"
  /** 银行发起冲正银行转期货通知 */
  | "rtn-repeal-from-bank-to-future-by-bank"
  /** 银行发起冲正期货转银行通知 */
  | "rtn-repeal-from-future-to-bank-by-bank"
  /** 期货发起银行资金转期货通知 */
  | "rtn-from-bank-to-future-by-future"
  /** 期货发起期货资金转银行通知 */
  | "rtn-from-future-to-bank-by-future"
  /** 系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知 */
  | "rtn-repeal-from-bank-to-future-by-future-manual"
  /** 系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知 */
  | "rtn-repeal-from-future-to-bank-by-future-manual"
  /** 期货发起查询银行余额通知 */
  | "rtn-query-bank-balance-by-future"
  /** 期货发起银行资金转期货错误回报 */
  | "err-rtn-bank-to-future-by-future"
  /** 期货发起期货资金转银行错误回报 */
  | "err-rtn-future-to-bank-by-future"
  /** 系统运行时期货端手工发起冲正银行转期货错误回报 */
  | "err-rtn-repeal-bank-to-future-by-future-manual"
  /** 系统运行时期货端手工发起冲正期货转银行错误回报 */
  | "err-rtn-repeal-future-to-bank-by-future-manual"
  /** 期货发起查询银行余额错误回报 */
  | "err-rtn-query-bank-balance-by-future"
  /** 期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知 */
  | "rtn-repeal-from-bank-to-future-by-future"
  /** 期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知 */
  | "rtn-repeal-from-future-to-bank-by-future"
  /** 期货发起银行资金转期货应答 */
  | "rsp-from-bank-to-future-by-future"
  /** 期货发起期货资金转银行应答 */
  | "rsp-from-future-to-bank-by-future"
  /** 期货发起查询银行余额应答 */
  | "rsp-query-bank-account-money-by-future"
  /** 银行发起银期开户通知 */
  | "rtn-open-account-by-bank"
  /** 银行发起银期销户通知 */
  | "rtn-cancel-account-by-bank"
  /** 银行发起变更银行账号通知 */
  | "rtn-change-account-by-bank"
  /** 请求查询分类合约响应 */
  | "rsp-qry-classified-instrument"
  /** 请求组合优惠比例响应 */
  | "rsp-qry-comb-promotion-param"
  /** 投资者风险结算持仓查询响应 */
  | "rsp-qry-risk-settle-invst-position"
  /** 风险结算产品查询响应 */
  | "rsp-qry-risk-settle-product-status";

/** 回调消息类型 */
export type CallbackMessage = undefined | number | MessageFields;

/** 回调消息信息 */
export type CallbackOptions = {
  /** 请求时产生的唯一编号 */
  requestId?: number;
  /** 是否为该请求的最后一条消息 */
  isLast?: boolean;
  /** CTP 返回的错误信息 */
  rspInfo?: RspInfoField;
};

/** 消息事件回调接口 */
export type CallbackFunction<T extends CallbackMessage> = (
  message: T,
  options: CallbackOptions
) => void;
