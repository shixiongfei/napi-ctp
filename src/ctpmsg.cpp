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

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pUserLogout, BrokerID));
  CHECK(SetObjectString(env, *result, pUserLogout, UserID));

  return napi_ok;
}

napi_status rspQryMulticastInstrument(napi_env env, const Message *message, napi_value *result) {
  auto pMulticastInstrument = MessageData<CThostFtdcMulticastInstrumentField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectInt32(env, *result, pMulticastInstrument, TopicID));
  CHECK(SetObjectString(env, *result, pMulticastInstrument, reserve1));
  CHECK(SetObjectInt32(env, *result, pMulticastInstrument, InstrumentNo));
  CHECK(SetObjectDouble(env, *result, pMulticastInstrument, CodePrice));
  CHECK(SetObjectInt32(env, *result, pMulticastInstrument, VolumeMultiple));
  CHECK(SetObjectDouble(env, *result, pMulticastInstrument, PriceTick));
  CHECK(SetObjectString(env, *result, pMulticastInstrument, InstrumentID));

  return napi_ok;
}

napi_status rspError(napi_env env, const Message *message, napi_value *result) {
  auto pRspInfo = MessageData<CThostFtdcRspInfoField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectInt32(env, *result, pRspInfo, ErrorID));
  CHECK(SetObjectString(env, *result, pRspInfo, ErrorMsg));

  return napi_ok;
}

napi_status rspSubMarketData(napi_env env, const Message *message, napi_value *result) {
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pSpecificInstrument, reserve1));
  CHECK(SetObjectString(env, *result, pSpecificInstrument, InstrumentID));

  return napi_ok;
}

napi_status rspUnSubMarketData(napi_env env, const Message *message, napi_value *result) {
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pSpecificInstrument, reserve1));
  CHECK(SetObjectString(env, *result, pSpecificInstrument, InstrumentID));

  return napi_ok;
}

napi_status rspSubForQuote(napi_env env, const Message *message, napi_value *result) {
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pSpecificInstrument, reserve1));
  CHECK(SetObjectString(env, *result, pSpecificInstrument, InstrumentID));

  return napi_ok;
}

napi_status rspUnSubForQuote(napi_env env, const Message *message, napi_value *result) {
  auto pSpecificInstrument = MessageData<CThostFtdcSpecificInstrumentField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pSpecificInstrument, reserve1));
  CHECK(SetObjectString(env, *result, pSpecificInstrument, InstrumentID));

  return napi_ok;
}

napi_status rtnDepthMarketData(napi_env env, const Message *message, napi_value *result) {
  auto pDepthMarketData = MessageData<CThostFtdcDepthMarketDataField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pDepthMarketData, TradingDay));
  CHECK(SetObjectString(env, *result, pDepthMarketData, reserve1));
  CHECK(SetObjectString(env, *result, pDepthMarketData, ExchangeID));
  CHECK(SetObjectString(env, *result, pDepthMarketData, reserve2));
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

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, TradingDay));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, reserve1));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, ForQuoteSysID));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, ForQuoteTime));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, ActionDay));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, ExchangeID));
  CHECK(SetObjectString(env, *result, pForQuoteRsp, InstrumentID));

  return napi_ok;
}

napi_status rspAuthenticate(napi_env env, const Message *message, napi_value *result) {
  auto pAuthenticate = MessageData<CThostFtdcRspAuthenticateField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pAuthenticate, BrokerID));
  CHECK(SetObjectString(env, *result, pAuthenticate, UserID));
  CHECK(SetObjectString(env, *result, pAuthenticate, UserProductInfo));
  CHECK(SetObjectString(env, *result, pAuthenticate, AppID));
  CHECK(SetObjectChar(env, *result, pAuthenticate, AppType));

  return napi_ok;
}

napi_status rspUserPasswordUpdate(napi_env env, const Message *message, napi_value *result) {
  auto pUserPasswordUpdate = MessageData<CThostFtdcUserPasswordUpdateField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pUserPasswordUpdate, BrokerID));
  CHECK(SetObjectString(env, *result, pUserPasswordUpdate, UserID));
  CHECK(SetObjectString(env, *result, pUserPasswordUpdate, OldPassword));
  CHECK(SetObjectString(env, *result, pUserPasswordUpdate, NewPassword));

  return napi_ok;
}

