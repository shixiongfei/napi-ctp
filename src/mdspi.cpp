/*
 * mdspi.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "mdspi.h"
#include <map>
#include <string>

static const std::map<int, std::string> eventNames = {
  {EM_QUIT,                       "quit"},
  {EM_FRONTCONNECTED,             "front-connected"},
  {EM_FRONTDISCONNECTED,          "front-disconnected"},
  {EM_HEARTBEATWARNING,           "heart-beat-warning"},
  {EM_RSPUSERLOGIN,               "rsp-user-login"},
  {EM_RSPUSERLOGOUT,              "rsp-user-logout"},
  {EM_RSPQRYMULTICASTINSTRUMENT,  "rsp-qry-multicast-instrument"},
  {EM_RSPERROR,                   "rsp-error"},
  {EM_RSPSUBMARKETDATA,           "rsp-sub-market-data"},
  {EM_RSPUNSUBMARKETDATA,         "rsp-unsub-market-data"},
  {EM_RSPSUBFORQUOTERSP,          "rsp-sub-for-quote"},
  {EM_RSPUNSUBFORQUOTERSP,        "rsp-unsub-for-quote"},
  {EM_RTNDEPTHMARKETDATA,         "rtn-depth-market-data"},
  {EM_RTNFORQUOTERSP,             "rtn-for-quote"},

};

static bool isFreeable(int event) {
  switch(event) {
    case EM_QUIT:
    case EM_FRONTCONNECTED:
    case EM_FRONTDISCONNECTED:
    case EM_HEARTBEATWARNING:
      return false;
    default:
      return true;
  }
}

MdSpi::MdSpi() {}

MdSpi::~MdSpi() {
  Message *msg;

  while (QUEUE_SUCCESS == poll(&msg, 0))
    done(msg);
}

int MdSpi::poll(Message **message, unsigned int millisec) {
  return _msgq.pop(message, millisec);
}

void MdSpi::done(Message *message) {
  if (isFreeable(message->event))
    free((void *)message->data);

  free(message);
}

void MdSpi::quit(int nCode) {
  _msgq.push(EM_QUIT, (uintptr_t)nCode, 0, Undefined);
}

const char *MdSpi::eventName(int event) {
  auto iter = eventNames.find(event);

  if (iter == eventNames.end())
    return nullptr;

  return iter->second.c_str();
}

void MdSpi::OnFrontConnected() {
  _msgq.push(EM_FRONTCONNECTED, 0, 0, Undefined);
}

void MdSpi::OnFrontDisconnected(int nReason) {
  _msgq.push(EM_FRONTDISCONNECTED, (uintptr_t)nReason, 0, Undefined);
}

void MdSpi::OnHeartBeatWarning(int nTimeLapse) {
  _msgq.push(EM_HEARTBEATWARNING, (uintptr_t)nTimeLapse, 0, Undefined);
}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(EM_RSPUSERLOGIN, copyData(pRspUserLogin), nRequestID, bIsLast);
}

void MdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(EM_RSPUSERLOGOUT, copyData(pUserLogout), nRequestID, bIsLast);
}

void MdSpi::OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField *pMulticastInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(EM_RSPQRYMULTICASTINSTRUMENT, copyData(pMulticastInstrument), nRequestID, bIsLast);
}

void MdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(EM_RSPERROR, copyData(pRspInfo), nRequestID, bIsLast);
}

void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(EM_RSPSUBMARKETDATA, copyData(pSpecificInstrument), nRequestID, bIsLast);
}

void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(EM_RSPUNSUBMARKETDATA, copyData(pSpecificInstrument), nRequestID, bIsLast);
}

void MdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(EM_RSPSUBFORQUOTERSP, copyData(pSpecificInstrument), nRequestID, bIsLast);
}

void MdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(EM_RSPUNSUBFORQUOTERSP, copyData(pSpecificInstrument), nRequestID, bIsLast);
}

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
  _msgq.push(EM_RTNDEPTHMARKETDATA, copyData(pDepthMarketData), 0, Undefined);
}

void MdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
  _msgq.push(EM_RTNFORQUOTERSP, copyData(pForQuoteRsp), 0, Undefined);
}

bool MdSpi::checkErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  bool isError = pRspInfo && pRspInfo->ErrorID != 0;

  if (isError)
    OnRspError(pRspInfo, nRequestID, bIsLast);

  return isError;
}
