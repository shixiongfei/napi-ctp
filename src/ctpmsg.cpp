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
  napi_status status;
  auto pRspUserLogin = MessageData<CThostFtdcRspUserLoginField>(message);

  status = napi_create_object(env, result);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspUserLogin, TradingDay);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspUserLogin, LoginTime);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspUserLogin, BrokerID);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspUserLogin, UserID);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspUserLogin, SystemName);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pRspUserLogin, FrontID);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pRspUserLogin, SessionID);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspUserLogin, MaxOrderRef);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspUserLogin, SHFETime);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspUserLogin, DCETime);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspUserLogin, CZCETime);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspUserLogin, FFEXTime);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspUserLogin, INETime);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspUserLogin, SysVersion);
  assert(status == napi_ok);

  return napi_ok;
}

napi_status rspUserLogout(napi_env env, const Message *message, napi_value *result) {
  napi_status status;
  auto pUserLogout = MessageData<CThostFtdcUserLogoutField>(message);

  status = napi_create_object(env, result);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pUserLogout, BrokerID);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pUserLogout, UserID);
  assert(status == napi_ok);

  return napi_ok;
}

napi_status rspQryMulticastInstrument(napi_env env, const Message *message, napi_value *result) {
  napi_status status;
  auto pMulticastInstrument = MessageData<CThostFtdcMulticastInstrumentField>(message);

  status = napi_create_object(env, result);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pMulticastInstrument, TopicID);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pMulticastInstrument, reserve1);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pMulticastInstrument, InstrumentNo);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pMulticastInstrument, CodePrice);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pMulticastInstrument, VolumeMultiple);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pMulticastInstrument, PriceTick);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pMulticastInstrument, InstrumentID);
  assert(status == napi_ok);

  return napi_ok;
}

napi_status rspError(napi_env env, const Message *message, napi_value *result) {
  napi_status status;
  auto pRspInfo = MessageData<CThostFtdcRspInfoField>(message);

  status = napi_create_object(env, result);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pRspInfo, ErrorID);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pRspInfo, ErrorMsg);
  assert(status == napi_ok);

  return napi_ok;
}

napi_status rspSubMarketData(napi_env env, const Message *message, napi_value *result) {
  napi_status status;
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  status = napi_create_object(env, result);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pSpecificInstrument, reserve1);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pSpecificInstrument, InstrumentID);
  assert(status == napi_ok);

  return napi_ok;
}

napi_status rspUnSubMarketData(napi_env env, const Message *message, napi_value *result) {
  napi_status status;
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  status = napi_create_object(env, result);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pSpecificInstrument, reserve1);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pSpecificInstrument, InstrumentID);
  assert(status == napi_ok);

  return napi_ok;
}

napi_status rspSubForQuote(napi_env env, const Message *message, napi_value *result) {
  napi_status status;
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  status = napi_create_object(env, result);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pSpecificInstrument, reserve1);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pSpecificInstrument, InstrumentID);
  assert(status == napi_ok);

  return napi_ok;
}

napi_status rspUnSubForQuote(napi_env env, const Message *message, napi_value *result) {
  napi_status status;
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  status = napi_create_object(env, result);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pSpecificInstrument, reserve1);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pSpecificInstrument, InstrumentID);
  assert(status == napi_ok);

  return napi_ok;
}

napi_status rtnDepthMarketData(napi_env env, const Message *message, napi_value *result) {
  napi_status status;
  auto pDepthMarketData = MessageData<CThostFtdcDepthMarketDataField>(message);

  status = napi_create_object(env, result);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pDepthMarketData, TradingDay);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pDepthMarketData, reserve1);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pDepthMarketData, ExchangeID);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pDepthMarketData, reserve2);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, LastPrice);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, PreSettlementPrice);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, PreClosePrice);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, PreOpenInterest);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, OpenPrice);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, HighestPrice);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, LowestPrice);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pDepthMarketData, Volume);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, Turnover);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, OpenInterest);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, ClosePrice);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, SettlementPrice);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, UpperLimitPrice);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, LowerLimitPrice);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, PreDelta);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, CurrDelta);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pDepthMarketData, UpdateTime);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pDepthMarketData, UpdateMillisec);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, BidPrice1);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pDepthMarketData, BidVolume1);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, AskPrice1);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pDepthMarketData, AskVolume1);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, BidPrice2);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pDepthMarketData, BidVolume2);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, AskPrice2);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pDepthMarketData, AskVolume2);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, BidPrice3);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pDepthMarketData, BidVolume3);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, AskPrice3);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pDepthMarketData, AskVolume3);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, BidPrice4);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pDepthMarketData, BidVolume4);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, AskPrice4);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pDepthMarketData, AskVolume4);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, BidPrice5);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pDepthMarketData, BidVolume5);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, AskPrice5);
  assert(status == napi_ok);

  status = ObjectInt32(env, *result, pDepthMarketData, AskVolume5);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, AveragePrice);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pDepthMarketData, ActionDay);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pDepthMarketData, InstrumentID);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pDepthMarketData, ExchangeInstID);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, BandingUpperPrice);
  assert(status == napi_ok);

  status = ObjectDouble(env, *result, pDepthMarketData, BandingLowerPrice);
  assert(status == napi_ok);

  return napi_ok;
}

napi_status rtnForQuote(napi_env env, const Message *message, napi_value *result) {
  napi_status status;
  auto pForQuoteRsp = MessageData<CThostFtdcForQuoteRspField>(message);

  status = napi_create_object(env, result);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pForQuoteRsp, TradingDay);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pForQuoteRsp, reserve1);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pForQuoteRsp, ForQuoteSysID);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pForQuoteRsp, ForQuoteTime);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pForQuoteRsp, ActionDay);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pForQuoteRsp, ExchangeID);
  assert(status == napi_ok);

  status = ObjectString(env, *result, pForQuoteRsp, InstrumentID);
  assert(status == napi_ok);

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