napi_status rspTradingAccountPasswordUpdate(napi_env env, const Message *message, napi_value *result) {
  auto pTradingAccountPasswordUpdate = MessageData<CThostFtdcTradingAccountPasswordUpdateField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pTradingAccountPasswordUpdate, BrokerID));
  CHECK(SetObjectString(env, *result, pTradingAccountPasswordUpdate, AccountID));
  CHECK(SetObjectString(env, *result, pTradingAccountPasswordUpdate, OldPassword));
  CHECK(SetObjectString(env, *result, pTradingAccountPasswordUpdate, NewPassword));
  CHECK(SetObjectString(env, *result, pTradingAccountPasswordUpdate, CurrencyID));

  return napi_ok;
}

napi_status rspUserAuthMethod(napi_env env, const Message *message, napi_value *result) {
  auto pRspUserAuthMethod = MessageData<CThostFtdcRspUserAuthMethodField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectInt32(env, *result, pRspUserAuthMethod, UsableAuthMethod));

  return napi_ok;
}

napi_status rspGenUserCaptcha(napi_env env, const Message *message, napi_value *result) {
  auto pRspGenUserCaptcha = MessageData<CThostFtdcRspGenUserCaptchaField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pRspGenUserCaptcha, BrokerID));
  CHECK(SetObjectString(env, *result, pRspGenUserCaptcha, UserID));
  CHECK(SetObjectInt32(env, *result, pRspGenUserCaptcha, CaptchaInfoLen));
  CHECK(SetObjectString(env, *result, pRspGenUserCaptcha, CaptchaInfo));

  return napi_ok;
}

napi_status rspGenUserText(napi_env env, const Message *message, napi_value *result) {
  auto pRspGenUserText = MessageData<CThostFtdcRspGenUserTextField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectInt32(env, *result, pRspGenUserText, UserTextSeq));

  return napi_ok;
}

napi_status rspOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputOrder = MessageData<CThostFtdcInputOrderField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pInputOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pInputOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pInputOrder, reserve1));
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
  CHECK(SetObjectString(env, *result, pInputOrder, reserve2));
  CHECK(SetObjectString(env, *result, pInputOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pInputOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputOrder, IPAddress));

  return napi_ok;
}

napi_status rspParkedOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pParkedOrder = MessageData<CThostFtdcParkedOrderField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pParkedOrder, BrokerID));
  CHECK(SetObjectString(env, *result, pParkedOrder, InvestorID));
  CHECK(SetObjectString(env, *result, pParkedOrder, reserve1));
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
  CHECK(SetObjectString(env, *result, pParkedOrder, reserve2));
  CHECK(SetObjectString(env, *result, pParkedOrder, MacAddress));
  CHECK(SetObjectString(env, *result, pParkedOrder, InstrumentID));
  CHECK(SetObjectString(env, *result, pParkedOrder, IPAddress));

  return napi_ok;
}

napi_status rspParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pParkedOrderAction = MessageData<CThostFtdcParkedOrderActionField>(message);

  CHECK(napi_create_object(env, result));
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
  CHECK(SetObjectString(env, *result, pParkedOrderAction, reserve1));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, ParkedOrderActionID));
  CHECK(SetObjectChar(env, *result, pParkedOrderAction, UserType));
  CHECK(SetObjectChar(env, *result, pParkedOrderAction, Status));
  CHECK(SetObjectInt32(env, *result, pParkedOrderAction, ErrorID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, ErrorMsg));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, reserve2));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, MacAddress));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pParkedOrderAction, IPAddress));

  return napi_ok;
}

napi_status rspOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputOrderAction = MessageData<CThostFtdcInputOrderActionField>(message);

  CHECK(napi_create_object(env, result));
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
  CHECK(SetObjectString(env, *result, pInputOrderAction, reserve1));
  CHECK(SetObjectString(env, *result, pInputOrderAction, InvestUnitID));
  CHECK(SetObjectString(env, *result, pInputOrderAction, reserve2));
  CHECK(SetObjectString(env, *result, pInputOrderAction, MacAddress));
  CHECK(SetObjectString(env, *result, pInputOrderAction, InstrumentID));
  CHECK(SetObjectString(env, *result, pInputOrderAction, IPAddress));

  return napi_ok;
}

