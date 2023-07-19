/*
 * ctpmsg.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __CTPMSG_H__
#define __CTPMSG_H__

#include "napi_ctp.h"
#include <map>

typedef napi_status (*MessageHandler)(napi_env env, const Message *message, napi_value *result);
typedef std::map<int, MessageHandler> MessageFuncs;

napi_status getMessageValue(napi_env env, const MessageFuncs &messageFuncs, const Message *message, napi_value *result);
napi_status getMessageOptions(napi_env env, const Message *message, napi_value *result);

napi_status msgQuit(napi_env env, const Message *message, napi_value *result);
napi_status msgFrontConnected(napi_env env, const Message *message, napi_value *result);
napi_status msgFrontDisconnected(napi_env env, const Message *message, napi_value *result);
napi_status msgHeartBeatWarning(napi_env env, const Message *message, napi_value *result);
napi_status rspUserLogin(napi_env env, const Message *message, napi_value *result);
napi_status rspUserLogout(napi_env env, const Message *message, napi_value *result);
napi_status rspQryMulticastInstrument(napi_env env, const Message *message, napi_value *result);
napi_status rspError(napi_env env, const Message *message, napi_value *result);
napi_status rspSubMarketData(napi_env env, const Message *message, napi_value *result);
napi_status rspUnSubMarketData(napi_env env, const Message *message, napi_value *result);
napi_status rspSubForQuote(napi_env env, const Message *message, napi_value *result);
napi_status rspUnSubForQuote(napi_env env, const Message *message, napi_value *result);
napi_status rtnDepthMarketData(napi_env env, const Message *message, napi_value *result);
napi_status rtnForQuote(napi_env env, const Message *message, napi_value *result);
napi_status rspAuthenticate(napi_env env, const Message *message, napi_value *result);
napi_status rspUserPasswordUpdate(napi_env env, const Message *message, napi_value *result);
napi_status rspTradingAccountPasswordUpdate(napi_env env, const Message *message, napi_value *result);
napi_status rspUserAuthMethod(napi_env env, const Message *message, napi_value *result);
napi_status rspGenUserCaptcha(napi_env env, const Message *message, napi_value *result);
napi_status rspGenUserText(napi_env env, const Message *message, napi_value *result);
napi_status rspOrderInsert(napi_env env, const Message *message, napi_value *result);
napi_status rspParkedOrderInsert(napi_env env, const Message *message, napi_value *result);
napi_status rspParkedOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status rspOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status rspQryMaxOrderVolume(napi_env env, const Message *message, napi_value *result);
napi_status rspSettlementInfoConfirm(napi_env env, const Message *message, napi_value *result);
napi_status rspRemoveParkedOrder(napi_env env, const Message *message, napi_value *result);
napi_status rspRemoveParkedOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status rspExecOrderInsert(napi_env env, const Message *message, napi_value *result);
napi_status rspExecOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status rspForQuoteInsert(napi_env env, const Message *message, napi_value *result);
napi_status rspQuoteInsert(napi_env env, const Message *message, napi_value *result);
napi_status rspQuoteAction(napi_env env, const Message *message, napi_value *result);
napi_status rspBatchOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status rspOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result);
napi_status rspOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result);
napi_status rspCombActionInsert(napi_env env, const Message *message, napi_value *result);
napi_status rspQryOrder(napi_env env, const Message *message, napi_value *result);
napi_status rspQryTrade(napi_env env, const Message *message, napi_value *result);
napi_status rspQryInvestorPosition(napi_env env, const Message *message, napi_value *result);
napi_status rspQryTradingAccount(napi_env env, const Message *message, napi_value *result);
napi_status rspQryInvestor(napi_env env, const Message *message, napi_value *result);
napi_status rspQryTradingCode(napi_env env, const Message *message, napi_value *result);
napi_status rspQryInstrumentMarginRate(napi_env env, const Message *message, napi_value *result);
napi_status rspQryInstrumentCommissionRate(napi_env env, const Message *message, napi_value *result);
napi_status rspQryExchange(napi_env env, const Message *message, napi_value *result);
napi_status rspQryProduct(napi_env env, const Message *message, napi_value *result);
napi_status rspQryInstrument(napi_env env, const Message *message, napi_value *result);
napi_status rspQryDepthMarketData(napi_env env, const Message *message, napi_value *result);
napi_status rspQryTraderOffer(napi_env env, const Message *message, napi_value *result);
napi_status rspQrySettlementInfo(napi_env env, const Message *message, napi_value *result);
napi_status rspQryTransferBank(napi_env env, const Message *message, napi_value *result);
napi_status rspQryInvestorPositionDetail(napi_env env, const Message *message, napi_value *result);
napi_status rspQryNotice(napi_env env, const Message *message, napi_value *result);
napi_status rspQrySettlementInfoConfirm(napi_env env, const Message *message, napi_value *result);
napi_status rspQryInvestorPositionCombineDetail(napi_env env, const Message *message, napi_value *result);
napi_status rspQryCFMMCTradingAccountKey(napi_env env, const Message *message, napi_value *result);
napi_status rspQryEWarrantOffset(napi_env env, const Message *message, napi_value *result);
napi_status rspQryInvestorProductGroupMargin(napi_env env, const Message *message, napi_value *result);
napi_status rspQryExchangeMarginRate(napi_env env, const Message *message, napi_value *result);
napi_status rspQryExchangeMarginRateAdjust(napi_env env, const Message *message, napi_value *result);
napi_status rspQryExchangeRate(napi_env env, const Message *message, napi_value *result);
napi_status rspQrySecAgentACIDMap(napi_env env, const Message *message, napi_value *result);
napi_status rspQryProductExchRate(napi_env env, const Message *message, napi_value *result);
napi_status rspQryProductGroup(napi_env env, const Message *message, napi_value *result);
napi_status rspQryMMInstrumentCommissionRate(napi_env env, const Message *message, napi_value *result);
napi_status rspQryMMOptionInstrCommRate(napi_env env, const Message *message, napi_value *result);
napi_status rspQryInstrumentOrderCommRate(napi_env env, const Message *message, napi_value *result);
napi_status rspQrySecAgentTradingAccount(napi_env env, const Message *message, napi_value *result);
napi_status rspQrySecAgentCheckMode(napi_env env, const Message *message, napi_value *result);
napi_status rspQrySecAgentTradeInfo(napi_env env, const Message *message, napi_value *result);
napi_status rspQryOptionInstrTradeCost(napi_env env, const Message *message, napi_value *result);
napi_status rspQryOptionInstrCommRate(napi_env env, const Message *message, napi_value *result);
napi_status rspQryExecOrder(napi_env env, const Message *message, napi_value *result);
napi_status rspQryForQuote(napi_env env, const Message *message, napi_value *result);
napi_status rspQryQuote(napi_env env, const Message *message, napi_value *result);
napi_status rspQryOptionSelfClose(napi_env env, const Message *message, napi_value *result);
napi_status rspQryInvestUnit(napi_env env, const Message *message, napi_value *result);
napi_status rspQryCombInstrumentGuard(napi_env env, const Message *message, napi_value *result);
napi_status rspQryCombAction(napi_env env, const Message *message, napi_value *result);
napi_status rspQryTransferSerial(napi_env env, const Message *message, napi_value *result);
napi_status rspQryAccountRegister(napi_env env, const Message *message, napi_value *result);
napi_status rtnOrder(napi_env env, const Message *message, napi_value *result);
napi_status rtnTrade(napi_env env, const Message *message, napi_value *result);
napi_status errRtnOrderInsert(napi_env env, const Message *message, napi_value *result);
napi_status errRtnOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status rtnInstrumentStatus(napi_env env, const Message *message, napi_value *result);
napi_status rtnBulletin(napi_env env, const Message *message, napi_value *result);
napi_status rtnTradingNotice(napi_env env, const Message *message, napi_value *result);
napi_status rtnErrorConditionalOrder(napi_env env, const Message *message, napi_value *result);
napi_status rtnExecOrder(napi_env env, const Message *message, napi_value *result);
napi_status errRtnExecOrderInsert(napi_env env, const Message *message, napi_value *result);
napi_status errRtnExecOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status errRtnForQuoteInsert(napi_env env, const Message *message, napi_value *result);
napi_status rtnQuote(napi_env env, const Message *message, napi_value *result);
napi_status errRtnQuoteInsert(napi_env env, const Message *message, napi_value *result);
napi_status errRtnQuoteAction(napi_env env, const Message *message, napi_value *result);
napi_status rtnCFMMCTradingAccountToken(napi_env env, const Message *message, napi_value *result);
napi_status errRtnBatchOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status rtnOptionSelfClose(napi_env env, const Message *message, napi_value *result);
napi_status errRtnOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result);
napi_status errRtnOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result);
napi_status rtnCombAction(napi_env env, const Message *message, napi_value *result);
napi_status errRtnCombActionInsert(napi_env env, const Message *message, napi_value *result);
napi_status rspQryContractBank(napi_env env, const Message *message, napi_value *result);
napi_status rspQryParkedOrder(napi_env env, const Message *message, napi_value *result);
napi_status rspQryParkedOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status rspQryTradingNotice(napi_env env, const Message *message, napi_value *result);
napi_status rspQryBrokerTradingParams(napi_env env, const Message *message, napi_value *result);
napi_status rspQryBrokerTradingAlgos(napi_env env, const Message *message, napi_value *result);
napi_status rspQueryCFMMCTradingAccountToken(napi_env env, const Message *message, napi_value *result);
napi_status rtnFromBankToFutureByBank(napi_env env, const Message *message, napi_value *result);
napi_status rtnFromFutureToBankByBank(napi_env env, const Message *message, napi_value *result);
napi_status rtnRepealFromBankToFutureByBank(napi_env env, const Message *message, napi_value *result);
napi_status rtnRepealFromFutureToBankByBank(napi_env env, const Message *message, napi_value *result);
napi_status rtnFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result);
napi_status rtnFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result);
napi_status rtnRepealFromBankToFutureByFutureManual(napi_env env, const Message *message, napi_value *result);
napi_status rtnRepealFromFutureToBankByFutureManual(napi_env env, const Message *message, napi_value *result);
napi_status rtnQueryBankBalanceByFuture(napi_env env, const Message *message, napi_value *result);
napi_status errRtnBankToFutureByFuture(napi_env env, const Message *message, napi_value *result);
napi_status errRtnFutureToBankByFuture(napi_env env, const Message *message, napi_value *result);
napi_status errRtnRepealBankToFutureByFutureManual(napi_env env, const Message *message, napi_value *result);
napi_status errRtnRepealFutureToBankByFutureManual(napi_env env, const Message *message, napi_value *result);
napi_status errRtnQueryBankBalanceByFuture(napi_env env, const Message *message, napi_value *result);
napi_status rtnRepealFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result);
napi_status rtnRepealFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result);
napi_status rspFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result);
napi_status rspFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result);
napi_status rspQueryBankAccountMoneyByFuture(napi_env env, const Message *message, napi_value *result);
napi_status rtnOpenAccountByBank(napi_env env, const Message *message, napi_value *result);
napi_status rtnCancelAccountByBank(napi_env env, const Message *message, napi_value *result);
napi_status rtnChangeAccountByBank(napi_env env, const Message *message, napi_value *result);
napi_status rspQryClassifiedInstrument(napi_env env, const Message *message, napi_value *result);
napi_status rspQryCombPromotionParam(napi_env env, const Message *message, napi_value *result);
napi_status rspQryRiskSettleInvstPosition(napi_env env, const Message *message, napi_value *result);
napi_status rspQryRiskSettleProductStatus(napi_env env, const Message *message, napi_value *result);

#endif /* __CTPMSG_H__ */
