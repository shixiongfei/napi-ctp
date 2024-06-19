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
  _msgq.push(ET_QUIT, nCode, 0, Undefined);
}

const char *TraderSpi::eventName(int event) {
  auto iter = eventNames.find(event);

  if (iter == eventNames.end())
    return nullptr;

  return iter->second.c_str();
}

void TraderSpi::OnFrontConnected() {
  _msgq.push(ET_FRONTCONNECTED);
}

void TraderSpi::OnFrontDisconnected(int nReason) {
  _msgq.push(ET_FRONTDISCONNECTED, nReason);
}

void TraderSpi::OnHeartBeatWarning(int nTimeLapse) {
  _msgq.push(ET_HEARTBEATWARNING, nTimeLapse);
}

void TraderSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPAUTHENTICATE, pRspAuthenticateField, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPUSERLOGIN, pRspUserLogin, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPUSERLOGOUT, pUserLogout, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPUSERPASSWORDUPDATE, pUserPasswordUpdate, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPTRADINGACCOUNTPASSWORDUPDATE, pTradingAccountPasswordUpdate, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPUSERAUTHMETHOD, pRspUserAuthMethod, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPGENUSERCAPTCHA, pRspGenUserCaptcha, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPGENUSERTEXT, pRspGenUserText, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPORDERINSERT, pInputOrder, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPPARKEDORDERINSERT, pParkedOrder, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPPARKEDORDERACTION, pParkedOrderAction, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPORDERACTION, pInputOrderAction, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField *pQryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYMAXORDERVOLUME, pQryMaxOrderVolume, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPSETTLEMENTINFOCONFIRM, pSettlementInfoConfirm, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPREMOVEPARKEDORDER, pRemoveParkedOrder, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPREMOVEPARKEDORDERACTION, pRemoveParkedOrderAction, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPEXECORDERINSERT, pInputExecOrder, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPEXECORDERACTION, pInputExecOrderAction, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPFORQUOTEINSERT, pInputForQuote, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQUOTEINSERT, pInputQuote, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQUOTEACTION, pInputQuoteAction, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPBATCHORDERACTION, pInputBatchOrderAction, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPOPTIONSELFCLOSEINSERT, pInputOptionSelfClose, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPOPTIONSELFCLOSEACTION, pInputOptionSelfCloseAction, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPCOMBACTIONINSERT, pInputCombAction, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYORDER, pOrder, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYTRADE, pTrade, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYINVESTORPOSITION, pInvestorPosition, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYTRADINGACCOUNT, pTradingAccount, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYINVESTOR, pInvestor, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYTRADINGCODE, pTradingCode, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYINSTRUMENTMARGINRATE, pInstrumentMarginRate, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYINSTRUMENTCOMMISSIONRATE, pInstrumentCommissionRate, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYEXCHANGE, pExchange, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYPRODUCT, pProduct, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYINSTRUMENT, pInstrument, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYDEPTHMARKETDATA, pDepthMarketData, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTraderOffer(CThostFtdcTraderOfferField *pTraderOffer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYTRADEROFFER, pTraderOffer, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYSETTLEMENTINFO, pSettlementInfo, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYTRANSFERBANK, pTransferBank, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYINVESTORPOSITIONDETAIL, pInvestorPositionDetail, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYNOTICE, pNotice, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYSETTLEMENTINFOCONFIRM, pSettlementInfoConfirm, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYINVESTORPOSITIONCOMBINEDETAIL, pInvestorPositionCombineDetail, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYCFMMCTRADINGACCOUNTKEY, pCFMMCTradingAccountKey, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYEWARRANTOFFSET, pEWarrantOffset, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYINVESTORPRODUCTGROUPMARGIN, pInvestorProductGroupMargin, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYEXCHANGEMARGINRATE, pExchangeMarginRate, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYEXCHANGEMARGINRATEADJUST, pExchangeMarginRateAdjust, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYEXCHANGERATE, pExchangeRate, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYSECAGENTACIDMAP, pSecAgentACIDMap, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYPRODUCTEXCHRATE, pProductExchRate, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYPRODUCTGROUP, pProductGroup, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYMMINSTRUMENTCOMMISSIONRATE, pMMInstrumentCommissionRate, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYMMOPTIONINSTRCOMMRATE, pMMOptionInstrCommRate, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYINSTRUMENTORDERCOMMRATE, pInstrumentOrderCommRate, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYSECAGENTTRADINGACCOUNT, pTradingAccount, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYSECAGENTCHECKMODE, pSecAgentCheckMode, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYSECAGENTTRADEINFO, pSecAgentTradeInfo, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYOPTIONINSTRTRADECOST, pOptionInstrTradeCost, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYOPTIONINSTRCOMMRATE, pOptionInstrCommRate, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYEXECORDER, pExecOrder, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYFORQUOTE, pForQuote, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYQUOTE, pQuote, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYOPTIONSELFCLOSE, pOptionSelfClose, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYINVESTUNIT, pInvestUnit, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYCOMBINSTRUMENTGUARD, pCombInstrumentGuard, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYCOMBACTION, pCombAction, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYTRANSFERSERIAL, pTransferSerial, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYACCOUNTREGISTER, pAccountregister, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPERROR, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder) {
  _msgq.push(ET_RTNORDER, pOrder);
}

void TraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade) {
  _msgq.push(ET_RTNTRADE, pTrade);
}

void TraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNORDERINSERT, pInputOrder, pRspInfo);
}

void TraderSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNORDERACTION, pOrderAction, pRspInfo);
}

void TraderSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {
  _msgq.push(ET_RTNINSTRUMENTSTATUS, pInstrumentStatus);
}

void TraderSpi::OnRtnBulletin(CThostFtdcBulletinField *pBulletin) {
  _msgq.push(ET_RTNBULLETIN, pBulletin);
}

void TraderSpi::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {
  _msgq.push(ET_RTNTRADINGNOTICE, pTradingNoticeInfo);
}

void TraderSpi::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {
  _msgq.push(ET_RTNERRORCONDITIONALORDER, pErrorConditionalOrder);
}

void TraderSpi::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) {
  _msgq.push(ET_RTNEXECORDER, pExecOrder);
}

void TraderSpi::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNEXECORDERINSERT, pInputExecOrder, pRspInfo);
}

void TraderSpi::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNEXECORDERACTION, pExecOrderAction, pRspInfo);
}

void TraderSpi::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNFORQUOTEINSERT, pInputForQuote, pRspInfo);
}

void TraderSpi::OnRtnQuote(CThostFtdcQuoteField *pQuote) {
  _msgq.push(ET_RTNQUOTE, pQuote);
}

void TraderSpi::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNQUOTEINSERT, pInputQuote, pRspInfo);
}

void TraderSpi::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNQUOTEACTION, pQuoteAction, pRspInfo);
}

void TraderSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
  _msgq.push(ET_RTNFORQUOTERSP, pForQuoteRsp);
}

void TraderSpi::OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) {
  _msgq.push(ET_RTNCFMMCTRADINGACCOUNTTOKEN, pCFMMCTradingAccountToken);
}

void TraderSpi::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNBATCHORDERACTION, pBatchOrderAction, pRspInfo);
}

void TraderSpi::OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose) {
  _msgq.push(ET_RTNOPTIONSELFCLOSE, pOptionSelfClose);
}

void TraderSpi::OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNOPTIONSELFCLOSEINSERT, pInputOptionSelfClose, pRspInfo);
}

void TraderSpi::OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNOPTIONSELFCLOSEACTION, pOptionSelfCloseAction, pRspInfo);
}

void TraderSpi::OnRtnCombAction(CThostFtdcCombActionField *pCombAction) {
  _msgq.push(ET_RTNCOMBACTION, pCombAction);
}