napi_status rspQryMaxOrderVolume(napi_env env, const Message *message, napi_value *result) {
  auto pQryMaxOrderVolume = MessageData<CThostFtdcQryMaxOrderVolumeField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pQryMaxOrderVolume, BrokerID));
  CHECK(SetObjectString(env, *result, pQryMaxOrderVolume, InvestorID));
  CHECK(SetObjectString(env, *result, pQryMaxOrderVolume, reserve1));
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

  CHECK(napi_create_object(env, result));
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

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pRemoveParkedOrder, BrokerID));
	CHECK(SetObjectString(env, *result, pRemoveParkedOrder, InvestorID));
	CHECK(SetObjectString(env, *result, pRemoveParkedOrder, ParkedOrderID));
	CHECK(SetObjectString(env, *result, pRemoveParkedOrder, InvestUnitID));

  return napi_ok;
}

napi_status rspRemoveParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pRemoveParkedOrderAction = MessageData<CThostFtdcRemoveParkedOrderActionField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pRemoveParkedOrderAction, BrokerID));
	CHECK(SetObjectString(env, *result, pRemoveParkedOrderAction, InvestorID));
	CHECK(SetObjectString(env, *result, pRemoveParkedOrderAction, ParkedOrderActionID));
	CHECK(SetObjectString(env, *result, pRemoveParkedOrderAction, InvestUnitID));

  return napi_ok;
}

napi_status rspExecOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputExecOrder = MessageData<CThostFtdcInputExecOrderField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pInputExecOrder, BrokerID));
	CHECK(SetObjectString(env, *result, pInputExecOrder, InvestorID));
	CHECK(SetObjectString(env, *result, pInputExecOrder, reserve1));
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
	CHECK(SetObjectString(env, *result, pInputExecOrder, reserve2));
	CHECK(SetObjectString(env, *result, pInputExecOrder, MacAddress));
	CHECK(SetObjectString(env, *result, pInputExecOrder, InstrumentID));
	CHECK(SetObjectString(env, *result, pInputExecOrder, IPAddress));

  return napi_ok;
}

napi_status rspExecOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputExecOrderAction = MessageData<CThostFtdcInputExecOrderActionField>(message);

  CHECK(napi_create_object(env, result));
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
	CHECK(SetObjectString(env, *result, pInputExecOrderAction, reserve1));
	CHECK(SetObjectString(env, *result, pInputExecOrderAction, InvestUnitID));
	CHECK(SetObjectString(env, *result, pInputExecOrderAction, reserve2));
	CHECK(SetObjectString(env, *result, pInputExecOrderAction, MacAddress));
	CHECK(SetObjectString(env, *result, pInputExecOrderAction, InstrumentID));
	CHECK(SetObjectString(env, *result, pInputExecOrderAction, IPAddress));

  return napi_ok;
}

napi_status rspForQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputForQuote = MessageData<CThostFtdcInputForQuoteField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pInputForQuote, BrokerID));
	CHECK(SetObjectString(env, *result, pInputForQuote, InvestorID));
	CHECK(SetObjectString(env, *result, pInputForQuote, reserve1));
	CHECK(SetObjectString(env, *result, pInputForQuote, ForQuoteRef));
	CHECK(SetObjectString(env, *result, pInputForQuote, UserID));
	CHECK(SetObjectString(env, *result, pInputForQuote, ExchangeID));
	CHECK(SetObjectString(env, *result, pInputForQuote, InvestUnitID));
	CHECK(SetObjectString(env, *result, pInputForQuote, reserve2));
	CHECK(SetObjectString(env, *result, pInputForQuote, MacAddress));
	CHECK(SetObjectString(env, *result, pInputForQuote, InstrumentID));
	CHECK(SetObjectString(env, *result, pInputForQuote, IPAddress));

  return napi_ok;
}

