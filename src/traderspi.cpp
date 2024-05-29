/*
 * traderspi.cpp
 *
 * Copyright (c) 2022-2024 Xiongfei Shi
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
  _msgq.done(message);
}

void TraderSpi::quit(int nCode) {
  _msgq.push(ET_QUIT, (uintptr_t)nCode, 0, Undefined);
}

const char *TraderSpi::eventName(int event) {
  auto iter = eventNames.find(event);

  if (iter == eventNames.end())
    return nullptr;

  return iter->second.c_str();
}

void TraderSpi::OnFrontConnected() {
  _msgq.push(ET_FRONTCONNECTED, 0, 0, Undefined);
}

void TraderSpi::OnFrontDisconnected(int nReason) {
  _msgq.push(ET_FRONTDISCONNECTED, (uintptr_t)nReason, 0, Undefined);
}

void TraderSpi::OnHeartBeatWarning(int nTimeLapse) {
  _msgq.push(ET_HEARTBEATWARNING, (uintptr_t)nTimeLapse, 0, Undefined);
}

void TraderSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPAUTHENTICATE, pRspAuthenticateField, nRequestID, bIsLast);
}

void TraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPUSERLOGIN, pRspUserLogin, nRequestID, bIsLast);
}

void TraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPUSERLOGOUT, pUserLogout, nRequestID, bIsLast);
}

void TraderSpi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPUSERPASSWORDUPDATE, pUserPasswordUpdate, nRequestID, bIsLast);
}

void TraderSpi::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPTRADINGACCOUNTPASSWORDUPDATE, pTradingAccountPasswordUpdate, nRequestID, bIsLast);
}

void TraderSpi::OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPUSERAUTHMETHOD, pRspUserAuthMethod, nRequestID, bIsLast);
}

void TraderSpi::OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPGENUSERCAPTCHA, pRspGenUserCaptcha, nRequestID, bIsLast);
}

void TraderSpi::OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPGENUSERTEXT, pRspGenUserText, nRequestID, bIsLast);
}

void TraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPORDERINSERT, pInputOrder, nRequestID, bIsLast);
}

void TraderSpi::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPPARKEDORDERINSERT, pParkedOrder, nRequestID, bIsLast);
}

void TraderSpi::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPPARKEDORDERACTION, pParkedOrderAction, nRequestID, bIsLast);
}

void TraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPORDERACTION, pInputOrderAction, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField *pQryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYMAXORDERVOLUME, pQryMaxOrderVolume, nRequestID, bIsLast);
}

void TraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPSETTLEMENTINFOCONFIRM, pSettlementInfoConfirm, nRequestID, bIsLast);
}

void TraderSpi::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPREMOVEPARKEDORDER, pRemoveParkedOrder, nRequestID, bIsLast);
}

void TraderSpi::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPREMOVEPARKEDORDERACTION, pRemoveParkedOrderAction, nRequestID, bIsLast);
}

void TraderSpi::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPEXECORDERINSERT, pInputExecOrder, nRequestID, bIsLast);
}

void TraderSpi::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPEXECORDERACTION, pInputExecOrderAction, nRequestID, bIsLast);
}

void TraderSpi::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPFORQUOTEINSERT, pInputForQuote, nRequestID, bIsLast);
}

void TraderSpi::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQUOTEINSERT, pInputQuote, nRequestID, bIsLast);
}

void TraderSpi::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQUOTEACTION, pInputQuoteAction, nRequestID, bIsLast);
}

void TraderSpi::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPBATCHORDERACTION, pInputBatchOrderAction, nRequestID, bIsLast);
}

void TraderSpi::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPOPTIONSELFCLOSEINSERT, pInputOptionSelfClose, nRequestID, bIsLast);
}

void TraderSpi::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPOPTIONSELFCLOSEACTION, pInputOptionSelfCloseAction, nRequestID, bIsLast);
}

void TraderSpi::OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPCOMBACTIONINSERT, pInputCombAction, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYORDER, pOrder, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRADE, pTrade, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINVESTORPOSITION, pInvestorPosition, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRADINGACCOUNT, pTradingAccount, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINVESTOR, pInvestor, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRADINGCODE, pTradingCode, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINSTRUMENTMARGINRATE, pInstrumentMarginRate, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINSTRUMENTCOMMISSIONRATE, pInstrumentCommissionRate, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYEXCHANGE, pExchange, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYPRODUCT, pProduct, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINSTRUMENT, pInstrument, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYDEPTHMARKETDATA, pDepthMarketData, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTraderOffer(CThostFtdcTraderOfferField *pTraderOffer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRADEROFFER, pTraderOffer, nRequestID, bIsLast);
}

void TraderSpi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYSETTLEMENTINFO, pSettlementInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRANSFERBANK, pTransferBank, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINVESTORPOSITIONDETAIL, pInvestorPositionDetail, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYNOTICE, pNotice, nRequestID, bIsLast);
}

void TraderSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYSETTLEMENTINFOCONFIRM, pSettlementInfoConfirm, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINVESTORPOSITIONCOMBINEDETAIL, pInvestorPositionCombineDetail, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYCFMMCTRADINGACCOUNTKEY, pCFMMCTradingAccountKey, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYEWARRANTOFFSET, pEWarrantOffset, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINVESTORPRODUCTGROUPMARGIN, pInvestorProductGroupMargin, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYEXCHANGEMARGINRATE, pExchangeMarginRate, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYEXCHANGEMARGINRATEADJUST, pExchangeMarginRateAdjust, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYEXCHANGERATE, pExchangeRate, nRequestID, bIsLast);
}

void TraderSpi::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYSECAGENTACIDMAP, pSecAgentACIDMap, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYPRODUCTEXCHRATE, pProductExchRate, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYPRODUCTGROUP, pProductGroup, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYMMINSTRUMENTCOMMISSIONRATE, pMMInstrumentCommissionRate, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYMMOPTIONINSTRCOMMRATE, pMMOptionInstrCommRate, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINSTRUMENTORDERCOMMRATE, pInstrumentOrderCommRate, nRequestID, bIsLast);
}

void TraderSpi::OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYSECAGENTTRADINGACCOUNT, pTradingAccount, nRequestID, bIsLast);
}

void TraderSpi::OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYSECAGENTCHECKMODE, pSecAgentCheckMode, nRequestID, bIsLast);
}

void TraderSpi::OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYSECAGENTTRADEINFO, pSecAgentTradeInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYOPTIONINSTRTRADECOST, pOptionInstrTradeCost, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYOPTIONINSTRCOMMRATE, pOptionInstrCommRate, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYEXECORDER, pExecOrder, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYFORQUOTE, pForQuote, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYQUOTE, pQuote, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYOPTIONSELFCLOSE, pOptionSelfClose, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYINVESTUNIT, pInvestUnit, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYCOMBINSTRUMENTGUARD, pCombInstrumentGuard, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYCOMBACTION, pCombAction, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRANSFERSERIAL, pTransferSerial, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYACCOUNTREGISTER, pAccountregister, nRequestID, bIsLast);
}

void TraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (nRequestID != 0)
    _msgq.push(ET_RSPERROR, pRspInfo, nRequestID, bIsLast);
  else
    _msgq.push(ET_RSPERROR, pRspInfo, 0, Undefined);
}

void TraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder) {
  _msgq.push(ET_RTNORDER, pOrder, 0, Undefined);
}

void TraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade) {
  _msgq.push(ET_RTNTRADE, pTrade, 0, Undefined);
}

void TraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNORDERINSERT, pInputOrder, 0, Undefined);
}

void TraderSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNORDERACTION, pOrderAction, 0, Undefined);
}

void TraderSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {
  _msgq.push(ET_RTNINSTRUMENTSTATUS, pInstrumentStatus, 0, Undefined);
}

void TraderSpi::OnRtnBulletin(CThostFtdcBulletinField *pBulletin) {
  _msgq.push(ET_RTNBULLETIN, pBulletin, 0, Undefined);
}

void TraderSpi::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {
  _msgq.push(ET_RTNTRADINGNOTICE, pTradingNoticeInfo, 0, Undefined);
}

void TraderSpi::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {
  _msgq.push(ET_RTNERRORCONDITIONALORDER, pErrorConditionalOrder, 0, Undefined);
}

void TraderSpi::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) {
  _msgq.push(ET_RTNEXECORDER, pExecOrder, 0, Undefined);
}

void TraderSpi::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNEXECORDERINSERT, pInputExecOrder, 0, Undefined);
}

void TraderSpi::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNEXECORDERACTION, pExecOrderAction, 0, Undefined);
}

void TraderSpi::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNFORQUOTEINSERT, pInputForQuote, 0, Undefined);
}

void TraderSpi::OnRtnQuote(CThostFtdcQuoteField *pQuote) {
  _msgq.push(ET_RTNQUOTE, pQuote, 0, Undefined);
}

void TraderSpi::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNQUOTEINSERT, pInputQuote, 0, Undefined);
}

void TraderSpi::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNQUOTEACTION, pQuoteAction, 0, Undefined);
}

void TraderSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
  _msgq.push(ET_RTNFORQUOTERSP, pForQuoteRsp, 0, Undefined);
}

void TraderSpi::OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) {
  _msgq.push(ET_RTNCFMMCTRADINGACCOUNTTOKEN, pCFMMCTradingAccountToken, 0, Undefined);
}

void TraderSpi::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNBATCHORDERACTION, pBatchOrderAction, 0, Undefined);
}

void TraderSpi::OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose) {
  _msgq.push(ET_RTNOPTIONSELFCLOSE, pOptionSelfClose, 0, Undefined);
}

void TraderSpi::OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNOPTIONSELFCLOSEINSERT, pInputOptionSelfClose, 0, Undefined);
}

void TraderSpi::OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNOPTIONSELFCLOSEACTION, pOptionSelfCloseAction, 0, Undefined);
}

void TraderSpi::OnRtnCombAction(CThostFtdcCombActionField *pCombAction) {
  _msgq.push(ET_RTNCOMBACTION, pCombAction, 0, Undefined);
}

void TraderSpi::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNCOMBACTIONINSERT, pInputCombAction, 0, Undefined);
}

void TraderSpi::OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYCONTRACTBANK, pContractBank, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYPARKEDORDER, pParkedOrder, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYPARKEDORDERACTION, pParkedOrderAction, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYTRADINGNOTICE, pTradingNotice, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYBROKERTRADINGPARAMS, pBrokerTradingParams, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYBROKERTRADINGALGOS, pBrokerTradingAlgos, nRequestID, bIsLast);
}

void TraderSpi::OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQUERYCFMMCTRADINGACCOUNTTOKEN, pQueryCFMMCTradingAccountToken, nRequestID, bIsLast);
}

void TraderSpi::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {
  _msgq.push(ET_RTNFROMBANKTOFUTUREBYBANK, pRspTransfer, 0, Undefined);
}

void TraderSpi::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {
  _msgq.push(ET_RTNFROMFUTURETOBANKBYBANK, pRspTransfer, 0, Undefined);
}

void TraderSpi::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMBANKTOFUTUREBYBANK, pRspRepeal, 0, Undefined);
}

void TraderSpi::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMFUTURETOBANKBYBANK, pRspRepeal, 0, Undefined);
}

void TraderSpi::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {
  _msgq.push(ET_RTNFROMBANKTOFUTUREBYFUTURE, pRspTransfer, 0, Undefined);
}

void TraderSpi::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {
  _msgq.push(ET_RTNFROMFUTURETOBANKBYFUTURE, pRspTransfer, 0, Undefined);
}

void TraderSpi::OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL, pRspRepeal, 0, Undefined);
}

void TraderSpi::OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL, pRspRepeal, 0, Undefined);
}

void TraderSpi::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {
  _msgq.push(ET_RTNQUERYBANKBALANCEBYFUTURE, pNotifyQueryAccount, 0, Undefined);
}

void TraderSpi::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNBANKTOFUTUREBYFUTURE, pReqTransfer, 0, Undefined);
}

void TraderSpi::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNFUTURETOBANKBYFUTURE, pReqTransfer, 0, Undefined);
}

void TraderSpi::OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL, pReqRepeal, 0, Undefined);
}

void TraderSpi::OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL, pReqRepeal, 0, Undefined);
}

void TraderSpi::OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) {
  if (checkErrorRspInfo(pRspInfo, 0, true))
    return;

  _msgq.push(ET_ERRRTNQUERYBANKBALANCEBYFUTURE, pReqQueryAccount, 0, Undefined);
}

void TraderSpi::OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMBANKTOFUTUREBYFUTURE, pRspRepeal, 0, Undefined);
}

void TraderSpi::OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMFUTURETOBANKBYFUTURE, pRspRepeal, 0, Undefined);
}

void TraderSpi::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPFROMBANKTOFUTUREBYFUTURE, pReqTransfer, nRequestID, bIsLast);
}

void TraderSpi::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPFROMFUTURETOBANKBYFUTURE, pReqTransfer, nRequestID, bIsLast);
}

void TraderSpi::OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQUERYBANKACCOUNTMONEYBYFUTURE, pReqQueryAccount, nRequestID, bIsLast);
}

void TraderSpi::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {
  _msgq.push(ET_RTNOPENACCOUNTBYBANK, pOpenAccount, 0, Undefined);
}

void TraderSpi::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {
  _msgq.push(ET_RTNCANCELACCOUNTBYBANK, pCancelAccount, 0, Undefined);
}

void TraderSpi::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {
  _msgq.push(ET_RTNCHANGEACCOUNTBYBANK, pChangeAccount, 0, Undefined);
}

void TraderSpi::OnRspQryClassifiedInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYCLASSIFIEDINSTRUMENT, pInstrument, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryCombPromotionParam(CThostFtdcCombPromotionParamField *pCombPromotionParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYCOMBPROMOTIONPARAM, pCombPromotionParam, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryRiskSettleInvstPosition(CThostFtdcRiskSettleInvstPositionField *pRiskSettleInvstPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYRISKSETTLEINVSTPOSITION, pRiskSettleInvstPosition, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryRiskSettleProductStatus(CThostFtdcRiskSettleProductStatusField *pRiskSettleProductStatus, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (checkErrorRspInfo(pRspInfo, nRequestID, bIsLast))
    return;

  _msgq.push(ET_RSPQRYRISKSETTLEPRODUCTSTATUS, pRiskSettleProductStatus, nRequestID, bIsLast);
}

bool TraderSpi::checkErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  bool isError = pRspInfo && pRspInfo->ErrorID != 0;

  if (isError)
    OnRspError(pRspInfo, nRequestID, bIsLast);

  return isError;
}
