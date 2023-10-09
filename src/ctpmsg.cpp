/*
 * ctpmsg.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https:
 */

#include "ctpmsg.h"

napi_status getMessageValue(napi_env env, const MessageFuncs &messageFuncs, const Message *message, napi_value *result) {
  auto iter = messageFuncs.find(message->event);

  if (iter == messageFuncs.end())
    return napi_get_undefined(env, result);

  MessageHandler msgFunc = iter->second;
  return msgFunc(env, message, result);
}

napi_status getMessageOptions(napi_env env, const Message *message, napi_value *result) {
  CHECK(napi_create_object(env, result));

  if (message->requestId != 0)
    CHECK(SetObjectInt32(env, *result, message, requestId));

  if (message->isLast != Undefined)
    CHECK(SetObjectBoolean(env, *result, message, isLast));

  CHECK(SetObjectInt64(env, *result, message, timestamp));

  return napi_ok;
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

  if (!pRspUserLogin)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspUserLoginField"));
  CHECK(SetObjectString(env, *result, pRspUserLogin, TradingDay));
  CHECK(SetObjectString(env, *result, pRspUserLogin, LoginTime));
  CHECK(SetObjectString(env, *result, pRspUserLogin, BrokerID));
  CHECK(SetObjectString(env, *result, pRspUserLogin, UserID));
  CHECK(SetObjectString(env, *result, pRspUserLogin, SystemName));
  CHECK(SetObjectInt32(env, *result, pRspUserLogin, FrontID));
  CHECK(SetObjectInt32(env, *result, pRspUserLogin, SessionID));
  CHECK(SetObjectString(env, *result, pRspUserLogin, MaxOrderRef));
  CHECK(SetObjectString(env, *result, pRspUserLogin, SHFETime));
  CHECK(SetObjectString(env, *result, pRspUserLogin, DCETime));
  CHECK(SetObjectString(env, *result, pRspUserLogin, CZCETime));
  CHECK(SetObjectString(env, *result, pRspUserLogin, FFEXTime));
  CHECK(SetObjectString(env, *result, pRspUserLogin, INETime));
  CHECK(SetObjectString(env, *result, pRspUserLogin, SysVersion));

  return napi_ok;
}

napi_status rspUserLogout(napi_env env, const Message *message, napi_value *result) {
  auto pUserLogout = MessageData<CThostFtdcUserLogoutField>(message);
  
  if (!pUserLogout)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcUserLogoutField"));
  CHECK(SetObjectString(env, *result, pUserLogout, BrokerID));
  CHECK(SetObjectString(env, *result, pUserLogout, UserID));

  return napi_ok;
}

napi_status rspQryMulticastInstrument(napi_env env, const Message *message, napi_value *result) {
  auto pMulticastInstrument = MessageData<CThostFtdcMulticastInstrumentField>(message);

  if (!pMulticastInstrument)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcMulticastInstrumentField"));
  CHECK(SetObjectInt32(env, *result, pMulticastInstrument, TopicID));
  CHECK(SetObjectInt32(env, *result, pMulticastInstrument, InstrumentNo));
  CHECK(SetObjectDouble(env, *result, pMulticastInstrument, CodePrice));
  CHECK(SetObjectInt32(env, *result, pMulticastInstrument, VolumeMultiple));
  CHECK(SetObjectDouble(env, *result, pMulticastInstrument, PriceTick));
  CHECK(SetObjectString(env, *result, pMulticastInstrument, InstrumentID));

  return napi_ok;
}

napi_status rspError(napi_env env, const Message *message, napi_value *result) {
  auto pRspInfo = MessageData<CThostFtdcRspInfoField>(message);

  if (!pRspInfo)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspInfoField"));
  CHECK(SetObjectInt32(env, *result, pRspInfo, ErrorID));
  CHECK(SetObjectString(env, *result, pRspInfo, ErrorMsg));

  return napi_ok;
}

napi_status rspSubMarketData(napi_env env, const Message *message, napi_value *result) {
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  if (!pSpecificInstrument)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcSpecificInstrumentField"));
  CHECK(SetObjectString(env, *result, pSpecificInstrument, InstrumentID));

  return napi_ok;
}

napi_status rspUnSubMarketData(napi_env env, const Message *message, napi_value *result) {
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  if (!pSpecificInstrument)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcSpecificInstrumentField"));
  CHECK(SetObjectString(env, *result, pSpecificInstrument, InstrumentID));

  return napi_ok;
}

napi_status rspSubForQuote(napi_env env, const Message *message, napi_value *result) {
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  if (!pSpecificInstrument)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcSpecificInstrumentField"));
  CHECK(SetObjectString(env, *result, pSpecificInstrument, InstrumentID));

  return napi_ok;
}

napi_status rspUnSubForQuote(napi_env env, const Message *message, napi_value *result) {
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  if (!pSpecificInstrument)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcSpecificInstrumentField"));
  CHECK(SetObjectString(env, *result, pSpecificInstrument, InstrumentID));

  return napi_ok;
}

napi_status rtnDepthMarketData(napi_env env, const Message *message, napi_value *result) {
  auto pDepthMarketData = MessageData<CThostFtdcDepthMarketDataField>(message);

  if (!pDepthMarketData)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcDepthMarketDataField"));
  CHECK(SetObjectString(env, *result, pDepthMarketData, TradingDay));
  CHECK(SetObjectString(env, *result, pDepthMarketData, ExchangeID));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, LastPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, PreSettlementPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, PreClosePrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, PreOpenInterest));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, OpenPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, HighestPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, LowestPrice));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, Volume));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, Turnover));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, OpenInterest));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, ClosePrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, SettlementPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, UpperLimitPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, LowerLimitPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, PreDelta));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, CurrDelta));
  CHECK(SetObjectString(env, *result, pDepthMarketData, UpdateTime));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, UpdateMillisec));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BidPrice1));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, BidVolume1));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, AskPrice1));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, AskVolume1));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BidPrice2));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, BidVolume2));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, AskPrice2));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, AskVolume2));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BidPrice3));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, BidVolume3));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, AskPrice3));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, AskVolume3));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BidPrice4));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, BidVolume4));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, AskPrice4));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, AskVolume4));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BidPrice5));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, BidVolume5));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, AskPrice5));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, AskVolume5));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, AveragePrice));
  CHECK(SetObjectString(env, *result, pDepthMarketData, ActionDay));
  CHECK(SetObjectString(env, *result, pDepthMarketData, InstrumentID));
  CHECK(SetObjectString(env, *result, pDepthMarketData, ExchangeInstID));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BandingUpperPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BandingLowerPrice));

  return napi_ok;
}

napi_status rtnForQuote(napi_env env, const Message *message, napi_value *result) {
  auto pForQuoteRsp = MessageData<CThostFtdcForQuoteRspField>(message);

  if (!pForQuoteRsp)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcForQuoteRspField"));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, TradingDay));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, ForQuoteSysID));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, ForQuoteTime));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, ActionDay));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, ExchangeID));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, InstrumentID));

  return napi_ok;
}

napi_status rspAuthenticate(napi_env env, const Message *message, napi_value *result) {
  auto pAuthenticate = MessageData<CThostFtdcRspAuthenticateField>(message);

  if (!pAuthenticate)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspAuthenticateField"));
  CHECK(SetObjectString(env, *result, pAuthenticate, BrokerID));
  CHECK(SetObjectString(env, *result, pAuthenticate, UserID));
  CHECK(SetObjectString(env, *result, pAuthenticate, UserProductInfo));
  CHECK(SetObjectString(env, *result, pAuthenticate, AppID));
  CHECK(SetObjectChar(env, *result, pAuthenticate, AppType));

  return napi_ok;
}

napi_status rspUserPasswordUpdate(napi_env env, const Message *message, napi_value *result) {
  auto pUserPasswordUpdate = MessageData<CThostFtdcUserPasswordUpdateField>(message);

  if (!pUserPasswordUpdate)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcUserPasswordUpdateField"));
  CHECK(SetObjectString(env, *result, pUserPasswordUpdate, BrokerID));
  CHECK(SetObjectString(env, *result, pUserPasswordUpdate, UserID));
  CHECK(SetObjectString(env, *result, pUserPasswordUpdate, OldPassword));
  CHECK(SetObjectString(env, *result, pUserPasswordUpdate, NewPassword));

  return napi_ok;
}

napi_status rspTradingAccountPasswordUpdate(napi_env env, const Message *message, napi_value *result) {
  auto pTradingAccountPasswordUpdate = MessageData<CThostFtdcTradingAccountPasswordUpdateField>(message);

  if (!pTradingAccountPasswordUpdate)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcTradingAccountPasswordUpdateField"));
  CHECK(SetObjectString(env, *result, pTradingAccountPasswordUpdate, BrokerID));
  CHECK(SetObjectString(env, *result, pTradingAccountPasswordUpdate, AccountID));
  CHECK(SetObjectString(env, *result, pTradingAccountPasswordUpdate, OldPassword));
  CHECK(SetObjectString(env, *result, pTradingAccountPasswordUpdate, NewPassword));
  CHECK(SetObjectString(env, *result, pTradingAccountPasswordUpdate, CurrencyID));

  return napi_ok;
}

napi_status rspUserAuthMethod(napi_env env, const Message *message, napi_value *result) {
  auto pRspUserAuthMethod = MessageData<CThostFtdcRspUserAuthMethodField>(message);

  if (!pRspUserAuthMethod)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspUserAuthMethodField"));
  CHECK(SetObjectInt32(env, *result, pRspUserAuthMethod, UsableAuthMethod));

  return napi_ok;
}

napi_status rspGenUserCaptcha(napi_env env, const Message *message, napi_value *result) {
  auto pRspGenUserCaptcha = MessageData<CThostFtdcRspGenUserCaptchaField>(message);

  if (!pRspGenUserCaptcha)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspGenUserCaptchaField"));
  CHECK(SetObjectString(env, *result, pRspGenUserCaptcha, BrokerID));
  CHECK(SetObjectString(env, *result, pRspGenUserCaptcha, UserID));
  CHECK(SetObjectBuffer(env, *result, pRspGenUserCaptcha, CaptchaInfo, CaptchaInfoLen));

  return napi_ok;
}

napi_status rspGenUserText(napi_env env, const Message *message, napi_value *result) {
  auto pRspGenUserText = MessageData<CThostFtdcRspGenUserTextField>(message);

  if (!pRspGenUserText)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspGenUserTextField"));
  CHECK(SetObjectInt32(env, *result, pRspGenUserText, UserTextSeq));

  return napi_ok;
}

napi_status rspOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputOrder = MessageData<CThostFtdcInputOrderField>(message);

  if (!pInputOrder)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputOrderField"));
  CHECK(SetObjectString(env, *result, pInputOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pInputOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pInputOrder, OrderRef));
  CHECK(SetObjectString(env, *result, pInputOrder, UserID));
  CHECK(SetObjectChar(env, *result, pInputOrder, OrderPriceType));
  CHECK(SetObjectChar(env, *result, pInputOrder, Direction));
  CHECK(SetObjectString(env, *result, pInputOrder, CombOffsetFlag));
  CHECK(SetObjectString(env, *result, pInputOrder, CombHedgeFlag));
  CHECK(SetObjectDouble(env, *result, pInputOrder, LimitPrice));
  CHECK(SetObjectInt32(env, *result, pInputOrder, VolumeTotalOriginal));
  CHECK(SetObjectChar(env, *result, pInputOrder, TimeCondition));
  CHECK(SetObjectString(env, *result, pInputOrder, GTDDate));
  CHECK(SetObjectChar(env, *result, pInputOrder, VolumeCondition));
  CHECK(SetObjectInt32(env, *result, pInputOrder, MinVolume));
  CHECK(SetObjectChar(env, *result, pInputOrder, ContingentCondition));
  CHECK(SetObjectDouble(env, *result, pInputOrder, StopPrice));
  CHECK(SetObjectChar(env, *result, pInputOrder, ForceCloseReason));
  CHECK(SetObjectInt32(env, *result, pInputOrder, IsAutoSuspend));
  CHECK(SetObjectString(env, *result, pInputOrder, BusinessUnit));
  CHECK(SetObjectInt32(env, *result, pInputOrder, RequestID));
  CHECK(SetObjectInt32(env, *result, pInputOrder, UserForceClose));
  CHECK(SetObjectInt32(env, *result, pInputOrder, IsSwapOrder));
  CHECK(SetObjectString(env, *result, pInputOrder, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputOrder, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputOrder, AccountID));
  CHECK(SetObjectString(env, *result, pInputOrder, CurrencyID));
  CHECK(SetObjectString(env, *result, pInputOrder, ClientID));
  CHECK(SetObjectString(env, *result, pInputOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pInputOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputOrder, IPAddress));

  return napi_ok;
}

napi_status rspParkedOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pParkedOrder = MessageData<CThostFtdcParkedOrderField>(message);

  if (!pParkedOrder)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcParkedOrderField"));
  CHECK(SetObjectString(env, *result, pParkedOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pParkedOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pParkedOrder, OrderRef));
  CHECK(SetObjectString(env, *result, pParkedOrder, UserID));
  CHECK(SetObjectChar(env, *result, pParkedOrder, OrderPriceType));
  CHECK(SetObjectChar(env, *result, pParkedOrder, Direction));
  CHECK(SetObjectString(env, *result, pParkedOrder, CombOffsetFlag));
  CHECK(SetObjectString(env, *result, pParkedOrder, CombHedgeFlag));
  CHECK(SetObjectDouble(env, *result, pParkedOrder, LimitPrice));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, VolumeTotalOriginal));
  CHECK(SetObjectChar(env, *result, pParkedOrder, TimeCondition));
  CHECK(SetObjectString(env, *result, pParkedOrder, GTDDate));
  CHECK(SetObjectChar(env, *result, pParkedOrder, VolumeCondition));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, MinVolume));
  CHECK(SetObjectChar(env, *result, pParkedOrder, ContingentCondition));
  CHECK(SetObjectDouble(env, *result, pParkedOrder, StopPrice));
  CHECK(SetObjectChar(env, *result, pParkedOrder, ForceCloseReason));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, IsAutoSuspend));
  CHECK(SetObjectString(env, *result, pParkedOrder, BusinessUnit));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, RequestID));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, UserForceClose));
  CHECK(SetObjectString(env, *result, pParkedOrder, ExchangeID));
  CHECK(SetObjectString(env, *result, pParkedOrder, ParkedOrderID));
  CHECK(SetObjectChar(env, *result, pParkedOrder, UserType));
  CHECK(SetObjectChar(env, *result, pParkedOrder, Status));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, ErrorID));
  CHECK(SetObjectString(env, *result, pParkedOrder, ErrorMsg));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, IsSwapOrder));
  CHECK(SetObjectString(env, *result, pParkedOrder, AccountID));
  CHECK(SetObjectString(env, *result, pParkedOrder, CurrencyID));
  CHECK(SetObjectString(env, *result, pParkedOrder, ClientID));
  CHECK(SetObjectString(env, *result, pParkedOrder, InvestUnitID));
  CHECK(SetObjectString(env, *result, pParkedOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pParkedOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pParkedOrder, IPAddress));

  return napi_ok;
}

napi_status rspParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pParkedOrderAction = MessageData<CThostFtdcParkedOrderActionField>(message);

  if (!pParkedOrderAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcParkedOrderActionField"));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, BrokerID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, InvestorID));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, OrderActionRef));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, OrderRef));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, RequestID));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, SessionID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, OrderSysID));
  CHECK(SetObjectChar(env, *result, pParkedOrderAction, ActionFlag));
  CHECK(SetObjectDouble(env, *result, pParkedOrderAction, LimitPrice));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, VolumeChange));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, UserID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, ParkedOrderActionID));
  CHECK(SetObjectChar(env, *result, pParkedOrderAction, UserType));
  CHECK(SetObjectChar(env, *result, pParkedOrderAction, Status));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, ErrorID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, ErrorMsg));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, MacAddress));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, IPAddress));

  return napi_ok;
}

napi_status rspOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputOrderAction = MessageData<CThostFtdcInputOrderActionField>(message);

  if (!pInputOrderAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputOrderActionField"));
  CHECK(SetObjectString(env, *result, pInputOrderAction, BrokerID));
  CHECK(SetObjectString(env, *result, pInputOrderAction, InvestorID));
  CHECK(SetObjectInt32(env, *result, pInputOrderAction, OrderActionRef));
  CHECK(SetObjectString(env, *result, pInputOrderAction, OrderRef));
  CHECK(SetObjectInt32(env, *result, pInputOrderAction, RequestID));
  CHECK(SetObjectInt32(env, *result, pInputOrderAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pInputOrderAction, SessionID));
  CHECK(SetObjectString(env, *result, pInputOrderAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputOrderAction, OrderSysID));
  CHECK(SetObjectChar(env, *result, pInputOrderAction, ActionFlag));
  CHECK(SetObjectDouble(env, *result, pInputOrderAction, LimitPrice));
  CHECK(SetObjectInt32(env, *result, pInputOrderAction, VolumeChange));
  CHECK(SetObjectString(env, *result, pInputOrderAction, UserID));
  CHECK(SetObjectString(env, *result, pInputOrderAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputOrderAction, MacAddress));
  CHECK(SetObjectString(env, *result, pInputOrderAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputOrderAction, IPAddress));

  return napi_ok;
}

napi_status rspQryMaxOrderVolume(napi_env env, const Message *message, napi_value *result) {
  auto pQryMaxOrderVolume = MessageData<CThostFtdcQryMaxOrderVolumeField>(message);

  if (!pQryMaxOrderVolume)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcQryMaxOrderVolumeField"));
  CHECK(SetObjectString(env, *result, pQryMaxOrderVolume, BrokerID));
  CHECK(SetObjectString(env, *result, pQryMaxOrderVolume, InvestorID));
  CHECK(SetObjectChar(env, *result, pQryMaxOrderVolume, Direction));
  CHECK(SetObjectChar(env, *result, pQryMaxOrderVolume, OffsetFlag));
  CHECK(SetObjectChar(env, *result, pQryMaxOrderVolume, HedgeFlag));
  CHECK(SetObjectInt32(env, *result, pQryMaxOrderVolume, MaxVolume));
  CHECK(SetObjectString(env, *result, pQryMaxOrderVolume, ExchangeID));
  CHECK(SetObjectString(env, *result, pQryMaxOrderVolume, InvestUnitID));
  CHECK(SetObjectString(env, *result, pQryMaxOrderVolume, InstrumentID));

  return napi_ok;
}

napi_status rspSettlementInfoConfirm(napi_env env, const Message *message, napi_value *result) {
  auto pSettlementInfoConfirm = MessageData<CThostFtdcSettlementInfoConfirmField>(message);

  if (!pSettlementInfoConfirm)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcSettlementInfoConfirmField"));
  CHECK(SetObjectString(env, *result, pSettlementInfoConfirm, BrokerID));
  CHECK(SetObjectString(env, *result, pSettlementInfoConfirm, InvestorID));
  CHECK(SetObjectString(env, *result, pSettlementInfoConfirm, ConfirmDate));
  CHECK(SetObjectString(env, *result, pSettlementInfoConfirm, ConfirmTime));
  CHECK(SetObjectInt32(env, *result, pSettlementInfoConfirm, SettlementID));
  CHECK(SetObjectString(env, *result, pSettlementInfoConfirm, AccountID));
  CHECK(SetObjectString(env, *result, pSettlementInfoConfirm, CurrencyID));

  return napi_ok;
}

napi_status rspRemoveParkedOrder(napi_env env, const Message *message, napi_value *result) {
  auto pRemoveParkedOrder = MessageData<CThostFtdcRemoveParkedOrderField>(message);

  if (!pRemoveParkedOrder)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRemoveParkedOrderField"));
  CHECK(SetObjectString(env, *result, pRemoveParkedOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pRemoveParkedOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pRemoveParkedOrder, ParkedOrderID));
  CHECK(SetObjectString(env, *result, pRemoveParkedOrder, InvestUnitID));

  return napi_ok;
}

napi_status rspRemoveParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pRemoveParkedOrderAction = MessageData<CThostFtdcRemoveParkedOrderActionField>(message);

  if (!pRemoveParkedOrderAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRemoveParkedOrderActionField"));
  CHECK(SetObjectString(env, *result, pRemoveParkedOrderAction, BrokerID));
  CHECK(SetObjectString(env, *result, pRemoveParkedOrderAction, InvestorID));
  CHECK(SetObjectString(env, *result, pRemoveParkedOrderAction, ParkedOrderActionID));
  CHECK(SetObjectString(env, *result, pRemoveParkedOrderAction, InvestUnitID));

  return napi_ok;
}

napi_status rspExecOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputExecOrder = MessageData<CThostFtdcInputExecOrderField>(message);

  if (!pInputExecOrder)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputExecOrderField"));
  CHECK(SetObjectString(env, *result, pInputExecOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, ExecOrderRef));
  CHECK(SetObjectString(env, *result, pInputExecOrder, UserID));
  CHECK(SetObjectInt32(env, *result, pInputExecOrder, Volume));
  CHECK(SetObjectInt32(env, *result, pInputExecOrder, RequestID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pInputExecOrder, OffsetFlag));
  CHECK(SetObjectChar(env, *result, pInputExecOrder, HedgeFlag));
  CHECK(SetObjectChar(env, *result, pInputExecOrder, ActionType));
  CHECK(SetObjectChar(env, *result, pInputExecOrder, PosiDirection));
  CHECK(SetObjectChar(env, *result, pInputExecOrder, ReservePositionFlag));
  CHECK(SetObjectChar(env, *result, pInputExecOrder, CloseFlag));
  CHECK(SetObjectString(env, *result, pInputExecOrder, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, AccountID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, CurrencyID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, ClientID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pInputExecOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, IPAddress));

  return napi_ok;
}

napi_status rspExecOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputExecOrderAction = MessageData<CThostFtdcInputExecOrderActionField>(message);

  if (!pInputExecOrderAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputExecOrderActionField"));
  CHECK(SetObjectString(env, *result, pInputExecOrderAction, BrokerID));
  CHECK(SetObjectString(env, *result, pInputExecOrderAction, InvestorID));
  CHECK(SetObjectInt32(env, *result, pInputExecOrderAction, ExecOrderActionRef));
  CHECK(SetObjectString(env, *result, pInputExecOrderAction, ExecOrderRef));
  CHECK(SetObjectInt32(env, *result, pInputExecOrderAction, RequestID));
  CHECK(SetObjectInt32(env, *result, pInputExecOrderAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pInputExecOrderAction, SessionID));
  CHECK(SetObjectString(env, *result, pInputExecOrderAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputExecOrderAction, ExecOrderSysID));
  CHECK(SetObjectChar(env, *result, pInputExecOrderAction, ActionFlag));
  CHECK(SetObjectString(env, *result, pInputExecOrderAction, UserID));
  CHECK(SetObjectString(env, *result, pInputExecOrderAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputExecOrderAction, MacAddress));
  CHECK(SetObjectString(env, *result, pInputExecOrderAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputExecOrderAction, IPAddress));

  return napi_ok;
}

napi_status rspForQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputForQuote = MessageData<CThostFtdcInputForQuoteField>(message);

  if (!pInputForQuote)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputForQuoteField"));
  CHECK(SetObjectString(env, *result, pInputForQuote, BrokerID));
  CHECK(SetObjectString(env, *result, pInputForQuote, InvestorID));
  CHECK(SetObjectString(env, *result, pInputForQuote, ForQuoteRef));
  CHECK(SetObjectString(env, *result, pInputForQuote, UserID));
  CHECK(SetObjectString(env, *result, pInputForQuote, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputForQuote, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputForQuote, MacAddress));
  CHECK(SetObjectString(env, *result, pInputForQuote, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputForQuote, IPAddress));

  return napi_ok;
}

napi_status rspQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputQuote = MessageData<CThostFtdcInputQuoteField>(message);

  if (!pInputQuote)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputQuoteField"));
  CHECK(SetObjectString(env, *result, pInputQuote, BrokerID));
  CHECK(SetObjectString(env, *result, pInputQuote, InvestorID));
  CHECK(SetObjectString(env, *result, pInputQuote, QuoteRef));
  CHECK(SetObjectString(env, *result, pInputQuote, UserID));
  CHECK(SetObjectDouble(env, *result, pInputQuote, AskPrice));
  CHECK(SetObjectDouble(env, *result, pInputQuote, BidPrice));
  CHECK(SetObjectInt32(env, *result, pInputQuote, AskVolume));
  CHECK(SetObjectInt32(env, *result, pInputQuote, BidVolume));
  CHECK(SetObjectInt32(env, *result, pInputQuote, RequestID));
  CHECK(SetObjectString(env, *result, pInputQuote, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pInputQuote, AskOffsetFlag));
  CHECK(SetObjectChar(env, *result, pInputQuote, BidOffsetFlag));
  CHECK(SetObjectChar(env, *result, pInputQuote, AskHedgeFlag));
  CHECK(SetObjectChar(env, *result, pInputQuote, BidHedgeFlag));
  CHECK(SetObjectString(env, *result, pInputQuote, AskOrderRef));
  CHECK(SetObjectString(env, *result, pInputQuote, BidOrderRef));
  CHECK(SetObjectString(env, *result, pInputQuote, ForQuoteSysID));
  CHECK(SetObjectString(env, *result, pInputQuote, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputQuote, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputQuote, ClientID));
  CHECK(SetObjectString(env, *result, pInputQuote, MacAddress));
  CHECK(SetObjectString(env, *result, pInputQuote, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputQuote, IPAddress));
  CHECK(SetObjectString(env, *result, pInputQuote, ReplaceSysID));

  return napi_ok;
}

