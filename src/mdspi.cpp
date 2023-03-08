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

MdSpi::MdSpi() {}

MdSpi::~MdSpi() {}

int MdSpi::poll(Message *message, unsigned int millisec) {
  return _msgq.pop(message, millisec);
}

void MdSpi::OnFrontConnected() {
  Message msg = {EM_CONNECTED, 0};
  _msgq.push(msg);
}

void MdSpi::OnFrontDisconnected(int nReason) {
  Message msg = {EM_DISCONNECTED, (uintptr_t)nReason};
  _msgq.push(msg);
}

void MdSpi::OnHeartBeatWarning(int nTimeLapse) {
  Message msg = {EM_HEARTBEATWARNING, (uintptr_t)nTimeLapse};
  _msgq.push(msg);
}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_USERLOGIN, copyData(pRspUserLogin)};
  _msgq.push(msg);
}

void MdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_USERLOGOUT, copyData(pUserLogout)};
  _msgq.push(msg);
}

void MdSpi::OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField *pMulticastInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_QUERYMULTICASTINSTRUMENT, copyData(pMulticastInstrument)};
  _msgq.push(msg);
}

void MdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  Message msg = {EM_ERROR, copyData(pRspInfo)};
  _msgq.push(msg);
}

void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_SUBMARKETDATA, copyData(pSpecificInstrument)};
  _msgq.push(msg);
}

void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_UNSUBMARKETDATA, copyData(pSpecificInstrument)};
  _msgq.push(msg);
}

void MdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_SUBFORQUOTE, copyData(pSpecificInstrument)};
  _msgq.push(msg);
}

void MdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {EM_UNSUBFORQUOTE, copyData(pSpecificInstrument)};
  _msgq.push(msg);
}

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
  Message msg = {EM_DEPTHMARKETDATA, copyData(pDepthMarketData)};
  _msgq.push(msg);
}

void MdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
  Message msg = {EM_FORQUOTE, copyData(pForQuoteRsp)};
  _msgq.push(msg);
}

bool MdSpi::checkErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  bool isError = pRspInfo && pRspInfo->ErrorID != 0;

  if (isError)
    OnRspError(pRspInfo, nRequestID, bIsLast);

  return isError;
}
