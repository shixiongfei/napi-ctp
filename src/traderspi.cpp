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
  Message *msg;

  while (QUEUE_SUCCESS == poll(&msg, 0))
    done(msg);
}

int TraderSpi::poll(Message **message, unsigned int millisec) {
  return _msgq.pop(message, millisec);
}

void TraderSpi::done(Message *message) {
  if (isFreeable(message->event))
    free((void *)message->data);

  free(message);
}

void TraderSpi::quit(int nCode) {
  _msgq.push(ET_QUIT, (uintptr_t)nCode);
}

const char *TraderSpi::eventName(int event) {
  auto iter = eventNames.find(event);

  if (iter == eventNames.end())
    return nullptr;

  return iter->second.c_str();
}

void TraderSpi::OnFrontConnected() {
  _msgq.push(ET_FRONTCONNECTED, 0);
}

void TraderSpi::OnFrontDisconnected(int nReason) {
  _msgq.push(ET_FRONTDISCONNECTED, (uintptr_t)nReason);
}

void TraderSpi::OnHeartBeatWarning(int nTimeLapse) {
  _msgq.push(ET_HEARTBEATWARNING, (uintptr_t)nTimeLapse);
}

void TraderSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPAUTHENTICATE, copyData(pRspAuthenticateField));
}

void TraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPUSERLOGIN, copyData(pRspUserLogin));
}

void TraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPUSERLOGOUT, copyData(pUserLogout));
}

void TraderSpi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPUSERPASSWORDUPDATE, copyData(pUserPasswordUpdate));
}

void TraderSpi::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPTRADINGACCOUNTPASSWORDUPDATE, copyData(pTradingAccountPasswordUpdate));
}

void TraderSpi::OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPUSERAUTHMETHOD, copyData(pRspUserAuthMethod));
}

void TraderSpi::OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPGENUSERCAPTCHA, copyData(pRspGenUserCaptcha));
}

void TraderSpi::OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPGENUSERTEXT, copyData(pRspGenUserText));
}

void TraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPORDERINSERT, copyData(pInputOrder));
}

void TraderSpi::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPPARKEDORDERINSERT, copyData(pParkedOrder));
}

void TraderSpi::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPPARKEDORDERACTION, copyData(pParkedOrderAction));
}

void TraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPORDERACTION, copyData(pInputOrderAction));
}

void TraderSpi::OnRspQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField *pQryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYMAXORDERVOLUME, copyData(pQryMaxOrderVolume));
}

void TraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPSETTLEMENTINFOCONFIRM, copyData(pSettlementInfoConfirm));
}

void TraderSpi::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPREMOVEPARKEDORDER, copyData(pRemoveParkedOrder));
}

void TraderSpi::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPREMOVEPARKEDORDERACTION, copyData(pRemoveParkedOrderAction));
}

void TraderSpi::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPEXECORDERINSERT, copyData(pInputExecOrder));
}

void TraderSpi::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPEXECORDERACTION, copyData(pInputExecOrderAction));
}

void TraderSpi::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPFORQUOTEINSERT, copyData(pInputForQuote));
}

void TraderSpi::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQUOTEINSERT, copyData(pInputQuote));
}

void TraderSpi::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQUOTEACTION, copyData(pInputQuoteAction));
}

void TraderSpi::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPBATCHORDERACTION, copyData(pInputBatchOrderAction));
}

void TraderSpi::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPOPTIONSELFCLOSEINSERT, copyData(pInputOptionSelfClose));
}

void TraderSpi::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPOPTIONSELFCLOSEACTION, copyData(pInputOptionSelfCloseAction));
}

void TraderSpi::OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPCOMBACTIONINSERT, copyData(pInputCombAction));
}

void TraderSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYORDER, copyData(pOrder));
}

void TraderSpi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRADE, copyData(pTrade));
}

void TraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINVESTORPOSITION, copyData(pInvestorPosition));
}

void TraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRADINGACCOUNT, copyData(pTradingAccount));
}

void TraderSpi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINVESTOR, copyData(pInvestor));
}

void TraderSpi::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRADINGCODE, copyData(pTradingCode));
}

void TraderSpi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINSTRUMENTMARGINRATE, copyData(pInstrumentMarginRate));
}

void TraderSpi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINSTRUMENTCOMMISSIONRATE, copyData(pInstrumentCommissionRate));
}

void TraderSpi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYEXCHANGE, copyData(pExchange));
}

void TraderSpi::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYPRODUCT, copyData(pProduct));
}

void TraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINSTRUMENT, copyData(pInstrument));
}

void TraderSpi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYDEPTHMARKETDATA, copyData(pDepthMarketData));
}

void TraderSpi::OnRspQryTraderOffer(CThostFtdcTraderOfferField *pTraderOffer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRADEROFFER, copyData(pTraderOffer));
}

void TraderSpi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYSETTLEMENTINFO, copyData(pSettlementInfo));
}

void TraderSpi::OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRANSFERBANK, copyData(pTransferBank));
}

void TraderSpi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINVESTORPOSITIONDETAIL, copyData(pInvestorPositionDetail));
}