napi_status rspQuoteAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputQuoteAction = MessageData<CThostFtdcInputQuoteActionField>(message);

  if (!pInputQuoteAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputQuoteActionField"));
  CHECK(SetObjectString(env, *result, pInputQuoteAction, BrokerID));
  CHECK(SetObjectString(env, *result, pInputQuoteAction, InvestorID));
  CHECK(SetObjectInt32(env, *result, pInputQuoteAction, QuoteActionRef));
  CHECK(SetObjectString(env, *result, pInputQuoteAction, QuoteRef));
  CHECK(SetObjectInt32(env, *result, pInputQuoteAction, RequestID));
  CHECK(SetObjectInt32(env, *result, pInputQuoteAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pInputQuoteAction, SessionID));
  CHECK(SetObjectString(env, *result, pInputQuoteAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputQuoteAction, QuoteSysID));
  CHECK(SetObjectChar(env, *result, pInputQuoteAction, ActionFlag));
  CHECK(SetObjectString(env, *result, pInputQuoteAction, UserID));
  CHECK(SetObjectString(env, *result, pInputQuoteAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputQuoteAction, ClientID));
  CHECK(SetObjectString(env, *result, pInputQuoteAction, MacAddress));
  CHECK(SetObjectString(env, *result, pInputQuoteAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputQuoteAction, IPAddress));

  return napi_ok;
}

napi_status rspBatchOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputBatchOrderAction = MessageData<CThostFtdcInputBatchOrderActionField>(message);

  if (!pInputBatchOrderAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputBatchOrderActionField"));
  CHECK(SetObjectString(env, *result, pInputBatchOrderAction, BrokerID));
  CHECK(SetObjectString(env, *result, pInputBatchOrderAction, InvestorID));
  CHECK(SetObjectInt32(env, *result, pInputBatchOrderAction, OrderActionRef));
  CHECK(SetObjectInt32(env, *result, pInputBatchOrderAction, RequestID));
  CHECK(SetObjectInt32(env, *result, pInputBatchOrderAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pInputBatchOrderAction, SessionID));
  CHECK(SetObjectString(env, *result, pInputBatchOrderAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputBatchOrderAction, UserID));
  CHECK(SetObjectString(env, *result, pInputBatchOrderAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputBatchOrderAction, MacAddress));
  CHECK(SetObjectString(env, *result, pInputBatchOrderAction, IPAddress));

  return napi_ok;
}

napi_status rspOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputOptionSelfClose = MessageData<CThostFtdcInputOptionSelfCloseField>(message);

  if (!pInputOptionSelfClose)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputOptionSelfCloseField"));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, BrokerID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, InvestorID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, OptionSelfCloseRef));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, UserID));
  CHECK(SetObjectInt32(env, *result, pInputOptionSelfClose, Volume));
  CHECK(SetObjectInt32(env, *result, pInputOptionSelfClose, RequestID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pInputOptionSelfClose, HedgeFlag));
  CHECK(SetObjectChar(env, *result, pInputOptionSelfClose, OptSelfCloseFlag));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, AccountID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, CurrencyID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, ClientID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, MacAddress));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, IPAddress));

  return napi_ok;
}

napi_status rspOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputOptionSelfCloseAction = MessageData<CThostFtdcInputOptionSelfCloseActionField>(message);

  if (!pInputOptionSelfCloseAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputOptionSelfCloseActionField"));
  CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, BrokerID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, InvestorID));
  CHECK(SetObjectInt32(env, *result, pInputOptionSelfCloseAction, OptionSelfCloseActionRef));
  CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, OptionSelfCloseRef));
  CHECK(SetObjectInt32(env, *result, pInputOptionSelfCloseAction, RequestID));
  CHECK(SetObjectInt32(env, *result, pInputOptionSelfCloseAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pInputOptionSelfCloseAction, SessionID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, OptionSelfCloseSysID));
  CHECK(SetObjectChar(env, *result, pInputOptionSelfCloseAction, ActionFlag));
  CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, UserID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, MacAddress));
  CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, IPAddress));

  return napi_ok;
}

napi_status rspCombActionInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputCombAction = MessageData<CThostFtdcInputCombActionField>(message);

  if (!pInputCombAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputCombActionField"));
  CHECK(SetObjectString(env, *result, pInputCombAction, BrokerID));
  CHECK(SetObjectString(env, *result, pInputCombAction, InvestorID));
  CHECK(SetObjectString(env, *result, pInputCombAction, CombActionRef));
  CHECK(SetObjectString(env, *result, pInputCombAction, UserID));
  CHECK(SetObjectChar(env, *result, pInputCombAction, Direction));
  CHECK(SetObjectInt32(env, *result, pInputCombAction, Volume));
  CHECK(SetObjectChar(env, *result, pInputCombAction, CombDirection));
  CHECK(SetObjectChar(env, *result, pInputCombAction, HedgeFlag));
  CHECK(SetObjectString(env, *result, pInputCombAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputCombAction, MacAddress));
  CHECK(SetObjectString(env, *result, pInputCombAction, InvestUnitID));
  CHECK(SetObjectInt32(env, *result, pInputCombAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pInputCombAction, SessionID));
  CHECK(SetObjectString(env, *result, pInputCombAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputCombAction, IPAddress));

  return napi_ok;
}

napi_status rspQryOrder(napi_env env, const Message *message, napi_value *result) {
  auto pOrder = MessageData<CThostFtdcOrderField>(message);

  if (!pOrder)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcOrderField"));
  CHECK(SetObjectString(env, *result, pOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pOrder, OrderRef));
  CHECK(SetObjectString(env, *result, pOrder, UserID));
  CHECK(SetObjectChar(env, *result, pOrder, OrderPriceType));
  CHECK(SetObjectChar(env, *result, pOrder, Direction));
  CHECK(SetObjectString(env, *result, pOrder, CombOffsetFlag));
  CHECK(SetObjectString(env, *result, pOrder, CombHedgeFlag));
  CHECK(SetObjectDouble(env, *result, pOrder, LimitPrice));
  CHECK(SetObjectInt32(env, *result, pOrder, VolumeTotalOriginal));
  CHECK(SetObjectChar(env, *result, pOrder, TimeCondition));
  CHECK(SetObjectString(env, *result, pOrder, GTDDate));
  CHECK(SetObjectChar(env, *result, pOrder, VolumeCondition));
  CHECK(SetObjectInt32(env, *result, pOrder, MinVolume));
  CHECK(SetObjectChar(env, *result, pOrder, ContingentCondition));
  CHECK(SetObjectInt32(env, *result, pOrder, StopPrice));
  CHECK(SetObjectChar(env, *result, pOrder, ForceCloseReason));
  CHECK(SetObjectInt32(env, *result, pOrder, IsAutoSuspend));
  CHECK(SetObjectString(env, *result, pOrder, BusinessUnit));
  CHECK(SetObjectInt32(env, *result, pOrder, RequestID));
  CHECK(SetObjectString(env, *result, pOrder, OrderLocalID));
  CHECK(SetObjectString(env, *result, pOrder, ExchangeID));
  CHECK(SetObjectString(env, *result, pOrder, ParticipantID));
  CHECK(SetObjectString(env, *result, pOrder, ClientID));
  CHECK(SetObjectString(env, *result, pOrder, TraderID));
  CHECK(SetObjectInt32(env, *result, pOrder, InstallID));
  CHECK(SetObjectChar(env, *result, pOrder, OrderSubmitStatus));
  CHECK(SetObjectInt32(env, *result, pOrder, NotifySequence));
  CHECK(SetObjectString(env, *result, pOrder, TradingDay));
  CHECK(SetObjectInt32(env, *result, pOrder, SettlementID));
  CHECK(SetObjectString(env, *result, pOrder, OrderSysID));
  CHECK(SetObjectChar(env, *result, pOrder, OrderSource));
  CHECK(SetObjectChar(env, *result, pOrder, OrderStatus));
  CHECK(SetObjectChar(env, *result, pOrder, OrderType));
  CHECK(SetObjectInt32(env, *result, pOrder, VolumeTraded));
  CHECK(SetObjectInt32(env, *result, pOrder, VolumeTotal));
  CHECK(SetObjectString(env, *result, pOrder, InsertDate));
  CHECK(SetObjectString(env, *result, pOrder, InsertTime));
  CHECK(SetObjectString(env, *result, pOrder, ActiveTime));
  CHECK(SetObjectString(env, *result, pOrder, SuspendTime));
  CHECK(SetObjectString(env, *result, pOrder, UpdateTime));
  CHECK(SetObjectString(env, *result, pOrder, CancelTime));
  CHECK(SetObjectString(env, *result, pOrder, ActiveTraderID));
  CHECK(SetObjectString(env, *result, pOrder, ClearingPartID));
  CHECK(SetObjectInt32(env, *result, pOrder, SequenceNo));
  CHECK(SetObjectInt32(env, *result, pOrder, FrontID));
  CHECK(SetObjectInt32(env, *result, pOrder, SessionID));
  CHECK(SetObjectString(env, *result, pOrder, UserProductInfo));
  CHECK(SetObjectString(env, *result, pOrder, StatusMsg));
  CHECK(SetObjectInt32(env, *result, pOrder, UserForceClose));
  CHECK(SetObjectString(env, *result, pOrder, ActiveUserID));
  CHECK(SetObjectInt32(env, *result, pOrder, BrokerOrderSeq));
  CHECK(SetObjectString(env, *result, pOrder, RelativeOrderSysID));
  CHECK(SetObjectInt32(env, *result, pOrder, ZCETotalTradedVolume));
  CHECK(SetObjectInt32(env, *result, pOrder, IsSwapOrder));
  CHECK(SetObjectString(env, *result, pOrder, BranchID));
  CHECK(SetObjectString(env, *result, pOrder, InvestUnitID));
  CHECK(SetObjectString(env, *result, pOrder, AccountID));
  CHECK(SetObjectString(env, *result, pOrder, CurrencyID));
  CHECK(SetObjectString(env, *result, pOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pOrder, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pOrder, IPAddress));

  return napi_ok;
}

napi_status rspQryTrade(napi_env env, const Message *message, napi_value *result) {
  auto pTrade = MessageData<CThostFtdcTradeField>(message);

  if (!pTrade)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcTradeField"));
  CHECK(SetObjectString(env, *result, pTrade, BrokerID));
  CHECK(SetObjectString(env, *result, pTrade, InvestorID));
  CHECK(SetObjectString(env, *result, pTrade, OrderRef));
  CHECK(SetObjectString(env, *result, pTrade, UserID));
  CHECK(SetObjectString(env, *result, pTrade, ExchangeID));
  CHECK(SetObjectString(env, *result, pTrade, TradeID));
  CHECK(SetObjectChar(env, *result, pTrade, Direction));
  CHECK(SetObjectString(env, *result, pTrade, OrderSysID));
  CHECK(SetObjectString(env, *result, pTrade, ParticipantID));
  CHECK(SetObjectString(env, *result, pTrade, ClientID));
  CHECK(SetObjectChar(env, *result, pTrade, TradingRole));
  CHECK(SetObjectChar(env, *result, pTrade, OffsetFlag));
  CHECK(SetObjectChar(env, *result, pTrade, HedgeFlag));
  CHECK(SetObjectDouble(env, *result, pTrade, Price));
  CHECK(SetObjectInt32(env, *result, pTrade, Volume));
  CHECK(SetObjectString(env, *result, pTrade, TradeDate));
  CHECK(SetObjectString(env, *result, pTrade, TradeTime));
  CHECK(SetObjectChar(env, *result, pTrade, TradeType));
  CHECK(SetObjectChar(env, *result, pTrade, PriceSource));
  CHECK(SetObjectString(env, *result, pTrade, TraderID));
  CHECK(SetObjectString(env, *result, pTrade, OrderLocalID));
  CHECK(SetObjectString(env, *result, pTrade, ClearingPartID));
  CHECK(SetObjectString(env, *result, pTrade, BusinessUnit));
  CHECK(SetObjectInt32(env, *result, pTrade, SequenceNo));
  CHECK(SetObjectString(env, *result, pTrade, TradingDay));
  CHECK(SetObjectInt32(env, *result, pTrade, SettlementID));
  CHECK(SetObjectInt32(env, *result, pTrade, BrokerOrderSeq));
  CHECK(SetObjectChar(env, *result, pTrade, TradeSource));
  CHECK(SetObjectString(env, *result, pTrade, InvestUnitID));
  CHECK(SetObjectString(env, *result, pTrade, InstrumentID));
  CHECK(SetObjectString(env, *result, pTrade, ExchangeInstID));

  return napi_ok;
}

napi_status rspQryInvestorPosition(napi_env env, const Message *message, napi_value *result) {
  auto pInvestorPosition = MessageData<CThostFtdcInvestorPositionField>(message);

  if (!pInvestorPosition)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInvestorPositionField"));
  CHECK(SetObjectString(env, *result, pInvestorPosition, BrokerID));
  CHECK(SetObjectString(env, *result, pInvestorPosition, InvestorID));
  CHECK(SetObjectChar(env, *result, pInvestorPosition, PosiDirection));
  CHECK(SetObjectChar(env, *result, pInvestorPosition, HedgeFlag));
  CHECK(SetObjectChar(env, *result, pInvestorPosition, PositionDate));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, YdPosition));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, Position));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, LongFrozen));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, ShortFrozen));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, LongFrozenAmount));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, ShortFrozenAmount));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, OpenVolume));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, CloseVolume));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, OpenAmount));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, CloseAmount));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, PositionCost));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, PreMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, UseMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, FrozenMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, FrozenCash));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, FrozenCommission));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, CashIn));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, Commission));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, CloseProfit));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, PositionProfit));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, PreSettlementPrice));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, SettlementPrice));
  CHECK(SetObjectString(env, *result, pInvestorPosition, TradingDay));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, SettlementID));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, OpenCost));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, ExchangeMargin));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, CombPosition));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, CombLongFrozen));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, CombShortFrozen));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, CloseProfitByDate));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, CloseProfitByTrade));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, TodayPosition));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, MarginRateByMoney));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, MarginRateByVolume));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, StrikeFrozen));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, StrikeFrozenAmount));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, AbandonFrozen));
  CHECK(SetObjectString(env, *result, pInvestorPosition, ExchangeID));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, YdStrikeFrozen));
  CHECK(SetObjectString(env, *result, pInvestorPosition, InvestUnitID));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, PositionCostOffset));
  CHECK(SetObjectInt32(env, *result, pInvestorPosition, TasPosition));
  CHECK(SetObjectDouble(env, *result, pInvestorPosition, TasPositionCost));
  CHECK(SetObjectString(env, *result, pInvestorPosition, InstrumentID));

  return napi_ok;
}

napi_status rspQryTradingAccount(napi_env env, const Message *message, napi_value *result) {
  auto pTradingAccount = MessageData<CThostFtdcTradingAccountField>(message);

  if (!pTradingAccount)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcTradingAccountField"));
  CHECK(SetObjectString(env, *result, pTradingAccount, BrokerID));
  CHECK(SetObjectString(env, *result, pTradingAccount, AccountID));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreMortgage));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreCredit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreDeposit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreBalance));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, InterestBase));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Interest));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Deposit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Withdraw));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FrozenMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FrozenCash));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FrozenCommission));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, CurrMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, CashIn));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Commission));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, CloseProfit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PositionProfit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Balance));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Available));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, WithdrawQuota));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Reserve));
  CHECK(SetObjectString(env, *result, pTradingAccount, TradingDay));
  CHECK(SetObjectInt32(env, *result, pTradingAccount, SettlementID));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Credit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Mortgage));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, ExchangeMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, DeliveryMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, ExchangeDeliveryMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, ReserveBalance));
  CHECK(SetObjectString(env, *result, pTradingAccount, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreFundMortgageIn));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreFundMortgageOut));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FundMortgageIn));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FundMortgageOut));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FundMortgageAvailable));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, MortgageableFund));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductFrozenMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductCommission));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductFrozenCommission));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductPositionProfit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductCloseProfit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductPositionProfitByAlg));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductExchangeMargin));
  CHECK(SetObjectChar(env, *result, pTradingAccount, BizType));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FrozenSwap));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, RemainSwap));

  return napi_ok;
}

napi_status rspQryInvestor(napi_env env, const Message *message, napi_value *result) {
  auto pInvestor = MessageData<CThostFtdcInvestorField>(message);

  if (!pInvestor)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInvestorField"));
  CHECK(SetObjectString(env, *result, pInvestor, InvestorID));
  CHECK(SetObjectString(env, *result, pInvestor, BrokerID));
  CHECK(SetObjectString(env, *result, pInvestor, InvestorGroupID));
  CHECK(SetObjectString(env, *result, pInvestor, InvestorName));
  CHECK(SetObjectChar(env, *result, pInvestor, IdentifiedCardType));
  CHECK(SetObjectString(env, *result, pInvestor, IdentifiedCardNo));
  CHECK(SetObjectInt32(env, *result, pInvestor, IsActive));
  CHECK(SetObjectString(env, *result, pInvestor, Telephone));
  CHECK(SetObjectString(env, *result, pInvestor, Address));
  CHECK(SetObjectString(env, *result, pInvestor, OpenDate));
  CHECK(SetObjectString(env, *result, pInvestor, Mobile));
  CHECK(SetObjectString(env, *result, pInvestor, CommModelID));
  CHECK(SetObjectString(env, *result, pInvestor, MarginModelID));
  CHECK(SetObjectChar(env, *result, pInvestor, IsOrderFreq));
  CHECK(SetObjectChar(env, *result, pInvestor, IsOpenVolLimit));

  return napi_ok;
}

napi_status rspQryTradingCode(napi_env env, const Message *message, napi_value *result) {
  auto pTradingCode = MessageData<CThostFtdcTradingCodeField>(message);

  if (!pTradingCode)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcTradingCodeField"));
  CHECK(SetObjectString(env, *result, pTradingCode, InvestorID));
  CHECK(SetObjectString(env, *result, pTradingCode, BrokerID));
  CHECK(SetObjectString(env, *result, pTradingCode, ExchangeID));
  CHECK(SetObjectString(env, *result, pTradingCode, ClientID));
  CHECK(SetObjectInt32(env, *result, pTradingCode, IsActive));
  CHECK(SetObjectChar(env, *result, pTradingCode, ClientIDType));
  CHECK(SetObjectString(env, *result, pTradingCode, BranchID));
  CHECK(SetObjectChar(env, *result, pTradingCode, BizType));
  CHECK(SetObjectString(env, *result, pTradingCode, InvestUnitID));

  return napi_ok;
}

napi_status rspQryInstrumentMarginRate(napi_env env, const Message *message, napi_value *result) {
  auto pInstrumentMarginRate = MessageData<CThostFtdcInstrumentMarginRateField>(message);

  if (!pInstrumentMarginRate)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInstrumentMarginRateField"));
  CHECK(SetObjectChar(env, *result, pInstrumentMarginRate, InvestorRange));
  CHECK(SetObjectString(env, *result, pInstrumentMarginRate, BrokerID));
  CHECK(SetObjectString(env, *result, pInstrumentMarginRate, InvestorID));
  CHECK(SetObjectChar(env, *result, pInstrumentMarginRate, HedgeFlag));
  CHECK(SetObjectDouble(env, *result, pInstrumentMarginRate, LongMarginRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pInstrumentMarginRate, LongMarginRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pInstrumentMarginRate, ShortMarginRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pInstrumentMarginRate, ShortMarginRatioByVolume));
  CHECK(SetObjectInt32(env, *result, pInstrumentMarginRate, IsRelative));
  CHECK(SetObjectString(env, *result, pInstrumentMarginRate, ExchangeID));
  CHECK(SetObjectString(env, *result, pInstrumentMarginRate, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInstrumentMarginRate, InstrumentID));

  return napi_ok;
}

napi_status rspQryInstrumentCommissionRate(napi_env env, const Message *message, napi_value *result) {
  auto pInstrumentCommissionRate = MessageData<CThostFtdcInstrumentCommissionRateField>(message);

  if (!pInstrumentCommissionRate)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInstrumentCommissionRateField"));
  CHECK(SetObjectChar(env, *result, pInstrumentCommissionRate, InvestorRange));
  CHECK(SetObjectString(env, *result, pInstrumentCommissionRate, BrokerID));
  CHECK(SetObjectString(env, *result, pInstrumentCommissionRate, InvestorID));
  CHECK(SetObjectDouble(env, *result, pInstrumentCommissionRate, OpenRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pInstrumentCommissionRate, OpenRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pInstrumentCommissionRate, CloseRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pInstrumentCommissionRate, CloseRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pInstrumentCommissionRate, CloseTodayRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pInstrumentCommissionRate, CloseTodayRatioByVolume));
  CHECK(SetObjectString(env, *result, pInstrumentCommissionRate, ExchangeID));
  CHECK(SetObjectChar(env, *result, pInstrumentCommissionRate, BizType));
  CHECK(SetObjectString(env, *result, pInstrumentCommissionRate, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInstrumentCommissionRate, InstrumentID));

  return napi_ok;
}

napi_status rspQryExchange(napi_env env, const Message *message, napi_value *result) {
  auto pExchange = MessageData<CThostFtdcExchangeField>(message);

  if (!pExchange)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcExchangeField"));
  CHECK(SetObjectString(env, *result, pExchange, ExchangeID));
  CHECK(SetObjectString(env, *result, pExchange, ExchangeName));
  CHECK(SetObjectChar(env, *result, pExchange, ExchangeProperty));

  return napi_ok;
}

napi_status rspQryProduct(napi_env env, const Message *message, napi_value *result) {
  auto pProduct = MessageData<CThostFtdcProductField>(message);

  if (!pProduct)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcProductField"));
  CHECK(SetObjectString(env, *result, pProduct, ProductName));
  CHECK(SetObjectString(env, *result, pProduct, ExchangeID));
  CHECK(SetObjectChar(env, *result, pProduct, ProductClass));
  CHECK(SetObjectInt32(env, *result, pProduct, VolumeMultiple));
  CHECK(SetObjectDouble(env, *result, pProduct, PriceTick));
  CHECK(SetObjectInt32(env, *result, pProduct, MaxMarketOrderVolume));
  CHECK(SetObjectInt32(env, *result, pProduct, MinMarketOrderVolume));
  CHECK(SetObjectInt32(env, *result, pProduct, MaxLimitOrderVolume));
  CHECK(SetObjectInt32(env, *result, pProduct, MinLimitOrderVolume));
  CHECK(SetObjectChar(env, *result, pProduct, PositionType));
  CHECK(SetObjectChar(env, *result, pProduct, PositionDateType));
  CHECK(SetObjectChar(env, *result, pProduct, CloseDealType));
  CHECK(SetObjectString(env, *result, pProduct, TradeCurrencyID));
  CHECK(SetObjectChar(env, *result, pProduct, MortgageFundUseRange));
  CHECK(SetObjectDouble(env, *result, pProduct, UnderlyingMultiple));
  CHECK(SetObjectString(env, *result, pProduct, ProductID));
  CHECK(SetObjectString(env, *result, pProduct, ExchangeProductID));
  CHECK(SetObjectChar(env, *result, pProduct, OpenLimitControlLevel));
  CHECK(SetObjectChar(env, *result, pProduct, OrderFreqControlLevel));

  return napi_ok;
}

napi_status rspQryInstrument(napi_env env, const Message *message, napi_value *result) {
  auto pInstrument = MessageData<CThostFtdcInstrumentField>(message);

  if (!pInstrument)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInstrumentField"));
  CHECK(SetObjectString(env, *result, pInstrument, ExchangeID));
  CHECK(SetObjectString(env, *result, pInstrument, InstrumentName));
  CHECK(SetObjectChar(env, *result, pInstrument, ProductClass));
  CHECK(SetObjectInt32(env, *result, pInstrument, DeliveryYear));
  CHECK(SetObjectInt32(env, *result, pInstrument, DeliveryMonth));
  CHECK(SetObjectInt32(env, *result, pInstrument, MaxMarketOrderVolume));
  CHECK(SetObjectInt32(env, *result, pInstrument, MinMarketOrderVolume));
  CHECK(SetObjectInt32(env, *result, pInstrument, MaxLimitOrderVolume));
  CHECK(SetObjectInt32(env, *result, pInstrument, MinLimitOrderVolume));
  CHECK(SetObjectInt32(env, *result, pInstrument, VolumeMultiple));
  CHECK(SetObjectDouble(env, *result, pInstrument, PriceTick));
  CHECK(SetObjectString(env, *result, pInstrument, CreateDate));
  CHECK(SetObjectString(env, *result, pInstrument, OpenDate));
  CHECK(SetObjectString(env, *result, pInstrument, ExpireDate));
  CHECK(SetObjectString(env, *result, pInstrument, StartDelivDate));
  CHECK(SetObjectString(env, *result, pInstrument, EndDelivDate));
  CHECK(SetObjectChar(env, *result, pInstrument, InstLifePhase));
  CHECK(SetObjectInt32(env, *result, pInstrument, IsTrading));
  CHECK(SetObjectChar(env, *result, pInstrument, PositionType));
  CHECK(SetObjectChar(env, *result, pInstrument, PositionDateType));
  CHECK(SetObjectDouble(env, *result, pInstrument, LongMarginRatio));
  CHECK(SetObjectDouble(env, *result, pInstrument, ShortMarginRatio));
  CHECK(SetObjectChar(env, *result, pInstrument, MaxMarginSideAlgorithm));
  CHECK(SetObjectDouble(env, *result, pInstrument, StrikePrice));
  CHECK(SetObjectChar(env, *result, pInstrument, OptionsType));
  CHECK(SetObjectDouble(env, *result, pInstrument, UnderlyingMultiple));
  CHECK(SetObjectChar(env, *result, pInstrument, CombinationType));
  CHECK(SetObjectString(env, *result, pInstrument, InstrumentID));
  CHECK(SetObjectString(env, *result, pInstrument, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pInstrument, ProductID));
  CHECK(SetObjectString(env, *result, pInstrument, UnderlyingInstrID));

  return napi_ok;
}