napi_status rspQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputQuote = MessageData<CThostFtdcInputQuoteField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pInputQuote, BrokerID));
	CHECK(SetObjectString(env, *result, pInputQuote, InvestorID));
	CHECK(SetObjectString(env, *result, pInputQuote, reserve1));
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
	CHECK(SetObjectString(env, *result, pInputQuote, reserve2));
	CHECK(SetObjectString(env, *result, pInputQuote, MacAddress));
	CHECK(SetObjectString(env, *result, pInputQuote, InstrumentID));
	CHECK(SetObjectString(env, *result, pInputQuote, IPAddress));
	CHECK(SetObjectString(env, *result, pInputQuote, ReplaceSysID));

  return napi_ok;
}

napi_status rspQuoteAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputQuoteAction = MessageData<CThostFtdcInputQuoteActionField>(message);

  CHECK(napi_create_object(env, result));
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
	CHECK(SetObjectString(env, *result, pInputQuoteAction, reserve1));
	CHECK(SetObjectString(env, *result, pInputQuoteAction, InvestUnitID));
	CHECK(SetObjectString(env, *result, pInputQuoteAction, ClientID));
	CHECK(SetObjectString(env, *result, pInputQuoteAction, reserve2));
	CHECK(SetObjectString(env, *result, pInputQuoteAction, MacAddress));
	CHECK(SetObjectString(env, *result, pInputQuoteAction, InstrumentID));
	CHECK(SetObjectString(env, *result, pInputQuoteAction, IPAddress));

  return napi_ok;
}

napi_status rspBatchOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputBatchOrderAction = MessageData<CThostFtdcInputBatchOrderActionField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pInputBatchOrderAction, BrokerID));
	CHECK(SetObjectString(env, *result, pInputBatchOrderAction, InvestorID));
	CHECK(SetObjectInt32(env, *result, pInputBatchOrderAction, OrderActionRef));
	CHECK(SetObjectInt32(env, *result, pInputBatchOrderAction, RequestID));
	CHECK(SetObjectInt32(env, *result, pInputBatchOrderAction, FrontID));
	CHECK(SetObjectInt32(env, *result, pInputBatchOrderAction, SessionID));
	CHECK(SetObjectString(env, *result, pInputBatchOrderAction, ExchangeID));
	CHECK(SetObjectString(env, *result, pInputBatchOrderAction, UserID));
	CHECK(SetObjectString(env, *result, pInputBatchOrderAction, InvestUnitID));
	CHECK(SetObjectString(env, *result, pInputBatchOrderAction, reserve1));
	CHECK(SetObjectString(env, *result, pInputBatchOrderAction, MacAddress));
	CHECK(SetObjectString(env, *result, pInputBatchOrderAction, IPAddress));

  return napi_ok;
}

napi_status rspOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputOptionSelfClose = MessageData<CThostFtdcInputOptionSelfCloseField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pInputOptionSelfClose, BrokerID));
	CHECK(SetObjectString(env, *result, pInputOptionSelfClose, InvestorID));
	CHECK(SetObjectString(env, *result, pInputOptionSelfClose, reserve1));
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
	CHECK(SetObjectString(env, *result, pInputOptionSelfClose, reserve2));
	CHECK(SetObjectString(env, *result, pInputOptionSelfClose, MacAddress));
	CHECK(SetObjectString(env, *result, pInputOptionSelfClose, InstrumentID));
	CHECK(SetObjectString(env, *result, pInputOptionSelfClose, IPAddress));

  return napi_ok;
}

napi_status rspOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputOptionSelfCloseAction = MessageData<CThostFtdcInputOptionSelfCloseActionField>(message);

  CHECK(napi_create_object(env, result));
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
	CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, reserve1));
	CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, InvestUnitID));
	CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, reserve2));
	CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, MacAddress));
	CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, InstrumentID));
	CHECK(SetObjectString(env, *result, pInputOptionSelfCloseAction, IPAddress));

  return napi_ok;
}

