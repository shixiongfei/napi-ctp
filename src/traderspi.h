/*
 * traderspi.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __TRADERSPI_H__
#define __TRADERSPI_H__

#include "message_queue.h"
#include "napi_ctp.h"

#define ET_BASE                                     0x2000
#define ET_QUIT                                     (ET_BASE + 0)
#define ET_FRONTCONNECTED                           (ET_BASE + 1)
#define ET_FRONTDISCONNECTED                        (ET_BASE + 2)
#define ET_HEARTBEATWARNING                         (ET_BASE + 3)
#define ET_RSPAUTHENTICATE                          (ET_BASE + 4)
#define ET_RSPUSERLOGIN                             (ET_BASE + 5)
#define ET_RSPUSERLOGOUT                            (ET_BASE + 6)
#define ET_RSPUSERPASSWORDUPDATE                    (ET_BASE + 7)
#define ET_RSPTRADINGACCOUNTPASSWORDUPDATE          (ET_BASE + 8)
#define ET_RSPUSERAUTHMETHOD                        (ET_BASE + 9)
#define ET_RSPGENUSERCAPTCHA                        (ET_BASE + 10)
#define ET_RSPGENUSERTEXT                           (ET_BASE + 11)
#define ET_RSPORDERINSERT                           (ET_BASE + 12)
#define ET_RSPPARKEDORDERINSERT                     (ET_BASE + 13)
#define ET_RSPPARKEDORDERACTION                     (ET_BASE + 14)
#define ET_RSPORDERACTION                           (ET_BASE + 15)
#define ET_RSPQRYMAXORDERVOLUME                     (ET_BASE + 16)
#define ET_RSPSETTLEMENTINFOCONFIRM                 (ET_BASE + 17)
#define ET_RSPREMOVEPARKEDORDER                     (ET_BASE + 18)
#define ET_RSPREMOVEPARKEDORDERACTION               (ET_BASE + 19)
#define ET_RSPEXECORDERINSERT                       (ET_BASE + 20)
#define ET_RSPEXECORDERACTION                       (ET_BASE + 21)
#define ET_RSPFORQUOTEINSERT                        (ET_BASE + 22)
#define ET_RSPQUOTEINSERT                           (ET_BASE + 23)
#define ET_RSPQUOTEACTION                           (ET_BASE + 24)
#define ET_RSPBATCHORDERACTION                      (ET_BASE + 25)
#define ET_RSPOPTIONSELFCLOSEINSERT                 (ET_BASE + 26)
#define ET_RSPOPTIONSELFCLOSEACTION                 (ET_BASE + 27)
#define ET_RSPCOMBACTIONINSERT                      (ET_BASE + 28)
#define ET_RSPQRYORDER                              (ET_BASE + 29)
#define ET_RSPQRYTRADE                              (ET_BASE + 30)
#define ET_RSPQRYINVESTORPOSITION                   (ET_BASE + 31)
#define ET_RSPQRYTRADINGACCOUNT                     (ET_BASE + 32)
#define ET_RSPQRYINVESTOR                           (ET_BASE + 33)
#define ET_RSPQRYTRADINGCODE                        (ET_BASE + 34)
#define ET_RSPQRYINSTRUMENTMARGINRATE               (ET_BASE + 35)
#define ET_RSPQRYINSTRUMENTCOMMISSIONRATE           (ET_BASE + 36)
#define ET_RSPQRYEXCHANGE                           (ET_BASE + 37)
#define ET_RSPQRYPRODUCT                            (ET_BASE + 38)
#define ET_RSPQRYINSTRUMENT                         (ET_BASE + 39)
#define ET_RSPQRYDEPTHMARKETDATA                    (ET_BASE + 40)
#define ET_RSPQRYTRADEROFFER                        (ET_BASE + 41)
#define ET_RSPQRYSETTLEMENTINFO                     (ET_BASE + 42)
#define ET_RSPQRYTRANSFERBANK                       (ET_BASE + 43)
#define ET_RSPQRYINVESTORPOSITIONDETAIL             (ET_BASE + 44)
#define ET_RSPQRYNOTICE                             (ET_BASE + 45)
#define ET_RSPQRYSETTLEMENTINFOCONFIRM              (ET_BASE + 46)
#define ET_RSPQRYINVESTORPOSITIONCOMBINEDETAIL      (ET_BASE + 47)
#define ET_RSPQRYCFMMCTRADINGACCOUNTKEY             (ET_BASE + 48)
#define ET_RSPQRYEWARRANTOFFSET                     (ET_BASE + 49)
#define ET_RSPQRYINVESTORPRODUCTGROUPMARGIN         (ET_BASE + 50)
#define ET_RSPQRYEXCHANGEMARGINRATE                 (ET_BASE + 51)
#define ET_RSPQRYEXCHANGEMARGINRATEADJUST           (ET_BASE + 52)
#define ET_RSPQRYEXCHANGERATE                       (ET_BASE + 53)
#define ET_RSPQRYSECAGENTACIDMAP                    (ET_BASE + 54)
#define ET_RSPQRYPRODUCTEXCHRATE                    (ET_BASE + 55)
#define ET_RSPQRYPRODUCTGROUP                       (ET_BASE + 56)
#define ET_RSPQRYMMINSTRUMENTCOMMISSIONRATE         (ET_BASE + 57)
#define ET_RSPQRYMMOPTIONINSTRCOMMRATE              (ET_BASE + 58)
#define ET_RSPQRYINSTRUMENTORDERCOMMRATE            (ET_BASE + 59)
#define ET_RSPQRYSECAGENTTRADINGACCOUNT             (ET_BASE + 60)
#define ET_RSPQRYSECAGENTCHECKMODE                  (ET_BASE + 61)
#define ET_RSPQRYSECAGENTTRADEINFO                  (ET_BASE + 62)
#define ET_RSPQRYOPTIONINSTRTRADECOST               (ET_BASE + 63)
#define ET_RSPQRYOPTIONINSTRCOMMRATE                (ET_BASE + 64)
#define ET_RSPQRYEXECORDER                          (ET_BASE + 65)
#define ET_RSPQRYFORQUOTE                           (ET_BASE + 66)
#define ET_RSPQRYQUOTE                              (ET_BASE + 67)
#define ET_RSPQRYOPTIONSELFCLOSE                    (ET_BASE + 68)
#define ET_RSPQRYINVESTUNIT                         (ET_BASE + 69)
#define ET_RSPQRYCOMBINSTRUMENTGUARD                (ET_BASE + 70)
#define ET_RSPQRYCOMBACTION                         (ET_BASE + 71)
#define ET_RSPQRYTRANSFERSERIAL                     (ET_BASE + 72)
#define ET_RSPQRYACCOUNTREGISTER                    (ET_BASE + 73)
#define ET_RSPERROR                                 (ET_BASE + 74)
#define ET_RTNORDER                                 (ET_BASE + 75)
#define ET_RTNTRADE                                 (ET_BASE + 76)
#define ET_ERRRTNORDERINSERT                        (ET_BASE + 77)
#define ET_ERRRTNORDERACTION                        (ET_BASE + 78)
#define ET_RTNINSTRUMENTSTATUS                      (ET_BASE + 79)
#define ET_RTNBULLETIN                              (ET_BASE + 80)
#define ET_RTNTRADINGNOTICE                         (ET_BASE + 81)
#define ET_RTNERRORCONDITIONALORDER                 (ET_BASE + 82)
#define ET_RTNEXECORDER                             (ET_BASE + 83)
#define ET_ERRRTNEXECORDERINSERT                    (ET_BASE + 84)
#define ET_ERRRTNEXECORDERACTION                    (ET_BASE + 85)
#define ET_ERRRTNFORQUOTEINSERT                     (ET_BASE + 86)
#define ET_RTNQUOTE                                 (ET_BASE + 87)
#define ET_ERRRTNQUOTEINSERT                        (ET_BASE + 88)
#define ET_ERRRTNQUOTEACTION                        (ET_BASE + 89)
#define ET_RTNFORQUOTERSP                           (ET_BASE + 90)
#define ET_RTNCFMMCTRADINGACCOUNTTOKEN              (ET_BASE + 91)
#define ET_ERRRTNBATCHORDERACTION                   (ET_BASE + 92)
#define ET_RTNOPTIONSELFCLOSE                       (ET_BASE + 93)
#define ET_ERRRTNOPTIONSELFCLOSEINSERT              (ET_BASE + 94)
#define ET_ERRRTNOPTIONSELFCLOSEACTION              (ET_BASE + 95)
#define ET_RTNCOMBACTION                            (ET_BASE + 96)
#define ET_ERRRTNCOMBACTIONINSERT                   (ET_BASE + 97)
#define ET_RSPQRYCONTRACTBANK                       (ET_BASE + 98)
#define ET_RSPQRYPARKEDORDER                        (ET_BASE + 99)
#define ET_RSPQRYPARKEDORDERACTION                  (ET_BASE + 100)
#define ET_RSPQRYTRADINGNOTICE                      (ET_BASE + 101)
#define ET_RSPQRYBROKERTRADINGPARAMS                (ET_BASE + 102)
#define ET_RSPQRYBROKERTRADINGALGOS                 (ET_BASE + 103)
#define ET_RSPQUERYCFMMCTRADINGACCOUNTTOKEN         (ET_BASE + 104)
#define ET_RTNFROMBANKTOFUTUREBYBANK                (ET_BASE + 105)
#define ET_RTNFROMFUTURETOBANKBYBANK                (ET_BASE + 106)
#define ET_RTNREPEALFROMBANKTOFUTUREBYBANK          (ET_BASE + 107)
#define ET_RTNREPEALFROMFUTURETOBANKBYBANK          (ET_BASE + 108)
#define ET_RTNFROMBANKTOFUTUREBYFUTURE              (ET_BASE + 109)
#define ET_RTNFROMFUTURETOBANKBYFUTURE              (ET_BASE + 110)
#define ET_RTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL  (ET_BASE + 111)
#define ET_RTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL  (ET_BASE + 112)
#define ET_RTNQUERYBANKBALANCEBYFUTURE              (ET_BASE + 113)
#define ET_ERRRTNBANKTOFUTUREBYFUTURE               (ET_BASE + 114)
#define ET_ERRRTNFUTURETOBANKBYFUTURE               (ET_BASE + 115)
#define ET_ERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL   (ET_BASE + 116)
#define ET_ERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL   (ET_BASE + 117)
#define ET_ERRRTNQUERYBANKBALANCEBYFUTURE           (ET_BASE + 118)
#define ET_RTNREPEALFROMBANKTOFUTUREBYFUTURE        (ET_BASE + 119)
#define ET_RTNREPEALFROMFUTURETOBANKBYFUTURE        (ET_BASE + 120)
#define ET_RSPFROMBANKTOFUTUREBYFUTURE              (ET_BASE + 121)
#define ET_RSPFROMFUTURETOBANKBYFUTURE              (ET_BASE + 122)
#define ET_RSPQUERYBANKACCOUNTMONEYBYFUTURE         (ET_BASE + 123)
#define ET_RTNOPENACCOUNTBYBANK                     (ET_BASE + 124)
#define ET_RTNCANCELACCOUNTBYBANK                   (ET_BASE + 125)
#define ET_RTNCHANGEACCOUNTBYBANK                   (ET_BASE + 126)
#define ET_RSPQRYCLASSIFIEDINSTRUMENT               (ET_BASE + 127)
#define ET_RSPQRYCOMBPROMOTIONPARAM                 (ET_BASE + 128)
#define ET_RSPQRYRISKSETTLEINVSTPOSITION            (ET_BASE + 129)
#define ET_RSPQRYRISKSETTLEPRODUCTSTATUS            (ET_BASE + 130)

class TraderSpi : public CThostFtdcTraderSpi {
public:
  TraderSpi();
  virtual ~TraderSpi();

  int poll(Message **message, unsigned int millisec = UINT_MAX);
  void done(Message *message);
  void quit(int nCode = 0);

public:
  static const char *eventName(int event);

public:
  virtual void OnFrontConnected();
  virtual void OnFrontDisconnected(int nReason);

  virtual void OnHeartBeatWarning(int nTimeLapse);

  virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField *pQryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryTraderOffer(CThostFtdcTraderOfferField *pTraderOffer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);
  virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

  virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);

  virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);

  virtual void OnRtnBulletin(CThostFtdcBulletinField *pBulletin);

  virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);

  virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);

  virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder);

  virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo);

  virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote);

  virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

  virtual void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken);

  virtual void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo);

  virtual void OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose);

  virtual void OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo);

  virtual void OnRtnCombAction(CThostFtdcCombActionField *pCombAction);

  virtual void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo);

  virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer);
  virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer);

  virtual void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal);
  virtual void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal);

  virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer);
  virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer);

  virtual void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal);
  virtual void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal);
  virtual void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount);

  virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);
  virtual void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo);

  virtual void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal);
  virtual void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal);

  virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount);
  virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount);
  virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount);

  virtual void OnRspQryClassifiedInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryCombPromotionParam(CThostFtdcCombPromotionParamField *pCombPromotionParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspQryRiskSettleInvstPosition(CThostFtdcRiskSettleInvstPositionField *pRiskSettleInvstPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspQryRiskSettleProductStatus(CThostFtdcRiskSettleProductStatusField *pRiskSettleProductStatus, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

private:
  bool checkErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

private:
  MessageQueue _msgq;
};

#endif /* __TRADERSPI_H__ */