napi_status rspQryDepthMarketData(napi_env env, const Message *message, napi_value *result) {
  auto pDepthMarketData = MessageData<CThostFtdcDepthMarketDataField>(message);

  if (!pDepthMarketData)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcDepthMarketDataField"));
  CHECK(SetObjectString(env, *result, pDepthMarketData, TradingDay));
  CHECK(SetObjectString(env, *result, pDepthMarketData, ExchangeID));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, LastPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, PreSettlementPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, PreClosePrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, PreOpenInterest));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, OpenPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, HighestPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, LowestPrice));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, Volume));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, Turnover));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, OpenInterest));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, ClosePrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, SettlementPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, UpperLimitPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, LowerLimitPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, PreDelta));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, CurrDelta));
  CHECK(SetObjectString(env, *result, pDepthMarketData, UpdateTime));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, UpdateMillisec));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BidPrice1));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, BidVolume1));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, AskPrice1));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, AskVolume1));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BidPrice2));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, BidVolume2));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, AskPrice2));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, AskVolume2));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BidPrice3));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, BidVolume3));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, AskPrice3));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, AskVolume3));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BidPrice4));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, BidVolume4));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, AskPrice4));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, AskVolume4));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BidPrice5));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, BidVolume5));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, AskPrice5));
  CHECK(SetObjectInt32(env, *result, pDepthMarketData, AskVolume5));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, AveragePrice));
  CHECK(SetObjectString(env, *result, pDepthMarketData, ActionDay));
  CHECK(SetObjectString(env, *result, pDepthMarketData, InstrumentID));
  CHECK(SetObjectString(env, *result, pDepthMarketData, ExchangeInstID));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BandingUpperPrice));
  CHECK(SetObjectDouble(env, *result, pDepthMarketData, BandingLowerPrice));

  return napi_ok;
}

napi_status rspQryTraderOffer(napi_env env, const Message *message, napi_value *result) {
  auto pTraderOffer = MessageData<CThostFtdcTraderOfferField>(message);

  if (!pTraderOffer)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcTraderOfferField"));
  CHECK(SetObjectString(env, *result, pTraderOffer, ExchangeID));
  CHECK(SetObjectString(env, *result, pTraderOffer, TraderID));
  CHECK(SetObjectString(env, *result, pTraderOffer, ParticipantID));
  CHECK(SetObjectString(env, *result, pTraderOffer, Password));
  CHECK(SetObjectInt32(env, *result, pTraderOffer, InstallID));
  CHECK(SetObjectString(env, *result, pTraderOffer, OrderLocalID));
  CHECK(SetObjectChar(env, *result, pTraderOffer, TraderConnectStatus));
  CHECK(SetObjectString(env, *result, pTraderOffer, ConnectRequestDate));
  CHECK(SetObjectString(env, *result, pTraderOffer, ConnectRequestTime));
  CHECK(SetObjectString(env, *result, pTraderOffer, LastReportDate));
  CHECK(SetObjectString(env, *result, pTraderOffer, LastReportTime));
  CHECK(SetObjectString(env, *result, pTraderOffer, ConnectDate));
  CHECK(SetObjectString(env, *result, pTraderOffer, ConnectTime));
  CHECK(SetObjectString(env, *result, pTraderOffer, StartDate));
  CHECK(SetObjectString(env, *result, pTraderOffer, StartTime));
  CHECK(SetObjectString(env, *result, pTraderOffer, TradingDay));
  CHECK(SetObjectString(env, *result, pTraderOffer, BrokerID));
  CHECK(SetObjectString(env, *result, pTraderOffer, MaxTradeID));
  CHECK(SetObjectString(env, *result, pTraderOffer, MaxOrderMessageReference));
  CHECK(SetObjectChar(env, *result, pTraderOffer, OrderCancelAlg));

  return napi_ok;
}

napi_status rspQrySettlementInfo(napi_env env, const Message *message, napi_value *result) {
  auto pSettlementInfo = MessageData<CThostFtdcSettlementInfoField>(message);

  if (!pSettlementInfo)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcSettlementInfoField"));
  CHECK(SetObjectString(env, *result, pSettlementInfo, TradingDay));
  CHECK(SetObjectInt32(env, *result, pSettlementInfo, SettlementID));
  CHECK(SetObjectString(env, *result, pSettlementInfo, BrokerID));
  CHECK(SetObjectString(env, *result, pSettlementInfo, InvestorID));
  CHECK(SetObjectInt32(env, *result, pSettlementInfo, SequenceNo));
  CHECK(SetObjectString(env, *result, pSettlementInfo, Content));
  CHECK(SetObjectString(env, *result, pSettlementInfo, AccountID));
  CHECK(SetObjectString(env, *result, pSettlementInfo, CurrencyID));

  return napi_ok;
}

napi_status rspQryTransferBank(napi_env env, const Message *message, napi_value *result) {
  auto pTransferBank = MessageData<CThostFtdcTransferBankField>(message);

  if (!pTransferBank)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcTransferBankField"));
  CHECK(SetObjectString(env, *result, pTransferBank, BankID));
  CHECK(SetObjectString(env, *result, pTransferBank, BankBrchID));
  CHECK(SetObjectString(env, *result, pTransferBank, BankName));
  CHECK(SetObjectInt32(env, *result, pTransferBank, IsActive));

  return napi_ok;
}

napi_status rspQryInvestorPositionDetail(napi_env env, const Message *message, napi_value *result) {
  auto pInvestorPositionDetail = MessageData<CThostFtdcInvestorPositionDetailField>(message);

  if (!pInvestorPositionDetail)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInvestorPositionDetailField"));
  CHECK(SetObjectString(env, *result, pInvestorPositionDetail, BrokerID));
  CHECK(SetObjectString(env, *result, pInvestorPositionDetail, InvestorID));
  CHECK(SetObjectChar(env, *result, pInvestorPositionDetail, HedgeFlag));
  CHECK(SetObjectChar(env, *result, pInvestorPositionDetail, Direction));
  CHECK(SetObjectString(env, *result, pInvestorPositionDetail, OpenDate));
  CHECK(SetObjectString(env, *result, pInvestorPositionDetail, TradeID));
  CHECK(SetObjectInt32(env, *result, pInvestorPositionDetail, Volume));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionDetail, OpenPrice));
  CHECK(SetObjectString(env, *result, pInvestorPositionDetail, TradingDay));
  CHECK(SetObjectInt32(env, *result, pInvestorPositionDetail, SettlementID));
  CHECK(SetObjectChar(env, *result, pInvestorPositionDetail, TradeType));
  CHECK(SetObjectString(env, *result, pInvestorPositionDetail, ExchangeID));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionDetail, CloseProfitByDate));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionDetail, CloseProfitByTrade));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionDetail, PositionProfitByDate));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionDetail, PositionProfitByTrade));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionDetail, Margin));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionDetail, ExchMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionDetail, MarginRateByMoney));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionDetail, MarginRateByVolume));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionDetail, LastSettlementPrice));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionDetail, SettlementPrice));
  CHECK(SetObjectInt32(env, *result, pInvestorPositionDetail, CloseVolume));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionDetail, CloseAmount));
  CHECK(SetObjectInt32(env, *result, pInvestorPositionDetail, TimeFirstVolume));
  CHECK(SetObjectString(env, *result, pInvestorPositionDetail, InvestUnitID));
  CHECK(SetObjectChar(env, *result, pInvestorPositionDetail, SpecPosiType));
  CHECK(SetObjectString(env, *result, pInvestorPositionDetail, InstrumentID));
  CHECK(SetObjectString(env, *result, pInvestorPositionDetail, CombInstrumentID));

  return napi_ok;
}

napi_status rspQryNotice(napi_env env, const Message *message, napi_value *result) {
  auto pNotice = MessageData<CThostFtdcNoticeField>(message);

  if (!pNotice)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcNoticeField"));
  CHECK(SetObjectString(env, *result, pNotice, BrokerID));
  CHECK(SetObjectString(env, *result, pNotice, Content));
  CHECK(SetObjectString(env, *result, pNotice, SequenceLabel));

  return napi_ok;
}

napi_status rspQrySettlementInfoConfirm(napi_env env, const Message *message, napi_value *result) {
  auto pSettlementInfoConfirm = MessageData<CThostFtdcSettlementInfoConfirmField>(message);

  if (!pSettlementInfoConfirm)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcSettlementInfoConfirmField"));
  CHECK(SetObjectString(env, *result, pSettlementInfoConfirm, BrokerID));
  CHECK(SetObjectString(env, *result, pSettlementInfoConfirm, InvestorID));
  CHECK(SetObjectString(env, *result, pSettlementInfoConfirm, ConfirmDate));
  CHECK(SetObjectString(env, *result, pSettlementInfoConfirm, ConfirmTime));
  CHECK(SetObjectInt32(env, *result, pSettlementInfoConfirm, SettlementID));
  CHECK(SetObjectString(env, *result, pSettlementInfoConfirm, AccountID));
  CHECK(SetObjectString(env, *result, pSettlementInfoConfirm, CurrencyID));

  return napi_ok;
}

napi_status rspQryInvestorPositionCombineDetail(napi_env env, const Message *message, napi_value *result) {
  auto pInvestorPositionCombineDetail = MessageData<CThostFtdcInvestorPositionCombineDetailField>(message);

  if (!pInvestorPositionCombineDetail)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInvestorPositionCombineDetailField"));
  CHECK(SetObjectString(env, *result, pInvestorPositionCombineDetail, TradingDay));
  CHECK(SetObjectString(env, *result, pInvestorPositionCombineDetail, OpenDate));
  CHECK(SetObjectString(env, *result, pInvestorPositionCombineDetail, ExchangeID));
  CHECK(SetObjectInt32(env, *result, pInvestorPositionCombineDetail, SettlementID));
  CHECK(SetObjectString(env, *result, pInvestorPositionCombineDetail, BrokerID));
  CHECK(SetObjectString(env, *result, pInvestorPositionCombineDetail, InvestorID));
  CHECK(SetObjectString(env, *result, pInvestorPositionCombineDetail, ComTradeID));
  CHECK(SetObjectString(env, *result, pInvestorPositionCombineDetail, TradeID));
  CHECK(SetObjectChar(env, *result, pInvestorPositionCombineDetail, HedgeFlag));
  CHECK(SetObjectChar(env, *result, pInvestorPositionCombineDetail, Direction));
  CHECK(SetObjectInt32(env, *result, pInvestorPositionCombineDetail, TotalAmt));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionCombineDetail, Margin));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionCombineDetail, ExchMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionCombineDetail, MarginRateByMoney));
  CHECK(SetObjectDouble(env, *result, pInvestorPositionCombineDetail, MarginRateByVolume));
  CHECK(SetObjectInt32(env, *result, pInvestorPositionCombineDetail, LegID));
  CHECK(SetObjectInt32(env, *result, pInvestorPositionCombineDetail, LegMultiple));
  CHECK(SetObjectInt32(env, *result, pInvestorPositionCombineDetail, TradeGroupID));
  CHECK(SetObjectString(env, *result, pInvestorPositionCombineDetail, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInvestorPositionCombineDetail, InstrumentID));
  CHECK(SetObjectString(env, *result, pInvestorPositionCombineDetail, CombInstrumentID));

  return napi_ok;
}

napi_status rspQryCFMMCTradingAccountKey(napi_env env, const Message *message, napi_value *result) {
  auto pCFMMCTradingAccountKey = MessageData<CThostFtdcCFMMCTradingAccountKeyField>(message);

  if (!pCFMMCTradingAccountKey)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcCFMMCTradingAccountKeyField"));
  CHECK(SetObjectString(env, *result, pCFMMCTradingAccountKey, BrokerID));
  CHECK(SetObjectString(env, *result, pCFMMCTradingAccountKey, ParticipantID));
  CHECK(SetObjectString(env, *result, pCFMMCTradingAccountKey, AccountID));
  CHECK(SetObjectInt32(env, *result, pCFMMCTradingAccountKey, KeyID));
  CHECK(SetObjectString(env, *result, pCFMMCTradingAccountKey, CurrentKey));

  return napi_ok;
}

napi_status rspQryEWarrantOffset(napi_env env, const Message *message, napi_value *result) {
  auto pEWarrantOffset = MessageData<CThostFtdcEWarrantOffsetField>(message);

  if (!pEWarrantOffset)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcEWarrantOffsetField"));
  CHECK(SetObjectString(env, *result, pEWarrantOffset, TradingDay));
  CHECK(SetObjectString(env, *result, pEWarrantOffset, BrokerID));
  CHECK(SetObjectString(env, *result, pEWarrantOffset, InvestorID));
  CHECK(SetObjectString(env, *result, pEWarrantOffset, ExchangeID));
  CHECK(SetObjectChar(env, *result, pEWarrantOffset, Direction));
  CHECK(SetObjectChar(env, *result, pEWarrantOffset, HedgeFlag));
  CHECK(SetObjectInt32(env, *result, pEWarrantOffset, Volume));
  CHECK(SetObjectString(env, *result, pEWarrantOffset, InvestUnitID));
  CHECK(SetObjectString(env, *result, pEWarrantOffset, InstrumentID));

  return napi_ok;
}

napi_status rspQryInvestorProductGroupMargin(napi_env env, const Message *message, napi_value *result) {
  auto pInvestorProductGroupMargin = MessageData<CThostFtdcInvestorProductGroupMarginField>(message);

  if (!pInvestorProductGroupMargin)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInvestorProductGroupMarginField"));
  CHECK(SetObjectString(env, *result, pInvestorProductGroupMargin, BrokerID));
  CHECK(SetObjectString(env, *result, pInvestorProductGroupMargin, InvestorID));
  CHECK(SetObjectString(env, *result, pInvestorProductGroupMargin, TradingDay));
  CHECK(SetObjectInt32(env, *result, pInvestorProductGroupMargin, SettlementID));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, FrozenMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, LongFrozenMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, ShortFrozenMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, UseMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, LongUseMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, ShortUseMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, ExchMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, LongExchMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, ShortExchMargin));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, CloseProfit));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, FrozenCommission));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, Commission));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, FrozenCash));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, CashIn));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, PositionProfit));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, OffsetAmount));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, LongOffsetAmount));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, ShortOffsetAmount));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, ExchOffsetAmount));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, LongExchOffsetAmount));
  CHECK(SetObjectDouble(env, *result, pInvestorProductGroupMargin, ShortExchOffsetAmount));
  CHECK(SetObjectChar(env, *result, pInvestorProductGroupMargin, HedgeFlag));
  CHECK(SetObjectString(env, *result, pInvestorProductGroupMargin, ExchangeID));
  CHECK(SetObjectString(env, *result, pInvestorProductGroupMargin, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInvestorProductGroupMargin, ProductGroupID));

  return napi_ok;
}

napi_status rspQryExchangeMarginRate(napi_env env, const Message *message, napi_value *result) {
  auto pExchangeMarginRate = MessageData<CThostFtdcExchangeMarginRateField>(message);

  if (!pExchangeMarginRate)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcExchangeMarginRateField"));
  CHECK(SetObjectString(env, *result, pExchangeMarginRate, BrokerID));
  CHECK(SetObjectChar(env, *result, pExchangeMarginRate, HedgeFlag));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRate, LongMarginRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRate, LongMarginRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRate, ShortMarginRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRate, ShortMarginRatioByVolume));
  CHECK(SetObjectString(env, *result, pExchangeMarginRate, ExchangeID));
  CHECK(SetObjectString(env, *result, pExchangeMarginRate, InstrumentID));

  return napi_ok;
}

napi_status rspQryExchangeMarginRateAdjust(napi_env env, const Message *message, napi_value *result) {
  auto pExchangeMarginRateAdjust = MessageData<CThostFtdcExchangeMarginRateAdjustField>(message);

  if (!pExchangeMarginRateAdjust)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcExchangeMarginRateAdjustField"));
  CHECK(SetObjectString(env, *result, pExchangeMarginRateAdjust, BrokerID));
  CHECK(SetObjectChar(env, *result, pExchangeMarginRateAdjust, HedgeFlag));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRateAdjust, LongMarginRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRateAdjust, LongMarginRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRateAdjust, ShortMarginRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRateAdjust, ShortMarginRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRateAdjust, ExchLongMarginRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRateAdjust, ExchLongMarginRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRateAdjust, ExchShortMarginRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRateAdjust, ExchShortMarginRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRateAdjust, NoLongMarginRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRateAdjust, NoLongMarginRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRateAdjust, NoShortMarginRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pExchangeMarginRateAdjust, NoShortMarginRatioByVolume));
  CHECK(SetObjectString(env, *result, pExchangeMarginRateAdjust, InstrumentID));

  return napi_ok;
}

napi_status rspQryExchangeRate(napi_env env, const Message *message, napi_value *result) {
  auto pExchangeRate = MessageData<CThostFtdcExchangeRateField>(message);

  if (!pExchangeRate)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcExchangeRateField"));
  CHECK(SetObjectString(env, *result, pExchangeRate, BrokerID));
  CHECK(SetObjectString(env, *result, pExchangeRate, FromCurrencyID));
  CHECK(SetObjectDouble(env, *result, pExchangeRate, FromCurrencyUnit));
  CHECK(SetObjectString(env, *result, pExchangeRate, ToCurrencyID));
  CHECK(SetObjectDouble(env, *result, pExchangeRate, ExchangeRate));

  return napi_ok;
}

napi_status rspQrySecAgentACIDMap(napi_env env, const Message *message, napi_value *result) {
  auto pSecAgentACIDMap = MessageData<CThostFtdcSecAgentACIDMapField>(message);

  if (!pSecAgentACIDMap)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcSecAgentACIDMapField"));
  CHECK(SetObjectString(env, *result, pSecAgentACIDMap, BrokerID));
  CHECK(SetObjectString(env, *result, pSecAgentACIDMap, UserID));
  CHECK(SetObjectString(env, *result, pSecAgentACIDMap, AccountID));
  CHECK(SetObjectString(env, *result, pSecAgentACIDMap, CurrencyID));
  CHECK(SetObjectString(env, *result, pSecAgentACIDMap, BrokerSecAgentID));

  return napi_ok;
}

napi_status rspQryProductExchRate(napi_env env, const Message *message, napi_value *result) {
  auto pProductExchRate = MessageData<CThostFtdcProductExchRateField>(message);

  if (!pProductExchRate)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcProductExchRateField"));
  CHECK(SetObjectString(env, *result, pProductExchRate, QuoteCurrencyID));
  CHECK(SetObjectDouble(env, *result, pProductExchRate, ExchangeRate));
  CHECK(SetObjectString(env, *result, pProductExchRate, ExchangeID));
  CHECK(SetObjectString(env, *result, pProductExchRate, ProductID));

  return napi_ok;
}

napi_status rspQryProductGroup(napi_env env, const Message *message, napi_value *result) {
  auto pProductGroup = MessageData<CThostFtdcProductGroupField>(message);

  if (!pProductGroup)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcProductGroupField"));
  CHECK(SetObjectString(env, *result, pProductGroup, ExchangeID));
  CHECK(SetObjectString(env, *result, pProductGroup, ProductID));
  CHECK(SetObjectString(env, *result, pProductGroup, ProductGroupID));

  return napi_ok;
}

napi_status rspQryMMInstrumentCommissionRate(napi_env env, const Message *message, napi_value *result) {
  auto pMMInstrumentCommissionRate = MessageData<CThostFtdcMMInstrumentCommissionRateField>(message);

  if (!pMMInstrumentCommissionRate)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcMMInstrumentCommissionRateField"));
  CHECK(SetObjectChar(env, *result, pMMInstrumentCommissionRate, InvestorRange));
  CHECK(SetObjectString(env, *result, pMMInstrumentCommissionRate, BrokerID));
  CHECK(SetObjectString(env, *result, pMMInstrumentCommissionRate, InvestorID));
  CHECK(SetObjectDouble(env, *result, pMMInstrumentCommissionRate, OpenRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pMMInstrumentCommissionRate, OpenRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pMMInstrumentCommissionRate, CloseRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pMMInstrumentCommissionRate, CloseRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pMMInstrumentCommissionRate, CloseTodayRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pMMInstrumentCommissionRate, CloseTodayRatioByVolume));
  CHECK(SetObjectString(env, *result, pMMInstrumentCommissionRate, InstrumentID));

  return napi_ok;
}

napi_status rspQryMMOptionInstrCommRate(napi_env env, const Message *message, napi_value *result) {
  auto pMMOptionInstrCommRate = MessageData<CThostFtdcMMOptionInstrCommRateField>(message);

  if (!pMMOptionInstrCommRate)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcMMOptionInstrCommRateField"));
  CHECK(SetObjectChar(env, *result, pMMOptionInstrCommRate, InvestorRange));
  CHECK(SetObjectString(env, *result, pMMOptionInstrCommRate, BrokerID));
  CHECK(SetObjectString(env, *result, pMMOptionInstrCommRate, InvestorID));
  CHECK(SetObjectDouble(env, *result, pMMOptionInstrCommRate, OpenRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pMMOptionInstrCommRate, OpenRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pMMOptionInstrCommRate, CloseRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pMMOptionInstrCommRate, CloseRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pMMOptionInstrCommRate, CloseTodayRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pMMOptionInstrCommRate, CloseTodayRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pMMOptionInstrCommRate, StrikeRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pMMOptionInstrCommRate, StrikeRatioByVolume));
  CHECK(SetObjectString(env, *result, pMMOptionInstrCommRate, InstrumentID));

  return napi_ok;
}

napi_status rspQryInstrumentOrderCommRate(napi_env env, const Message *message, napi_value *result) {
  auto pInstrumentOrderCommRate = MessageData<CThostFtdcInstrumentOrderCommRateField>(message);

  if (!pInstrumentOrderCommRate)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInstrumentOrderCommRateField"));
  CHECK(SetObjectChar(env, *result, pInstrumentOrderCommRate, InvestorRange));
  CHECK(SetObjectString(env, *result, pInstrumentOrderCommRate, BrokerID));
  CHECK(SetObjectString(env, *result, pInstrumentOrderCommRate, InvestorID));
  CHECK(SetObjectChar(env, *result, pInstrumentOrderCommRate, HedgeFlag));
  CHECK(SetObjectDouble(env, *result, pInstrumentOrderCommRate, OrderCommByVolume));
  CHECK(SetObjectDouble(env, *result, pInstrumentOrderCommRate, OrderActionCommByVolume));
  CHECK(SetObjectString(env, *result, pInstrumentOrderCommRate, ExchangeID));
  CHECK(SetObjectString(env, *result, pInstrumentOrderCommRate, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInstrumentOrderCommRate, InstrumentID));
  CHECK(SetObjectDouble(env, *result, pInstrumentOrderCommRate, OrderCommByTrade));
  CHECK(SetObjectDouble(env, *result, pInstrumentOrderCommRate, OrderActionCommByTrade));

  return napi_ok;
}

napi_status rspQrySecAgentTradingAccount(napi_env env, const Message *message, napi_value *result) {
  auto pTradingAccount = MessageData<CThostFtdcTradingAccountField>(message);

  if (!pTradingAccount)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcTradingAccountField"));
  CHECK(SetObjectString(env, *result, pTradingAccount, BrokerID));
  CHECK(SetObjectString(env, *result, pTradingAccount, AccountID));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreMortgage));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreCredit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreDeposit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreBalance));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, InterestBase));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Interest));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Deposit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Withdraw));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FrozenMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FrozenCash));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FrozenCommission));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, CurrMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, CashIn));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Commission));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, CloseProfit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PositionProfit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Balance));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Available));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, WithdrawQuota));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Reserve));
  CHECK(SetObjectString(env, *result, pTradingAccount, TradingDay));
  CHECK(SetObjectInt32(env, *result, pTradingAccount, SettlementID));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Credit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, Mortgage));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, ExchangeMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, DeliveryMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, ExchangeDeliveryMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, ReserveBalance));
  CHECK(SetObjectString(env, *result, pTradingAccount, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreFundMortgageIn));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, PreFundMortgageOut));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FundMortgageIn));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FundMortgageOut));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FundMortgageAvailable));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, MortgageableFund));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductFrozenMargin));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductCommission));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductFrozenCommission));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductPositionProfit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductCloseProfit));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductPositionProfitByAlg));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, SpecProductExchangeMargin));
  CHECK(SetObjectChar(env, *result, pTradingAccount, BizType));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, FrozenSwap));
  CHECK(SetObjectDouble(env, *result, pTradingAccount, RemainSwap));

  return napi_ok;
}