void TraderSpi::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYNOTICE, copyData(pNotice));
}

void TraderSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYSETTLEMENTINFOCONFIRM, copyData(pSettlementInfoConfirm));
}

void TraderSpi::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINVESTORPOSITIONCOMBINEDETAIL, copyData(pInvestorPositionCombineDetail));
}

void TraderSpi::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYCFMMCTRADINGACCOUNTKEY, copyData(pCFMMCTradingAccountKey));
}

void TraderSpi::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYEWARRANTOFFSET, copyData(pEWarrantOffset));
}

void TraderSpi::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINVESTORPRODUCTGROUPMARGIN, copyData(pInvestorProductGroupMargin));
}

void TraderSpi::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYEXCHANGEMARGINRATE, copyData(pExchangeMarginRate));
}

void TraderSpi::OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYEXCHANGEMARGINRATEADJUST, copyData(pExchangeMarginRateAdjust));
}

void TraderSpi::OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYEXCHANGERATE, copyData(pExchangeRate));
}

void TraderSpi::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYSECAGENTACIDMAP, copyData(pSecAgentACIDMap));
}

void TraderSpi::OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYPRODUCTEXCHRATE, copyData(pProductExchRate));
}

void TraderSpi::OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYPRODUCTGROUP, copyData(pProductGroup));
}

void TraderSpi::OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYMMINSTRUMENTCOMMISSIONRATE, copyData(pMMInstrumentCommissionRate));
}

void TraderSpi::OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYMMOPTIONINSTRCOMMRATE, copyData(pMMOptionInstrCommRate));
}

void TraderSpi::OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINSTRUMENTORDERCOMMRATE, copyData(pInstrumentOrderCommRate));
}

void TraderSpi::OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYSECAGENTTRADINGACCOUNT, copyData(pTradingAccount));
}

void TraderSpi::OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYSECAGENTCHECKMODE, copyData(pSecAgentCheckMode));
}

void TraderSpi::OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYSECAGENTTRADEINFO, copyData(pSecAgentTradeInfo));
}

void TraderSpi::OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYOPTIONINSTRTRADECOST, copyData(pOptionInstrTradeCost));
}

void TraderSpi::OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYOPTIONINSTRCOMMRATE, copyData(pOptionInstrCommRate));
}

void TraderSpi::OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYEXECORDER, copyData(pExecOrder));
}

void TraderSpi::OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYFORQUOTE, copyData(pForQuote));
}

void TraderSpi::OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYQUOTE, copyData(pQuote));
}

void TraderSpi::OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYOPTIONSELFCLOSE, copyData(pOptionSelfClose));
}

void TraderSpi::OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINVESTUNIT, copyData(pInvestUnit));
}

void TraderSpi::OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYCOMBINSTRUMENTGUARD, copyData(pCombInstrumentGuard));
}

void TraderSpi::OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYCOMBACTION, copyData(pCombAction));
}

void TraderSpi::OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRANSFERSERIAL, copyData(pTransferSerial));
}

void TraderSpi::OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYACCOUNTREGISTER, copyData(pAccountregister));
}


void TraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPERROR, copyData(pRspInfo));
}

void TraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder) {
  _msgq.push(ET_RTNORDER, copyData(pOrder));
}

void TraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade) {
  _msgq.push(ET_RTNTRADE, copyData(pTrade));
}

void TraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNORDERINSERT, copyData(pInputOrder));
}

void TraderSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNORDERACTION, copyData(pOrderAction));
}

void TraderSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {
  _msgq.push(ET_RTNINSTRUMENTSTATUS, copyData(pInstrumentStatus));
}

void TraderSpi::OnRtnBulletin(CThostFtdcBulletinField *pBulletin) {
  _msgq.push(ET_RTNBULLETIN, copyData(pBulletin));
}

void TraderSpi::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {
  _msgq.push(ET_RTNTRADINGNOTICE, copyData(pTradingNoticeInfo));
}

void TraderSpi::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {
  _msgq.push(ET_RTNERRORCONDITIONALORDER, copyData(pErrorConditionalOrder));
}

void TraderSpi::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) {
  _msgq.push(ET_RTNEXECORDER, copyData(pExecOrder));
}

void TraderSpi::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNEXECORDERINSERT, copyData(pInputExecOrder));
}

void TraderSpi::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNEXECORDERACTION, copyData(pExecOrderAction));
}

void TraderSpi::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNFORQUOTEINSERT, copyData(pInputForQuote));
}

void TraderSpi::OnRtnQuote(CThostFtdcQuoteField *pQuote) {
  _msgq.push(ET_RTNQUOTE, copyData(pQuote));
}

void TraderSpi::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNQUOTEINSERT, copyData(pInputQuote));
}

void TraderSpi::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNQUOTEACTION, copyData(pQuoteAction));
}

void TraderSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
  _msgq.push(ET_RTNFORQUOTERSP, copyData(pForQuoteRsp));
}

void TraderSpi::OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) {
  _msgq.push(ET_RTNCFMMCTRADINGACCOUNTTOKEN, copyData(pCFMMCTradingAccountToken));
}