napi_status rspCombActionInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputCombAction = MessageData<CThostFtdcInputCombActionField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pInputCombAction, BrokerID));
	CHECK(SetObjectString(env, *result, pInputCombAction, InvestorID));
	CHECK(SetObjectString(env, *result, pInputCombAction, reserve1));
	CHECK(SetObjectString(env, *result, pInputCombAction, CombActionRef));
	CHECK(SetObjectString(env, *result, pInputCombAction, UserID));
	CHECK(SetObjectChar(env, *result, pInputCombAction, Direction));
	CHECK(SetObjectInt32(env, *result, pInputCombAction, Volume));
	CHECK(SetObjectChar(env, *result, pInputCombAction, CombDirection));
	CHECK(SetObjectChar(env, *result, pInputCombAction, HedgeFlag));
	CHECK(SetObjectString(env, *result, pInputCombAction, ExchangeID));
	CHECK(SetObjectString(env, *result, pInputCombAction, reserve2));
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

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pOrder, BrokerID));
	CHECK(SetObjectString(env, *result, pOrder, InvestorID));
	CHECK(SetObjectString(env, *result, pOrder, reserve1));
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
	CHECK(SetObjectString(env, *result, pOrder, reserve2));
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
	CHECK(SetObjectString(env, *result, pOrder, reserve3));
	CHECK(SetObjectString(env, *result, pOrder, MacAddress));
	CHECK(SetObjectString(env, *result, pOrder, InstrumentID));
	CHECK(SetObjectString(env, *result, pOrder, ExchangeInstID));
	CHECK(SetObjectString(env, *result, pOrder, IPAddress));

  return napi_ok;
}