napi_status rspQrySecAgentCheckMode(napi_env env, const Message *message, napi_value *result) {
  auto pSecAgentCheckMode = MessageData<CThostFtdcSecAgentCheckModeField>(message);

  if (!pSecAgentCheckMode)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcSecAgentCheckModeField"));
  CHECK(SetObjectString(env, *result, pSecAgentCheckMode, InvestorID));
  CHECK(SetObjectString(env, *result, pSecAgentCheckMode, BrokerID));
  CHECK(SetObjectString(env, *result, pSecAgentCheckMode, CurrencyID));
  CHECK(SetObjectString(env, *result, pSecAgentCheckMode, BrokerSecAgentID));
  CHECK(SetObjectInt32(env, *result, pSecAgentCheckMode, CheckSelfAccount));

  return napi_ok;
}

napi_status rspQrySecAgentTradeInfo(napi_env env, const Message *message, napi_value *result) {
  auto pSecAgentTradeInfo = MessageData<CThostFtdcSecAgentTradeInfoField>(message);

  if (!pSecAgentTradeInfo)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcSecAgentTradeInfoField"));
  CHECK(SetObjectString(env, *result, pSecAgentTradeInfo, BrokerID));
  CHECK(SetObjectString(env, *result, pSecAgentTradeInfo, BrokerSecAgentID));
  CHECK(SetObjectString(env, *result, pSecAgentTradeInfo, InvestorID));
  CHECK(SetObjectString(env, *result, pSecAgentTradeInfo, LongCustomerName));

  return napi_ok;
}

napi_status rspQryOptionInstrTradeCost(napi_env env, const Message *message, napi_value *result) {
  auto pOptionInstrTradeCost = MessageData<CThostFtdcOptionInstrTradeCostField>(message);

  if (!pOptionInstrTradeCost)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcOptionInstrTradeCostField"));
  CHECK(SetObjectString(env, *result, pOptionInstrTradeCost, BrokerID));
  CHECK(SetObjectString(env, *result, pOptionInstrTradeCost, InvestorID));
  CHECK(SetObjectChar(env, *result, pOptionInstrTradeCost, HedgeFlag));
  CHECK(SetObjectDouble(env, *result, pOptionInstrTradeCost, FixedMargin));
  CHECK(SetObjectDouble(env, *result, pOptionInstrTradeCost, MiniMargin));
  CHECK(SetObjectDouble(env, *result, pOptionInstrTradeCost, Royalty));
  CHECK(SetObjectDouble(env, *result, pOptionInstrTradeCost, ExchFixedMargin));
  CHECK(SetObjectDouble(env, *result, pOptionInstrTradeCost, ExchMiniMargin));
  CHECK(SetObjectString(env, *result, pOptionInstrTradeCost, ExchangeID));
  CHECK(SetObjectString(env, *result, pOptionInstrTradeCost, InvestUnitID));
  CHECK(SetObjectString(env, *result, pOptionInstrTradeCost, InstrumentID));

  return napi_ok;
}

napi_status rspQryOptionInstrCommRate(napi_env env, const Message *message, napi_value *result) {
  auto pOptionInstrCommRate = MessageData<CThostFtdcOptionInstrCommRateField>(message);

  if (!pOptionInstrCommRate)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcOptionInstrCommRateField"));
  CHECK(SetObjectChar(env, *result, pOptionInstrCommRate, InvestorRange));
  CHECK(SetObjectString(env, *result, pOptionInstrCommRate, BrokerID));
  CHECK(SetObjectString(env, *result, pOptionInstrCommRate, InvestorID));
  CHECK(SetObjectDouble(env, *result, pOptionInstrCommRate, OpenRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pOptionInstrCommRate, OpenRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pOptionInstrCommRate, CloseRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pOptionInstrCommRate, CloseRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pOptionInstrCommRate, CloseTodayRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pOptionInstrCommRate, CloseTodayRatioByVolume));
  CHECK(SetObjectDouble(env, *result, pOptionInstrCommRate, StrikeRatioByMoney));
  CHECK(SetObjectDouble(env, *result, pOptionInstrCommRate, StrikeRatioByVolume));
  CHECK(SetObjectString(env, *result, pOptionInstrCommRate, ExchangeID));
  CHECK(SetObjectString(env, *result, pOptionInstrCommRate, InvestUnitID));
  CHECK(SetObjectString(env, *result, pOptionInstrCommRate, InstrumentID));

  return napi_ok;
}

napi_status rspQryExecOrder(napi_env env, const Message *message, napi_value *result) {
  auto pExecOrder = MessageData<CThostFtdcExecOrderField>(message);

  if (!pExecOrder)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcExecOrderField"));
  CHECK(SetObjectString(env, *result, pExecOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pExecOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pExecOrder, ExecOrderRef));
  CHECK(SetObjectString(env, *result, pExecOrder, UserID));
  CHECK(SetObjectInt32(env, *result, pExecOrder, Volume));
  CHECK(SetObjectInt32(env, *result, pExecOrder, RequestID));
  CHECK(SetObjectString(env, *result, pExecOrder, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pExecOrder, OffsetFlag));
  CHECK(SetObjectChar(env, *result, pExecOrder, HedgeFlag));
  CHECK(SetObjectChar(env, *result, pExecOrder, ActionType));
  CHECK(SetObjectChar(env, *result, pExecOrder, PosiDirection));
  CHECK(SetObjectChar(env, *result, pExecOrder, ReservePositionFlag));
  CHECK(SetObjectChar(env, *result, pExecOrder, CloseFlag));
  CHECK(SetObjectString(env, *result, pExecOrder, ExecOrderLocalID));
  CHECK(SetObjectString(env, *result, pExecOrder, ExchangeID));
  CHECK(SetObjectString(env, *result, pExecOrder, ParticipantID));
  CHECK(SetObjectString(env, *result, pExecOrder, ClientID));
  CHECK(SetObjectString(env, *result, pExecOrder, TraderID));
  CHECK(SetObjectInt32(env, *result, pExecOrder, InstallID));
  CHECK(SetObjectChar(env, *result, pExecOrder, OrderSubmitStatus));
  CHECK(SetObjectInt32(env, *result, pExecOrder, NotifySequence));
  CHECK(SetObjectString(env, *result, pExecOrder, TradingDay));
  CHECK(SetObjectInt32(env, *result, pExecOrder, SettlementID));
  CHECK(SetObjectString(env, *result, pExecOrder, ExecOrderSysID));
  CHECK(SetObjectString(env, *result, pExecOrder, InsertDate));
  CHECK(SetObjectString(env, *result, pExecOrder, InsertTime));
  CHECK(SetObjectString(env, *result, pExecOrder, CancelTime));
  CHECK(SetObjectChar(env, *result, pExecOrder, ExecResult));
  CHECK(SetObjectString(env, *result, pExecOrder, ClearingPartID));
  CHECK(SetObjectInt32(env, *result, pExecOrder, SequenceNo));
  CHECK(SetObjectInt32(env, *result, pExecOrder, FrontID));
  CHECK(SetObjectInt32(env, *result, pExecOrder, SessionID));
  CHECK(SetObjectString(env, *result, pExecOrder, UserProductInfo));
  CHECK(SetObjectString(env, *result, pExecOrder, StatusMsg));
  CHECK(SetObjectString(env, *result, pExecOrder, ActiveUserID));
  CHECK(SetObjectInt32(env, *result, pExecOrder, BrokerExecOrderSeq));
  CHECK(SetObjectString(env, *result, pExecOrder, BranchID));
  CHECK(SetObjectString(env, *result, pExecOrder, InvestUnitID));
  CHECK(SetObjectString(env, *result, pExecOrder, AccountID));
  CHECK(SetObjectString(env, *result, pExecOrder, CurrencyID));
  CHECK(SetObjectString(env, *result, pExecOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pExecOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pExecOrder, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pExecOrder, IPAddress));

  return napi_ok;
}

napi_status rspQryForQuote(napi_env env, const Message *message, napi_value *result) {
  auto pForQuote = MessageData<CThostFtdcForQuoteField>(message);

  if (!pForQuote)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcForQuoteField"));
  CHECK(SetObjectString(env, *result, pForQuote, BrokerID));
  CHECK(SetObjectString(env, *result, pForQuote, InvestorID));
  CHECK(SetObjectString(env, *result, pForQuote, ForQuoteRef));
  CHECK(SetObjectString(env, *result, pForQuote, UserID));
  CHECK(SetObjectString(env, *result, pForQuote, ForQuoteLocalID));
  CHECK(SetObjectString(env, *result, pForQuote, ExchangeID));
  CHECK(SetObjectString(env, *result, pForQuote, ParticipantID));
  CHECK(SetObjectString(env, *result, pForQuote, ClientID));
  CHECK(SetObjectString(env, *result, pForQuote, TraderID));
  CHECK(SetObjectInt32(env, *result, pForQuote, InstallID));
  CHECK(SetObjectString(env, *result, pForQuote, InsertDate));
  CHECK(SetObjectString(env, *result, pForQuote, InsertTime));
  CHECK(SetObjectChar(env, *result, pForQuote, ForQuoteStatus));
  CHECK(SetObjectInt32(env, *result, pForQuote, FrontID));
  CHECK(SetObjectInt32(env, *result, pForQuote, SessionID));
  CHECK(SetObjectString(env, *result, pForQuote, StatusMsg));
  CHECK(SetObjectString(env, *result, pForQuote, ActiveUserID));
  CHECK(SetObjectInt32(env, *result, pForQuote, BrokerForQutoSeq));
  CHECK(SetObjectString(env, *result, pForQuote, InvestUnitID));
  CHECK(SetObjectString(env, *result, pForQuote, MacAddress));
  CHECK(SetObjectString(env, *result, pForQuote, InstrumentID));
  CHECK(SetObjectString(env, *result, pForQuote, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pForQuote, IPAddress));

  return napi_ok;
}

napi_status rspQryQuote(napi_env env, const Message *message, napi_value *result) {
  auto pQuote = MessageData<CThostFtdcQuoteField>(message);

  if (!pQuote)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcQuoteField"));
  CHECK(SetObjectString(env, *result, pQuote, BrokerID));
  CHECK(SetObjectString(env, *result, pQuote, InvestorID));
  CHECK(SetObjectString(env, *result, pQuote, QuoteRef));
  CHECK(SetObjectString(env, *result, pQuote, UserID));
  CHECK(SetObjectDouble(env, *result, pQuote, AskPrice));
  CHECK(SetObjectDouble(env, *result, pQuote, BidPrice));
  CHECK(SetObjectInt32(env, *result, pQuote, AskVolume));
  CHECK(SetObjectInt32(env, *result, pQuote, BidVolume));
  CHECK(SetObjectInt32(env, *result, pQuote, RequestID));
  CHECK(SetObjectString(env, *result, pQuote, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pQuote, AskOffsetFlag));
  CHECK(SetObjectChar(env, *result, pQuote, BidOffsetFlag));
  CHECK(SetObjectChar(env, *result, pQuote, AskHedgeFlag));
  CHECK(SetObjectChar(env, *result, pQuote, BidHedgeFlag));
  CHECK(SetObjectString(env, *result, pQuote, QuoteLocalID));
  CHECK(SetObjectString(env, *result, pQuote, ExchangeID));
  CHECK(SetObjectString(env, *result, pQuote, ParticipantID));
  CHECK(SetObjectString(env, *result, pQuote, ClientID));
  CHECK(SetObjectString(env, *result, pQuote, TraderID));
  CHECK(SetObjectInt32(env, *result, pQuote, InstallID));
  CHECK(SetObjectInt32(env, *result, pQuote, NotifySequence));
  CHECK(SetObjectChar(env, *result, pQuote, OrderSubmitStatus));
  CHECK(SetObjectString(env, *result, pQuote, TradingDay));
  CHECK(SetObjectInt32(env, *result, pQuote, SettlementID));
  CHECK(SetObjectString(env, *result, pQuote, QuoteSysID));
  CHECK(SetObjectString(env, *result, pQuote, InsertDate));
  CHECK(SetObjectString(env, *result, pQuote, InsertTime));
  CHECK(SetObjectString(env, *result, pQuote, CancelTime));
  CHECK(SetObjectChar(env, *result, pQuote, QuoteStatus));
  CHECK(SetObjectString(env, *result, pQuote, ClearingPartID));
  CHECK(SetObjectInt32(env, *result, pQuote, SequenceNo));
  CHECK(SetObjectString(env, *result, pQuote, AskOrderSysID));
  CHECK(SetObjectString(env, *result, pQuote, BidOrderSysID));
  CHECK(SetObjectInt32(env, *result, pQuote, FrontID));
  CHECK(SetObjectInt32(env, *result, pQuote, SessionID));
  CHECK(SetObjectString(env, *result, pQuote, UserProductInfo));
  CHECK(SetObjectString(env, *result, pQuote, StatusMsg));
  CHECK(SetObjectString(env, *result, pQuote, ActiveUserID));
  CHECK(SetObjectInt32(env, *result, pQuote, BrokerQuoteSeq));
  CHECK(SetObjectString(env, *result, pQuote, AskOrderRef));
  CHECK(SetObjectString(env, *result, pQuote, BidOrderRef));
  CHECK(SetObjectString(env, *result, pQuote, ForQuoteSysID));
  CHECK(SetObjectString(env, *result, pQuote, BranchID));
  CHECK(SetObjectString(env, *result, pQuote, InvestUnitID));
  CHECK(SetObjectString(env, *result, pQuote, AccountID));
  CHECK(SetObjectString(env, *result, pQuote, CurrencyID));
  CHECK(SetObjectString(env, *result, pQuote, MacAddress));
  CHECK(SetObjectString(env, *result, pQuote, InstrumentID));
  CHECK(SetObjectString(env, *result, pQuote, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pQuote, IPAddress));
  CHECK(SetObjectString(env, *result, pQuote, ReplaceSysID));

  return napi_ok;
}

napi_status rspQryOptionSelfClose(napi_env env, const Message *message, napi_value *result) {
  auto pOptionSelfClose = MessageData<CThostFtdcOptionSelfCloseField>(message);

  if (!pOptionSelfClose)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcOptionSelfCloseField"));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, BrokerID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, InvestorID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, OptionSelfCloseRef));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, UserID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, Volume));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, RequestID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pOptionSelfClose, HedgeFlag));
  CHECK(SetObjectChar(env, *result, pOptionSelfClose, OptSelfCloseFlag));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, OptionSelfCloseLocalID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, ExchangeID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, ParticipantID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, ClientID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, TraderID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, InstallID));
  CHECK(SetObjectChar(env, *result, pOptionSelfClose, OrderSubmitStatus));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, NotifySequence));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, TradingDay));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, SettlementID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, OptionSelfCloseSysID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, InsertDate));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, InsertTime));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, CancelTime));
  CHECK(SetObjectChar(env, *result, pOptionSelfClose, ExecResult));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, ClearingPartID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, SequenceNo));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, FrontID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, SessionID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, UserProductInfo));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, StatusMsg));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, ActiveUserID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, BrokerOptionSelfCloseSeq));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, BranchID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, InvestUnitID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, AccountID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, CurrencyID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, MacAddress));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, InstrumentID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, IPAddress));

  return napi_ok;
}

napi_status rspQryInvestUnit(napi_env env, const Message *message, napi_value *result) {
  auto pInvestUnit = MessageData<CThostFtdcInvestUnitField>(message);

  if (!pInvestUnit)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInvestUnitField"));
  CHECK(SetObjectString(env, *result, pInvestUnit, BrokerID));
  CHECK(SetObjectString(env, *result, pInvestUnit, InvestorID));
  CHECK(SetObjectString(env, *result, pInvestUnit, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInvestUnit, InvestorUnitName));
  CHECK(SetObjectString(env, *result, pInvestUnit, InvestorGroupID));
  CHECK(SetObjectString(env, *result, pInvestUnit, CommModelID));
  CHECK(SetObjectString(env, *result, pInvestUnit, MarginModelID));
  CHECK(SetObjectString(env, *result, pInvestUnit, AccountID));
  CHECK(SetObjectString(env, *result, pInvestUnit, CurrencyID));

  return napi_ok;
}

napi_status rspQryCombInstrumentGuard(napi_env env, const Message *message, napi_value *result) {
  auto pCombInstrumentGuard = MessageData<CThostFtdcCombInstrumentGuardField>(message);

  if (!pCombInstrumentGuard)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcCombInstrumentGuardField"));
  CHECK(SetObjectString(env, *result, pCombInstrumentGuard, BrokerID));
  CHECK(SetObjectDouble(env, *result, pCombInstrumentGuard, GuarantRatio));
  CHECK(SetObjectString(env, *result, pCombInstrumentGuard, ExchangeID));
  CHECK(SetObjectString(env, *result, pCombInstrumentGuard, InstrumentID));

  return napi_ok;
}

napi_status rspQryCombAction(napi_env env, const Message *message, napi_value *result) {
  auto pCombAction = MessageData<CThostFtdcCombActionField>(message);

  if (!pCombAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcCombActionField"));
  CHECK(SetObjectString(env, *result, pCombAction, BrokerID));
  CHECK(SetObjectString(env, *result, pCombAction, InvestorID));
  CHECK(SetObjectString(env, *result, pCombAction, CombActionRef));
  CHECK(SetObjectString(env, *result, pCombAction, UserID));
  CHECK(SetObjectChar(env, *result, pCombAction, Direction));
  CHECK(SetObjectInt32(env, *result, pCombAction, Volume));
  CHECK(SetObjectChar(env, *result, pCombAction, CombDirection));
  CHECK(SetObjectChar(env, *result, pCombAction, HedgeFlag));
  CHECK(SetObjectString(env, *result, pCombAction, ActionLocalID));
  CHECK(SetObjectString(env, *result, pCombAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pCombAction, ParticipantID));
  CHECK(SetObjectString(env, *result, pCombAction, ClientID));
  CHECK(SetObjectString(env, *result, pCombAction, TraderID));
  CHECK(SetObjectInt32(env, *result, pCombAction, InstallID));
  CHECK(SetObjectChar(env, *result, pCombAction, ActionStatus));
  CHECK(SetObjectInt32(env, *result, pCombAction, NotifySequence));
  CHECK(SetObjectString(env, *result, pCombAction, TradingDay));
  CHECK(SetObjectInt32(env, *result, pCombAction, SettlementID));
  CHECK(SetObjectInt32(env, *result, pCombAction, SequenceNo));
  CHECK(SetObjectInt32(env, *result, pCombAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pCombAction, SessionID));
  CHECK(SetObjectString(env, *result, pCombAction, UserProductInfo));
  CHECK(SetObjectString(env, *result, pCombAction, StatusMsg));
  CHECK(SetObjectString(env, *result, pCombAction, MacAddress));
  CHECK(SetObjectString(env, *result, pCombAction, ComTradeID));
  CHECK(SetObjectString(env, *result, pCombAction, BranchID));
  CHECK(SetObjectString(env, *result, pCombAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pCombAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pCombAction, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pCombAction, IPAddress));

  return napi_ok;
}

napi_status rspQryTransferSerial(napi_env env, const Message *message, napi_value *result) {
  auto pTransferSerial = MessageData<CThostFtdcTransferSerialField>(message);

  if (!pTransferSerial)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcTransferSerialField"));
  CHECK(SetObjectInt32(env, *result, pTransferSerial, PlateSerial));
  CHECK(SetObjectString(env, *result, pTransferSerial, TradeDate));
  CHECK(SetObjectString(env, *result, pTransferSerial, TradingDay));
  CHECK(SetObjectString(env, *result, pTransferSerial, TradeTime));
  CHECK(SetObjectString(env, *result, pTransferSerial, TradeCode));
  CHECK(SetObjectInt32(env, *result, pTransferSerial, SessionID));
  CHECK(SetObjectString(env, *result, pTransferSerial, BankID));
  CHECK(SetObjectString(env, *result, pTransferSerial, BankBranchID));
  CHECK(SetObjectChar(env, *result, pTransferSerial, BankAccType));
  CHECK(SetObjectString(env, *result, pTransferSerial, BankAccount));
  CHECK(SetObjectString(env, *result, pTransferSerial, BankSerial));
  CHECK(SetObjectString(env, *result, pTransferSerial, BrokerID));
  CHECK(SetObjectString(env, *result, pTransferSerial, BrokerBranchID));
  CHECK(SetObjectChar(env, *result, pTransferSerial, FutureAccType));
  CHECK(SetObjectString(env, *result, pTransferSerial, AccountID));
  CHECK(SetObjectString(env, *result, pTransferSerial, InvestorID));
  CHECK(SetObjectInt32(env, *result, pTransferSerial, FutureSerial));
  CHECK(SetObjectChar(env, *result, pTransferSerial, IdCardType));
  CHECK(SetObjectString(env, *result, pTransferSerial, IdentifiedCardNo));
  CHECK(SetObjectString(env, *result, pTransferSerial, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pTransferSerial, CustFee));
  CHECK(SetObjectDouble(env, *result, pTransferSerial, BrokerFee));
  CHECK(SetObjectChar(env, *result, pTransferSerial, AvailabilityFlag));
  CHECK(SetObjectString(env, *result, pTransferSerial, OperatorCode));
  CHECK(SetObjectString(env, *result, pTransferSerial, BankNewAccount));
  CHECK(SetObjectInt32(env, *result, pTransferSerial, ErrorID));
  CHECK(SetObjectString(env, *result, pTransferSerial, ErrorMsg));

  return napi_ok;
}

napi_status rspQryAccountRegister(napi_env env, const Message *message, napi_value *result) {
  auto pAccountRegister = MessageData<CThostFtdcAccountregisterField>(message);

  if (!pAccountRegister)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcAccountregisterField"));
  CHECK(SetObjectString(env, *result, pAccountRegister, TradeDay));
  CHECK(SetObjectString(env, *result, pAccountRegister, BankID));
  CHECK(SetObjectString(env, *result, pAccountRegister, BankBranchID));
  CHECK(SetObjectString(env, *result, pAccountRegister, BankAccount));
  CHECK(SetObjectString(env, *result, pAccountRegister, BrokerID));
  CHECK(SetObjectString(env, *result, pAccountRegister, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pAccountRegister, AccountID));
  CHECK(SetObjectChar(env, *result, pAccountRegister, IdCardType));
  CHECK(SetObjectString(env, *result, pAccountRegister, IdentifiedCardNo));
  CHECK(SetObjectString(env, *result, pAccountRegister, CustomerName));
  CHECK(SetObjectString(env, *result, pAccountRegister, CurrencyID));
  CHECK(SetObjectChar(env, *result, pAccountRegister, OpenOrDestroy));
  CHECK(SetObjectString(env, *result, pAccountRegister, RegDate));
  CHECK(SetObjectString(env, *result, pAccountRegister, OutDate));
  CHECK(SetObjectInt32(env, *result, pAccountRegister, TID));
  CHECK(SetObjectChar(env, *result, pAccountRegister, CustType));
  CHECK(SetObjectChar(env, *result, pAccountRegister, BankAccType));
  CHECK(SetObjectString(env, *result, pAccountRegister, LongCustomerName));

  return napi_ok;
}

napi_status rtnOrder(napi_env env, const Message *message, napi_value *result) {
  auto pOrder = MessageData<CThostFtdcOrderField>(message);

  if (!pOrder)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcOrderField"));
  CHECK(SetObjectString(env, *result, pOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pOrder, OrderRef));
  CHECK(SetObjectString(env, *result, pOrder, UserID));
  CHECK(SetObjectChar(env, *result, pOrder, OrderPriceType));
  CHECK(SetObjectChar(env, *result, pOrder, Direction));
  CHECK(SetObjectString(env, *result, pOrder, CombOffsetFlag));
  CHECK(SetObjectString(env, *result, pOrder, CombHedgeFlag));
  CHECK(SetObjectDouble(env, *result, pOrder, LimitPrice));
  CHECK(SetObjectInt32(env, *result, pOrder, VolumeTotalOriginal));
  CHECK(SetObjectChar(env, *result, pOrder, TimeCondition));
  CHECK(SetObjectString(env, *result, pOrder, GTDDate));
  CHECK(SetObjectChar(env, *result, pOrder, VolumeCondition));
  CHECK(SetObjectInt32(env, *result, pOrder, MinVolume));
  CHECK(SetObjectChar(env, *result, pOrder, ContingentCondition));
  CHECK(SetObjectInt32(env, *result, pOrder, StopPrice));
  CHECK(SetObjectChar(env, *result, pOrder, ForceCloseReason));
  CHECK(SetObjectInt32(env, *result, pOrder, IsAutoSuspend));
  CHECK(SetObjectString(env, *result, pOrder, BusinessUnit));
  CHECK(SetObjectInt32(env, *result, pOrder, RequestID));
  CHECK(SetObjectString(env, *result, pOrder, OrderLocalID));
  CHECK(SetObjectString(env, *result, pOrder, ExchangeID));
  CHECK(SetObjectString(env, *result, pOrder, ParticipantID));
  CHECK(SetObjectString(env, *result, pOrder, ClientID));
  CHECK(SetObjectString(env, *result, pOrder, TraderID));
  CHECK(SetObjectInt32(env, *result, pOrder, InstallID));
  CHECK(SetObjectChar(env, *result, pOrder, OrderSubmitStatus));
  CHECK(SetObjectInt32(env, *result, pOrder, NotifySequence));
  CHECK(SetObjectString(env, *result, pOrder, TradingDay));
  CHECK(SetObjectInt32(env, *result, pOrder, SettlementID));
  CHECK(SetObjectString(env, *result, pOrder, OrderSysID));
  CHECK(SetObjectChar(env, *result, pOrder, OrderSource));
  CHECK(SetObjectChar(env, *result, pOrder, OrderStatus));
  CHECK(SetObjectChar(env, *result, pOrder, OrderType));
  CHECK(SetObjectInt32(env, *result, pOrder, VolumeTraded));
  CHECK(SetObjectInt32(env, *result, pOrder, VolumeTotal));
  CHECK(SetObjectString(env, *result, pOrder, InsertDate));
  CHECK(SetObjectString(env, *result, pOrder, InsertTime));
  CHECK(SetObjectString(env, *result, pOrder, ActiveTime));
  CHECK(SetObjectString(env, *result, pOrder, SuspendTime));
  CHECK(SetObjectString(env, *result, pOrder, UpdateTime));
  CHECK(SetObjectString(env, *result, pOrder, CancelTime));
  CHECK(SetObjectString(env, *result, pOrder, ActiveTraderID));
  CHECK(SetObjectString(env, *result, pOrder, ClearingPartID));
  CHECK(SetObjectInt32(env, *result, pOrder, SequenceNo));
  CHECK(SetObjectInt32(env, *result, pOrder, FrontID));
  CHECK(SetObjectInt32(env, *result, pOrder, SessionID));
  CHECK(SetObjectString(env, *result, pOrder, UserProductInfo));
  CHECK(SetObjectString(env, *result, pOrder, StatusMsg));
  CHECK(SetObjectInt32(env, *result, pOrder, UserForceClose));
  CHECK(SetObjectString(env, *result, pOrder, ActiveUserID));
  CHECK(SetObjectInt32(env, *result, pOrder, BrokerOrderSeq));
  CHECK(SetObjectString(env, *result, pOrder, RelativeOrderSysID));
  CHECK(SetObjectInt32(env, *result, pOrder, ZCETotalTradedVolume));
  CHECK(SetObjectInt32(env, *result, pOrder, IsSwapOrder));
  CHECK(SetObjectString(env, *result, pOrder, BranchID));
  CHECK(SetObjectString(env, *result, pOrder, InvestUnitID));
  CHECK(SetObjectString(env, *result, pOrder, AccountID));
  CHECK(SetObjectString(env, *result, pOrder, CurrencyID));
  CHECK(SetObjectString(env, *result, pOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pOrder, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pOrder, IPAddress));

  return napi_ok;
}

napi_status rtnTrade(napi_env env, const Message *message, napi_value *result) {
  auto pTrade = MessageData<CThostFtdcTradeField>(message);

  if (!pTrade)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcTradeField"));
  CHECK(SetObjectString(env, *result, pTrade, BrokerID));
  CHECK(SetObjectString(env, *result, pTrade, InvestorID));
  CHECK(SetObjectString(env, *result, pTrade, OrderRef));
  CHECK(SetObjectString(env, *result, pTrade, UserID));
  CHECK(SetObjectString(env, *result, pTrade, ExchangeID));
  CHECK(SetObjectString(env, *result, pTrade, TradeID));
  CHECK(SetObjectChar(env, *result, pTrade, Direction));
  CHECK(SetObjectString(env, *result, pTrade, OrderSysID));
  CHECK(SetObjectString(env, *result, pTrade, ParticipantID));
  CHECK(SetObjectString(env, *result, pTrade, ClientID));
  CHECK(SetObjectChar(env, *result, pTrade, TradingRole));
  CHECK(SetObjectChar(env, *result, pTrade, OffsetFlag));
  CHECK(SetObjectChar(env, *result, pTrade, HedgeFlag));
  CHECK(SetObjectDouble(env, *result, pTrade, Price));
  CHECK(SetObjectInt32(env, *result, pTrade, Volume));
  CHECK(SetObjectString(env, *result, pTrade, TradeDate));
  CHECK(SetObjectString(env, *result, pTrade, TradeTime));
  CHECK(SetObjectChar(env, *result, pTrade, TradeType));
  CHECK(SetObjectChar(env, *result, pTrade, PriceSource));
  CHECK(SetObjectString(env, *result, pTrade, TraderID));
  CHECK(SetObjectString(env, *result, pTrade, OrderLocalID));
  CHECK(SetObjectString(env, *result, pTrade, ClearingPartID));
  CHECK(SetObjectString(env, *result, pTrade, BusinessUnit));
  CHECK(SetObjectInt32(env, *result, pTrade, SequenceNo));
  CHECK(SetObjectString(env, *result, pTrade, TradingDay));
  CHECK(SetObjectInt32(env, *result, pTrade, SettlementID));
  CHECK(SetObjectInt32(env, *result, pTrade, BrokerOrderSeq));
  CHECK(SetObjectChar(env, *result, pTrade, TradeSource));
  CHECK(SetObjectString(env, *result, pTrade, InvestUnitID));
  CHECK(SetObjectString(env, *result, pTrade, InstrumentID));
  CHECK(SetObjectString(env, *result, pTrade, ExchangeInstID));

  return napi_ok;
}

napi_status errRtnOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputOrder = MessageData<CThostFtdcInputOrderField>(message);

  if (!pInputOrder)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputOrderField"));
  CHECK(SetObjectString(env, *result, pInputOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pInputOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pInputOrder, OrderRef));
  CHECK(SetObjectString(env, *result, pInputOrder, UserID));
  CHECK(SetObjectChar(env, *result, pInputOrder, OrderPriceType));
  CHECK(SetObjectChar(env, *result, pInputOrder, Direction));
  CHECK(SetObjectString(env, *result, pInputOrder, CombOffsetFlag));
  CHECK(SetObjectString(env, *result, pInputOrder, CombHedgeFlag));
  CHECK(SetObjectDouble(env, *result, pInputOrder, LimitPrice));
  CHECK(SetObjectInt32(env, *result, pInputOrder, VolumeTotalOriginal));
  CHECK(SetObjectChar(env, *result, pInputOrder, TimeCondition));
  CHECK(SetObjectString(env, *result, pInputOrder, GTDDate));
  CHECK(SetObjectChar(env, *result, pInputOrder, VolumeCondition));
  CHECK(SetObjectInt32(env, *result, pInputOrder, MinVolume));
  CHECK(SetObjectChar(env, *result, pInputOrder, ContingentCondition));
  CHECK(SetObjectDouble(env, *result, pInputOrder, StopPrice));
  CHECK(SetObjectChar(env, *result, pInputOrder, ForceCloseReason));
  CHECK(SetObjectInt32(env, *result, pInputOrder, IsAutoSuspend));
  CHECK(SetObjectString(env, *result, pInputOrder, BusinessUnit));
  CHECK(SetObjectInt32(env, *result, pInputOrder, RequestID));
  CHECK(SetObjectInt32(env, *result, pInputOrder, UserForceClose));
  CHECK(SetObjectInt32(env, *result, pInputOrder, IsSwapOrder));
  CHECK(SetObjectString(env, *result, pInputOrder, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputOrder, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputOrder, AccountID));
  CHECK(SetObjectString(env, *result, pInputOrder, CurrencyID));
  CHECK(SetObjectString(env, *result, pInputOrder, ClientID));
  CHECK(SetObjectString(env, *result, pInputOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pInputOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputOrder, IPAddress));

  return napi_ok;
}

