/*
 * traderspi.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "traderspi.h"
#include <map>
#include <string>

static const std::map<int, std::string> eventNames = {
  {ET_QUIT,                                     "quit"},
  {ET_FRONTCONNECTED,                           "front-connected"},
  {ET_FRONTDISCONNECTED,                        "front-disconnected"},
  {ET_HEARTBEATWARNING,                         "heart-beat-warning"},
  {ET_RSPAUTHENTICATE,                          "rsp-authenticate"},
  {ET_RSPUSERLOGIN,                             "rsp-user-login"},
  {ET_RSPUSERLOGOUT,                            "rsp-user-logout"},
  {ET_RSPUSERPASSWORDUPDATE,                    "rsp-user-password-update"},
  {ET_RSPTRADINGACCOUNTPASSWORDUPDATE,          "rsp-trading-account-password-update"},
  {ET_RSPUSERAUTHMETHOD,                        "rsp-user-auth-method"},
  {ET_RSPGENUSERCAPTCHA,                        "rsp-gen-user-captcha"},
  {ET_RSPGENUSERTEXT,                           "rsp-gen-user-text"},
  {ET_RSPORDERINSERT,                           "rsp-order-insert"},
  {ET_RSPPARKEDORDERINSERT,                     "rsp-parked-order-insert"},
  {ET_RSPPARKEDORDERACTION,                     "rsp-parked-order-action"},
  {ET_RSPORDERACTION,                           "rsp-order-action"},
  {ET_RSPQRYMAXORDERVOLUME,                     "rsp-qry-max-order-volume"},
  {ET_RSPSETTLEMENTINFOCONFIRM,                 "rsp-settlement-info-confirm"},
  {ET_RSPREMOVEPARKEDORDER,                     "rsp-remove-parked-order"},
  {ET_RSPREMOVEPARKEDORDERACTION,               "rsp-remove-parked-order-action"},
  {ET_RSPEXECORDERINSERT,                       "rsp-exec-order-insert"},
  {ET_RSPEXECORDERACTION,                       "rsp-exec-order-action"},
  {ET_RSPFORQUOTEINSERT,                        "rsp-for-quote-insert"},
  {ET_RSPQUOTEINSERT,                           "rsp-quote-insert"},
  {ET_RSPQUOTEACTION,                           "rsp-quote-action"},
  {ET_RSPBATCHORDERACTION,                      "rsp-batch-order-action"},
  {ET_RSPOPTIONSELFCLOSEINSERT,                 "rsp-option-self-close-insert"},
  {ET_RSPOPTIONSELFCLOSEACTION,                 "rsp-option-self-close-action"},
  {ET_RSPCOMBACTIONINSERT,                      "rsp-comb-action-insert"},
  {ET_RSPQRYORDER,                              "rsp-qry-order"},
  {ET_RSPQRYTRADE,                              "rsp-qry-trade"},
  {ET_RSPQRYINVESTORPOSITION,                   "rsp-qry-investor-position"},
  {ET_RSPQRYTRADINGACCOUNT,                     "rsp-qry-trading-account"},
  {ET_RSPQRYINVESTOR,                           "rsp-qry-investor"},
  {ET_RSPQRYTRADINGCODE,                        "rsp-qry-trading-code"},
  {ET_RSPQRYINSTRUMENTMARGINRATE,               "rsp-qry-instrument-margin-rate"},
  {ET_RSPQRYINSTRUMENTCOMMISSIONRATE,           "rsp-qry-instrument-commission-rate"},
  {ET_RSPQRYEXCHANGE,                           "rsp-qry-exchange"},
  {ET_RSPQRYPRODUCT,                            "rsp-qry-product"},
  {ET_RSPQRYINSTRUMENT,                         "rsp-qry-instrument"},
  {ET_RSPQRYDEPTHMARKETDATA,                    "rsp-qry-depth-market-data"},
  {ET_RSPQRYTRADEROFFER,                        "rsp-qry-trader-offer"},
  {ET_RSPQRYSETTLEMENTINFO,                     "rsp-qry-settlement-info"},
  {ET_RSPQRYTRANSFERBANK,                       "rsp-qry-transfer-bank"},
  {ET_RSPQRYINVESTORPOSITIONDETAIL,             "rsp-qry-investor-position-detail"},
  {ET_RSPQRYNOTICE,                             "rsp-qry-notice"},
  {ET_RSPQRYSETTLEMENTINFOCONFIRM,              "rsp-qry-settlement-info-confirm"},
  {ET_RSPQRYINVESTORPOSITIONCOMBINEDETAIL,      "rsp-qry-investor-position-combine-detail"},
  {ET_RSPQRYCFMMCTRADINGACCOUNTKEY,             "rsp-qry-cfmmc-trading-account-key"},
  {ET_RSPQRYEWARRANTOFFSET,                     "rsp-qry-e-warrant-offset"},
  {ET_RSPQRYINVESTORPRODUCTGROUPMARGIN,         "rsp-qry-investor-product-group-margin"},
  {ET_RSPQRYEXCHANGEMARGINRATE,                 "rsp-qry-exchange-margin-rate"},
  {ET_RSPQRYEXCHANGEMARGINRATEADJUST,           "rsp-qry-exchange-margin-rate-adjust"},
  {ET_RSPQRYEXCHANGERATE,                       "rsp-qry-exchange-rate"},
  {ET_RSPQRYSECAGENTACIDMAP,                    "rsp-qry-sec-agent-acid-map"},
  {ET_RSPQRYPRODUCTEXCHRATE,                    "rsp-qry-product-exch-rate"},
  {ET_RSPQRYPRODUCTGROUP,                       "rsp-qry-product-group"},
  {ET_RSPQRYMMINSTRUMENTCOMMISSIONRATE,         "rsp-qry-mm-instrument-commission-rate"},
  {ET_RSPQRYMMOPTIONINSTRCOMMRATE,              "rsp-qry-mm-option-instr-comm-rate"},
  {ET_RSPQRYINSTRUMENTORDERCOMMRATE,            "rsp-qry-instrument-order-comm-rate"},
  {ET_RSPQRYSECAGENTTRADINGACCOUNT,             "rsp-qry-sec-agent-trading-account"},
  {ET_RSPQRYSECAGENTCHECKMODE,                  "rsp-qry-sec-agent-check-mode"},
  {ET_RSPQRYSECAGENTTRADEINFO,                  "rsp-qry-sec-agent-trade-info"},
  {ET_RSPQRYOPTIONINSTRTRADECOST,               "rsp-qry-option-instr-trade-cost"},
  {ET_RSPQRYOPTIONINSTRCOMMRATE,                "rsp-qry-option-instr-comm-rate"},
  {ET_RSPQRYEXECORDER,                          "rsp-qry-exec-order"},
  {ET_RSPQRYFORQUOTE,                           "rsp-qry-for-quote"},
  {ET_RSPQRYQUOTE,                              "rsp-qry-quote"},
  {ET_RSPQRYOPTIONSELFCLOSE,                    "rsp-qry-option-self-close"},
  {ET_RSPQRYINVESTUNIT,                         "rsp-qry-invest-unit"},
  {ET_RSPQRYCOMBINSTRUMENTGUARD,                "rsp-qry-comb-instrument-guard"},
  {ET_RSPQRYCOMBACTION,                         "rsp-qry-comb-action"},
  {ET_RSPQRYTRANSFERSERIAL,                     "rsp-qry-transfer-serial"},
  {ET_RSPQRYACCOUNTREGISTER,                    "rsp-qry-account-register"},
  {ET_RSPERROR,                                 "rsp-error"},
  {ET_RTNORDER,                                 "rtn-order"},
  {ET_RTNTRADE,                                 "rtn-trade"},
  {ET_ERRRTNORDERINSERT,                        "err-rtn-order-insert"},
  {ET_ERRRTNORDERACTION,                        "err-rtn-order-action"},
  {ET_RTNINSTRUMENTSTATUS,                      "rtn-instrument-status"},
  {ET_RTNBULLETIN,                              "rtn-bulletin"},
  {ET_RTNTRADINGNOTICE,                         "rtn-trading-notice"},
  {ET_RTNERRORCONDITIONALORDER,                 "rtn-error-conditional-order"},
  {ET_RTNEXECORDER,                             "rtn-exec-order"},
  {ET_ERRRTNEXECORDERINSERT,                    "err-rtn-exec-order-insert"},
  {ET_ERRRTNEXECORDERACTION,                    "err-rtn-exec-order-action"},
  {ET_ERRRTNFORQUOTEINSERT,                     "err-rtn-for-quote-insert"},
  {ET_RTNQUOTE,                                 "rtn-quote"},
  {ET_ERRRTNQUOTEINSERT,                        "err-rtn-quote-insert"},
  {ET_ERRRTNQUOTEACTION,                        "err-rtn-quote-action"},
  {ET_RTNFORQUOTERSP,                           "rtn-for-quote"},
  {ET_RTNCFMMCTRADINGACCOUNTTOKEN,              "rtn-cfmmc-trading-account-token"},
  {ET_ERRRTNBATCHORDERACTION,                   "err-rtn-batch-order-action"},
  {ET_RTNOPTIONSELFCLOSE,                       "rtn-option-self-close"},
  {ET_ERRRTNOPTIONSELFCLOSEINSERT,              "err-rtn-option-self-close-insert"},
  {ET_ERRRTNOPTIONSELFCLOSEACTION,              "err-rtn-option-self-close-action"},
  {ET_RTNCOMBACTION,                            "rtn-comb-action"},
  {ET_ERRRTNCOMBACTIONINSERT,                   "err-rtn-comb-action-insert"},
  {ET_RSPQRYCONTRACTBANK,                       "rsp-qry-contract-bank"},
  {ET_RSPQRYPARKEDORDER,                        "rsp-qry-parked-order"},
  {ET_RSPQRYPARKEDORDERACTION,                  "rsp-qry-parked-order-action"},
  {ET_RSPQRYTRADINGNOTICE,                      "rsp-qry-trading-notice"},
  {ET_RSPQRYBROKERTRADINGPARAMS,                "rsp-qry-broker-trading-params"},
  {ET_RSPQRYBROKERTRADINGALGOS,                 "rsp-qry-broker-trading-algos"},
  {ET_RSPQUERYCFMMCTRADINGACCOUNTTOKEN,         "rsp-query-cfmmc-trading-account-token"},
  {ET_RTNFROMBANKTOFUTUREBYBANK,                "rtn-from-bank-to-future-by-bank"},
  {ET_RTNFROMFUTURETOBANKBYBANK,                "rtn-from-future-to-bank-by-bank"},
  {ET_RTNREPEALFROMBANKTOFUTUREBYBANK,          "rtn-repeal-from-bank-to-future-by-bank"},
  {ET_RTNREPEALFROMFUTURETOBANKBYBANK,          "rtn-repeal-from-future-to-bank-by-bank"},
  {ET_RTNFROMBANKTOFUTUREBYFUTURE,              "rtn-from-bank-to-future-by-future"},
  {ET_RTNFROMFUTURETOBANKBYFUTURE,              "rtn-from-future-to-bank-by-future"},
  {ET_RTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL,  "rtn-repeal-from-bank-to-future-by-future-manual"},
  {ET_RTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL,  "rtn-repeal-from-future-to-bank-by-future-manual"},
  {ET_RTNQUERYBANKBALANCEBYFUTURE,              "rtn-query-bank-balance-by-future"},
  {ET_ERRRTNBANKTOFUTUREBYFUTURE,               "err-rtn-bank-to-future-by-future"},
  {ET_ERRRTNFUTURETOBANKBYFUTURE,               "err-rtn-future-to-bank-by-future"},
  {ET_ERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL,   "err-rtn-repeal-bank-to-future-by-future-manual"},
  {ET_ERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL,   "err-rtn-repeal-future-to-bank-by-future-manual"},
  {ET_ERRRTNQUERYBANKBALANCEBYFUTURE,           "err-rtn-query-bank-balance-by-future"},
  {ET_RTNREPEALFROMBANKTOFUTUREBYFUTURE,        "rtn-repeal-from-bank-to-future-by-future"},
  {ET_RTNREPEALFROMFUTURETOBANKBYFUTURE,        "rtn-repeal-from-future-to-bank-by-future"},
  {ET_RSPFROMBANKTOFUTUREBYFUTURE,              "rsp-from-bank-to-future-by-future"},
  {ET_RSPFROMFUTURETOBANKBYFUTURE,              "rsp-from-future-to-bank-by-future"},
  {ET_RSPQUERYBANKACCOUNTMONEYBYFUTURE,         "rsp-query-bank-account-money-by-future"},
  {ET_RTNOPENACCOUNTBYBANK,                     "rtn-open-account-by-bank"},
  {ET_RTNCANCELACCOUNTBYBANK,                   "rtn-cancel-account-by-bank"},
  {ET_RTNCHANGEACCOUNTBYBANK,                   "rtn-change-account-by-bank"},
  {ET_RSPQRYCLASSIFIEDINSTRUMENT,               "rsp-qry-classified-instrument"},
  {ET_RSPQRYCOMBPROMOTIONPARAM,                 "rsp-qry-comb-promotion-param"},
  {ET_RSPQRYRISKSETTLEINVSTPOSITION,            "rsp-qry-risk-settle-invst-position"},
  {ET_RSPQRYRISKSETTLEPRODUCTSTATUS,            "rsp-qry-risk-settle-product-status"},
};

static bool isFreeable(int event) {
  switch(event) {
    case ET_QUIT:
    case ET_FRONTCONNECTED:
    case ET_FRONTDISCONNECTED:
    case ET_HEARTBEATWARNING:
      return false;
    default:
      return true;
  }
}

TraderSpi::TraderSpi() {}

TraderSpi::~TraderSpi() {
  Message msg;

  while (QUEUE_SUCCESS == poll(&msg, 0))
    done(msg);
}

int TraderSpi::poll(Message *message, unsigned int millisec) {
  return _msgq.pop(message, millisec);
}

void TraderSpi::done(Message &message) {
  if (isFreeable(message.event))
    free((void *)message.data);

  message.data = 0;
}

void TraderSpi::quit(int nCode) {
  Message msg = {ET_QUIT, (uintptr_t)nCode};
  _msgq.push(msg);
}

const char *TraderSpi::eventName(int event) {
  auto iter = eventNames.find(event);

  if (iter == eventNames.end())
    return nullptr;

  return iter->second.c_str();
}

void TraderSpi::OnFrontConnected() {
  Message msg = {ET_FRONTCONNECTED, 0};
  _msgq.push(msg);
}

void TraderSpi::OnFrontDisconnected(int nReason) {
  Message msg = {ET_FRONTDISCONNECTED, (uintptr_t)nReason};
  _msgq.push(msg);
}

void TraderSpi::OnHeartBeatWarning(int nTimeLapse) {
  Message msg = {ET_HEARTBEATWARNING, (uintptr_t)nTimeLapse};
  _msgq.push(msg);
}

void TraderSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPAUTHENTICATE, copyData(pRspAuthenticateField)};
  _msgq.push(msg);
}

void TraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPUSERLOGIN, copyData(pRspUserLogin)};
  _msgq.push(msg);
}

void TraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPUSERLOGOUT, copyData(pUserLogout)};
  _msgq.push(msg);
}

void TraderSpi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPUSERPASSWORDUPDATE, copyData(pUserPasswordUpdate)};
  _msgq.push(msg);
}

void TraderSpi::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPTRADINGACCOUNTPASSWORDUPDATE, copyData(pTradingAccountPasswordUpdate)};
  _msgq.push(msg);
}

void TraderSpi::OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPUSERAUTHMETHOD, copyData(pRspUserAuthMethod)};
  _msgq.push(msg);
}

void TraderSpi::OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPGENUSERCAPTCHA, copyData(pRspGenUserCaptcha)};
  _msgq.push(msg);
}

void TraderSpi::OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPGENUSERTEXT, copyData(pRspGenUserText)};
  _msgq.push(msg);
}

void TraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPORDERINSERT, copyData(pInputOrder)};
  _msgq.push(msg);
}

void TraderSpi::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPPARKEDORDERINSERT, copyData(pParkedOrder)};
  _msgq.push(msg);
}

void TraderSpi::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPPARKEDORDERACTION, copyData(pParkedOrderAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPORDERACTION, copyData(pInputOrderAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField *pQryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYMAXORDERVOLUME, copyData(pQryMaxOrderVolume)};
  _msgq.push(msg);
}

void TraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPSETTLEMENTINFOCONFIRM, copyData(pSettlementInfoConfirm)};
  _msgq.push(msg);
}

void TraderSpi::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPREMOVEPARKEDORDER, copyData(pRemoveParkedOrder)};
  _msgq.push(msg);
}

void TraderSpi::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPREMOVEPARKEDORDERACTION, copyData(pRemoveParkedOrderAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPEXECORDERINSERT, copyData(pInputExecOrder)};
  _msgq.push(msg);
}

void TraderSpi::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPEXECORDERACTION, copyData(pInputExecOrderAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPFORQUOTEINSERT, copyData(pInputForQuote)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQUOTEINSERT, copyData(pInputQuote)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQUOTEACTION, copyData(pInputQuoteAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPBATCHORDERACTION, copyData(pInputBatchOrderAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPOPTIONSELFCLOSEINSERT, copyData(pInputOptionSelfClose)};
  _msgq.push(msg);
}

void TraderSpi::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPOPTIONSELFCLOSEACTION, copyData(pInputOptionSelfCloseAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPCOMBACTIONINSERT, copyData(pInputCombAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYORDER, copyData(pOrder)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYTRADE, copyData(pTrade)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYINVESTORPOSITION, copyData(pInvestorPosition)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYTRADINGACCOUNT, copyData(pTradingAccount)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYINVESTOR, copyData(pInvestor)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYTRADINGCODE, copyData(pTradingCode)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYINSTRUMENTMARGINRATE, copyData(pInstrumentMarginRate)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYINSTRUMENTCOMMISSIONRATE, copyData(pInstrumentCommissionRate)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYEXCHANGE, copyData(pExchange)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYPRODUCT, copyData(pProduct)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYINSTRUMENT, copyData(pInstrument)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYDEPTHMARKETDATA, copyData(pDepthMarketData)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryTraderOffer(CThostFtdcTraderOfferField *pTraderOffer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYTRADEROFFER, copyData(pTraderOffer)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYSETTLEMENTINFO, copyData(pSettlementInfo)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYTRANSFERBANK, copyData(pTransferBank)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYINVESTORPOSITIONDETAIL, copyData(pInvestorPositionDetail)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYNOTICE, copyData(pNotice)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYSETTLEMENTINFOCONFIRM, copyData(pSettlementInfoConfirm)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYINVESTORPOSITIONCOMBINEDETAIL, copyData(pInvestorPositionCombineDetail)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYCFMMCTRADINGACCOUNTKEY, copyData(pCFMMCTradingAccountKey)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYEWARRANTOFFSET, copyData(pEWarrantOffset)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYINVESTORPRODUCTGROUPMARGIN, copyData(pInvestorProductGroupMargin)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYEXCHANGEMARGINRATE, copyData(pExchangeMarginRate)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYEXCHANGEMARGINRATEADJUST, copyData(pExchangeMarginRateAdjust)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYEXCHANGERATE, copyData(pExchangeRate)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYSECAGENTACIDMAP, copyData(pSecAgentACIDMap)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYPRODUCTEXCHRATE, copyData(pProductExchRate)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYPRODUCTGROUP, copyData(pProductGroup)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYMMINSTRUMENTCOMMISSIONRATE, copyData(pMMInstrumentCommissionRate)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYMMOPTIONINSTRCOMMRATE, copyData(pMMOptionInstrCommRate)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYINSTRUMENTORDERCOMMRATE, copyData(pInstrumentOrderCommRate)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYSECAGENTTRADINGACCOUNT, copyData(pTradingAccount)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYSECAGENTCHECKMODE, copyData(pSecAgentCheckMode)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYSECAGENTTRADEINFO, copyData(pSecAgentTradeInfo)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYOPTIONINSTRTRADECOST, copyData(pOptionInstrTradeCost)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYOPTIONINSTRCOMMRATE, copyData(pOptionInstrCommRate)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYEXECORDER, copyData(pExecOrder)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYFORQUOTE, copyData(pForQuote)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYQUOTE, copyData(pQuote)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYOPTIONSELFCLOSE, copyData(pOptionSelfClose)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYINVESTUNIT, copyData(pInvestUnit)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYCOMBINSTRUMENTGUARD, copyData(pCombInstrumentGuard)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYCOMBACTION, copyData(pCombAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYTRANSFERSERIAL, copyData(pTransferSerial)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYACCOUNTREGISTER, copyData(pAccountregister)};
  _msgq.push(msg);
}


void TraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  Message msg = {ET_RSPERROR, copyData(pRspInfo)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder) {
  Message msg = {ET_RTNORDER, copyData(pOrder)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade) {
  Message msg = {ET_RTNTRADE, copyData(pTrade)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNORDERINSERT, copyData(pInputOrder)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNORDERACTION, copyData(pOrderAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {
  Message msg = {ET_RTNINSTRUMENTSTATUS, copyData(pInstrumentStatus)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnBulletin(CThostFtdcBulletinField *pBulletin) {
  Message msg = {ET_RTNBULLETIN, copyData(pBulletin)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {
  Message msg = {ET_RTNTRADINGNOTICE, copyData(pTradingNoticeInfo)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {
  Message msg = {ET_RTNERRORCONDITIONALORDER, copyData(pErrorConditionalOrder)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) {
  Message msg = {ET_RTNEXECORDER, copyData(pExecOrder)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNEXECORDERINSERT, copyData(pInputExecOrder)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNEXECORDERACTION, copyData(pExecOrderAction)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNFORQUOTEINSERT, copyData(pInputForQuote)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnQuote(CThostFtdcQuoteField *pQuote) {
  Message msg = {ET_RTNQUOTE, copyData(pQuote)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNQUOTEINSERT, copyData(pInputQuote)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNQUOTEACTION, copyData(pQuoteAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
  Message msg = {ET_RTNFORQUOTERSP, copyData(pForQuoteRsp)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) {
  Message msg = {ET_RTNCFMMCTRADINGACCOUNTTOKEN, copyData(pCFMMCTradingAccountToken)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNBATCHORDERACTION, copyData(pBatchOrderAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose) {
  Message msg = {ET_RTNOPTIONSELFCLOSE, copyData(pOptionSelfClose)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNOPTIONSELFCLOSEINSERT, copyData(pInputOptionSelfClose)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNOPTIONSELFCLOSEACTION, copyData(pOptionSelfCloseAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnCombAction(CThostFtdcCombActionField *pCombAction) {
  Message msg = {ET_RTNCOMBACTION, copyData(pCombAction)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNCOMBACTIONINSERT, copyData(pInputCombAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYCONTRACTBANK, copyData(pContractBank)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYPARKEDORDER, copyData(pParkedOrder)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYPARKEDORDERACTION, copyData(pParkedOrderAction)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYTRADINGNOTICE, copyData(pTradingNotice)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYBROKERTRADINGPARAMS, copyData(pBrokerTradingParams)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYBROKERTRADINGALGOS, copyData(pBrokerTradingAlgos)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQUERYCFMMCTRADINGACCOUNTTOKEN, copyData(pQueryCFMMCTradingAccountToken)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {
  Message msg = {ET_RTNFROMBANKTOFUTUREBYBANK, copyData(pRspTransfer)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {
  Message msg = {ET_RTNFROMFUTURETOBANKBYBANK, copyData(pRspTransfer)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {
  Message msg = {ET_RTNREPEALFROMBANKTOFUTUREBYBANK, copyData(pRspRepeal)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {
  Message msg = {ET_RTNREPEALFROMFUTURETOBANKBYBANK, copyData(pRspRepeal)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {
  Message msg = {ET_RTNFROMBANKTOFUTUREBYFUTURE, copyData(pRspTransfer)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {
  Message msg = {ET_RTNFROMFUTURETOBANKBYFUTURE, copyData(pRspTransfer)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {
  Message msg = {ET_RTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL, copyData(pRspRepeal)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {
  Message msg = {ET_RTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL, copyData(pRspRepeal)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {
  Message msg = {ET_RTNQUERYBANKBALANCEBYFUTURE, copyData(pNotifyQueryAccount)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNBANKTOFUTUREBYFUTURE, copyData(pReqTransfer)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNFUTURETOBANKBYFUTURE, copyData(pReqTransfer)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL, copyData(pReqRepeal)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL, copyData(pReqRepeal)};
  _msgq.push(msg);
}

void TraderSpi::OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  Message msg = {ET_ERRRTNQUERYBANKBALANCEBYFUTURE, copyData(pReqQueryAccount)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {
  Message msg = {ET_RTNREPEALFROMBANKTOFUTUREBYFUTURE, copyData(pRspRepeal)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {
  Message msg = {ET_RTNREPEALFROMFUTURETOBANKBYFUTURE, copyData(pRspRepeal)};
  _msgq.push(msg);
}

void TraderSpi::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPFROMBANKTOFUTUREBYFUTURE, copyData(pReqTransfer)};
  _msgq.push(msg);
}

void TraderSpi::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPFROMFUTURETOBANKBYFUTURE, copyData(pReqTransfer)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQUERYBANKACCOUNTMONEYBYFUTURE, copyData(pReqQueryAccount)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {
  Message msg = {ET_RTNOPENACCOUNTBYBANK, copyData(pOpenAccount)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {
  Message msg = {ET_RTNCANCELACCOUNTBYBANK, copyData(pCancelAccount)};
  _msgq.push(msg);
}

void TraderSpi::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {
  Message msg = {ET_RTNCHANGEACCOUNTBYBANK, copyData(pChangeAccount)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryClassifiedInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYCLASSIFIEDINSTRUMENT, copyData(pInstrument)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryCombPromotionParam(CThostFtdcCombPromotionParamField *pCombPromotionParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYCOMBPROMOTIONPARAM, copyData(pCombPromotionParam)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryRiskSettleInvstPosition(CThostFtdcRiskSettleInvstPositionField *pRiskSettleInvstPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYRISKSETTLEINVSTPOSITION, copyData(pRiskSettleInvstPosition)};
  _msgq.push(msg);
}

void TraderSpi::OnRspQryRiskSettleProductStatus(CThostFtdcRiskSettleProductStatusField *pRiskSettleProductStatus, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  Message msg = {ET_RSPQRYRISKSETTLEPRODUCTSTATUS, copyData(pRiskSettleProductStatus)};
  _msgq.push(msg);
}

bool TraderSpi::checkErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  bool isError = pRspInfo && pRspInfo->ErrorID != 0;

  if (isError)
    OnRspError(pRspInfo, nRequestID, bIsLast);

  return isError;
}
