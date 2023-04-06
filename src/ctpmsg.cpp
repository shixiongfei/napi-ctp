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

  return napi_ok;
}

napi_status rspUserPasswordUpdate(napi_env env, const Message *message, napi_value *result) {
  auto pUserPasswordUpdate = MessageData<CThostFtdcUserPasswordUpdateField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspTradingAccountPasswordUpdate(napi_env env, const Message *message, napi_value *result) {
  auto pTradingAccountPasswordUpdate = MessageData<CThostFtdcTradingAccountPasswordUpdateField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspUserAuthMethod(napi_env env, const Message *message, napi_value *result) {
  auto pRspUserAuthMethod = MessageData<CThostFtdcRspUserAuthMethodField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspGenUserCaptcha(napi_env env, const Message *message, napi_value *result) {
  auto pRspGenUserCaptcha = MessageData<CThostFtdcRspGenUserCaptchaField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspGenUserText(napi_env env, const Message *message, napi_value *result) {
  auto pRspGenUserText = MessageData<CThostFtdcRspGenUserTextField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputOrder = MessageData<CThostFtdcInputOrderField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspParkedOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pParkedOrder = MessageData<CThostFtdcParkedOrderField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pParkedOrderAction = MessageData<CThostFtdcParkedOrderActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputOrderAction = MessageData<CThostFtdcInputOrderActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryMaxOrderVolume(napi_env env, const Message *message, napi_value *result) {
  auto pQryMaxOrderVolume = MessageData<CThostFtdcQryMaxOrderVolumeField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspSettlementInfoConfirm(napi_env env, const Message *message, napi_value *result) {
  auto pSettlementInfoConfirm = MessageData<CThostFtdcSettlementInfoConfirmField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspRemoveParkedOrder(napi_env env, const Message *message, napi_value *result) {
  auto pRemoveParkedOrder = MessageData<CThostFtdcRemoveParkedOrderField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspRemoveParkedOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pRemoveParkedOrderAction = MessageData<CThostFtdcRemoveParkedOrderActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspExecOrderInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputExecOrder = MessageData<CThostFtdcInputExecOrderField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspExecOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputExecOrderAction = MessageData<CThostFtdcInputExecOrderActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspForQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputForQuote = MessageData<CThostFtdcInputForQuoteField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQuoteInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputQuote = MessageData<CThostFtdcInputQuoteField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQuoteAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputQuoteAction = MessageData<CThostFtdcInputQuoteActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspBatchOrderAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputBatchOrderAction = MessageData<CThostFtdcInputBatchOrderActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspOptionSelfCloseInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputOptionSelfClose = MessageData<CThostFtdcInputOptionSelfCloseField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspOptionSelfCloseAction(napi_env env, const Message *message, napi_value *result) {
  auto pInputOptionSelfCloseAction = MessageData<CThostFtdcInputOptionSelfCloseActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspCombActionInsert(napi_env env, const Message *message, napi_value *result) {
  auto pInputCombAction = MessageData<CThostFtdcInputCombActionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryOrder(napi_env env, const Message *message, napi_value *result) {
  auto pOrder = MessageData<CThostFtdcOrderField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryTrade(napi_env env, const Message *message, napi_value *result) {
  auto pTrade = MessageData<CThostFtdcTradeField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryInvestorPosition(napi_env env, const Message *message, napi_value *result) {
  auto pInvestorPosition = MessageData<CThostFtdcInvestorPositionField>(message);

  CHECK(napi_create_object(env, result));

  return napi_ok;
}

napi_status rspQryTradingAccount(napi_env env, const Message *message, napi_value *result) {
  auto pTradingAccount = MessageData<CThostFtdcTradingAccountField>(message);

  CHECK(napi_create_object(env, result));

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
