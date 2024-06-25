/*
 * mdspi.cpp
 *
 * Copyright (c) 2022-2024 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "mdspi.h"
#include <map>
#include <string>

static const std::map<std::string, int> eventMaps = {
  { "quit",                            EM_QUIT },
  { "front-connected",                 EM_FRONTCONNECTED },
  { "front-disconnected",              EM_FRONTDISCONNECTED },
  { "heart-beat-warning",              EM_HEARTBEATWARNING },
  { "rsp-user-login",                  EM_RSPUSERLOGIN },
  { "rsp-user-logout",                 EM_RSPUSERLOGOUT },
  { "rsp-qry-multicast-instrument",    EM_RSPQRYMULTICASTINSTRUMENT },
  { "rsp-error",                       EM_RSPERROR },
  { "rsp-sub-market-data",             EM_RSPSUBMARKETDATA },
  { "rsp-unsub-market-data",           EM_RSPUNSUBMARKETDATA },
  { "rsp-sub-for-quote",               EM_RSPSUBFORQUOTERSP },
  { "rsp-unsub-for-quote",             EM_RSPUNSUBFORQUOTERSP },
  { "rtn-depth-market-data",           EM_RTNDEPTHMARKETDATA },
  { "rtn-for-quote",                   EM_RTNFORQUOTERSP },
};

MdSpi::MdSpi(const std::map<int, napi_threadsafe_function> *tsfns)
  : SpiEvent(tsfns) {}

MdSpi::~MdSpi() {}

int MdSpi::eventFromName(const char *name) {
  auto iter = eventMaps.find(name);

  if (iter == eventMaps.end())
    return 0;

  return iter->second;
}

void MdSpi::quit(int nCode) {
  SpiEvent::quit(EM_QUIT, nCode);
}

void MdSpi::OnFrontConnected() {
  SpiEvent::push(EM_FRONTCONNECTED);
}

void MdSpi::OnFrontDisconnected(int nReason) {
  SpiEvent::push(EM_FRONTDISCONNECTED, nReason);
}

void MdSpi::OnHeartBeatWarning(int nTimeLapse) {
  SpiEvent::push(EM_HEARTBEATWARNING, nTimeLapse);
}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  SpiEvent::push(EM_RSPUSERLOGIN, pRspUserLogin, pRspInfo, nRequestID, bIsLast);
}

void MdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  SpiEvent::push(EM_RSPUSERLOGOUT, pUserLogout, pRspInfo, nRequestID, bIsLast);
}

void MdSpi::OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField *pMulticastInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  SpiEvent::push(EM_RSPQRYMULTICASTINSTRUMENT, pMulticastInstrument, pRspInfo, nRequestID, bIsLast);
}

void MdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  SpiEvent::push(EM_RSPERROR, pRspInfo, nRequestID, bIsLast);
}

void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  SpiEvent::push(EM_RSPSUBMARKETDATA, pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
}

void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  SpiEvent::push(EM_RSPUNSUBMARKETDATA, pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
}

void MdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  SpiEvent::push(EM_RSPSUBFORQUOTERSP, pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
}

void MdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  SpiEvent::push(EM_RSPUNSUBFORQUOTERSP, pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
}

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
  SpiEvent::push(EM_RTNDEPTHMARKETDATA, pDepthMarketData);
}

void MdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
  SpiEvent::push(EM_RTNFORQUOTERSP, pForQuoteRsp);
}