napi_status errRtnOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pOrderAction = MessageData<CThostFtdcOrderActionField>(message);

  if (!pOrderAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcOrderActionField"));
  CHECK(SetObjectString(env, *result, pOrderAction, BrokerID));
  CHECK(SetObjectString(env, *result, pOrderAction, InvestorID));
  CHECK(SetObjectInt32(env, *result, pOrderAction, OrderActionRef));
  CHECK(SetObjectString(env, *result, pOrderAction, OrderRef));
  CHECK(SetObjectInt32(env, *result, pOrderAction, RequestID));
  CHECK(SetObjectInt32(env, *result, pOrderAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pOrderAction, SessionID));
  CHECK(SetObjectString(env, *result, pOrderAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pOrderAction, OrderSysID));
  CHECK(SetObjectChar(env, *result, pOrderAction, ActionFlag));
  CHECK(SetObjectDouble(env, *result, pOrderAction, LimitPrice));
  CHECK(SetObjectInt32(env, *result, pOrderAction, VolumeChange));
  CHECK(SetObjectString(env, *result, pOrderAction, ActionDate));
  CHECK(SetObjectString(env, *result, pOrderAction, ActionTime));
  CHECK(SetObjectString(env, *result, pOrderAction, TraderID));
  CHECK(SetObjectInt32(env, *result, pOrderAction, InstallID));
  CHECK(SetObjectString(env, *result, pOrderAction, OrderLocalID));
  CHECK(SetObjectString(env, *result, pOrderAction, ActionLocalID));
  CHECK(SetObjectString(env, *result, pOrderAction, ParticipantID));
  CHECK(SetObjectString(env, *result, pOrderAction, ClientID));
  CHECK(SetObjectString(env, *result, pOrderAction, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pOrderAction, OrderActionStatus));
  CHECK(SetObjectString(env, *result, pOrderAction, UserID));
  CHECK(SetObjectString(env, *result, pOrderAction, StatusMsg));
  CHECK(SetObjectString(env, *result, pOrderAction, BranchID));
  CHECK(SetObjectString(env, *result, pOrderAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pOrderAction, MacAddress));
  CHECK(SetObjectString(env, *result, pOrderAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pOrderAction, IPAddress));

  return napi_ok;
}

napi_status rtnInstrumentStatus(napi_env env, const Message *message, napi_value *result) {
  auto pInstrumentStatus = MessageData<CThostFtdcInstrumentStatusField>(message);

  if (!pInstrumentStatus)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInstrumentStatusField"));
  CHECK(SetObjectString(env, *result, pInstrumentStatus, ExchangeID));
  CHECK(SetObjectString(env, *result, pInstrumentStatus, SettlementGroupID));
  CHECK(SetObjectChar(env, *result, pInstrumentStatus, InstrumentStatus));
  CHECK(SetObjectInt32(env, *result, pInstrumentStatus, TradingSegmentSN));
  CHECK(SetObjectString(env, *result, pInstrumentStatus, EnterTime));
  CHECK(SetObjectChar(env, *result, pInstrumentStatus, EnterReason));
  CHECK(SetObjectString(env, *result, pInstrumentStatus, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pInstrumentStatus, InstrumentID));

  return napi_ok;
}

napi_status rtnBulletin(napi_env env, const Message *message, napi_value *result) {
  auto pBulletin = MessageData<CThostFtdcBulletinField>(message);

  if (!pBulletin)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcBulletinField"));
  CHECK(SetObjectString(env, *result, pBulletin, ExchangeID));
  CHECK(SetObjectString(env, *result, pBulletin, TradingDay));
  CHECK(SetObjectInt32(env, *result, pBulletin, BulletinID));
  CHECK(SetObjectInt32(env, *result, pBulletin, SequenceNo));
  CHECK(SetObjectString(env, *result, pBulletin, NewsType));
  CHECK(SetObjectChar(env, *result, pBulletin, NewsUrgency));
  CHECK(SetObjectString(env, *result, pBulletin, SendTime));
  CHECK(SetObjectString(env, *result, pBulletin, Abstract));
  CHECK(SetObjectString(env, *result, pBulletin, ComeFrom));
  CHECK(SetObjectString(env, *result, pBulletin, Content));
  CHECK(SetObjectString(env, *result, pBulletin, URLLink));
  CHECK(SetObjectString(env, *result, pBulletin, MarketID));

  return napi_ok;
}

napi_status rtnTradingNotice(napi_env env, const Message *message, napi_value *result) {
  auto pTradingNoticeInfo = MessageData<CThostFtdcTradingNoticeInfoField>(message);

  if (!pTradingNoticeInfo)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcTradingNoticeInfoField"));
  CHECK(SetObjectString(env, *result, pTradingNoticeInfo, BrokerID));
  CHECK(SetObjectString(env, *result, pTradingNoticeInfo, InvestorID));
  CHECK(SetObjectString(env, *result, pTradingNoticeInfo, SendTime));
  CHECK(SetObjectString(env, *result, pTradingNoticeInfo, FieldContent));
  CHECK(SetObjectInt32(env, *result, pTradingNoticeInfo, SequenceSeries));
  CHECK(SetObjectInt32(env, *result, pTradingNoticeInfo, SequenceNo));
  CHECK(SetObjectString(env, *result, pTradingNoticeInfo, InvestUnitID));

  return napi_ok;
}

napi_status rtnErrorConditionalOrder(napi_env env, const Message *message, napi_value *result) {
  auto pErrorConditionalOrder = MessageData<CThostFtdcErrorConditionalOrderField>(message);

  if (!pErrorConditionalOrder)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcErrorConditionalOrderField"));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, OrderRef));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, UserID));
  CHECK(SetObjectChar(env, *result, pErrorConditionalOrder, OrderPriceType));
  CHECK(SetObjectChar(env, *result, pErrorConditionalOrder, Direction));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, CombOffsetFlag));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, CombHedgeFlag));
  CHECK(SetObjectDouble(env, *result, pErrorConditionalOrder, LimitPrice));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, VolumeTotalOriginal));
  CHECK(SetObjectChar(env, *result, pErrorConditionalOrder, TimeCondition));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, GTDDate));
  CHECK(SetObjectChar(env, *result, pErrorConditionalOrder, VolumeCondition));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, MinVolume));
  CHECK(SetObjectChar(env, *result, pErrorConditionalOrder, ContingentCondition));
  CHECK(SetObjectDouble(env, *result, pErrorConditionalOrder, StopPrice));
  CHECK(SetObjectChar(env, *result, pErrorConditionalOrder, ForceCloseReason));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, IsAutoSuspend));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, BusinessUnit));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, RequestID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, OrderLocalID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, ExchangeID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, ParticipantID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, ClientID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, TraderID));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, InstallID));
  CHECK(SetObjectChar(env, *result, pErrorConditionalOrder, OrderSubmitStatus));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, NotifySequence));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, TradingDay));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, SettlementID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, OrderSysID));
  CHECK(SetObjectChar(env, *result, pErrorConditionalOrder, OrderSource));
  CHECK(SetObjectChar(env, *result, pErrorConditionalOrder, OrderStatus));
  CHECK(SetObjectChar(env, *result, pErrorConditionalOrder, OrderType));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, VolumeTraded));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, VolumeTotal));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, InsertDate));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, InsertTime));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, ActiveTime));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, SuspendTime));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, UpdateTime));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, CancelTime));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, ActiveTraderID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, ClearingPartID));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, SequenceNo));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, FrontID));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, SessionID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, UserProductInfo));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, StatusMsg));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, UserForceClose));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, ActiveUserID));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, BrokerOrderSeq));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, RelativeOrderSysID));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, ZCETotalTradedVolume));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, ErrorID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, ErrorMsg));
  CHECK(SetObjectInt32(env, *result, pErrorConditionalOrder, IsSwapOrder));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, BranchID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, InvestUnitID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, AccountID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, CurrencyID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pErrorConditionalOrder, IPAddress));

  return napi_ok;
}

napi_status rtnExecOrder(napi_env env, const Message *message, napi_value *result) {
  auto pExecOrder = MessageData<CThostFtdcExecOrderField>(message);

  if (!pExecOrder)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcExecOrderField"));
  CHECK(SetObjectString(env, *result, pExecOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pExecOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pExecOrder, ExecOrderRef));
  CHECK(SetObjectString(env, *result, pExecOrder, UserID));
  CHECK(SetObjectInt32(env, *result, pExecOrder, Volume));
  CHECK(SetObjectInt32(env, *result, pExecOrder, RequestID));
  CHECK(SetObjectString(env, *result, pExecOrder, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pExecOrder, OffsetFlag));
  CHECK(SetObjectChar(env, *result, pExecOrder, HedgeFlag));
  CHECK(SetObjectChar(env, *result, pExecOrder, ActionType));
  CHECK(SetObjectChar(env, *result, pExecOrder, PosiDirection));
  CHECK(SetObjectChar(env, *result, pExecOrder, ReservePositionFlag));
  CHECK(SetObjectChar(env, *result, pExecOrder, CloseFlag));
  CHECK(SetObjectString(env, *result, pExecOrder, ExecOrderLocalID));
  CHECK(SetObjectString(env, *result, pExecOrder, ExchangeID));
  CHECK(SetObjectString(env, *result, pExecOrder, ParticipantID));
  CHECK(SetObjectString(env, *result, pExecOrder, ClientID));
  CHECK(SetObjectString(env, *result, pExecOrder, TraderID));
  CHECK(SetObjectInt32(env, *result, pExecOrder, InstallID));
  CHECK(SetObjectChar(env, *result, pExecOrder, OrderSubmitStatus));
  CHECK(SetObjectInt32(env, *result, pExecOrder, NotifySequence));
  CHECK(SetObjectString(env, *result, pExecOrder, TradingDay));
  CHECK(SetObjectInt32(env, *result, pExecOrder, SettlementID));
  CHECK(SetObjectString(env, *result, pExecOrder, ExecOrderSysID));
  CHECK(SetObjectString(env, *result, pExecOrder, InsertDate));
  CHECK(SetObjectString(env, *result, pExecOrder, InsertTime));
  CHECK(SetObjectString(env, *result, pExecOrder, CancelTime));
  CHECK(SetObjectChar(env, *result, pExecOrder, ExecResult));
  CHECK(SetObjectString(env, *result, pExecOrder, ClearingPartID));
  CHECK(SetObjectInt32(env, *result, pExecOrder, SequenceNo));
  CHECK(SetObjectInt32(env, *result, pExecOrder, FrontID));
  CHECK(SetObjectInt32(env, *result, pExecOrder, SessionID));
  CHECK(SetObjectString(env, *result, pExecOrder, UserProductInfo));
  CHECK(SetObjectString(env, *result, pExecOrder, StatusMsg));
  CHECK(SetObjectString(env, *result, pExecOrder, ActiveUserID));
  CHECK(SetObjectInt32(env, *result, pExecOrder, BrokerExecOrderSeq));
  CHECK(SetObjectString(env, *result, pExecOrder, BranchID));
  CHECK(SetObjectString(env, *result, pExecOrder, InvestUnitID));
  CHECK(SetObjectString(env, *result, pExecOrder, AccountID));
  CHECK(SetObjectString(env, *result, pExecOrder, CurrencyID));
  CHECK(SetObjectString(env, *result, pExecOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pExecOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pExecOrder, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pExecOrder, IPAddress));

  return napi_ok;
}

napi_status errRtnExecOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputExecOrder = MessageData<CThostFtdcInputExecOrderField>(message);

  if (!pInputExecOrder)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputExecOrderField"));
  CHECK(SetObjectString(env, *result, pInputExecOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, ExecOrderRef));
  CHECK(SetObjectString(env, *result, pInputExecOrder, UserID));
  CHECK(SetObjectInt32(env, *result, pInputExecOrder, Volume));
  CHECK(SetObjectInt32(env, *result, pInputExecOrder, RequestID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pInputExecOrder, OffsetFlag));
  CHECK(SetObjectChar(env, *result, pInputExecOrder, HedgeFlag));
  CHECK(SetObjectChar(env, *result, pInputExecOrder, ActionType));
  CHECK(SetObjectChar(env, *result, pInputExecOrder, PosiDirection));
  CHECK(SetObjectChar(env, *result, pInputExecOrder, ReservePositionFlag));
  CHECK(SetObjectChar(env, *result, pInputExecOrder, CloseFlag));
  CHECK(SetObjectString(env, *result, pInputExecOrder, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, AccountID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, CurrencyID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, ClientID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pInputExecOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputExecOrder, IPAddress));

  return napi_ok;
}

napi_status errRtnExecOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pExecOrderAction = MessageData<CThostFtdcExecOrderActionField>(message);

  if (!pExecOrderAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcExecOrderActionField"));
  CHECK(SetObjectString(env, *result, pExecOrderAction, BrokerID));
  CHECK(SetObjectString(env, *result, pExecOrderAction, InvestorID));
  CHECK(SetObjectInt32(env, *result, pExecOrderAction, ExecOrderActionRef));
  CHECK(SetObjectString(env, *result, pExecOrderAction, ExecOrderRef));
  CHECK(SetObjectInt32(env, *result, pExecOrderAction, RequestID));
  CHECK(SetObjectInt32(env, *result, pExecOrderAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pExecOrderAction, SessionID));
  CHECK(SetObjectString(env, *result, pExecOrderAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pExecOrderAction, ExecOrderSysID));
  CHECK(SetObjectChar(env, *result, pExecOrderAction, ActionFlag));
  CHECK(SetObjectString(env, *result, pExecOrderAction, ActionDate));
  CHECK(SetObjectString(env, *result, pExecOrderAction, ActionTime));
  CHECK(SetObjectString(env, *result, pExecOrderAction, TraderID));
  CHECK(SetObjectInt32(env, *result, pExecOrderAction, InstallID));
  CHECK(SetObjectString(env, *result, pExecOrderAction, ExecOrderLocalID));
  CHECK(SetObjectString(env, *result, pExecOrderAction, ActionLocalID));
  CHECK(SetObjectString(env, *result, pExecOrderAction, ParticipantID));
  CHECK(SetObjectString(env, *result, pExecOrderAction, ClientID));
  CHECK(SetObjectString(env, *result, pExecOrderAction, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pExecOrderAction, OrderActionStatus));
  CHECK(SetObjectString(env, *result, pExecOrderAction, UserID));
  CHECK(SetObjectChar(env, *result, pExecOrderAction, ActionType));
  CHECK(SetObjectString(env, *result, pExecOrderAction, StatusMsg));
  CHECK(SetObjectString(env, *result, pExecOrderAction, BranchID));
  CHECK(SetObjectString(env, *result, pExecOrderAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pExecOrderAction, MacAddress));
  CHECK(SetObjectString(env, *result, pExecOrderAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pExecOrderAction, IPAddress));

  return napi_ok;
}

napi_status errRtnForQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputForQuote = MessageData<CThostFtdcInputForQuoteField>(message);

  if (!pInputForQuote)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputForQuoteField"));
  CHECK(SetObjectString(env, *result, pInputForQuote, BrokerID));
  CHECK(SetObjectString(env, *result, pInputForQuote, InvestorID));
  CHECK(SetObjectString(env, *result, pInputForQuote, ForQuoteRef));
  CHECK(SetObjectString(env, *result, pInputForQuote, UserID));
  CHECK(SetObjectString(env, *result, pInputForQuote, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputForQuote, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputForQuote, MacAddress));
  CHECK(SetObjectString(env, *result, pInputForQuote, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputForQuote, IPAddress));

  return napi_ok;
}

napi_status rtnQuote(napi_env env, const Message *message, napi_value *result) {
  auto pQuote = MessageData<CThostFtdcQuoteField>(message);

  if (!pQuote)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcQuoteField"));
  CHECK(SetObjectString(env, *result, pQuote, BrokerID));
  CHECK(SetObjectString(env, *result, pQuote, InvestorID));
  CHECK(SetObjectString(env, *result, pQuote, QuoteRef));
  CHECK(SetObjectString(env, *result, pQuote, UserID));
  CHECK(SetObjectDouble(env, *result, pQuote, AskPrice));
  CHECK(SetObjectDouble(env, *result, pQuote, BidPrice));
  CHECK(SetObjectInt32(env, *result, pQuote, AskVolume));
  CHECK(SetObjectInt32(env, *result, pQuote, BidVolume));
  CHECK(SetObjectInt32(env, *result, pQuote, RequestID));
  CHECK(SetObjectString(env, *result, pQuote, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pQuote, AskOffsetFlag));
  CHECK(SetObjectChar(env, *result, pQuote, BidOffsetFlag));
  CHECK(SetObjectChar(env, *result, pQuote, AskHedgeFlag));
  CHECK(SetObjectChar(env, *result, pQuote, BidHedgeFlag));
  CHECK(SetObjectString(env, *result, pQuote, QuoteLocalID));
  CHECK(SetObjectString(env, *result, pQuote, ExchangeID));
  CHECK(SetObjectString(env, *result, pQuote, ParticipantID));
  CHECK(SetObjectString(env, *result, pQuote, ClientID));
  CHECK(SetObjectString(env, *result, pQuote, TraderID));
  CHECK(SetObjectInt32(env, *result, pQuote, InstallID));
  CHECK(SetObjectInt32(env, *result, pQuote, NotifySequence));
  CHECK(SetObjectChar(env, *result, pQuote, OrderSubmitStatus));
  CHECK(SetObjectString(env, *result, pQuote, TradingDay));
  CHECK(SetObjectInt32(env, *result, pQuote, SettlementID));
  CHECK(SetObjectString(env, *result, pQuote, QuoteSysID));
  CHECK(SetObjectString(env, *result, pQuote, InsertDate));
  CHECK(SetObjectString(env, *result, pQuote, InsertTime));
  CHECK(SetObjectString(env, *result, pQuote, CancelTime));
  CHECK(SetObjectChar(env, *result, pQuote, QuoteStatus));
  CHECK(SetObjectString(env, *result, pQuote, ClearingPartID));
  CHECK(SetObjectInt32(env, *result, pQuote, SequenceNo));
  CHECK(SetObjectString(env, *result, pQuote, AskOrderSysID));
  CHECK(SetObjectString(env, *result, pQuote, BidOrderSysID));
  CHECK(SetObjectInt32(env, *result, pQuote, FrontID));
  CHECK(SetObjectInt32(env, *result, pQuote, SessionID));
  CHECK(SetObjectString(env, *result, pQuote, UserProductInfo));
  CHECK(SetObjectString(env, *result, pQuote, StatusMsg));
  CHECK(SetObjectString(env, *result, pQuote, ActiveUserID));
  CHECK(SetObjectInt32(env, *result, pQuote, BrokerQuoteSeq));
  CHECK(SetObjectString(env, *result, pQuote, AskOrderRef));
  CHECK(SetObjectString(env, *result, pQuote, BidOrderRef));
  CHECK(SetObjectString(env, *result, pQuote, ForQuoteSysID));
  CHECK(SetObjectString(env, *result, pQuote, BranchID));
  CHECK(SetObjectString(env, *result, pQuote, InvestUnitID));
  CHECK(SetObjectString(env, *result, pQuote, AccountID));
  CHECK(SetObjectString(env, *result, pQuote, CurrencyID));
  CHECK(SetObjectString(env, *result, pQuote, MacAddress));
  CHECK(SetObjectString(env, *result, pQuote, InstrumentID));
  CHECK(SetObjectString(env, *result, pQuote, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pQuote, IPAddress));
  CHECK(SetObjectString(env, *result, pQuote, ReplaceSysID));

  return napi_ok;
}