void TraderSpi::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNCOMBACTIONINSERT, pInputCombAction, pRspInfo);
}

void TraderSpi::OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYCONTRACTBANK, pContractBank, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYPARKEDORDER, pParkedOrder, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYPARKEDORDERACTION, pParkedOrderAction, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYTRADINGNOTICE, pTradingNotice, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYBROKERTRADINGPARAMS, pBrokerTradingParams, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYBROKERTRADINGALGOS, pBrokerTradingAlgos, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQUERYCFMMCTRADINGACCOUNTTOKEN, pQueryCFMMCTradingAccountToken, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {
  _msgq.push(ET_RTNFROMBANKTOFUTUREBYBANK, pRspTransfer);
}

void TraderSpi::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {
  _msgq.push(ET_RTNFROMFUTURETOBANKBYBANK, pRspTransfer);
}

void TraderSpi::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMBANKTOFUTUREBYBANK, pRspRepeal);
}

void TraderSpi::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMFUTURETOBANKBYBANK, pRspRepeal);
}

void TraderSpi::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {
  _msgq.push(ET_RTNFROMBANKTOFUTUREBYFUTURE, pRspTransfer);
}

void TraderSpi::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {
  _msgq.push(ET_RTNFROMFUTURETOBANKBYFUTURE, pRspTransfer);
}

void TraderSpi::OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL, pRspRepeal);
}

void TraderSpi::OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL, pRspRepeal);
}

void TraderSpi::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {
  _msgq.push(ET_RTNQUERYBANKBALANCEBYFUTURE, pNotifyQueryAccount);
}

void TraderSpi::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNBANKTOFUTUREBYFUTURE, pReqTransfer, pRspInfo);
}

void TraderSpi::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNFUTURETOBANKBYFUTURE, pReqTransfer, pRspInfo);
}

void TraderSpi::OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL, pReqRepeal, pRspInfo);
}

void TraderSpi::OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL, pReqRepeal, pRspInfo);
}

void TraderSpi::OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) {
  _msgq.push(ET_ERRRTNQUERYBANKBALANCEBYFUTURE, pReqQueryAccount, pRspInfo);
}

void TraderSpi::OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMBANKTOFUTUREBYFUTURE, pRspRepeal);
}

void TraderSpi::OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {
  _msgq.push(ET_RTNREPEALFROMFUTURETOBANKBYFUTURE, pRspRepeal);
}

void TraderSpi::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPFROMBANKTOFUTUREBYFUTURE, pReqTransfer, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPFROMFUTURETOBANKBYFUTURE, pReqTransfer, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQUERYBANKACCOUNTMONEYBYFUTURE, pReqQueryAccount, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {
  _msgq.push(ET_RTNOPENACCOUNTBYBANK, pOpenAccount);
}

void TraderSpi::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {
  _msgq.push(ET_RTNCANCELACCOUNTBYBANK, pCancelAccount);
}

void TraderSpi::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {
  _msgq.push(ET_RTNCHANGEACCOUNTBYBANK, pChangeAccount);
}

void TraderSpi::OnRspQryClassifiedInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYCLASSIFIEDINSTRUMENT, pInstrument, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryCombPromotionParam(CThostFtdcCombPromotionParamField *pCombPromotionParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYCOMBPROMOTIONPARAM, pCombPromotionParam, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryRiskSettleInvstPosition(CThostFtdcRiskSettleInvstPositionField *pRiskSettleInvstPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYRISKSETTLEINVSTPOSITION, pRiskSettleInvstPosition, pRspInfo, nRequestID, bIsLast);
}

void TraderSpi::OnRspQryRiskSettleProductStatus(CThostFtdcRiskSettleProductStatusField *pRiskSettleProductStatus, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  _msgq.push(ET_RSPQRYRISKSETTLEPRODUCTSTATUS, pRiskSettleProductStatus, pRspInfo, nRequestID, bIsLast);
}
