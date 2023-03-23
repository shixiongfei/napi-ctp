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

  MessageFunc msgFunc = iter->second;
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