napi_status errRtnQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputQuote = MessageData<CThostFtdcInputQuoteField>(message);

  if (!pInputQuote)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputQuoteField"));
  CHECK(SetObjectString(env, *result, pInputQuote, BrokerID));
  CHECK(SetObjectString(env, *result, pInputQuote, InvestorID));
  CHECK(SetObjectString(env, *result, pInputQuote, QuoteRef));
  CHECK(SetObjectString(env, *result, pInputQuote, UserID));
  CHECK(SetObjectDouble(env, *result, pInputQuote, AskPrice));
  CHECK(SetObjectDouble(env, *result, pInputQuote, BidPrice));
  CHECK(SetObjectInt32(env, *result, pInputQuote, AskVolume));
  CHECK(SetObjectInt32(env, *result, pInputQuote, BidVolume));
  CHECK(SetObjectInt32(env, *result, pInputQuote, RequestID));
  CHECK(SetObjectString(env, *result, pInputQuote, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pInputQuote, AskOffsetFlag));
  CHECK(SetObjectChar(env, *result, pInputQuote, BidOffsetFlag));
  CHECK(SetObjectChar(env, *result, pInputQuote, AskHedgeFlag));
  CHECK(SetObjectChar(env, *result, pInputQuote, BidHedgeFlag));
  CHECK(SetObjectString(env, *result, pInputQuote, AskOrderRef));
  CHECK(SetObjectString(env, *result, pInputQuote, BidOrderRef));
  CHECK(SetObjectString(env, *result, pInputQuote, ForQuoteSysID));
  CHECK(SetObjectString(env, *result, pInputQuote, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputQuote, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputQuote, ClientID));
  CHECK(SetObjectString(env, *result, pInputQuote, MacAddress));
  CHECK(SetObjectString(env, *result, pInputQuote, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputQuote, IPAddress));
  CHECK(SetObjectString(env, *result, pInputQuote, ReplaceSysID));

  return napi_ok;
}

napi_status errRtnQuoteAction(napi_env env, const Message *message, napi_value *result) {
  auto pQuoteAction = MessageData<CThostFtdcQuoteActionField>(message);

  if (!pQuoteAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcQuoteActionField"));
  CHECK(SetObjectString(env, *result, pQuoteAction, BrokerID));
  CHECK(SetObjectString(env, *result, pQuoteAction, InvestorID));
  CHECK(SetObjectInt32(env, *result, pQuoteAction, QuoteActionRef));
  CHECK(SetObjectString(env, *result, pQuoteAction, QuoteRef));
  CHECK(SetObjectInt32(env, *result, pQuoteAction, RequestID));
  CHECK(SetObjectInt32(env, *result, pQuoteAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pQuoteAction, SessionID));
  CHECK(SetObjectString(env, *result, pQuoteAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pQuoteAction, QuoteSysID));
  CHECK(SetObjectChar(env, *result, pQuoteAction, ActionFlag));
  CHECK(SetObjectString(env, *result, pQuoteAction, ActionDate));
  CHECK(SetObjectString(env, *result, pQuoteAction, ActionTime));
  CHECK(SetObjectString(env, *result, pQuoteAction, TraderID));
  CHECK(SetObjectInt32(env, *result, pQuoteAction, InstallID));
  CHECK(SetObjectString(env, *result, pQuoteAction, QuoteLocalID));
  CHECK(SetObjectString(env, *result, pQuoteAction, ActionLocalID));
  CHECK(SetObjectString(env, *result, pQuoteAction, ParticipantID));
  CHECK(SetObjectString(env, *result, pQuoteAction, ClientID));
  CHECK(SetObjectString(env, *result, pQuoteAction, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pQuoteAction, OrderActionStatus));
  CHECK(SetObjectString(env, *result, pQuoteAction, UserID));
  CHECK(SetObjectString(env, *result, pQuoteAction, StatusMsg));
  CHECK(SetObjectString(env, *result, pQuoteAction, BranchID));
  CHECK(SetObjectString(env, *result, pQuoteAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pQuoteAction, MacAddress));
  CHECK(SetObjectString(env, *result, pQuoteAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pQuoteAction, IPAddress));

  return napi_ok;
}

napi_status rtnCFMMCTradingAccountToken(napi_env env, const Message *message, napi_value *result) {
  auto pCFMMCTradingAccountToken = MessageData<CThostFtdcCFMMCTradingAccountTokenField>(message);

  if (!pCFMMCTradingAccountToken)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcCFMMCTradingAccountTokenField"));
  CHECK(SetObjectString(env, *result, pCFMMCTradingAccountToken, BrokerID));
  CHECK(SetObjectString(env, *result, pCFMMCTradingAccountToken, ParticipantID));
  CHECK(SetObjectString(env, *result, pCFMMCTradingAccountToken, AccountID));
  CHECK(SetObjectInt32(env, *result, pCFMMCTradingAccountToken, KeyID));
  CHECK(SetObjectString(env, *result, pCFMMCTradingAccountToken, Token));

  return napi_ok;
}

napi_status errRtnBatchOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pBatchOrderAction = MessageData<CThostFtdcBatchOrderActionField>(message);

  if (!pBatchOrderAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcBatchOrderActionField"));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, BrokerID));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, InvestorID));
  CHECK(SetObjectInt32(env, *result, pBatchOrderAction, OrderActionRef));
  CHECK(SetObjectInt32(env, *result, pBatchOrderAction, RequestID));
  CHECK(SetObjectInt32(env, *result, pBatchOrderAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pBatchOrderAction, SessionID));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, ActionDate));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, ActionTime));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, TraderID));
  CHECK(SetObjectInt32(env, *result, pBatchOrderAction, InstallID));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, ActionLocalID));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, ParticipantID));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, ClientID));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pBatchOrderAction, OrderActionStatus));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, UserID));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, StatusMsg));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, MacAddress));
  CHECK(SetObjectString(env, *result, pBatchOrderAction, IPAddress));

  return napi_ok;
}

napi_status rtnOptionSelfClose(napi_env env, const Message *message, napi_value *result) {
  auto pOptionSelfClose = MessageData<CThostFtdcOptionSelfCloseField>(message);

  if (!pOptionSelfClose)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcOptionSelfCloseField"));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, BrokerID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, InvestorID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, OptionSelfCloseRef));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, UserID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, Volume));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, RequestID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pOptionSelfClose, HedgeFlag));
  CHECK(SetObjectChar(env, *result, pOptionSelfClose, OptSelfCloseFlag));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, OptionSelfCloseLocalID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, ExchangeID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, ParticipantID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, ClientID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, TraderID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, InstallID));
  CHECK(SetObjectChar(env, *result, pOptionSelfClose, OrderSubmitStatus));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, NotifySequence));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, TradingDay));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, SettlementID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, OptionSelfCloseSysID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, InsertDate));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, InsertTime));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, CancelTime));
  CHECK(SetObjectChar(env, *result, pOptionSelfClose, ExecResult));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, ClearingPartID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, SequenceNo));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, FrontID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, SessionID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, UserProductInfo));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, StatusMsg));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, ActiveUserID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfClose, BrokerOptionSelfCloseSeq));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, BranchID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, InvestUnitID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, AccountID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, CurrencyID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, MacAddress));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, InstrumentID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pOptionSelfClose, IPAddress));

  return napi_ok;
}

napi_status errRtnOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputOptionSelfClose = MessageData<CThostFtdcInputOptionSelfCloseField>(message);

  if (!pInputOptionSelfClose)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputOptionSelfCloseField"));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, BrokerID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, InvestorID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, OptionSelfCloseRef));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, UserID));
  CHECK(SetObjectInt32(env, *result, pInputOptionSelfClose, Volume));
  CHECK(SetObjectInt32(env, *result, pInputOptionSelfClose, RequestID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pInputOptionSelfClose, HedgeFlag));
  CHECK(SetObjectChar(env, *result, pInputOptionSelfClose, OptSelfCloseFlag));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, AccountID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, CurrencyID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, ClientID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, MacAddress));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, IPAddress));

  return napi_ok;
}

napi_status errRtnOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result) {
  auto pOptionSelfCloseAction = MessageData<CThostFtdcOptionSelfCloseActionField>(message);

  if (!pOptionSelfCloseAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcOptionSelfCloseActionField"));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, BrokerID));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, InvestorID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfCloseAction, OptionSelfCloseActionRef));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, OptionSelfCloseRef));
  CHECK(SetObjectInt32(env, *result, pOptionSelfCloseAction, RequestID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfCloseAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfCloseAction, SessionID));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, OptionSelfCloseSysID));
  CHECK(SetObjectChar(env, *result, pOptionSelfCloseAction, ActionFlag));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, ActionDate));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, ActionTime));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, TraderID));
  CHECK(SetObjectInt32(env, *result, pOptionSelfCloseAction, InstallID));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, OptionSelfCloseLocalID));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, ActionLocalID));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, ParticipantID));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, ClientID));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, BusinessUnit));
  CHECK(SetObjectChar(env, *result, pOptionSelfCloseAction, OrderActionStatus));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, UserID));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, StatusMsg));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, BranchID));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, MacAddress));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pOptionSelfCloseAction, IPAddress));

  return napi_ok;
}

napi_status rtnCombAction(napi_env env, const Message *message, napi_value *result) {
  auto pCombAction = MessageData<CThostFtdcCombActionField>(message);

  if (!pCombAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcCombActionField"));
  CHECK(SetObjectString(env, *result, pCombAction, BrokerID));
  CHECK(SetObjectString(env, *result, pCombAction, InvestorID));
  CHECK(SetObjectString(env, *result, pCombAction, CombActionRef));
  CHECK(SetObjectString(env, *result, pCombAction, UserID));
  CHECK(SetObjectChar(env, *result, pCombAction, Direction));
  CHECK(SetObjectInt32(env, *result, pCombAction, Volume));
  CHECK(SetObjectChar(env, *result, pCombAction, CombDirection));
  CHECK(SetObjectChar(env, *result, pCombAction, HedgeFlag));
  CHECK(SetObjectString(env, *result, pCombAction, ActionLocalID));
  CHECK(SetObjectString(env, *result, pCombAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pCombAction, ParticipantID));
  CHECK(SetObjectString(env, *result, pCombAction, ClientID));
  CHECK(SetObjectString(env, *result, pCombAction, TraderID));
  CHECK(SetObjectInt32(env, *result, pCombAction, InstallID));
  CHECK(SetObjectChar(env, *result, pCombAction, ActionStatus));
  CHECK(SetObjectInt32(env, *result, pCombAction, NotifySequence));
  CHECK(SetObjectString(env, *result, pCombAction, TradingDay));
  CHECK(SetObjectInt32(env, *result, pCombAction, SettlementID));
  CHECK(SetObjectInt32(env, *result, pCombAction, SequenceNo));
  CHECK(SetObjectInt32(env, *result, pCombAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pCombAction, SessionID));
  CHECK(SetObjectString(env, *result, pCombAction, UserProductInfo));
  CHECK(SetObjectString(env, *result, pCombAction, StatusMsg));
  CHECK(SetObjectString(env, *result, pCombAction, MacAddress));
  CHECK(SetObjectString(env, *result, pCombAction, ComTradeID));
  CHECK(SetObjectString(env, *result, pCombAction, BranchID));
  CHECK(SetObjectString(env, *result, pCombAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pCombAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pCombAction, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pCombAction, IPAddress));

  return napi_ok;
}

napi_status errRtnCombActionInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputCombAction = MessageData<CThostFtdcInputCombActionField>(message);

  if (!pInputCombAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInputCombActionField"));
  CHECK(SetObjectString(env, *result, pInputCombAction, BrokerID));
  CHECK(SetObjectString(env, *result, pInputCombAction, InvestorID));
  CHECK(SetObjectString(env, *result, pInputCombAction, CombActionRef));
  CHECK(SetObjectString(env, *result, pInputCombAction, UserID));
  CHECK(SetObjectChar(env, *result, pInputCombAction, Direction));
  CHECK(SetObjectInt32(env, *result, pInputCombAction, Volume));
  CHECK(SetObjectChar(env, *result, pInputCombAction, CombDirection));
  CHECK(SetObjectChar(env, *result, pInputCombAction, HedgeFlag));
  CHECK(SetObjectString(env, *result, pInputCombAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pInputCombAction, MacAddress));
  CHECK(SetObjectString(env, *result, pInputCombAction, InvestUnitID));
  CHECK(SetObjectInt32(env, *result, pInputCombAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pInputCombAction, SessionID));
  CHECK(SetObjectString(env, *result, pInputCombAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputCombAction, IPAddress));

  return napi_ok;
}

napi_status rspQryContractBank(napi_env env, const Message *message, napi_value *result) {
  auto pContractBank = MessageData<CThostFtdcContractBankField>(message);

  if (!pContractBank)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcContractBankField"));
  CHECK(SetObjectString(env, *result, pContractBank, BrokerID));
  CHECK(SetObjectString(env, *result, pContractBank, BankID));
  CHECK(SetObjectString(env, *result, pContractBank, BankBrchID));
  CHECK(SetObjectString(env, *result, pContractBank, BankName));

  return napi_ok;
}

napi_status rspQryParkedOrder(napi_env env, const Message *message, napi_value *result) {
  auto pParkedOrder = MessageData<CThostFtdcParkedOrderField>(message);

  if (!pParkedOrder)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcParkedOrderField"));
  CHECK(SetObjectString(env, *result, pParkedOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pParkedOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pParkedOrder, OrderRef));
  CHECK(SetObjectString(env, *result, pParkedOrder, UserID));
  CHECK(SetObjectChar(env, *result, pParkedOrder, OrderPriceType));
  CHECK(SetObjectChar(env, *result, pParkedOrder, Direction));
  CHECK(SetObjectString(env, *result, pParkedOrder, CombOffsetFlag));
  CHECK(SetObjectString(env, *result, pParkedOrder, CombHedgeFlag));
  CHECK(SetObjectDouble(env, *result, pParkedOrder, LimitPrice));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, VolumeTotalOriginal));
  CHECK(SetObjectChar(env, *result, pParkedOrder, TimeCondition));
  CHECK(SetObjectString(env, *result, pParkedOrder, GTDDate));
  CHECK(SetObjectChar(env, *result, pParkedOrder, VolumeCondition));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, MinVolume));
  CHECK(SetObjectChar(env, *result, pParkedOrder, ContingentCondition));
  CHECK(SetObjectDouble(env, *result, pParkedOrder, StopPrice));
  CHECK(SetObjectChar(env, *result, pParkedOrder, ForceCloseReason));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, IsAutoSuspend));
  CHECK(SetObjectString(env, *result, pParkedOrder, BusinessUnit));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, RequestID));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, UserForceClose));
  CHECK(SetObjectString(env, *result, pParkedOrder, ExchangeID));
  CHECK(SetObjectString(env, *result, pParkedOrder, ParkedOrderID));
  CHECK(SetObjectChar(env, *result, pParkedOrder, UserType));
  CHECK(SetObjectChar(env, *result, pParkedOrder, Status));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, ErrorID));
  CHECK(SetObjectString(env, *result, pParkedOrder, ErrorMsg));
  CHECK(SetObjectInt32(env, *result, pParkedOrder, IsSwapOrder));
  CHECK(SetObjectString(env, *result, pParkedOrder, AccountID));
  CHECK(SetObjectString(env, *result, pParkedOrder, CurrencyID));
  CHECK(SetObjectString(env, *result, pParkedOrder, ClientID));
  CHECK(SetObjectString(env, *result, pParkedOrder, InvestUnitID));
  CHECK(SetObjectString(env, *result, pParkedOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pParkedOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pParkedOrder, IPAddress));

  return napi_ok;
}

napi_status rspQryParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pParkedOrderAction = MessageData<CThostFtdcParkedOrderActionField>(message);

  if (!pParkedOrderAction)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcParkedOrderActionField"));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, BrokerID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, InvestorID));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, OrderActionRef));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, OrderRef));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, RequestID));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, FrontID));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, SessionID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, ExchangeID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, OrderSysID));
  CHECK(SetObjectChar(env, *result, pParkedOrderAction, ActionFlag));
  CHECK(SetObjectDouble(env, *result, pParkedOrderAction, LimitPrice));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, VolumeChange));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, UserID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, ParkedOrderActionID));
  CHECK(SetObjectChar(env, *result, pParkedOrderAction, UserType));
  CHECK(SetObjectChar(env, *result, pParkedOrderAction, Status));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, ErrorID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, ErrorMsg));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, MacAddress));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, IPAddress));

  return napi_ok;
}

napi_status rspQryTradingNotice(napi_env env, const Message *message, napi_value *result) {
  auto pTradingNotice = MessageData<CThostFtdcTradingNoticeField>(message);

  if (!pTradingNotice)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcTradingNoticeField"));
  CHECK(SetObjectString(env, *result, pTradingNotice, BrokerID));
  CHECK(SetObjectChar(env, *result, pTradingNotice, InvestorRange));
  CHECK(SetObjectString(env, *result, pTradingNotice, InvestorID));
  CHECK(SetObjectInt32(env, *result, pTradingNotice, SequenceSeries));
  CHECK(SetObjectString(env, *result, pTradingNotice, UserID));
  CHECK(SetObjectString(env, *result, pTradingNotice, SendTime));
  CHECK(SetObjectInt32(env, *result, pTradingNotice, SequenceNo));
  CHECK(SetObjectString(env, *result, pTradingNotice, FieldContent));
  CHECK(SetObjectString(env, *result, pTradingNotice, InvestUnitID));

  return napi_ok;
}

napi_status rspQryBrokerTradingParams(napi_env env, const Message *message, napi_value *result) {
  auto pBrokerTradingParams = MessageData<CThostFtdcBrokerTradingParamsField>(message);

  if (!pBrokerTradingParams)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcBrokerTradingParamsField"));
  CHECK(SetObjectString(env, *result, pBrokerTradingParams, BrokerID));
  CHECK(SetObjectString(env, *result, pBrokerTradingParams, InvestorID));
  CHECK(SetObjectChar(env, *result, pBrokerTradingParams, MarginPriceType));
  CHECK(SetObjectChar(env, *result, pBrokerTradingParams, Algorithm));
  CHECK(SetObjectChar(env, *result, pBrokerTradingParams, AvailIncludeCloseProfit));
  CHECK(SetObjectString(env, *result, pBrokerTradingParams, CurrencyID));
  CHECK(SetObjectChar(env, *result, pBrokerTradingParams, OptionRoyaltyPriceType));
  CHECK(SetObjectString(env, *result, pBrokerTradingParams, AccountID));

  return napi_ok;
}

napi_status rspQryBrokerTradingAlgos(napi_env env, const Message *message, napi_value *result) {
  auto pBrokerTradingAlgos = MessageData<CThostFtdcBrokerTradingAlgosField>(message);

  if (!pBrokerTradingAlgos)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcBrokerTradingAlgosField"));
  CHECK(SetObjectString(env, *result, pBrokerTradingAlgos, BrokerID));
  CHECK(SetObjectString(env, *result, pBrokerTradingAlgos, ExchangeID));
  CHECK(SetObjectChar(env, *result, pBrokerTradingAlgos, HandlePositionAlgoID));
  CHECK(SetObjectChar(env, *result, pBrokerTradingAlgos, FindMarginRateAlgoID));
  CHECK(SetObjectChar(env, *result, pBrokerTradingAlgos, HandleTradingAccountAlgoID));
  CHECK(SetObjectString(env, *result, pBrokerTradingAlgos, InstrumentID));

  return napi_ok;
}

napi_status rspQueryCFMMCTradingAccountToken(napi_env env, const Message *message, napi_value *result) {
  auto pQueryCFMMCTradingAccountToken = MessageData<CThostFtdcQueryCFMMCTradingAccountTokenField>(message);

  if (!pQueryCFMMCTradingAccountToken)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcQueryCFMMCTradingAccountTokenField"));
  CHECK(SetObjectString(env, *result, pQueryCFMMCTradingAccountToken, BrokerID));
  CHECK(SetObjectString(env, *result, pQueryCFMMCTradingAccountToken, InvestorID));
  CHECK(SetObjectString(env, *result, pQueryCFMMCTradingAccountToken, InvestUnitID));

  return napi_ok;
}

napi_status rtnFromBankToFutureByBank(napi_env env, const Message *message, napi_value *result) {
  auto pRspTransfer = MessageData<CThostFtdcRspTransferField>(message);

  if (!pRspTransfer)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspTransferField"));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradeCode));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankID));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankBranchID));
  CHECK(SetObjectString(env, *result, pRspTransfer, BrokerID));
  CHECK(SetObjectString(env, *result, pRspTransfer, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradeDate));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradeTime));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankSerial));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradingDay));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, PlateSerial));
  CHECK(SetObjectChar(env, *result, pRspTransfer, LastFragment));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, SessionID));
  CHECK(SetObjectString(env, *result, pRspTransfer, CustomerName));
  CHECK(SetObjectChar(env, *result, pRspTransfer, IdCardType));
  CHECK(SetObjectString(env, *result, pRspTransfer, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pRspTransfer, CustType));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankAccount));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankPassWord));
  CHECK(SetObjectString(env, *result, pRspTransfer, AccountID));
  CHECK(SetObjectString(env, *result, pRspTransfer, Password));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, InstallID));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, FutureSerial));
  CHECK(SetObjectString(env, *result, pRspTransfer, UserID));
  CHECK(SetObjectChar(env, *result, pRspTransfer, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pRspTransfer, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pRspTransfer, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, CustFee));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, BrokerFee));
  CHECK(SetObjectString(env, *result, pRspTransfer, Message));
  CHECK(SetObjectString(env, *result, pRspTransfer, Digest));
  CHECK(SetObjectChar(env, *result, pRspTransfer, BankAccType));
  CHECK(SetObjectString(env, *result, pRspTransfer, DeviceID));
  CHECK(SetObjectChar(env, *result, pRspTransfer, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pRspTransfer, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pRspTransfer, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pRspTransfer, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pRspTransfer, OperNo));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, RequestID));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, TID));
  CHECK(SetObjectChar(env, *result, pRspTransfer, TransferStatus));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, ErrorID));
  CHECK(SetObjectString(env, *result, pRspTransfer, ErrorMsg));
  CHECK(SetObjectString(env, *result, pRspTransfer, LongCustomerName));

  return napi_ok;
}

napi_status rtnFromFutureToBankByBank(napi_env env, const Message *message, napi_value *result) {
  auto pRspTransfer = MessageData<CThostFtdcRspTransferField>(message);

  if (!pRspTransfer)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspTransferField"));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradeCode));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankID));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankBranchID));
  CHECK(SetObjectString(env, *result, pRspTransfer, BrokerID));
  CHECK(SetObjectString(env, *result, pRspTransfer, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradeDate));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradeTime));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankSerial));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradingDay));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, PlateSerial));
  CHECK(SetObjectChar(env, *result, pRspTransfer, LastFragment));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, SessionID));
  CHECK(SetObjectString(env, *result, pRspTransfer, CustomerName));
  CHECK(SetObjectChar(env, *result, pRspTransfer, IdCardType));
  CHECK(SetObjectString(env, *result, pRspTransfer, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pRspTransfer, CustType));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankAccount));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankPassWord));
  CHECK(SetObjectString(env, *result, pRspTransfer, AccountID));
  CHECK(SetObjectString(env, *result, pRspTransfer, Password));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, InstallID));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, FutureSerial));
  CHECK(SetObjectString(env, *result, pRspTransfer, UserID));
  CHECK(SetObjectChar(env, *result, pRspTransfer, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pRspTransfer, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pRspTransfer, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, CustFee));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, BrokerFee));
  CHECK(SetObjectString(env, *result, pRspTransfer, Message));
  CHECK(SetObjectString(env, *result, pRspTransfer, Digest));
  CHECK(SetObjectChar(env, *result, pRspTransfer, BankAccType));
  CHECK(SetObjectString(env, *result, pRspTransfer, DeviceID));
  CHECK(SetObjectChar(env, *result, pRspTransfer, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pRspTransfer, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pRspTransfer, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pRspTransfer, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pRspTransfer, OperNo));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, RequestID));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, TID));
  CHECK(SetObjectChar(env, *result, pRspTransfer, TransferStatus));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, ErrorID));
  CHECK(SetObjectString(env, *result, pRspTransfer, ErrorMsg));
  CHECK(SetObjectString(env, *result, pRspTransfer, LongCustomerName));

  return napi_ok;
}

