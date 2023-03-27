/*
 * ctpmsg.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "ctpmsg.h"

napi_status getMessageValue(napi_env env, const MessageFuncs &messageFuncs, const Message *message, napi_value *result) {
  auto iter = messageFuncs.find(message->event);

  if (iter == messageFuncs.end())
    return napi_get_undefined(env, result);

  MessageHandler msgFunc = iter->second;
  return msgFunc(env, message, result);
}

napi_status msgQuit(napi_env env, const Message *message, napi_value *result) {
  return napi_create_int32(env, (int32_t)message->data, result);
}

napi_status msgFrontConnected(napi_env env, const Message *message, napi_value *result) {
  return napi_get_undefined(env, result);
}

napi_status msgFrontDisconnected(napi_env env, const Message *message, napi_value *result) {
  return napi_create_int32(env, (int32_t)message->data, result);
}

napi_status msgHeartBeatWarning(napi_env env, const Message *message, napi_value *result) {
  return napi_create_int32(env, (int32_t)message->data, result);
}

napi_status rspUserLogin(napi_env env, const Message *message, napi_value *result) {
  auto pRspUserLogin = MessageData<CThostFtdcRspUserLoginField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(ObjectString(env, *result, pRspUserLogin, TradingDay));
  CHECK(ObjectString(env, *result, pRspUserLogin, LoginTime));
  CHECK(ObjectString(env, *result, pRspUserLogin, BrokerID));
  CHECK(ObjectString(env, *result, pRspUserLogin, UserID));
  CHECK(ObjectString(env, *result, pRspUserLogin, SystemName));
  CHECK(ObjectInt32(env, *result, pRspUserLogin, FrontID));
  CHECK(ObjectInt32(env, *result, pRspUserLogin, SessionID));
  CHECK(ObjectString(env, *result, pRspUserLogin, MaxOrderRef));
  CHECK(ObjectString(env, *result, pRspUserLogin, SHFETime));
  CHECK(ObjectString(env, *result, pRspUserLogin, DCETime));
  CHECK(ObjectString(env, *result, pRspUserLogin, CZCETime));
  CHECK(ObjectString(env, *result, pRspUserLogin, FFEXTime));
  CHECK(ObjectString(env, *result, pRspUserLogin, INETime));
  CHECK(ObjectString(env, *result, pRspUserLogin, SysVersion));

  return napi_ok;
}

napi_status rspUserLogout(napi_env env, const Message *message, napi_value *result) {
  auto pUserLogout = MessageData<CThostFtdcUserLogoutField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(ObjectString(env, *result, pUserLogout, BrokerID));
  CHECK(ObjectString(env, *result, pUserLogout, UserID));

  return napi_ok;
}

napi_status rspQryMulticastInstrument(napi_env env, const Message *message, napi_value *result) {
  auto pMulticastInstrument = MessageData<CThostFtdcMulticastInstrumentField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(ObjectInt32(env, *result, pMulticastInstrument, TopicID));
  CHECK(ObjectString(env, *result, pMulticastInstrument, reserve1));
  CHECK(ObjectInt32(env, *result, pMulticastInstrument, InstrumentNo));
  CHECK(ObjectDouble(env, *result, pMulticastInstrument, CodePrice));
  CHECK(ObjectInt32(env, *result, pMulticastInstrument, VolumeMultiple));
  CHECK(ObjectDouble(env, *result, pMulticastInstrument, PriceTick));
  CHECK(ObjectString(env, *result, pMulticastInstrument, InstrumentID));

  return napi_ok;
}

napi_status rspError(napi_env env, const Message *message, napi_value *result) {
  auto pRspInfo = MessageData<CThostFtdcRspInfoField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(ObjectInt32(env, *result, pRspInfo, ErrorID));
  CHECK(ObjectString(env, *result, pRspInfo, ErrorMsg));

  return napi_ok;
}

napi_status rspSubMarketData(napi_env env, const Message *message, napi_value *result) {
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(ObjectString(env, *result, pSpecificInstrument, reserve1));
  CHECK(ObjectString(env, *result, pSpecificInstrument, InstrumentID));

  return napi_ok;
}

napi_status rspUnSubMarketData(napi_env env, const Message *message, napi_value *result) {
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(ObjectString(env, *result, pSpecificInstrument, reserve1));
  CHECK(ObjectString(env, *result, pSpecificInstrument, InstrumentID));

  return napi_ok;
}

napi_status rspSubForQuote(napi_env env, const Message *message, napi_value *result) {
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(ObjectString(env, *result, pSpecificInstrument, reserve1));
  CHECK(ObjectString(env, *result, pSpecificInstrument, InstrumentID));

  return napi_ok;
}

napi_status rspUnSubForQuote(napi_env env, const Message *message, napi_value *result) {
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(ObjectString(env, *result, pSpecificInstrument, reserve1));
  CHECK(ObjectString(env, *result, pSpecificInstrument, InstrumentID));

  return napi_ok;
}

napi_status rtnDepthMarketData(napi_env env, const Message *message, napi_value *result) {
  auto pDepthMarketData = MessageData<CThostFtdcDepthMarketDataField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(ObjectString(env, *result, pDepthMarketData, TradingDay));
  CHECK(ObjectString(env, *result, pDepthMarketData, reserve1));
  CHECK(ObjectString(env, *result, pDepthMarketData, ExchangeID));
  CHECK(ObjectString(env, *result, pDepthMarketData, reserve2));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, LastPrice));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, PreSettlementPrice));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, PreClosePrice));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, PreOpenInterest));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, OpenPrice));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, HighestPrice));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, LowestPrice));
  CHECK(ObjectInt32(env, *result, pDepthMarketData, Volume));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, Turnover));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, OpenInterest));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, ClosePrice));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, SettlementPrice));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, UpperLimitPrice));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, LowerLimitPrice));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, PreDelta));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, CurrDelta));
  CHECK(ObjectString(env, *result, pDepthMarketData, UpdateTime));
  CHECK(ObjectInt32(env, *result, pDepthMarketData, UpdateMillisec));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, BidPrice1));
  CHECK(ObjectInt32(env, *result, pDepthMarketData, BidVolume1));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, AskPrice1));
  CHECK(ObjectInt32(env, *result, pDepthMarketData, AskVolume1));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, BidPrice2));
  CHECK(ObjectInt32(env, *result, pDepthMarketData, BidVolume2));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, AskPrice2));
  CHECK(ObjectInt32(env, *result, pDepthMarketData, AskVolume2));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, BidPrice3));
  CHECK(ObjectInt32(env, *result, pDepthMarketData, BidVolume3));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, AskPrice3));
  CHECK(ObjectInt32(env, *result, pDepthMarketData, AskVolume3));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, BidPrice4));
  CHECK(ObjectInt32(env, *result, pDepthMarketData, BidVolume4));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, AskPrice4));
  CHECK(ObjectInt32(env, *result, pDepthMarketData, AskVolume4));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, BidPrice5));
  CHECK(ObjectInt32(env, *result, pDepthMarketData, BidVolume5));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, AskPrice5));
  CHECK(ObjectInt32(env, *result, pDepthMarketData, AskVolume5));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, AveragePrice));
  CHECK(ObjectString(env, *result, pDepthMarketData, ActionDay));
  CHECK(ObjectString(env, *result, pDepthMarketData, InstrumentID));
  CHECK(ObjectString(env, *result, pDepthMarketData, ExchangeInstID));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, BandingUpperPrice));
  CHECK(ObjectDouble(env, *result, pDepthMarketData, BandingLowerPrice));

  return napi_ok;
}

napi_status rtnForQuote(napi_env env, const Message *message, napi_value *result) {
  auto pForQuoteRsp = MessageData<CThostFtdcForQuoteRspField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(ObjectString(env, *result, pForQuoteRsp, TradingDay));
  CHECK(ObjectString(env, *result, pForQuoteRsp, reserve1));
  CHECK(ObjectString(env, *result, pForQuoteRsp, ForQuoteSysID));
  CHECK(ObjectString(env, *result, pForQuoteRsp, ForQuoteTime));
  CHECK(ObjectString(env, *result, pForQuoteRsp, ActionDay));
  CHECK(ObjectString(env, *result, pForQuoteRsp, ExchangeID));
  CHECK(ObjectString(env, *result, pForQuoteRsp, InstrumentID));

  return napi_ok;
}

napi_status rspAuthenticate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspUserPasswordUpdate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspTradingAccountPasswordUpdate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspUserAuthMethod(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspGenUserCaptcha(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspGenUserText(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspOrderInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspParkedOrderInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryMaxOrderVolume(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspSettlementInfoConfirm(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspRemoveParkedOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspRemoveParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspExecOrderInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspExecOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspForQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQuoteAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspBatchOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspCombActionInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryTrade(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryInvestorPosition(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryTradingAccount(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryInvestor(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryTradingCode(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryInstrumentMarginRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryInstrumentCommissionRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryExchange(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryProduct(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryInstrument(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryDepthMarketData(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryTraderOffer(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQrySettlementInfo(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryTransferBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryInvestorPositionDetail(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryNotice(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQrySettlementInfoConfirm(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryInvestorPositionCombineDetail(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryCFMMCTradingAccountKey(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryEWarrantOffset(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryInvestorProductGroupMargin(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryExchangeMarginRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryExchangeMarginRateAdjust(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryExchangeRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQrySecAgentACIDMap(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryProductExchRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryProductGroup(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryMMInstrumentCommissionRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryMMOptionInstrCommRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryInstrumentOrderCommRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQrySecAgentTradingAccount(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQrySecAgentCheckMode(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQrySecAgentTradeInfo(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryOptionInstrTradeCost(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryOptionInstrCommRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryExecOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryForQuote(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryQuote(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryOptionSelfClose(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryInvestUnit(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryCombInstrumentGuard(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryCombAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryTransferSerial(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryAccountRegister(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnTrade(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnOrderInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnInstrumentStatus(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnBulletin(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnTradingNotice(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnErrorConditionalOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnExecOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnExecOrderInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnExecOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnForQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnQuote(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnQuoteAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnCFMMCTradingAccountToken(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnBatchOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnOptionSelfClose(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnCombAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnCombActionInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryContractBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryParkedOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryTradingNotice(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryBrokerTradingParams(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryBrokerTradingAlgos(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQueryCFMMCTradingAccountToken(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnFromBankToFutureByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnFromFutureToBankByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnRepealFromBankToFutureByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnRepealFromFutureToBankByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnRepealFromBankToFutureByFutureManual(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnRepealFromFutureToBankByFutureManual(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnQueryBankBalanceByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnRepealBankToFutureByFutureManual(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnRepealFutureToBankByFutureManual(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status errRtnQueryBankBalanceByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnRepealFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnRepealFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQueryBankAccountMoneyByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnOpenAccountByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnCancelAccountByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rtnChangeAccountByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryClassifiedInstrument(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryCombPromotionParam(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryRiskSettleInvstPosition(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status rspQryRiskSettleProductStatus(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}