napi_status rspQryTrade(napi_env env, const Message *message, napi_value *result) {
  auto pTrade = MessageData<CThostFtdcTradeField>(message);

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pTrade, BrokerID));
	CHECK(SetObjectString(env, *result, pTrade, InvestorID));
	CHECK(SetObjectString(env, *result, pTrade, reserve1));
	CHECK(SetObjectString(env, *result, pTrade, OrderRef));
	CHECK(SetObjectString(env, *result, pTrade, UserID));
	CHECK(SetObjectString(env, *result, pTrade, ExchangeID));
	CHECK(SetObjectString(env, *result, pTrade, TradeID));
	CHECK(SetObjectChar(env, *result, pTrade, Direction));
	CHECK(SetObjectString(env, *result, pTrade, OrderSysID));
	CHECK(SetObjectString(env, *result, pTrade, ParticipantID));
	CHECK(SetObjectString(env, *result, pTrade, ClientID));
	CHECK(SetObjectChar(env, *result, pTrade, TradingRole));
	CHECK(SetObjectString(env, *result, pTrade, reserve2));
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

  CHECK(napi_create_object(env, result));
  CHECK(SetObjectString(env, *result, pInvestorPosition, reserve1));
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

  CHECK(napi_create_object(env, result));
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

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryTradingCode(napi_env env, const Message *message, napi_value *result) {
  auto pTradingCode = MessageData<CThostFtdcTradingCodeField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryInstrumentMarginRate(napi_env env, const Message *message, napi_value *result) {
  auto pInstrumentMarginRate = MessageData<CThostFtdcInstrumentMarginRateField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryInstrumentCommissionRate(napi_env env, const Message *message, napi_value *result) {
  auto pInstrumentCommissionRate = MessageData<CThostFtdcInstrumentCommissionRateField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryExchange(napi_env env, const Message *message, napi_value *result) {
  auto pExchange = MessageData<CThostFtdcExchangeField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryProduct(napi_env env, const Message *message, napi_value *result) {
  auto pProduct = MessageData<CThostFtdcProductField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryInstrument(napi_env env, const Message *message, napi_value *result) {
  auto pInstrument = MessageData<CThostFtdcInstrumentField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryDepthMarketData(napi_env env, const Message *message, napi_value *result) {
  auto pDepthMarketData = MessageData<CThostFtdcDepthMarketDataField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryTraderOffer(napi_env env, const Message *message, napi_value *result) {
  auto pTraderOffer = MessageData<CThostFtdcTraderOfferField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQrySettlementInfo(napi_env env, const Message *message, napi_value *result) {
  auto pSettlementInfo = MessageData<CThostFtdcSettlementInfoField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryTransferBank(napi_env env, const Message *message, napi_value *result) {
  auto pTransferBank = MessageData<CThostFtdcTransferBankField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryInvestorPositionDetail(napi_env env, const Message *message, napi_value *result) {
  auto pInvestorPositionDetail = MessageData<CThostFtdcInvestorPositionDetailField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryNotice(napi_env env, const Message *message, napi_value *result) {
  auto pNotice = MessageData<CThostFtdcNoticeField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQrySettlementInfoConfirm(napi_env env, const Message *message, napi_value *result) {
  auto pSettlementInfoConfirm = MessageData<CThostFtdcSettlementInfoConfirmField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryInvestorPositionCombineDetail(napi_env env, const Message *message, napi_value *result) {
  auto pInvestorPositionCombineDetail = MessageData<CThostFtdcInvestorPositionCombineDetailField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryCFMMCTradingAccountKey(napi_env env, const Message *message, napi_value *result) {
  auto pCFMMCTradingAccountKey = MessageData<CThostFtdcCFMMCTradingAccountKeyField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryEWarrantOffset(napi_env env, const Message *message, napi_value *result) {
  auto pEWarrantOffset = MessageData<CThostFtdcEWarrantOffsetField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryInvestorProductGroupMargin(napi_env env, const Message *message, napi_value *result) {
  auto pInvestorProductGroupMargin = MessageData<CThostFtdcInvestorProductGroupMarginField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryExchangeMarginRate(napi_env env, const Message *message, napi_value *result) {
  auto pExchangeMarginRate = MessageData<CThostFtdcExchangeMarginRateField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryExchangeMarginRateAdjust(napi_env env, const Message *message, napi_value *result) {
  auto pExchangeMarginRateAdjust = MessageData<CThostFtdcExchangeMarginRateAdjustField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryExchangeRate(napi_env env, const Message *message, napi_value *result) {
  auto pExchangeRate = MessageData<CThostFtdcExchangeRateField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQrySecAgentACIDMap(napi_env env, const Message *message, napi_value *result) {
  auto pSecAgentACIDMap = MessageData<CThostFtdcSecAgentACIDMapField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryProductExchRate(napi_env env, const Message *message, napi_value *result) {
  auto pProductExchRate = MessageData<CThostFtdcProductExchRateField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryProductGroup(napi_env env, const Message *message, napi_value *result) {
  auto pProductGroup = MessageData<CThostFtdcProductGroupField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryMMInstrumentCommissionRate(napi_env env, const Message *message, napi_value *result) {
  auto pMMInstrumentCommissionRate = MessageData<CThostFtdcMMInstrumentCommissionRateField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryMMOptionInstrCommRate(napi_env env, const Message *message, napi_value *result) {
  auto pMMOptionInstrCommRate = MessageData<CThostFtdcMMOptionInstrCommRateField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryInstrumentOrderCommRate(napi_env env, const Message *message, napi_value *result) {
  auto pInstrumentOrderCommRate = MessageData<CThostFtdcInstrumentOrderCommRateField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQrySecAgentTradingAccount(napi_env env, const Message *message, napi_value *result) {
  auto pTradingAccount = MessageData<CThostFtdcTradingAccountField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQrySecAgentCheckMode(napi_env env, const Message *message, napi_value *result) {
  auto pSecAgentCheckMode = MessageData<CThostFtdcSecAgentCheckModeField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQrySecAgentTradeInfo(napi_env env, const Message *message, napi_value *result) {
  auto pSecAgentTradeInfo = MessageData<CThostFtdcSecAgentTradeInfoField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryOptionInstrTradeCost(napi_env env, const Message *message, napi_value *result) {
  auto pOptionInstrTradeCost = MessageData<CThostFtdcOptionInstrTradeCostField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryOptionInstrCommRate(napi_env env, const Message *message, napi_value *result) {
  auto pOptionInstrCommRate = MessageData<CThostFtdcOptionInstrCommRateField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryExecOrder(napi_env env, const Message *message, napi_value *result) {
  auto pExecOrder = MessageData<CThostFtdcExecOrderField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryForQuote(napi_env env, const Message *message, napi_value *result) {
  auto pForQuote = MessageData<CThostFtdcForQuoteField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryQuote(napi_env env, const Message *message, napi_value *result) {
  auto pQuote = MessageData<CThostFtdcQuoteField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryOptionSelfClose(napi_env env, const Message *message, napi_value *result) {
  auto pOptionSelfClose = MessageData<CThostFtdcOptionSelfCloseField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryInvestUnit(napi_env env, const Message *message, napi_value *result) {
  auto pInvestUnit = MessageData<CThostFtdcInvestUnitField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryCombInstrumentGuard(napi_env env, const Message *message, napi_value *result) {
  auto pCombInstrumentGuard = MessageData<CThostFtdcCombInstrumentGuardField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryCombAction(napi_env env, const Message *message, napi_value *result) {
  auto pCombAction = MessageData<CThostFtdcCombActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryTransferSerial(napi_env env, const Message *message, napi_value *result) {
  auto pTransferSerial = MessageData<CThostFtdcTransferSerialField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryAccountRegister(napi_env env, const Message *message, napi_value *result) {
  auto pAccountRegister = MessageData<CThostFtdcAccountregisterField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnOrder(napi_env env, const Message *message, napi_value *result) {
  auto pOrder = MessageData<CThostFtdcOrderField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnTrade(napi_env env, const Message *message, napi_value *result) {
  auto pTrade = MessageData<CThostFtdcTradeField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputOrder = MessageData<CThostFtdcInputOrderField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pOrderAction = MessageData<CThostFtdcOrderActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnInstrumentStatus(napi_env env, const Message *message, napi_value *result) {
  auto pInstrumentStatus = MessageData<CThostFtdcInstrumentStatusField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnBulletin(napi_env env, const Message *message, napi_value *result) {
  auto pBulletin = MessageData<CThostFtdcBulletinField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnTradingNotice(napi_env env, const Message *message, napi_value *result) {
  auto pTradingNoticeInfo = MessageData<CThostFtdcTradingNoticeInfoField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnErrorConditionalOrder(napi_env env, const Message *message, napi_value *result) {
  auto pErrorConditionalOrder = MessageData<CThostFtdcErrorConditionalOrderField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnExecOrder(napi_env env, const Message *message, napi_value *result) {
  auto pExecOrder = MessageData<CThostFtdcExecOrderField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnExecOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputExecOrder = MessageData<CThostFtdcInputExecOrderField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnExecOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pExecOrderAction = MessageData<CThostFtdcExecOrderActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnForQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputForQuote = MessageData<CThostFtdcInputForQuoteField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnQuote(napi_env env, const Message *message, napi_value *result) {
  auto pQuote = MessageData<CThostFtdcQuoteField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputQuote = MessageData<CThostFtdcInputQuoteField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnQuoteAction(napi_env env, const Message *message, napi_value *result) {
  auto pQuoteAction = MessageData<CThostFtdcQuoteActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnCFMMCTradingAccountToken(napi_env env, const Message *message, napi_value *result) {
  auto pCFMMCTradingAccountToken = MessageData<CThostFtdcCFMMCTradingAccountTokenField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnBatchOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pBatchOrderAction = MessageData<CThostFtdcBatchOrderActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnOptionSelfClose(napi_env env, const Message *message, napi_value *result) {
  auto pOptionSelfClose = MessageData<CThostFtdcOptionSelfCloseField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputOptionSelfClose = MessageData<CThostFtdcInputOptionSelfCloseField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result) {
  auto pOptionSelfCloseAction = MessageData<CThostFtdcOptionSelfCloseActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnCombAction(napi_env env, const Message *message, napi_value *result) {
  auto pCombAction = MessageData<CThostFtdcCombActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnCombActionInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputCombAction = MessageData<CThostFtdcInputCombActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryContractBank(napi_env env, const Message *message, napi_value *result) {
  auto pContractBank = MessageData<CThostFtdcContractBankField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryParkedOrder(napi_env env, const Message *message, napi_value *result) {
  auto pParkedOrder = MessageData<CThostFtdcParkedOrderField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pParkedOrderAction = MessageData<CThostFtdcParkedOrderActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryTradingNotice(napi_env env, const Message *message, napi_value *result) {
  auto pTradingNotice = MessageData<CThostFtdcTradingNoticeField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryBrokerTradingParams(napi_env env, const Message *message, napi_value *result) {
  auto pBrokerTradingParams = MessageData<CThostFtdcBrokerTradingParamsField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryBrokerTradingAlgos(napi_env env, const Message *message, napi_value *result) {
  auto pBrokerTradingAlgos = MessageData<CThostFtdcBrokerTradingAlgosField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQueryCFMMCTradingAccountToken(napi_env env, const Message *message, napi_value *result) {
  auto pQueryCFMMCTradingAccountToken = MessageData<CThostFtdcQueryCFMMCTradingAccountTokenField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnFromBankToFutureByBank(napi_env env, const Message *message, napi_value *result) {
  auto pRspTransfer = MessageData<CThostFtdcRspTransferField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnFromFutureToBankByBank(napi_env env, const Message *message, napi_value *result) {
  auto pRspTransfer = MessageData<CThostFtdcRspTransferField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnRepealFromBankToFutureByBank(napi_env env, const Message *message, napi_value *result) {
  auto pRspRepeal = MessageData<CThostFtdcRspRepealField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnRepealFromFutureToBankByBank(napi_env env, const Message *message, napi_value *result) {
  auto pRspRepeal = MessageData<CThostFtdcRspRepealField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pRspTransfer = MessageData<CThostFtdcRspTransferField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pRspTransfer = MessageData<CThostFtdcRspTransferField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnRepealFromBankToFutureByFutureManual(napi_env env, const Message *message, napi_value *result) {
  auto pRspRepeal = MessageData<CThostFtdcRspRepealField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnRepealFromFutureToBankByFutureManual(napi_env env, const Message *message, napi_value *result) {
  auto pRspRepeal = MessageData<CThostFtdcRspRepealField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnQueryBankBalanceByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pNotifyQueryAccount = MessageData<CThostFtdcNotifyQueryAccountField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pReqTransfer = MessageData<CThostFtdcReqTransferField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pReqTransfer = MessageData<CThostFtdcReqTransferField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnRepealBankToFutureByFutureManual(napi_env env, const Message *message, napi_value *result) {
  auto pReqRepeal = MessageData<CThostFtdcReqRepealField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnRepealFutureToBankByFutureManual(napi_env env, const Message *message, napi_value *result) {
  auto pReqRepeal = MessageData<CThostFtdcReqRepealField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status errRtnQueryBankBalanceByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pReqQueryAccount = MessageData<CThostFtdcReqQueryAccountField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnRepealFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pRspRepeal = MessageData<CThostFtdcRspRepealField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnRepealFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pRspRepeal = MessageData<CThostFtdcRspRepealField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspFromBankToFutureByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pReqTransfer = MessageData<CThostFtdcReqTransferField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspFromFutureToBankByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pReqTransfer = MessageData<CThostFtdcReqTransferField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQueryBankAccountMoneyByFuture(napi_env env, const Message *message, napi_value *result) {
  auto pReqQueryAccount = MessageData<CThostFtdcReqQueryAccountField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnOpenAccountByBank(napi_env env, const Message *message, napi_value *result) {
  auto pOpenAccount = MessageData<CThostFtdcOpenAccountField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnCancelAccountByBank(napi_env env, const Message *message, napi_value *result) {
  auto pCancelAccount = MessageData<CThostFtdcCancelAccountField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rtnChangeAccountByBank(napi_env env, const Message *message, napi_value *result) {
  auto pChangeAccount = MessageData<CThostFtdcChangeAccountField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryClassifiedInstrument(napi_env env, const Message *message, napi_value *result) {
  auto pInstrument = MessageData<CThostFtdcInstrumentField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryCombPromotionParam(napi_env env, const Message *message, napi_value *result) {
  auto pCombPromotionParam = MessageData<CThostFtdcCombPromotionParamField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryRiskSettleInvstPosition(napi_env env, const Message *message, napi_value *result) {
  auto pRiskSettleInvstPosition = MessageData<CThostFtdcRiskSettleInvstPositionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryRiskSettleProductStatus(napi_env env, const Message *message, napi_value *result) {
  auto pRiskSettleProductStatus = MessageData<CThostFtdcRiskSettleProductStatusField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}
