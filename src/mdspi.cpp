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
  Message msg;

  while (QUEUE_SUCCESS == poll(&msg, 0))
    done(msg);
}

int MdSpi::poll(Message *message, unsigned int millisec) {
  return _msgq.pop(message, millisec);
}

void MdSpi::done(Message &message) {
  if (isFreeable(message.event))
    free((void *)message.data);

  message.data = 0;
}

void MdSpi::quit(int nCode) {
  Message msg = {EM_QUIT, (uintptr_t)nCode};
  _msgq.push(msg);
}

void MdSpi::OnFrontConnected() {
  Message msg = {EM_FRONTCONNECTED, 0};
  _msgq.push(msg);
}

void MdSpi::OnFrontDisconnected(int nReason) {
  Message msg = {EM_FRONTDISCONNECTED, (uintptr_t)nReason};
  _msgq.push(msg);
}

void MdSpi::OnHeartBeatWarning(int nTimeLapse) {
  Message msg = {EM_HEARTBEATWARNING, (uintptr_t)nTimeLapse};
  _msgq.push(msg);
}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_RSPUSERLOGIN, copyData(pRspUserLogin)};
  _msgq.push(msg);
}

void MdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_RSPUSERLOGOUT, copyData(pUserLogout)};
  _msgq.push(msg);
}

void MdSpi::OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField *pMulticastInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_RSPQRYMULTICASTINSTRUMENT, copyData(pMulticastInstrument)};
  _msgq.push(msg);
}

void MdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  Message msg = {EM_RSPERROR, copyData(pRspInfo)};
  _msgq.push(msg);
}

void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_RSPSUBMARKETDATA, copyData(pSpecificInstrument)};
  _msgq.push(msg);
}

void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_RSPUNSUBMARKETDATA, copyData(pSpecificInstrument)};
  _msgq.push(msg);
}

void MdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_RSPSUBFORQUOTERSP, copyData(pSpecificInstrument)};
  _msgq.push(msg);
}

void MdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_RSPUNSUBFORQUOTERSP, copyData(pSpecificInstrument)};
  _msgq.push(msg);
}

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
  Message msg = {EM_RTNDEPTHMARKETDATA, copyData(pDepthMarketData)};
  _msgq.push(msg);
}

void MdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
  Message msg = {EM_RTNFORQUOTERSP, copyData(pForQuoteRsp)};
  _msgq.push(msg);
}

bool MdSpi::checkErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  bool isError = pRspInfo && pRspInfo->ErrorID != 0;

  if (isError)
    OnRspError(pRspInfo, nRequestID, bIsLast);

  return isError;
}