void TraderSpi::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNBATCHORDERACTION, copyData(pBatchOrderAction));
}

void TraderSpi::OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose) {
  _msgq.push(ET_RTNOPTIONSELFCLOSE, copyData(pOptionSelfClose));
}

void TraderSpi::OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNOPTIONSELFCLOSEINSERT, copyData(pInputOptionSelfClose));
}

void TraderSpi::OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNOPTIONSELFCLOSEACTION, copyData(pOptionSelfCloseAction));
}

void TraderSpi::OnRtnCombAction(CThostFtdcCombActionField *pCombAction) {
  _msgq.push(ET_RTNCOMBACTION, copyData(pCombAction));
}

void TraderSpi::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNCOMBACTIONINSERT, copyData(pInputCombAction));
}

void TraderSpi::OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYCONTRACTBANK, copyData(pContractBank));
}

void TraderSpi::OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYPARKEDORDER, copyData(pParkedOrder));
}

void TraderSpi::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYPARKEDORDERACTION, copyData(pParkedOrderAction));
}

void TraderSpi::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRADINGNOTICE, copyData(pTradingNotice));
}

void TraderSpi::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYBROKERTRADINGPARAMS, copyData(pBrokerTradingParams));
}

void TraderSpi::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYBROKERTRADINGALGOS, copyData(pBrokerTradingAlgos));
}

void TraderSpi::OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQUERYCFMMCTRADINGACCOUNTTOKEN, copyData(pQueryCFMMCTradingAccountToken));
}

void TraderSpi::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {
  _msgq.push(ET_RTNFROMBANKTOFUTUREBYBANK, copyData(pRspTransfer));
}

void TraderSpi::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {
  _msgq.push(ET_RTNFROMFUTURETOBANKBYBANK, copyData(pRspTransfer));
}

void TraderSpi::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMBANKTOFUTUREBYBANK, copyData(pRspRepeal));
}

void TraderSpi::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMFUTURETOBANKBYBANK, copyData(pRspRepeal));
}

void TraderSpi::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {
  _msgq.push(ET_RTNFROMBANKTOFUTUREBYFUTURE, copyData(pRspTransfer));
}

void TraderSpi::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {
  _msgq.push(ET_RTNFROMFUTURETOBANKBYFUTURE, copyData(pRspTransfer));
}

void TraderSpi::OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL, copyData(pRspRepeal));
}

void TraderSpi::OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL, copyData(pRspRepeal));
}

void TraderSpi::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {
  _msgq.push(ET_RTNQUERYBANKBALANCEBYFUTURE, copyData(pNotifyQueryAccount));
}

void TraderSpi::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNBANKTOFUTUREBYFUTURE, copyData(pReqTransfer));
}

void TraderSpi::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNFUTURETOBANKBYFUTURE, copyData(pReqTransfer));
}

void TraderSpi::OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL, copyData(pReqRepeal));
}

void TraderSpi::OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL, copyData(pReqRepeal));
}

void TraderSpi::OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNQUERYBANKBALANCEBYFUTURE, copyData(pReqQueryAccount));
}

void TraderSpi::OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMBANKTOFUTUREBYFUTURE, copyData(pRspRepeal));
}

void TraderSpi::OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMFUTURETOBANKBYFUTURE, copyData(pRspRepeal));
}

void TraderSpi::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPFROMBANKTOFUTUREBYFUTURE, copyData(pReqTransfer));
}

void TraderSpi::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPFROMFUTURETOBANKBYFUTURE, copyData(pReqTransfer));
}

void TraderSpi::OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQUERYBANKACCOUNTMONEYBYFUTURE, copyData(pReqQueryAccount));
}

void TraderSpi::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {
  _msgq.push(ET_RTNOPENACCOUNTBYBANK, copyData(pOpenAccount));
}

void TraderSpi::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {
  _msgq.push(ET_RTNCANCELACCOUNTBYBANK, copyData(pCancelAccount));
}

void TraderSpi::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {
  _msgq.push(ET_RTNCHANGEACCOUNTBYBANK, copyData(pChangeAccount));
}

void TraderSpi::OnRspQryClassifiedInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYCLASSIFIEDINSTRUMENT, copyData(pInstrument));
}

void TraderSpi::OnRspQryCombPromotionParam(CThostFtdcCombPromotionParamField *pCombPromotionParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYCOMBPROMOTIONPARAM, copyData(pCombPromotionParam));
}

void TraderSpi::OnRspQryRiskSettleInvstPosition(CThostFtdcRiskSettleInvstPositionField *pRiskSettleInvstPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYRISKSETTLEINVSTPOSITION, copyData(pRiskSettleInvstPosition));
}

void TraderSpi::OnRspQryRiskSettleProductStatus(CThostFtdcRiskSettleProductStatusField *pRiskSettleProductStatus, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYRISKSETTLEPRODUCTSTATUS, copyData(pRiskSettleProductStatus));
}

bool TraderSpi::checkErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  bool isError = pRspInfo && pRspInfo->ErrorID != 0;

  if (isError)
    OnRspError(pRspInfo, nRequestID, bIsLast);

  return isError;
}
