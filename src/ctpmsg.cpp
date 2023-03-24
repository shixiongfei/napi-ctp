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

napi_status msgUserLogin(napi_env env, const Message *message, napi_value *result) {
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

napi_status msgUserLogout(napi_env env, const Message *message, napi_value *result) {
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

napi_status msgQryMulticastInstrument(napi_env env, const Message *message, napi_value *result) {
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

napi_status msgError(napi_env env, const Message *message, napi_value *result) {
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

napi_status msgSubMarketData(napi_env env, const Message *message, napi_value *result) {
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

napi_status msgUnSubMarketData(napi_env env, const Message *message, napi_value *result) {
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

napi_status msgSubForQuote(napi_env env, const Message *message, napi_value *result) {
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

napi_status msgUnSubForQuote(napi_env env, const Message *message, napi_value *result) {
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

napi_status msgDepthMarketData(napi_env env, const Message *message, napi_value *result) {
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

napi_status msgForQuote(napi_env env, const Message *message, napi_value *result) {
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

napi_status msgAuthenticate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgUserPasswordUpdate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgTradingAccountPasswordUpdate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgUserAuthMethod(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgGenUserCaptcha(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgGenUserText(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgOrderInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgParkedOrderInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryMaxOrderVolume(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgSettlementInfoConfirm(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgRemoveParkedOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgRemoveParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgExecOrderInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgExecOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgForQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQuoteAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgBatchOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgCombActionInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryTrade(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryInvestorPosition(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryTradingAccount(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryInvestor(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryTradingCode(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryInstrumentMarginRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryInstrumentCommissionRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryExchange(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryProduct(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryInstrument(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryDepthMarketData(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryTraderOffer(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQrySettlementInfo(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryTransferBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryInvestorPositionDetail(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryNotice(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQrySettlementInfoConfirm(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryInvestorPositionCombineDetail(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryCFMMCTradingAccountKey(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryEWarrantOffset(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryInvestorProductGroupMargin(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryExchangeMarginRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryExchangeMarginRateAdjust(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryExchangeRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQrySecAgentACIDMap(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryProductExchRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryProductGroup(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryMMInstrumentCommissionRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryMMOptionInstrCommRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryInstrumentOrderCommRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQrySecAgentTradingAccount(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQrySecAgentCheckMode(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQrySecAgentTradeInfo(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryOptionInstrTradeCost(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryOptionInstrCommRate(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryExecOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryForQuote(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryQuote(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryOptionSelfClose(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryInvestUnit(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryCombInstrumentGuard(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryCombAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryTransferSerial(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryAccountRegister(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgTrade(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrOrderInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgInstrumentStatus(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgBulletin(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgTradingNotice(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrorConditionalOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgExecOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrExecOrderInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrExecOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrForQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQuote(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrQuoteAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgCFMMCTradingAccountToken(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrBatchOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgOptionSelfClose(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgCombAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrCombActionInsert(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryContractBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryParkedOrder(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryTradingNotice(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryBrokerTradingParams(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryBrokerTradingAlgos(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQueryCFMMCTradingAccountToken(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgFromBankToFutureByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgFromFutureToBankByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgRepealFromBankToFutureByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgRepealFromFutureToBankByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgRepealFromBankToFutureByFutureManual(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgRepealFromFutureToBankByFutureManual(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQueryBankBalanceByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrRepealBankToFutureByFutureManual(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrRepealFutureToBankByFutureManual(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgErrQueryBankBalanceByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgRepealFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgRepealFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgRspFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgRspFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQueryBankAccountMoneyByFuture(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgOpenAccountByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgCancelAccountByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgChangeAccountByBank(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryClassifiedInstrument(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryCombPromotionParam(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryRiskSettleInvstPosition(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}

napi_status msgQryRiskSettleProductStatus(napi_env env, const Message *message, napi_value *result) {
  return napi_ok;
}
