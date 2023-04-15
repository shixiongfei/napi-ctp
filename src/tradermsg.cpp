/*
 * tradermsg.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "tradermsg.h"
#include "traderspi.h"
#include "ctpmsg.h"

static const MessageFuncs messageFuncs = {
  {ET_QUIT,                                     msgQuit},
  {ET_FRONTCONNECTED,                           msgFrontConnected},
  {ET_FRONTDISCONNECTED,                        msgFrontDisconnected},
  {ET_HEARTBEATWARNING,                         msgHeartBeatWarning},
  {ET_RSPAUTHENTICATE,                          rspAuthenticate},
  {ET_RSPUSERLOGIN,                             rspUserLogin},
  {ET_RSPUSERLOGOUT,                            rspUserLogout},
  {ET_RSPUSERPASSWORDUPDATE,                    rspUserPasswordUpdate},
  {ET_RSPTRADINGACCOUNTPASSWORDUPDATE,          rspTradingAccountPasswordUpdate},
  {ET_RSPUSERAUTHMETHOD,                        rspUserAuthMethod},
  {ET_RSPGENUSERCAPTCHA,                        rspGenUserCaptcha},
  {ET_RSPGENUSERTEXT,                           rspGenUserText},
  {ET_RSPORDERINSERT,                           rspOrderInsert},
  {ET_RSPPARKEDORDERINSERT,                     rspParkedOrderInsert},
  {ET_RSPPARKEDORDERACTION,                     rspParkedOrderAction},
  {ET_RSPORDERACTION,                           rspOrderAction},
  {ET_RSPQRYMAXORDERVOLUME,                     rspQryMaxOrderVolume},
  {ET_RSPSETTLEMENTINFOCONFIRM,                 rspSettlementInfoConfirm},
  {ET_RSPREMOVEPARKEDORDER,                     rspRemoveParkedOrder},
  {ET_RSPREMOVEPARKEDORDERACTION,               rspRemoveParkedOrderAction},
  {ET_RSPEXECORDERINSERT,                       rspExecOrderInsert},
  {ET_RSPEXECORDERACTION,                       rspExecOrderAction},
  {ET_RSPFORQUOTEINSERT,                        rspForQuoteInsert},
  {ET_RSPQUOTEINSERT,                           rspQuoteInsert},
  {ET_RSPQUOTEACTION,                           rspQuoteAction},
  {ET_RSPBATCHORDERACTION,                      rspBatchOrderAction},
  {ET_RSPOPTIONSELFCLOSEINSERT,                 rspOptionSelfCloseInsert},
  {ET_RSPOPTIONSELFCLOSEACTION,                 rspOptionSelfCloseAction},
  {ET_RSPCOMBACTIONINSERT,                      rspCombActionInsert},
  {ET_RSPQRYORDER,                              rspQryOrder},
  {ET_RSPQRYTRADE,                              rspQryTrade},
  {ET_RSPQRYINVESTORPOSITION,                   rspQryInvestorPosition},
  {ET_RSPQRYTRADINGACCOUNT,                     rspQryTradingAccount},
  {ET_RSPQRYINVESTOR,                           rspQryInvestor},
  {ET_RSPQRYTRADINGCODE,                        rspQryTradingCode},
  {ET_RSPQRYINSTRUMENTMARGINRATE,               rspQryInstrumentMarginRate},
  {ET_RSPQRYINSTRUMENTCOMMISSIONRATE,           rspQryInstrumentCommissionRate},
  {ET_RSPQRYEXCHANGE,                           rspQryExchange},
  {ET_RSPQRYPRODUCT,                            rspQryProduct},
  {ET_RSPQRYINSTRUMENT,                         rspQryInstrument},
  {ET_RSPQRYDEPTHMARKETDATA,                    rspQryDepthMarketData},
  {ET_RSPQRYTRADEROFFER,                        rspQryTraderOffer},
  {ET_RSPQRYSETTLEMENTINFO,                     rspQrySettlementInfo},
  {ET_RSPQRYTRANSFERBANK,                       rspQryTransferBank},
  {ET_RSPQRYINVESTORPOSITIONDETAIL,             rspQryInvestorPositionDetail},
  {ET_RSPQRYNOTICE,                             rspQryNotice},
  {ET_RSPQRYSETTLEMENTINFOCONFIRM,              rspQrySettlementInfoConfirm},
  {ET_RSPQRYINVESTORPOSITIONCOMBINEDETAIL,      rspQryInvestorPositionCombineDetail},
  {ET_RSPQRYCFMMCTRADINGACCOUNTKEY,             rspQryCFMMCTradingAccountKey},
  {ET_RSPQRYEWARRANTOFFSET,                     rspQryEWarrantOffset},
  {ET_RSPQRYINVESTORPRODUCTGROUPMARGIN,         rspQryInvestorProductGroupMargin},
  {ET_RSPQRYEXCHANGEMARGINRATE,                 rspQryExchangeMarginRate},
  {ET_RSPQRYEXCHANGEMARGINRATEADJUST,           rspQryExchangeMarginRateAdjust},
  {ET_RSPQRYEXCHANGERATE,                       rspQryExchangeRate},
  {ET_RSPQRYSECAGENTACIDMAP,                    rspQrySecAgentACIDMap},
  {ET_RSPQRYPRODUCTEXCHRATE,                    rspQryProductExchRate},
  {ET_RSPQRYPRODUCTGROUP,                       rspQryProductGroup},
  {ET_RSPQRYMMINSTRUMENTCOMMISSIONRATE,         rspQryMMInstrumentCommissionRate},
  {ET_RSPQRYMMOPTIONINSTRCOMMRATE,              rspQryMMOptionInstrCommRate},
  {ET_RSPQRYINSTRUMENTORDERCOMMRATE,            rspQryInstrumentOrderCommRate},
  {ET_RSPQRYSECAGENTTRADINGACCOUNT,             rspQrySecAgentTradingAccount},
  {ET_RSPQRYSECAGENTCHECKMODE,                  rspQrySecAgentCheckMode},
  {ET_RSPQRYSECAGENTTRADEINFO,                  rspQrySecAgentTradeInfo},
  {ET_RSPQRYOPTIONINSTRTRADECOST,               rspQryOptionInstrTradeCost},
  {ET_RSPQRYOPTIONINSTRCOMMRATE,                rspQryOptionInstrCommRate},
  {ET_RSPQRYEXECORDER,                          rspQryExecOrder},
  {ET_RSPQRYFORQUOTE,                           rspQryForQuote},
  {ET_RSPQRYQUOTE,                              rspQryQuote},
  {ET_RSPQRYOPTIONSELFCLOSE,                    rspQryOptionSelfClose},
  {ET_RSPQRYINVESTUNIT,                         rspQryInvestUnit},
  {ET_RSPQRYCOMBINSTRUMENTGUARD,                rspQryCombInstrumentGuard},
  {ET_RSPQRYCOMBACTION,                         rspQryCombAction},
  {ET_RSPQRYTRANSFERSERIAL,                     rspQryTransferSerial},
  {ET_RSPQRYACCOUNTREGISTER,                    rspQryAccountRegister},
  {ET_RSPERROR,                                 rspError},
  {ET_RTNORDER,                                 rtnOrder},
  {ET_RTNTRADE,                                 rtnTrade},
  {ET_ERRRTNORDERINSERT,                        errRtnOrderInsert},
  {ET_ERRRTNORDERACTION,                        errRtnOrderAction},
  {ET_RTNINSTRUMENTSTATUS,                      rtnInstrumentStatus},
  {ET_RTNBULLETIN,                              rtnBulletin},
  {ET_RTNTRADINGNOTICE,                         rtnTradingNotice},
  {ET_RTNERRORCONDITIONALORDER,                 rtnErrorConditionalOrder},
  {ET_RTNEXECORDER,                             rtnExecOrder},
  {ET_ERRRTNEXECORDERINSERT,                    errRtnExecOrderInsert},
  {ET_ERRRTNEXECORDERACTION,                    errRtnExecOrderAction},
  {ET_ERRRTNFORQUOTEINSERT,                     errRtnForQuoteInsert},
  {ET_RTNQUOTE,                                 rtnQuote},
  {ET_ERRRTNQUOTEINSERT,                        errRtnQuoteInsert},
  {ET_ERRRTNQUOTEACTION,                        errRtnQuoteAction},
  {ET_RTNFORQUOTERSP,                           rtnForQuote},
  {ET_RTNCFMMCTRADINGACCOUNTTOKEN,              rtnCFMMCTradingAccountToken},
  {ET_ERRRTNBATCHORDERACTION,                   errRtnBatchOrderAction},
  {ET_RTNOPTIONSELFCLOSE,                       rtnOptionSelfClose},
  {ET_ERRRTNOPTIONSELFCLOSEINSERT,              errRtnOptionSelfCloseInsert},
  {ET_ERRRTNOPTIONSELFCLOSEACTION,              errRtnOptionSelfCloseAction},
  {ET_RTNCOMBACTION,                            rtnCombAction},
  {ET_ERRRTNCOMBACTIONINSERT,                   errRtnCombActionInsert},
  {ET_RSPQRYCONTRACTBANK,                       rspQryContractBank},
  {ET_RSPQRYPARKEDORDER,                        rspQryParkedOrder},
  {ET_RSPQRYPARKEDORDERACTION,                  rspQryParkedOrderAction},
  {ET_RSPQRYTRADINGNOTICE,                      rspQryTradingNotice},
  {ET_RSPQRYBROKERTRADINGPARAMS,                rspQryBrokerTradingParams},
  {ET_RSPQRYBROKERTRADINGALGOS,                 rspQryBrokerTradingAlgos},
  {ET_RSPQUERYCFMMCTRADINGACCOUNTTOKEN,         rspQueryCFMMCTradingAccountToken},
  {ET_RTNFROMBANKTOFUTUREBYBANK,                rtnFromBankToFutureByBank},
  {ET_RTNFROMFUTURETOBANKBYBANK,                rtnFromFutureToBankByBank},
  {ET_RTNREPEALFROMBANKTOFUTUREBYBANK,          rtnRepealFromBankToFutureByBank},
  {ET_RTNREPEALFROMFUTURETOBANKBYBANK,          rtnRepealFromFutureToBankByBank},
  {ET_RTNFROMBANKTOFUTUREBYFUTURE,              rtnFromBankToFutureByFuture},
  {ET_RTNFROMFUTURETOBANKBYFUTURE,              rtnFromFutureToBankByFuture},
  {ET_RTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL,  rtnRepealFromBankToFutureByFutureManual},
  {ET_RTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL,  rtnRepealFromFutureToBankByFutureManual},
  {ET_RTNQUERYBANKBALANCEBYFUTURE,              rtnQueryBankBalanceByFuture},
  {ET_ERRRTNBANKTOFUTUREBYFUTURE,               errRtnBankToFutureByFuture},
  {ET_ERRRTNFUTURETOBANKBYFUTURE,               errRtnFutureToBankByFuture},
  {ET_ERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL,   errRtnRepealBankToFutureByFutureManual},
  {ET_ERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL,   errRtnRepealFutureToBankByFutureManual},
  {ET_ERRRTNQUERYBANKBALANCEBYFUTURE,           errRtnQueryBankBalanceByFuture},
  {ET_RTNREPEALFROMBANKTOFUTUREBYFUTURE,        rtnRepealFromBankToFutureByFuture},
  {ET_RTNREPEALFROMFUTURETOBANKBYFUTURE,        rtnRepealFromFutureToBankByFuture},
  {ET_RSPFROMBANKTOFUTUREBYFUTURE,              rspFromBankToFutureByFuture},
  {ET_RSPFROMFUTURETOBANKBYFUTURE,              rspFromFutureToBankByFuture},
  {ET_RSPQUERYBANKACCOUNTMONEYBYFUTURE,         rspQueryBankAccountMoneyByFuture},
  {ET_RTNOPENACCOUNTBYBANK,                     rtnOpenAccountByBank},
  {ET_RTNCANCELACCOUNTBYBANK,                   rtnCancelAccountByBank},
  {ET_RTNCHANGEACCOUNTBYBANK,                   rtnChangeAccountByBank},
  {ET_RSPQRYCLASSIFIEDINSTRUMENT,               rspQryClassifiedInstrument},
  {ET_RSPQRYCOMBPROMOTIONPARAM,                 rspQryCombPromotionParam},
  {ET_RSPQRYRISKSETTLEINVSTPOSITION,            rspQryRiskSettleInvstPosition},
  {ET_RSPQRYRISKSETTLEPRODUCTSTATUS,            rspQryRiskSettleProductStatus},
};

napi_status getTraderMessageValue(napi_env env, const Message *message, napi_value *result) {
  return getMessageValue(env, messageFuncs, message, result);
}