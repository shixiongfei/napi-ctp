/*
 * mdspi.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __MDSPI_H__
#define __MDSPI_H__

#include "message_queue.h"
#include "napi_ctp.h"

#define EM_BASE                       0x1000
#define EM_QUIT                       (EM_BASE + 0)
#define EM_FRONTCONNECTED             (EM_BASE + 1)
#define EM_FRONTDISCONNECTED          (EM_BASE + 2)
#define EM_HEARTBEATWARNING           (EM_BASE + 3)
#define EM_RSPUSERLOGIN               (EM_BASE + 4)
#define EM_RSPUSERLOGOUT              (EM_BASE + 5)
#define EM_RSPQRYMULTICASTINSTRUMENT  (EM_BASE + 6)
#define EM_RSPERROR                   (EM_BASE + 7)
#define EM_RSPSUBMARKETDATA           (EM_BASE + 8)
#define EM_RSPUNSUBMARKETDATA         (EM_BASE + 9)
#define EM_RSPSUBFORQUOTERSP          (EM_BASE + 10)
#define EM_RSPUNSUBFORQUOTERSP        (EM_BASE + 11)
#define EM_RTNDEPTHMARKETDATA         (EM_BASE + 12)
#define EM_RTNFORQUOTERSP             (EM_BASE + 13)

class MdSpi : public CThostFtdcMdSpi {
public:
  MdSpi();
  virtual ~MdSpi();

  int poll(Message **message, unsigned int millisec = UINT_MAX);
  void done(Message *message);
  void quit(int nCode = 0);

public:
  static const char *eventName(int event);

public:
  virtual void OnFrontConnected();
  virtual void OnFrontDisconnected(int nReason);

  virtual void OnHeartBeatWarning(int nTimeLapse);

  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField *pMulticastInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
  
  virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

private:
  bool checkErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

private:
  MessageQueue _msgq;
};

#endif /* __MDSPI_H__ */