napi_status rtnRepealFromBankToFutureByBank(napi_env env, const Message *message, napi_value *result) {
  auto pRspRepeal = MessageData<CThostFtdcRspRepealField>(message);

  if (!pRspRepeal)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspRepealField"));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RepealTimeInterval));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RepealedTimes));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankRepealFlag));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BrokerRepealFlag));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, PlateRepealSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankRepealSerial));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, FutureRepealSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeCode));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankBranchID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeDate));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeTime));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradingDay));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, PlateSerial));
  CHECK(SetObjectChar(env, *result, pRspRepeal, LastFragment));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, SessionID));
  CHECK(SetObjectString(env, *result, pRspRepeal, CustomerName));
  CHECK(SetObjectChar(env, *result, pRspRepeal, IdCardType));
  CHECK(SetObjectString(env, *result, pRspRepeal, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pRspRepeal, CustType));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankAccount));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankPassWord));
  CHECK(SetObjectString(env, *result, pRspRepeal, AccountID));
  CHECK(SetObjectString(env, *result, pRspRepeal, Password));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, InstallID));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, FutureSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, UserID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pRspRepeal, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pRspRepeal, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, CustFee));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, BrokerFee));
  CHECK(SetObjectString(env, *result, pRspRepeal, Message));
  CHECK(SetObjectString(env, *result, pRspRepeal, Digest));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankAccType));
  CHECK(SetObjectString(env, *result, pRspRepeal, DeviceID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pRspRepeal, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pRspRepeal, OperNo));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RequestID));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, TID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, TransferStatus));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, ErrorID));
  CHECK(SetObjectString(env, *result, pRspRepeal, ErrorMsg));
  CHECK(SetObjectString(env, *result, pRspRepeal, LongCustomerName));

  return napi_ok;
}

napi_status rtnRepealFromFutureToBankByBank(napi_env env, const Message *message, napi_value *result) {
  auto pRspRepeal = MessageData<CThostFtdcRspRepealField>(message);

  if (!pRspRepeal)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspRepealField"));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RepealTimeInterval));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RepealedTimes));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankRepealFlag));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BrokerRepealFlag));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, PlateRepealSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankRepealSerial));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, FutureRepealSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeCode));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankBranchID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeDate));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeTime));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradingDay));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, PlateSerial));
  CHECK(SetObjectChar(env, *result, pRspRepeal, LastFragment));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, SessionID));
  CHECK(SetObjectString(env, *result, pRspRepeal, CustomerName));
  CHECK(SetObjectChar(env, *result, pRspRepeal, IdCardType));
  CHECK(SetObjectString(env, *result, pRspRepeal, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pRspRepeal, CustType));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankAccount));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankPassWord));
  CHECK(SetObjectString(env, *result, pRspRepeal, AccountID));
  CHECK(SetObjectString(env, *result, pRspRepeal, Password));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, InstallID));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, FutureSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, UserID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pRspRepeal, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pRspRepeal, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, CustFee));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, BrokerFee));
  CHECK(SetObjectString(env, *result, pRspRepeal, Message));
  CHECK(SetObjectString(env, *result, pRspRepeal, Digest));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankAccType));
  CHECK(SetObjectString(env, *result, pRspRepeal, DeviceID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pRspRepeal, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pRspRepeal, OperNo));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RequestID));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, TID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, TransferStatus));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, ErrorID));
  CHECK(SetObjectString(env, *result, pRspRepeal, ErrorMsg));
  CHECK(SetObjectString(env, *result, pRspRepeal, LongCustomerName));

  return napi_ok;
}

napi_status rtnFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pRspTransfer = MessageData<CThostFtdcRspTransferField>(message);

  if (!pRspTransfer)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspTransferField"));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradeCode));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankID));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankBranchID));
  CHECK(SetObjectString(env, *result, pRspTransfer, BrokerID));
  CHECK(SetObjectString(env, *result, pRspTransfer, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradeDate));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradeTime));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankSerial));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradingDay));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, PlateSerial));
  CHECK(SetObjectChar(env, *result, pRspTransfer, LastFragment));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, SessionID));
  CHECK(SetObjectString(env, *result, pRspTransfer, CustomerName));
  CHECK(SetObjectChar(env, *result, pRspTransfer, IdCardType));
  CHECK(SetObjectString(env, *result, pRspTransfer, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pRspTransfer, CustType));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankAccount));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankPassWord));
  CHECK(SetObjectString(env, *result, pRspTransfer, AccountID));
  CHECK(SetObjectString(env, *result, pRspTransfer, Password));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, InstallID));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, FutureSerial));
  CHECK(SetObjectString(env, *result, pRspTransfer, UserID));
  CHECK(SetObjectChar(env, *result, pRspTransfer, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pRspTransfer, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pRspTransfer, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, CustFee));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, BrokerFee));
  CHECK(SetObjectString(env, *result, pRspTransfer, Message));
  CHECK(SetObjectString(env, *result, pRspTransfer, Digest));
  CHECK(SetObjectChar(env, *result, pRspTransfer, BankAccType));
  CHECK(SetObjectString(env, *result, pRspTransfer, DeviceID));
  CHECK(SetObjectChar(env, *result, pRspTransfer, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pRspTransfer, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pRspTransfer, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pRspTransfer, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pRspTransfer, OperNo));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, RequestID));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, TID));
  CHECK(SetObjectChar(env, *result, pRspTransfer, TransferStatus));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, ErrorID));
  CHECK(SetObjectString(env, *result, pRspTransfer, ErrorMsg));
  CHECK(SetObjectString(env, *result, pRspTransfer, LongCustomerName));

  return napi_ok;
}

napi_status rtnFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pRspTransfer = MessageData<CThostFtdcRspTransferField>(message);

  if (!pRspTransfer)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspTransferField"));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradeCode));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankID));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankBranchID));
  CHECK(SetObjectString(env, *result, pRspTransfer, BrokerID));
  CHECK(SetObjectString(env, *result, pRspTransfer, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradeDate));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradeTime));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankSerial));
  CHECK(SetObjectString(env, *result, pRspTransfer, TradingDay));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, PlateSerial));
  CHECK(SetObjectChar(env, *result, pRspTransfer, LastFragment));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, SessionID));
  CHECK(SetObjectString(env, *result, pRspTransfer, CustomerName));
  CHECK(SetObjectChar(env, *result, pRspTransfer, IdCardType));
  CHECK(SetObjectString(env, *result, pRspTransfer, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pRspTransfer, CustType));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankAccount));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankPassWord));
  CHECK(SetObjectString(env, *result, pRspTransfer, AccountID));
  CHECK(SetObjectString(env, *result, pRspTransfer, Password));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, InstallID));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, FutureSerial));
  CHECK(SetObjectString(env, *result, pRspTransfer, UserID));
  CHECK(SetObjectChar(env, *result, pRspTransfer, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pRspTransfer, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pRspTransfer, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, CustFee));
  CHECK(SetObjectDouble(env, *result, pRspTransfer, BrokerFee));
  CHECK(SetObjectString(env, *result, pRspTransfer, Message));
  CHECK(SetObjectString(env, *result, pRspTransfer, Digest));
  CHECK(SetObjectChar(env, *result, pRspTransfer, BankAccType));
  CHECK(SetObjectString(env, *result, pRspTransfer, DeviceID));
  CHECK(SetObjectChar(env, *result, pRspTransfer, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pRspTransfer, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pRspTransfer, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pRspTransfer, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pRspTransfer, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pRspTransfer, OperNo));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, RequestID));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, TID));
  CHECK(SetObjectChar(env, *result, pRspTransfer, TransferStatus));
  CHECK(SetObjectInt32(env, *result, pRspTransfer, ErrorID));
  CHECK(SetObjectString(env, *result, pRspTransfer, ErrorMsg));
  CHECK(SetObjectString(env, *result, pRspTransfer, LongCustomerName));

  return napi_ok;
}

napi_status rtnRepealFromBankToFutureByFutureManual(napi_env env, const Message *message, napi_value *result) {
  auto pRspRepeal = MessageData<CThostFtdcRspRepealField>(message);

  if (!pRspRepeal)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspRepealField"));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RepealTimeInterval));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RepealedTimes));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankRepealFlag));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BrokerRepealFlag));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, PlateRepealSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankRepealSerial));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, FutureRepealSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeCode));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankBranchID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeDate));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeTime));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradingDay));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, PlateSerial));
  CHECK(SetObjectChar(env, *result, pRspRepeal, LastFragment));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, SessionID));
  CHECK(SetObjectString(env, *result, pRspRepeal, CustomerName));
  CHECK(SetObjectChar(env, *result, pRspRepeal, IdCardType));
  CHECK(SetObjectString(env, *result, pRspRepeal, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pRspRepeal, CustType));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankAccount));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankPassWord));
  CHECK(SetObjectString(env, *result, pRspRepeal, AccountID));
  CHECK(SetObjectString(env, *result, pRspRepeal, Password));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, InstallID));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, FutureSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, UserID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pRspRepeal, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pRspRepeal, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, CustFee));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, BrokerFee));
  CHECK(SetObjectString(env, *result, pRspRepeal, Message));
  CHECK(SetObjectString(env, *result, pRspRepeal, Digest));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankAccType));
  CHECK(SetObjectString(env, *result, pRspRepeal, DeviceID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pRspRepeal, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pRspRepeal, OperNo));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RequestID));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, TID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, TransferStatus));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, ErrorID));
  CHECK(SetObjectString(env, *result, pRspRepeal, ErrorMsg));
  CHECK(SetObjectString(env, *result, pRspRepeal, LongCustomerName));

  return napi_ok;
}

napi_status rtnRepealFromFutureToBankByFutureManual(napi_env env, const Message *message, napi_value *result) {
  auto pRspRepeal = MessageData<CThostFtdcRspRepealField>(message);

  if (!pRspRepeal)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspRepealField"));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RepealTimeInterval));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RepealedTimes));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankRepealFlag));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BrokerRepealFlag));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, PlateRepealSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankRepealSerial));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, FutureRepealSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeCode));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankBranchID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeDate));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeTime));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradingDay));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, PlateSerial));
  CHECK(SetObjectChar(env, *result, pRspRepeal, LastFragment));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, SessionID));
  CHECK(SetObjectString(env, *result, pRspRepeal, CustomerName));
  CHECK(SetObjectChar(env, *result, pRspRepeal, IdCardType));
  CHECK(SetObjectString(env, *result, pRspRepeal, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pRspRepeal, CustType));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankAccount));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankPassWord));
  CHECK(SetObjectString(env, *result, pRspRepeal, AccountID));
  CHECK(SetObjectString(env, *result, pRspRepeal, Password));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, InstallID));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, FutureSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, UserID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pRspRepeal, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pRspRepeal, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, CustFee));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, BrokerFee));
  CHECK(SetObjectString(env, *result, pRspRepeal, Message));
  CHECK(SetObjectString(env, *result, pRspRepeal, Digest));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankAccType));
  CHECK(SetObjectString(env, *result, pRspRepeal, DeviceID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pRspRepeal, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pRspRepeal, OperNo));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RequestID));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, TID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, TransferStatus));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, ErrorID));
  CHECK(SetObjectString(env, *result, pRspRepeal, ErrorMsg));
  CHECK(SetObjectString(env, *result, pRspRepeal, LongCustomerName));


  return napi_ok;
}

napi_status rtnQueryBankBalanceByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pNotifyQueryAccount = MessageData<CThostFtdcNotifyQueryAccountField>(message);

  if (!pNotifyQueryAccount)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcNotifyQueryAccountField"));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, TradeCode));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, BankID));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, BankBranchID));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, BrokerID));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, TradeDate));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, TradeTime));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, BankSerial));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, TradingDay));
  CHECK(SetObjectInt32(env, *result, pNotifyQueryAccount, PlateSerial));
  CHECK(SetObjectChar(env, *result, pNotifyQueryAccount, LastFragment));
  CHECK(SetObjectInt32(env, *result, pNotifyQueryAccount, SessionID));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, CustomerName));
  CHECK(SetObjectChar(env, *result, pNotifyQueryAccount, IdCardType));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pNotifyQueryAccount, CustType));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, BankAccount));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, BankPassWord));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, AccountID));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, Password));
  CHECK(SetObjectInt32(env, *result, pNotifyQueryAccount, FutureSerial));
  CHECK(SetObjectInt32(env, *result, pNotifyQueryAccount, InstallID));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, UserID));
  CHECK(SetObjectChar(env, *result, pNotifyQueryAccount, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, CurrencyID));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, Digest));
  CHECK(SetObjectChar(env, *result, pNotifyQueryAccount, BankAccType));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, DeviceID));
  CHECK(SetObjectChar(env, *result, pNotifyQueryAccount, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pNotifyQueryAccount, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pNotifyQueryAccount, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, OperNo));
  CHECK(SetObjectInt32(env, *result, pNotifyQueryAccount, RequestID));
  CHECK(SetObjectInt32(env, *result, pNotifyQueryAccount, TID));
  CHECK(SetObjectDouble(env, *result, pNotifyQueryAccount, BankUseAmount));
  CHECK(SetObjectDouble(env, *result, pNotifyQueryAccount, BankFetchAmount));
  CHECK(SetObjectInt32(env, *result, pNotifyQueryAccount, ErrorID));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, ErrorMsg));
  CHECK(SetObjectString(env, *result, pNotifyQueryAccount, LongCustomerName));

  return napi_ok;
}

napi_status errRtnBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pReqTransfer = MessageData<CThostFtdcReqTransferField>(message);

  if (!pReqTransfer)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcReqTransferField"));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradeCode));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankID));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankBranchID));
  CHECK(SetObjectString(env, *result, pReqTransfer, BrokerID));
  CHECK(SetObjectString(env, *result, pReqTransfer, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradeDate));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradeTime));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankSerial));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradingDay));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, PlateSerial));
  CHECK(SetObjectChar(env, *result, pReqTransfer, LastFragment));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, SessionID));
  CHECK(SetObjectString(env, *result, pReqTransfer, CustomerName));
  CHECK(SetObjectChar(env, *result, pReqTransfer, IdCardType));
  CHECK(SetObjectString(env, *result, pReqTransfer, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pReqTransfer, CustType));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankAccount));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankPassWord));
  CHECK(SetObjectString(env, *result, pReqTransfer, AccountID));
  CHECK(SetObjectString(env, *result, pReqTransfer, Password));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, InstallID));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, FutureSerial));
  CHECK(SetObjectString(env, *result, pReqTransfer, UserID));
  CHECK(SetObjectChar(env, *result, pReqTransfer, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pReqTransfer, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pReqTransfer, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, CustFee));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, BrokerFee));
  CHECK(SetObjectString(env, *result, pReqTransfer, Message));
  CHECK(SetObjectString(env, *result, pReqTransfer, Digest));
  CHECK(SetObjectChar(env, *result, pReqTransfer, BankAccType));
  CHECK(SetObjectString(env, *result, pReqTransfer, DeviceID));
  CHECK(SetObjectChar(env, *result, pReqTransfer, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pReqTransfer, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pReqTransfer, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pReqTransfer, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pReqTransfer, OperNo));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, RequestID));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, TID));
  CHECK(SetObjectChar(env, *result, pReqTransfer, TransferStatus));
  CHECK(SetObjectString(env, *result, pReqTransfer, LongCustomerName));

  return napi_ok;
}

napi_status errRtnFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pReqTransfer = MessageData<CThostFtdcReqTransferField>(message);

  if (!pReqTransfer)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcReqTransferField"));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradeCode));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankID));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankBranchID));
  CHECK(SetObjectString(env, *result, pReqTransfer, BrokerID));
  CHECK(SetObjectString(env, *result, pReqTransfer, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradeDate));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradeTime));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankSerial));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradingDay));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, PlateSerial));
  CHECK(SetObjectChar(env, *result, pReqTransfer, LastFragment));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, SessionID));
  CHECK(SetObjectString(env, *result, pReqTransfer, CustomerName));
  CHECK(SetObjectChar(env, *result, pReqTransfer, IdCardType));
  CHECK(SetObjectString(env, *result, pReqTransfer, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pReqTransfer, CustType));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankAccount));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankPassWord));
  CHECK(SetObjectString(env, *result, pReqTransfer, AccountID));
  CHECK(SetObjectString(env, *result, pReqTransfer, Password));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, InstallID));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, FutureSerial));
  CHECK(SetObjectString(env, *result, pReqTransfer, UserID));
  CHECK(SetObjectChar(env, *result, pReqTransfer, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pReqTransfer, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pReqTransfer, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, CustFee));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, BrokerFee));
  CHECK(SetObjectString(env, *result, pReqTransfer, Message));
  CHECK(SetObjectString(env, *result, pReqTransfer, Digest));
  CHECK(SetObjectChar(env, *result, pReqTransfer, BankAccType));
  CHECK(SetObjectString(env, *result, pReqTransfer, DeviceID));
  CHECK(SetObjectChar(env, *result, pReqTransfer, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pReqTransfer, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pReqTransfer, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pReqTransfer, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pReqTransfer, OperNo));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, RequestID));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, TID));
  CHECK(SetObjectChar(env, *result, pReqTransfer, TransferStatus));
  CHECK(SetObjectString(env, *result, pReqTransfer, LongCustomerName));

  return napi_ok;
}

napi_status errRtnRepealBankToFutureByFutureManual(napi_env env, const Message *message, napi_value *result) {
  auto pReqRepeal = MessageData<CThostFtdcReqRepealField>(message);

  if (!pReqRepeal)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcReqRepealField"));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, RepealTimeInterval));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, RepealedTimes));
  CHECK(SetObjectChar(env, *result, pReqRepeal, BankRepealFlag));
  CHECK(SetObjectChar(env, *result, pReqRepeal, BrokerRepealFlag));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, PlateRepealSerial));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankRepealSerial));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, FutureRepealSerial));
  CHECK(SetObjectString(env, *result, pReqRepeal, TradeCode));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankID));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankBranchID));
  CHECK(SetObjectString(env, *result, pReqRepeal, BrokerID));
  CHECK(SetObjectString(env, *result, pReqRepeal, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pReqRepeal, TradeDate));
  CHECK(SetObjectString(env, *result, pReqRepeal, TradeTime));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankSerial));
  CHECK(SetObjectString(env, *result, pReqRepeal, TradingDay));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, PlateSerial));
  CHECK(SetObjectChar(env, *result, pReqRepeal, LastFragment));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, SessionID));
  CHECK(SetObjectString(env, *result, pReqRepeal, CustomerName));
  CHECK(SetObjectChar(env, *result, pReqRepeal, IdCardType));
  CHECK(SetObjectString(env, *result, pReqRepeal, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pReqRepeal, CustType));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankAccount));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankPassWord));
  CHECK(SetObjectString(env, *result, pReqRepeal, AccountID));
  CHECK(SetObjectString(env, *result, pReqRepeal, Password));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, InstallID));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, FutureSerial));
  CHECK(SetObjectString(env, *result, pReqRepeal, UserID));
  CHECK(SetObjectChar(env, *result, pReqRepeal, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pReqRepeal, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pReqRepeal, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pReqRepeal, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pReqRepeal, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pReqRepeal, CustFee));
  CHECK(SetObjectDouble(env, *result, pReqRepeal, BrokerFee));
  CHECK(SetObjectString(env, *result, pReqRepeal, Message));
  CHECK(SetObjectString(env, *result, pReqRepeal, Digest));
  CHECK(SetObjectChar(env, *result, pReqRepeal, BankAccType));
  CHECK(SetObjectString(env, *result, pReqRepeal, DeviceID));
  CHECK(SetObjectChar(env, *result, pReqRepeal, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pReqRepeal, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pReqRepeal, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pReqRepeal, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pReqRepeal, OperNo));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, RequestID));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, TID));
  CHECK(SetObjectChar(env, *result, pReqRepeal, TransferStatus));
  CHECK(SetObjectString(env, *result, pReqRepeal, LongCustomerName));

  return napi_ok;
}

napi_status errRtnRepealFutureToBankByFutureManual(napi_env env, const Message *message, napi_value *result) {
  auto pReqRepeal = MessageData<CThostFtdcReqRepealField>(message);

  if (!pReqRepeal)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcReqRepealField"));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, RepealTimeInterval));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, RepealedTimes));
  CHECK(SetObjectChar(env, *result, pReqRepeal, BankRepealFlag));
  CHECK(SetObjectChar(env, *result, pReqRepeal, BrokerRepealFlag));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, PlateRepealSerial));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankRepealSerial));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, FutureRepealSerial));
  CHECK(SetObjectString(env, *result, pReqRepeal, TradeCode));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankID));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankBranchID));
  CHECK(SetObjectString(env, *result, pReqRepeal, BrokerID));
  CHECK(SetObjectString(env, *result, pReqRepeal, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pReqRepeal, TradeDate));
  CHECK(SetObjectString(env, *result, pReqRepeal, TradeTime));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankSerial));
  CHECK(SetObjectString(env, *result, pReqRepeal, TradingDay));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, PlateSerial));
  CHECK(SetObjectChar(env, *result, pReqRepeal, LastFragment));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, SessionID));
  CHECK(SetObjectString(env, *result, pReqRepeal, CustomerName));
  CHECK(SetObjectChar(env, *result, pReqRepeal, IdCardType));
  CHECK(SetObjectString(env, *result, pReqRepeal, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pReqRepeal, CustType));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankAccount));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankPassWord));
  CHECK(SetObjectString(env, *result, pReqRepeal, AccountID));
  CHECK(SetObjectString(env, *result, pReqRepeal, Password));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, InstallID));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, FutureSerial));
  CHECK(SetObjectString(env, *result, pReqRepeal, UserID));
  CHECK(SetObjectChar(env, *result, pReqRepeal, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pReqRepeal, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pReqRepeal, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pReqRepeal, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pReqRepeal, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pReqRepeal, CustFee));
  CHECK(SetObjectDouble(env, *result, pReqRepeal, BrokerFee));
  CHECK(SetObjectString(env, *result, pReqRepeal, Message));
  CHECK(SetObjectString(env, *result, pReqRepeal, Digest));
  CHECK(SetObjectChar(env, *result, pReqRepeal, BankAccType));
  CHECK(SetObjectString(env, *result, pReqRepeal, DeviceID));
  CHECK(SetObjectChar(env, *result, pReqRepeal, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pReqRepeal, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pReqRepeal, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pReqRepeal, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pReqRepeal, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pReqRepeal, OperNo));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, RequestID));
  CHECK(SetObjectInt32(env, *result, pReqRepeal, TID));
  CHECK(SetObjectChar(env, *result, pReqRepeal, TransferStatus));
  CHECK(SetObjectString(env, *result, pReqRepeal, LongCustomerName));

  return napi_ok;
}

napi_status errRtnQueryBankBalanceByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pReqQueryAccount = MessageData<CThostFtdcReqQueryAccountField>(message);

  if (!pReqQueryAccount)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcReqQueryAccountField"));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, TradeCode));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BankID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BankBranchID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BrokerID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, TradeDate));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, TradeTime));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BankSerial));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, TradingDay));
  CHECK(SetObjectInt32(env, *result, pReqQueryAccount, PlateSerial));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, LastFragment));
  CHECK(SetObjectInt32(env, *result, pReqQueryAccount, SessionID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, CustomerName));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, IdCardType));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, CustType));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BankAccount));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BankPassWord));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, AccountID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, Password));
  CHECK(SetObjectInt32(env, *result, pReqQueryAccount, FutureSerial));
  CHECK(SetObjectInt32(env, *result, pReqQueryAccount, InstallID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, UserID));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, CurrencyID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, Digest));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, BankAccType));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, DeviceID));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, OperNo));
  CHECK(SetObjectInt32(env, *result, pReqQueryAccount, RequestID));
  CHECK(SetObjectInt32(env, *result, pReqQueryAccount, TID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, LongCustomerName));

  return napi_ok;
}

napi_status rtnRepealFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pRspRepeal = MessageData<CThostFtdcRspRepealField>(message);

  if (!pRspRepeal)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspRepealField"));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RepealTimeInterval));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RepealedTimes));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankRepealFlag));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BrokerRepealFlag));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, PlateRepealSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankRepealSerial));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, FutureRepealSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeCode));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankBranchID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeDate));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeTime));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradingDay));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, PlateSerial));
  CHECK(SetObjectChar(env, *result, pRspRepeal, LastFragment));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, SessionID));
  CHECK(SetObjectString(env, *result, pRspRepeal, CustomerName));
  CHECK(SetObjectChar(env, *result, pRspRepeal, IdCardType));
  CHECK(SetObjectString(env, *result, pRspRepeal, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pRspRepeal, CustType));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankAccount));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankPassWord));
  CHECK(SetObjectString(env, *result, pRspRepeal, AccountID));
  CHECK(SetObjectString(env, *result, pRspRepeal, Password));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, InstallID));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, FutureSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, UserID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pRspRepeal, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pRspRepeal, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, CustFee));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, BrokerFee));
  CHECK(SetObjectString(env, *result, pRspRepeal, Message));
  CHECK(SetObjectString(env, *result, pRspRepeal, Digest));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankAccType));
  CHECK(SetObjectString(env, *result, pRspRepeal, DeviceID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pRspRepeal, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pRspRepeal, OperNo));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RequestID));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, TID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, TransferStatus));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, ErrorID));
  CHECK(SetObjectString(env, *result, pRspRepeal, ErrorMsg));
  CHECK(SetObjectString(env, *result, pRspRepeal, LongCustomerName));

  return napi_ok;
}

