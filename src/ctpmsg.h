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

napi_status msgQuit(napi_env env, const Message *message, napi_value *result);
napi_status msgFrontConnected(napi_env env, const Message *message, napi_value *result);
napi_status msgFrontDisconnected(napi_env env, const Message *message, napi_value *result);
napi_status msgHeartBeatWarning(napi_env env, const Message *message, napi_value *result);
napi_status msgUserLogin(napi_env env, const Message *message, napi_value *result);
napi_status msgUserLogout(napi_env env, const Message *message, napi_value *result);
napi_status msgQryMulticastInstrument(napi_env env, const Message *message, napi_value *result);
napi_status msgError(napi_env env, const Message *message, napi_value *result);
napi_status msgSubMarketData(napi_env env, const Message *message, napi_value *result);
napi_status msgUnSubMarketData(napi_env env, const Message *message, napi_value *result);
napi_status msgSubForQuote(napi_env env, const Message *message, napi_value *result);
napi_status msgUnSubForQuote(napi_env env, const Message *message, napi_value *result);
napi_status msgDepthMarketData(napi_env env, const Message *message, napi_value *result);
napi_status msgForQuote(napi_env env, const Message *message, napi_value *result);

napi_status msgAuthenticate(napi_env env, const Message *message, napi_value *result);
napi_status msgUserPasswordUpdate(napi_env env, const Message *message, napi_value *result);
napi_status msgTradingAccountPasswordUpdate(napi_env env, const Message *message, napi_value *result);
napi_status msgUserAuthMethod(napi_env env, const Message *message, napi_value *result);
napi_status msgGenUserCaptcha(napi_env env, const Message *message, napi_value *result);
napi_status msgGenUserText(napi_env env, const Message *message, napi_value *result);
napi_status msgOrderInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgParkedOrderInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgParkedOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status msgOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status msgQryMaxOrderVolume(napi_env env, const Message *message, napi_value *result);
napi_status msgSettlementInfoConfirm(napi_env env, const Message *message, napi_value *result);
napi_status msgRemoveParkedOrder(napi_env env, const Message *message, napi_value *result);
napi_status msgRemoveParkedOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status msgExecOrderInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgExecOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status msgForQuoteInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgQuoteInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgQuoteAction(napi_env env, const Message *message, napi_value *result);
napi_status msgBatchOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status msgOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result);
napi_status msgCombActionInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgQryOrder(napi_env env, const Message *message, napi_value *result);
napi_status msgQryTrade(napi_env env, const Message *message, napi_value *result);
napi_status msgQryInvestorPosition(napi_env env, const Message *message, napi_value *result);
napi_status msgQryTradingAccount(napi_env env, const Message *message, napi_value *result);
napi_status msgQryInvestor(napi_env env, const Message *message, napi_value *result);
napi_status msgQryTradingCode(napi_env env, const Message *message, napi_value *result);
napi_status msgQryInstrumentMarginRate(napi_env env, const Message *message, napi_value *result);
napi_status msgQryInstrumentCommissionRate(napi_env env, const Message *message, napi_value *result);
napi_status msgQryExchange(napi_env env, const Message *message, napi_value *result);
napi_status msgQryProduct(napi_env env, const Message *message, napi_value *result);
napi_status msgQryInstrument(napi_env env, const Message *message, napi_value *result);
napi_status msgQryDepthMarketData(napi_env env, const Message *message, napi_value *result);
napi_status msgQryTraderOffer(napi_env env, const Message *message, napi_value *result);
napi_status msgQrySettlementInfo(napi_env env, const Message *message, napi_value *result);
napi_status msgQryTransferBank(napi_env env, const Message *message, napi_value *result);
napi_status msgQryInvestorPositionDetail(napi_env env, const Message *message, napi_value *result);
napi_status msgQryNotice(napi_env env, const Message *message, napi_value *result);
napi_status msgQrySettlementInfoConfirm(napi_env env, const Message *message, napi_value *result);
napi_status msgQryInvestorPositionCombineDetail(napi_env env, const Message *message, napi_value *result);
napi_status msgQryCFMMCTradingAccountKey(napi_env env, const Message *message, napi_value *result);
napi_status msgQryEWarrantOffset(napi_env env, const Message *message, napi_value *result);
napi_status msgQryInvestorProductGroupMargin(napi_env env, const Message *message, napi_value *result);
napi_status msgQryExchangeMarginRate(napi_env env, const Message *message, napi_value *result);
napi_status msgQryExchangeMarginRateAdjust(napi_env env, const Message *message, napi_value *result);
napi_status msgQryExchangeRate(napi_env env, const Message *message, napi_value *result);
napi_status msgQrySecAgentACIDMap(napi_env env, const Message *message, napi_value *result);
napi_status msgQryProductExchRate(napi_env env, const Message *message, napi_value *result);
napi_status msgQryProductGroup(napi_env env, const Message *message, napi_value *result);
napi_status msgQryMMInstrumentCommissionRate(napi_env env, const Message *message, napi_value *result);
napi_status msgQryMMOptionInstrCommRate(napi_env env, const Message *message, napi_value *result);
napi_status msgQryInstrumentOrderCommRate(napi_env env, const Message *message, napi_value *result);
napi_status msgQrySecAgentTradingAccount(napi_env env, const Message *message, napi_value *result);
napi_status msgQrySecAgentCheckMode(napi_env env, const Message *message, napi_value *result);
napi_status msgQrySecAgentTradeInfo(napi_env env, const Message *message, napi_value *result);
napi_status msgQryOptionInstrTradeCost(napi_env env, const Message *message, napi_value *result);
napi_status msgQryOptionInstrCommRate(napi_env env, const Message *message, napi_value *result);
napi_status msgQryExecOrder(napi_env env, const Message *message, napi_value *result);
napi_status msgQryForQuote(napi_env env, const Message *message, napi_value *result);
napi_status msgQryQuote(napi_env env, const Message *message, napi_value *result);
napi_status msgQryOptionSelfClose(napi_env env, const Message *message, napi_value *result);
napi_status msgQryInvestUnit(napi_env env, const Message *message, napi_value *result);
napi_status msgQryCombInstrumentGuard(napi_env env, const Message *message, napi_value *result);
napi_status msgQryCombAction(napi_env env, const Message *message, napi_value *result);
napi_status msgQryTransferSerial(napi_env env, const Message *message, napi_value *result);
napi_status msgQryAccountRegister(napi_env env, const Message *message, napi_value *result);
napi_status msgOrder(napi_env env, const Message *message, napi_value *result);
napi_status msgTrade(napi_env env, const Message *message, napi_value *result);
napi_status msgErrOrderInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgErrOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status msgInstrumentStatus(napi_env env, const Message *message, napi_value *result);
napi_status msgBulletin(napi_env env, const Message *message, napi_value *result);
napi_status msgTradingNotice(napi_env env, const Message *message, napi_value *result);
napi_status msgErrorConditionalOrder(napi_env env, const Message *message, napi_value *result);
napi_status msgExecOrder(napi_env env, const Message *message, napi_value *result);
napi_status msgErrExecOrderInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgErrExecOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status msgErrForQuoteInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgQuote(napi_env env, const Message *message, napi_value *result);
napi_status msgErrQuoteInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgErrQuoteAction(napi_env env, const Message *message, napi_value *result);
napi_status msgCFMMCTradingAccountToken(napi_env env, const Message *message, napi_value *result);
napi_status msgErrBatchOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status msgOptionSelfClose(napi_env env, const Message *message, napi_value *result);
napi_status msgErrOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgErrOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result);
napi_status msgCombAction(napi_env env, const Message *message, napi_value *result);
napi_status msgErrCombActionInsert(napi_env env, const Message *message, napi_value *result);
napi_status msgQryContractBank(napi_env env, const Message *message, napi_value *result);
napi_status msgQryParkedOrder(napi_env env, const Message *message, napi_value *result);
napi_status msgQryParkedOrderAction(napi_env env, const Message *message, napi_value *result);
napi_status msgQryTradingNotice(napi_env env, const Message *message, napi_value *result);
napi_status msgQryBrokerTradingParams(napi_env env, const Message *message, napi_value *result);
napi_status msgQryBrokerTradingAlgos(napi_env env, const Message *message, napi_value *result);
napi_status msgQueryCFMMCTradingAccountToken(napi_env env, const Message *message, napi_value *result);
napi_status msgFromBankToFutureByBank(napi_env env, const Message *message, napi_value *result);
napi_status msgFromFutureToBankByBank(napi_env env, const Message *message, napi_value *result);
napi_status msgRepealFromBankToFutureByBank(napi_env env, const Message *message, napi_value *result);
napi_status msgRepealFromFutureToBankByBank(napi_env env, const Message *message, napi_value *result);
napi_status msgFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result);
napi_status msgFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result);
napi_status msgRepealFromBankToFutureByFutureManual(napi_env env, const Message *message, napi_value *result);
napi_status msgRepealFromFutureToBankByFutureManual(napi_env env, const Message *message, napi_value *result);
napi_status msgQueryBankBalanceByFuture(napi_env env, const Message *message, napi_value *result);
napi_status msgErrBankToFutureByFuture(napi_env env, const Message *message, napi_value *result);
napi_status msgErrFutureToBankByFuture(napi_env env, const Message *message, napi_value *result);
napi_status msgErrRepealBankToFutureByFutureManual(napi_env env, const Message *message, napi_value *result);
napi_status msgErrRepealFutureToBankByFutureManual(napi_env env, const Message *message, napi_value *result);
napi_status msgErrQueryBankBalanceByFuture(napi_env env, const Message *message, napi_value *result);
napi_status msgRepealFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result);
napi_status msgRepealFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result);
napi_status msgRspFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result);
napi_status msgRspFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result);
napi_status msgQueryBankAccountMoneyByFuture(napi_env env, const Message *message, napi_value *result);
napi_status msgOpenAccountByBank(napi_env env, const Message *message, napi_value *result);
napi_status msgCancelAccountByBank(napi_env env, const Message *message, napi_value *result);
napi_status msgChangeAccountByBank(napi_env env, const Message *message, napi_value *result);
napi_status msgQryClassifiedInstrument(napi_env env, const Message *message, napi_value *result);
napi_status msgQryCombPromotionParam(napi_env env, const Message *message, napi_value *result);
napi_status msgQryRiskSettleInvstPosition(napi_env env, const Message *message, napi_value *result);
napi_status msgQryRiskSettleProductStatus(napi_env env, const Message *message, napi_value *result);

#endif /* __CTPMSG_H__ */