napi_status rtnRepealFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pRspRepeal = MessageData<CThostFtdcRspRepealField>(message);

  if (!pRspRepeal)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRspRepealField"));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RepealTimeInterval));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RepealedTimes));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankRepealFlag));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BrokerRepealFlag));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, PlateRepealSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankRepealSerial));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, FutureRepealSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeCode));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankBranchID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerID));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeDate));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradeTime));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, TradingDay));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, PlateSerial));
  CHECK(SetObjectChar(env, *result, pRspRepeal, LastFragment));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, SessionID));
  CHECK(SetObjectString(env, *result, pRspRepeal, CustomerName));
  CHECK(SetObjectChar(env, *result, pRspRepeal, IdCardType));
  CHECK(SetObjectString(env, *result, pRspRepeal, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pRspRepeal, CustType));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankAccount));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankPassWord));
  CHECK(SetObjectString(env, *result, pRspRepeal, AccountID));
  CHECK(SetObjectString(env, *result, pRspRepeal, Password));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, InstallID));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, FutureSerial));
  CHECK(SetObjectString(env, *result, pRspRepeal, UserID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pRspRepeal, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pRspRepeal, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, CustFee));
  CHECK(SetObjectDouble(env, *result, pRspRepeal, BrokerFee));
  CHECK(SetObjectString(env, *result, pRspRepeal, Message));
  CHECK(SetObjectString(env, *result, pRspRepeal, Digest));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankAccType));
  CHECK(SetObjectString(env, *result, pRspRepeal, DeviceID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pRspRepeal, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pRspRepeal, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pRspRepeal, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pRspRepeal, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pRspRepeal, OperNo));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, RequestID));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, TID));
  CHECK(SetObjectChar(env, *result, pRspRepeal, TransferStatus));
  CHECK(SetObjectInt32(env, *result, pRspRepeal, ErrorID));
  CHECK(SetObjectString(env, *result, pRspRepeal, ErrorMsg));
  CHECK(SetObjectString(env, *result, pRspRepeal, LongCustomerName));

  return napi_ok;
}

napi_status rspFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pReqTransfer = MessageData<CThostFtdcReqTransferField>(message);

  if (!pReqTransfer)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcReqTransferField"));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradeCode));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankID));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankBranchID));
  CHECK(SetObjectString(env, *result, pReqTransfer, BrokerID));
  CHECK(SetObjectString(env, *result, pReqTransfer, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradeDate));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradeTime));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankSerial));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradingDay));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, PlateSerial));
  CHECK(SetObjectChar(env, *result, pReqTransfer, LastFragment));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, SessionID));
  CHECK(SetObjectString(env, *result, pReqTransfer, CustomerName));
  CHECK(SetObjectChar(env, *result, pReqTransfer, IdCardType));
  CHECK(SetObjectString(env, *result, pReqTransfer, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pReqTransfer, CustType));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankAccount));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankPassWord));
  CHECK(SetObjectString(env, *result, pReqTransfer, AccountID));
  CHECK(SetObjectString(env, *result, pReqTransfer, Password));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, InstallID));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, FutureSerial));
  CHECK(SetObjectString(env, *result, pReqTransfer, UserID));
  CHECK(SetObjectChar(env, *result, pReqTransfer, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pReqTransfer, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pReqTransfer, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, CustFee));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, BrokerFee));
  CHECK(SetObjectString(env, *result, pReqTransfer, Message));
  CHECK(SetObjectString(env, *result, pReqTransfer, Digest));
  CHECK(SetObjectChar(env, *result, pReqTransfer, BankAccType));
  CHECK(SetObjectString(env, *result, pReqTransfer, DeviceID));
  CHECK(SetObjectChar(env, *result, pReqTransfer, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pReqTransfer, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pReqTransfer, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pReqTransfer, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pReqTransfer, OperNo));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, RequestID));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, TID));
  CHECK(SetObjectChar(env, *result, pReqTransfer, TransferStatus));
  CHECK(SetObjectString(env, *result, pReqTransfer, LongCustomerName));

  return napi_ok;
}

napi_status rspFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pReqTransfer = MessageData<CThostFtdcReqTransferField>(message);

  if (!pReqTransfer)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcReqTransferField"));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradeCode));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankID));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankBranchID));
  CHECK(SetObjectString(env, *result, pReqTransfer, BrokerID));
  CHECK(SetObjectString(env, *result, pReqTransfer, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradeDate));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradeTime));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankSerial));
  CHECK(SetObjectString(env, *result, pReqTransfer, TradingDay));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, PlateSerial));
  CHECK(SetObjectChar(env, *result, pReqTransfer, LastFragment));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, SessionID));
  CHECK(SetObjectString(env, *result, pReqTransfer, CustomerName));
  CHECK(SetObjectChar(env, *result, pReqTransfer, IdCardType));
  CHECK(SetObjectString(env, *result, pReqTransfer, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pReqTransfer, CustType));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankAccount));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankPassWord));
  CHECK(SetObjectString(env, *result, pReqTransfer, AccountID));
  CHECK(SetObjectString(env, *result, pReqTransfer, Password));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, InstallID));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, FutureSerial));
  CHECK(SetObjectString(env, *result, pReqTransfer, UserID));
  CHECK(SetObjectChar(env, *result, pReqTransfer, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pReqTransfer, CurrencyID));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, TradeAmount));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, FutureFetchAmount));
  CHECK(SetObjectChar(env, *result, pReqTransfer, FeePayFlag));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, CustFee));
  CHECK(SetObjectDouble(env, *result, pReqTransfer, BrokerFee));
  CHECK(SetObjectString(env, *result, pReqTransfer, Message));
  CHECK(SetObjectString(env, *result, pReqTransfer, Digest));
  CHECK(SetObjectChar(env, *result, pReqTransfer, BankAccType));
  CHECK(SetObjectString(env, *result, pReqTransfer, DeviceID));
  CHECK(SetObjectChar(env, *result, pReqTransfer, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pReqTransfer, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pReqTransfer, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pReqTransfer, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pReqTransfer, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pReqTransfer, OperNo));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, RequestID));
  CHECK(SetObjectInt32(env, *result, pReqTransfer, TID));
  CHECK(SetObjectChar(env, *result, pReqTransfer, TransferStatus));
  CHECK(SetObjectString(env, *result, pReqTransfer, LongCustomerName));

  return napi_ok;
}

napi_status rspQueryBankAccountMoneyByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pReqQueryAccount = MessageData<CThostFtdcReqQueryAccountField>(message);

  if (!pReqQueryAccount)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcReqQueryAccountField"));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, TradeCode));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BankID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BankBranchID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BrokerID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, TradeDate));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, TradeTime));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BankSerial));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, TradingDay));
  CHECK(SetObjectInt32(env, *result, pReqQueryAccount, PlateSerial));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, LastFragment));
  CHECK(SetObjectInt32(env, *result, pReqQueryAccount, SessionID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, CustomerName));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, IdCardType));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, CustType));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BankAccount));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BankPassWord));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, AccountID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, Password));
  CHECK(SetObjectInt32(env, *result, pReqQueryAccount, FutureSerial));
  CHECK(SetObjectInt32(env, *result, pReqQueryAccount, InstallID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, UserID));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, CurrencyID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, Digest));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, BankAccType));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, DeviceID));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pReqQueryAccount, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, OperNo));
  CHECK(SetObjectInt32(env, *result, pReqQueryAccount, RequestID));
  CHECK(SetObjectInt32(env, *result, pReqQueryAccount, TID));
  CHECK(SetObjectString(env, *result, pReqQueryAccount, LongCustomerName));

  return napi_ok;
}

napi_status rtnOpenAccountByBank(napi_env env, const Message *message, napi_value *result) {
  auto pOpenAccount = MessageData<CThostFtdcOpenAccountField>(message);

  if (!pOpenAccount)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcOpenAccountField"));
  CHECK(SetObjectString(env, *result, pOpenAccount, TradeCode));
  CHECK(SetObjectString(env, *result, pOpenAccount, BankID));
  CHECK(SetObjectString(env, *result, pOpenAccount, BankBranchID));
  CHECK(SetObjectString(env, *result, pOpenAccount, BrokerID));
  CHECK(SetObjectString(env, *result, pOpenAccount, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pOpenAccount, TradeDate));
  CHECK(SetObjectString(env, *result, pOpenAccount, TradeTime));
  CHECK(SetObjectString(env, *result, pOpenAccount, BankSerial));
  CHECK(SetObjectString(env, *result, pOpenAccount, TradingDay));
  CHECK(SetObjectInt32(env, *result, pOpenAccount, PlateSerial));
  CHECK(SetObjectChar(env, *result, pOpenAccount, LastFragment));
  CHECK(SetObjectInt32(env, *result, pOpenAccount, SessionID));
  CHECK(SetObjectString(env, *result, pOpenAccount, CustomerName));
  CHECK(SetObjectChar(env, *result, pOpenAccount, IdCardType));
  CHECK(SetObjectString(env, *result, pOpenAccount, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pOpenAccount, Gender));
  CHECK(SetObjectString(env, *result, pOpenAccount, CountryCode));
  CHECK(SetObjectChar(env, *result, pOpenAccount, CustType));
  CHECK(SetObjectString(env, *result, pOpenAccount, Address));
  CHECK(SetObjectString(env, *result, pOpenAccount, ZipCode));
  CHECK(SetObjectString(env, *result, pOpenAccount, Telephone));
  CHECK(SetObjectString(env, *result, pOpenAccount, MobilePhone));
  CHECK(SetObjectString(env, *result, pOpenAccount, Fax));
  CHECK(SetObjectString(env, *result, pOpenAccount, EMail));
  CHECK(SetObjectChar(env, *result, pOpenAccount, MoneyAccountStatus));
  CHECK(SetObjectString(env, *result, pOpenAccount, BankAccount));
  CHECK(SetObjectString(env, *result, pOpenAccount, BankPassWord));
  CHECK(SetObjectString(env, *result, pOpenAccount, AccountID));
  CHECK(SetObjectString(env, *result, pOpenAccount, Password));
  CHECK(SetObjectInt32(env, *result, pOpenAccount, InstallID));
  CHECK(SetObjectChar(env, *result, pOpenAccount, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pOpenAccount, CurrencyID));
  CHECK(SetObjectChar(env, *result, pOpenAccount, CashExchangeCode));
  CHECK(SetObjectString(env, *result, pOpenAccount, Digest));
  CHECK(SetObjectChar(env, *result, pOpenAccount, BankAccType));
  CHECK(SetObjectString(env, *result, pOpenAccount, DeviceID));
  CHECK(SetObjectChar(env, *result, pOpenAccount, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pOpenAccount, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pOpenAccount, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pOpenAccount, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pOpenAccount, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pOpenAccount, OperNo));
  CHECK(SetObjectInt32(env, *result, pOpenAccount, TID));
  CHECK(SetObjectString(env, *result, pOpenAccount, UserID));
  CHECK(SetObjectInt32(env, *result, pOpenAccount, ErrorID));
  CHECK(SetObjectString(env, *result, pOpenAccount, ErrorMsg));
  CHECK(SetObjectString(env, *result, pOpenAccount, LongCustomerName));

  return napi_ok;
}

napi_status rtnCancelAccountByBank(napi_env env, const Message *message, napi_value *result) {
  auto pCancelAccount = MessageData<CThostFtdcCancelAccountField>(message);

  if (!pCancelAccount)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcCancelAccountField"));
  CHECK(SetObjectString(env, *result, pCancelAccount, TradeCode));
  CHECK(SetObjectString(env, *result, pCancelAccount, BankID));
  CHECK(SetObjectString(env, *result, pCancelAccount, BankBranchID));
  CHECK(SetObjectString(env, *result, pCancelAccount, BrokerID));
  CHECK(SetObjectString(env, *result, pCancelAccount, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pCancelAccount, TradeDate));
  CHECK(SetObjectString(env, *result, pCancelAccount, TradeTime));
  CHECK(SetObjectString(env, *result, pCancelAccount, BankSerial));
  CHECK(SetObjectString(env, *result, pCancelAccount, TradingDay));
  CHECK(SetObjectInt32(env, *result, pCancelAccount, PlateSerial));
  CHECK(SetObjectChar(env, *result, pCancelAccount, LastFragment));
  CHECK(SetObjectInt32(env, *result, pCancelAccount, SessionID));
  CHECK(SetObjectString(env, *result, pCancelAccount, CustomerName));
  CHECK(SetObjectChar(env, *result, pCancelAccount, IdCardType));
  CHECK(SetObjectString(env, *result, pCancelAccount, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pCancelAccount, Gender));
  CHECK(SetObjectString(env, *result, pCancelAccount, CountryCode));
  CHECK(SetObjectChar(env, *result, pCancelAccount, CustType));
  CHECK(SetObjectString(env, *result, pCancelAccount, Address));
  CHECK(SetObjectString(env, *result, pCancelAccount, ZipCode));
  CHECK(SetObjectString(env, *result, pCancelAccount, Telephone));
  CHECK(SetObjectString(env, *result, pCancelAccount, MobilePhone));
  CHECK(SetObjectString(env, *result, pCancelAccount, Fax));
  CHECK(SetObjectString(env, *result, pCancelAccount, EMail));
  CHECK(SetObjectChar(env, *result, pCancelAccount, MoneyAccountStatus));
  CHECK(SetObjectString(env, *result, pCancelAccount, BankAccount));
  CHECK(SetObjectString(env, *result, pCancelAccount, BankPassWord));
  CHECK(SetObjectString(env, *result, pCancelAccount, AccountID));
  CHECK(SetObjectString(env, *result, pCancelAccount, Password));
  CHECK(SetObjectInt32(env, *result, pCancelAccount, InstallID));
  CHECK(SetObjectChar(env, *result, pCancelAccount, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pCancelAccount, CurrencyID));
  CHECK(SetObjectChar(env, *result, pCancelAccount, CashExchangeCode));
  CHECK(SetObjectString(env, *result, pCancelAccount, Digest));
  CHECK(SetObjectChar(env, *result, pCancelAccount, BankAccType));
  CHECK(SetObjectString(env, *result, pCancelAccount, DeviceID));
  CHECK(SetObjectChar(env, *result, pCancelAccount, BankSecuAccType));
  CHECK(SetObjectString(env, *result, pCancelAccount, BrokerIDByBank));
  CHECK(SetObjectString(env, *result, pCancelAccount, BankSecuAcc));
  CHECK(SetObjectChar(env, *result, pCancelAccount, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pCancelAccount, SecuPwdFlag));
  CHECK(SetObjectString(env, *result, pCancelAccount, OperNo));
  CHECK(SetObjectInt32(env, *result, pCancelAccount, TID));
  CHECK(SetObjectString(env, *result, pCancelAccount, UserID));
  CHECK(SetObjectInt32(env, *result, pCancelAccount, ErrorID));
  CHECK(SetObjectString(env, *result, pCancelAccount, ErrorMsg));
  CHECK(SetObjectString(env, *result, pCancelAccount, LongCustomerName));

  return napi_ok;
}

napi_status rtnChangeAccountByBank(napi_env env, const Message *message, napi_value *result) {
  auto pChangeAccount = MessageData<CThostFtdcChangeAccountField>(message);

  if (!pChangeAccount)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcChangeAccountField"));
  CHECK(SetObjectString(env, *result, pChangeAccount, TradeCode));
  CHECK(SetObjectString(env, *result, pChangeAccount, BankID));
  CHECK(SetObjectString(env, *result, pChangeAccount, BankBranchID));
  CHECK(SetObjectString(env, *result, pChangeAccount, BrokerID));
  CHECK(SetObjectString(env, *result, pChangeAccount, BrokerBranchID));
  CHECK(SetObjectString(env, *result, pChangeAccount, TradeDate));
  CHECK(SetObjectString(env, *result, pChangeAccount, TradeTime));
  CHECK(SetObjectString(env, *result, pChangeAccount, BankSerial));
  CHECK(SetObjectString(env, *result, pChangeAccount, TradingDay));
  CHECK(SetObjectInt32(env, *result, pChangeAccount, PlateSerial));
  CHECK(SetObjectChar(env, *result, pChangeAccount, LastFragment));
  CHECK(SetObjectInt32(env, *result, pChangeAccount, SessionID));
  CHECK(SetObjectString(env, *result, pChangeAccount, CustomerName));
  CHECK(SetObjectChar(env, *result, pChangeAccount, IdCardType));
  CHECK(SetObjectString(env, *result, pChangeAccount, IdentifiedCardNo));
  CHECK(SetObjectChar(env, *result, pChangeAccount, Gender));
  CHECK(SetObjectString(env, *result, pChangeAccount, CountryCode));
  CHECK(SetObjectChar(env, *result, pChangeAccount, CustType));
  CHECK(SetObjectString(env, *result, pChangeAccount, Address));
  CHECK(SetObjectString(env, *result, pChangeAccount, ZipCode));
  CHECK(SetObjectString(env, *result, pChangeAccount, Telephone));
  CHECK(SetObjectString(env, *result, pChangeAccount, MobilePhone));
  CHECK(SetObjectString(env, *result, pChangeAccount, Fax));
  CHECK(SetObjectString(env, *result, pChangeAccount, EMail));
  CHECK(SetObjectChar(env, *result, pChangeAccount, MoneyAccountStatus));
  CHECK(SetObjectString(env, *result, pChangeAccount, BankAccount));
  CHECK(SetObjectString(env, *result, pChangeAccount, BankPassWord));
  CHECK(SetObjectString(env, *result, pChangeAccount, NewBankAccount));
  CHECK(SetObjectString(env, *result, pChangeAccount, NewBankPassWord));
  CHECK(SetObjectString(env, *result, pChangeAccount, AccountID));
  CHECK(SetObjectString(env, *result, pChangeAccount, Password));
  CHECK(SetObjectChar(env, *result, pChangeAccount, BankAccType));
  CHECK(SetObjectInt32(env, *result, pChangeAccount, InstallID));
  CHECK(SetObjectChar(env, *result, pChangeAccount, VerifyCertNoFlag));
  CHECK(SetObjectString(env, *result, pChangeAccount, CurrencyID));
  CHECK(SetObjectString(env, *result, pChangeAccount, BrokerIDByBank));
  CHECK(SetObjectChar(env, *result, pChangeAccount, BankPwdFlag));
  CHECK(SetObjectChar(env, *result, pChangeAccount, SecuPwdFlag));
  CHECK(SetObjectInt32(env, *result, pChangeAccount, TID));
  CHECK(SetObjectString(env, *result, pChangeAccount, Digest));
  CHECK(SetObjectInt32(env, *result, pChangeAccount, ErrorID));
  CHECK(SetObjectString(env, *result, pChangeAccount, ErrorMsg));
  CHECK(SetObjectString(env, *result, pChangeAccount, LongCustomerName));

  return napi_ok;
}

napi_status rspQryClassifiedInstrument(napi_env env, const Message *message, napi_value *result) {
  auto pInstrument = MessageData<CThostFtdcInstrumentField>(message);

  if (!pInstrument)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcInstrumentField"));
  CHECK(SetObjectString(env, *result, pInstrument, ExchangeID));
  CHECK(SetObjectString(env, *result, pInstrument, InstrumentName));
  CHECK(SetObjectChar(env, *result, pInstrument, ProductClass));
  CHECK(SetObjectInt32(env, *result, pInstrument, DeliveryYear));
  CHECK(SetObjectInt32(env, *result, pInstrument, DeliveryMonth));
  CHECK(SetObjectInt32(env, *result, pInstrument, MaxMarketOrderVolume));
  CHECK(SetObjectInt32(env, *result, pInstrument, MinMarketOrderVolume));
  CHECK(SetObjectInt32(env, *result, pInstrument, MaxLimitOrderVolume));
  CHECK(SetObjectInt32(env, *result, pInstrument, MinLimitOrderVolume));
  CHECK(SetObjectInt32(env, *result, pInstrument, VolumeMultiple));
  CHECK(SetObjectDouble(env, *result, pInstrument, PriceTick));
  CHECK(SetObjectString(env, *result, pInstrument, CreateDate));
  CHECK(SetObjectString(env, *result, pInstrument, OpenDate));
  CHECK(SetObjectString(env, *result, pInstrument, ExpireDate));
  CHECK(SetObjectString(env, *result, pInstrument, StartDelivDate));
  CHECK(SetObjectString(env, *result, pInstrument, EndDelivDate));
  CHECK(SetObjectChar(env, *result, pInstrument, InstLifePhase));
  CHECK(SetObjectInt32(env, *result, pInstrument, IsTrading));
  CHECK(SetObjectChar(env, *result, pInstrument, PositionType));
  CHECK(SetObjectChar(env, *result, pInstrument, PositionDateType));
  CHECK(SetObjectDouble(env, *result, pInstrument, LongMarginRatio));
  CHECK(SetObjectDouble(env, *result, pInstrument, ShortMarginRatio));
  CHECK(SetObjectChar(env, *result, pInstrument, MaxMarginSideAlgorithm));
  CHECK(SetObjectDouble(env, *result, pInstrument, StrikePrice));
  CHECK(SetObjectChar(env, *result, pInstrument, OptionsType));
  CHECK(SetObjectDouble(env, *result, pInstrument, UnderlyingMultiple));
  CHECK(SetObjectChar(env, *result, pInstrument, CombinationType));
  CHECK(SetObjectString(env, *result, pInstrument, InstrumentID));
  CHECK(SetObjectString(env, *result, pInstrument, ExchangeInstID));
  CHECK(SetObjectString(env, *result, pInstrument, ProductID));
  CHECK(SetObjectString(env, *result, pInstrument, UnderlyingInstrID));

  return napi_ok;
}

napi_status rspQryCombPromotionParam(napi_env env, const Message *message, napi_value *result) {
  auto pCombPromotionParam = MessageData<CThostFtdcCombPromotionParamField>(message);

  if (!pCombPromotionParam)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcCombPromotionParamField"));
  CHECK(SetObjectString(env, *result, pCombPromotionParam, ExchangeID));
  CHECK(SetObjectString(env, *result, pCombPromotionParam, InstrumentID));
  CHECK(SetObjectString(env, *result, pCombPromotionParam, CombHedgeFlag));
  CHECK(SetObjectDouble(env, *result, pCombPromotionParam, Xparameter));

  return napi_ok;
}

napi_status rspQryRiskSettleInvstPosition(napi_env env, const Message *message, napi_value *result) {
  auto pRiskSettleInvstPosition = MessageData<CThostFtdcRiskSettleInvstPositionField>(message);

  if (!pRiskSettleInvstPosition)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRiskSettleInvstPositionField"));
  CHECK(SetObjectString(env, *result, pRiskSettleInvstPosition, InstrumentID));
  CHECK(SetObjectString(env, *result, pRiskSettleInvstPosition, BrokerID));
  CHECK(SetObjectString(env, *result, pRiskSettleInvstPosition, InvestorID));
  CHECK(SetObjectChar(env, *result, pRiskSettleInvstPosition, PosiDirection));
  CHECK(SetObjectChar(env, *result, pRiskSettleInvstPosition, HedgeFlag));
  CHECK(SetObjectChar(env, *result, pRiskSettleInvstPosition, PositionDate));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, YdPosition));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, Position));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, LongFrozen));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, ShortFrozen));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, LongFrozenAmount));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, ShortFrozenAmount));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, OpenVolume));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, CloseVolume));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, OpenAmount));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, CloseAmount));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, PositionCost));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, PreMargin));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, UseMargin));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, FrozenMargin));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, FrozenCash));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, FrozenCommission));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, CashIn));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, Commission));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, CloseProfit));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, PositionProfit));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, PreSettlementPrice));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, SettlementPrice));
  CHECK(SetObjectString(env, *result, pRiskSettleInvstPosition, TradingDay));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, SettlementID));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, OpenCost));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, ExchangeMargin));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, CombPosition));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, CombLongFrozen));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, CombShortFrozen));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, CloseProfitByDate));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, CloseProfitByTrade));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, TodayPosition));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, MarginRateByMoney));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, MarginRateByVolume));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, StrikeFrozen));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, StrikeFrozenAmount));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, AbandonFrozen));
  CHECK(SetObjectString(env, *result, pRiskSettleInvstPosition, ExchangeID));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, YdStrikeFrozen));
  CHECK(SetObjectString(env, *result, pRiskSettleInvstPosition, InvestUnitID));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, PositionCostOffset));
  CHECK(SetObjectInt32(env, *result, pRiskSettleInvstPosition, TasPosition));
  CHECK(SetObjectDouble(env, *result, pRiskSettleInvstPosition, TasPositionCost));

  return napi_ok;
}

napi_status rspQryRiskSettleProductStatus(napi_env env, const Message *message, napi_value *result) {
  auto pRiskSettleProductStatus = MessageData<CThostFtdcRiskSettleProductStatusField>(message);

  if (!pRiskSettleProductStatus)
    return napi_get_undefined(env, result);

  CHECK(napi_create_object(env, result));
  CHECK(objectSetString(env, *result, "kind", "CThostFtdcRiskSettleProductStatusField"));
  CHECK(SetObjectString(env, *result, pRiskSettleProductStatus, ExchangeID));
  CHECK(SetObjectString(env, *result, pRiskSettleProductStatus, ProductID));
  CHECK(SetObjectChar(env, *result, pRiskSettleProductStatus, ProductStatus));

  return napi_ok;
}
