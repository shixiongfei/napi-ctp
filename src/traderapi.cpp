/*
 * traderapi.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "traderapi.h"
#include "tradermsg.h"
#include "traderspi.h"
#include <string.h>
#include <map>
#include <string>
#include <functional>

typedef struct Trader {
  napi_env env;
  napi_ref wrapper;
  uv_thread_t thread;
  TraderSpi *spi;
  CThostFtdcTraderApi *api;
  std::map<std::string, napi_threadsafe_function> tsfns;
} Trader;

static napi_value getApiVersion(napi_env env, napi_callback_info info) {
  napi_value jsthis, version;
  Trader *trader;

  CHECK(napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));
  CHECK(napi_create_string_utf8(env, trader->api->GetApiVersion(), NAPI_AUTO_LENGTH, &version));

  return version;
}

static napi_value getTradingDay(napi_env env, napi_callback_info info) {
  napi_value jsthis, tradingDay;
  Trader *trader;

  CHECK(napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));
  CHECK(napi_create_string_utf8(env, trader->api->GetTradingDay(), NAPI_AUTO_LENGTH, &tradingDay));

  return tradingDay;
}

static napi_value callRequestFunc(napi_env env, napi_callback_info info, const std::function<int(Trader*, napi_value)> &func) {
  size_t argc = 1;
  int result;
  napi_value object, jsthis, retval;
  Trader *trader;

  CHECK(napi_get_cb_info(env, info, &argc, &object, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  CHECK(checkIsObject(env, object));

  result = func(trader, object);
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value reqAuthenticate(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcReqAuthenticateField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, UserProductInfo));
    CHECK(GetObjectString(env, object, req, AuthCode));
    CHECK(GetObjectString(env, object, req, AppID));

    return trader->api->ReqAuthenticate(&req, sequenceId());
  });
}

static napi_value reqUserLogin(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcReqUserLoginField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, TradingDay));
    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, Password));
    CHECK(GetObjectString(env, object, req, UserProductInfo));
    CHECK(GetObjectString(env, object, req, InterfaceProductInfo));
    CHECK(GetObjectString(env, object, req, ProtocolInfo));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, OneTimePassword));
    CHECK(GetObjectString(env, object, req, LoginRemark));
    CHECK(GetObjectInt32(env, object, req, ClientIPPort));
    CHECK(GetObjectString(env, object, req, ClientIPAddress));

    return trader->api->ReqUserLogin(&req, sequenceId());
  });
}

static napi_value reqUserLogout(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcUserLogoutField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, UserID));

    return trader->api->ReqUserLogout(&req, sequenceId());
  });
}

static napi_value reqUserPasswordUpdate(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcUserPasswordUpdateField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, OldPassword));
    CHECK(GetObjectString(env, object, req, NewPassword));

    return trader->api->ReqUserPasswordUpdate(&req, sequenceId());
  });
}

static napi_value reqTradingAccountPasswordUpdate(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcTradingAccountPasswordUpdateField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, OldPassword));
    CHECK(GetObjectString(env, object, req, NewPassword));
    CHECK(GetObjectString(env, object, req, CurrencyID));

    return trader->api->ReqTradingAccountPasswordUpdate(&req, sequenceId());
  });
}

static napi_value reqUserAuthMethod(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcReqUserAuthMethodField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, TradingDay));
    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, UserID));

    return trader->api->ReqUserAuthMethod(&req, sequenceId());
  });
}

static napi_value reqGenUserCaptcha(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcReqGenUserCaptchaField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, TradingDay));
    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, UserID));

    return trader->api->ReqGenUserCaptcha(&req, sequenceId());
  });
}

static napi_value reqGenUserText(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcReqGenUserTextField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, TradingDay));
    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, UserID));

    return trader->api->ReqGenUserText(&req, sequenceId());
  });
}

static napi_value reqUserLoginWithCaptcha(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcReqUserLoginWithCaptchaField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, TradingDay));
    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, Password));
    CHECK(GetObjectString(env, object, req, UserProductInfo));
    CHECK(GetObjectString(env, object, req, InterfaceProductInfo));
    CHECK(GetObjectString(env, object, req, ProtocolInfo));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, LoginRemark));
    CHECK(GetObjectString(env, object, req, Captcha));
    CHECK(GetObjectInt32(env, object, req, ClientIPPort));
    CHECK(GetObjectString(env, object, req, ClientIPAddress));

    return trader->api->ReqUserLoginWithCaptcha(&req, sequenceId());
  });
}

static napi_value reqUserLoginWithText(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcReqUserLoginWithTextField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, TradingDay));
    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, Password));
    CHECK(GetObjectString(env, object, req, UserProductInfo));
    CHECK(GetObjectString(env, object, req, InterfaceProductInfo));
    CHECK(GetObjectString(env, object, req, ProtocolInfo));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, LoginRemark));
    CHECK(GetObjectString(env, object, req, Text));
    CHECK(GetObjectInt32(env, object, req, ClientIPPort));
    CHECK(GetObjectString(env, object, req, ClientIPAddress));

    return trader->api->ReqUserLoginWithText(&req, sequenceId());
  });
}

static napi_value reqUserLoginWithOTP(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcReqUserLoginWithOTPField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, TradingDay));
    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, Password));
    CHECK(GetObjectString(env, object, req, UserProductInfo));
    CHECK(GetObjectString(env, object, req, InterfaceProductInfo));
    CHECK(GetObjectString(env, object, req, ProtocolInfo));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, LoginRemark));
    CHECK(GetObjectString(env, object, req, OTPPassword));
    CHECK(GetObjectInt32(env, object, req, ClientIPPort));
    CHECK(GetObjectString(env, object, req, ClientIPAddress));

    return trader->api->ReqUserLoginWithOTP(&req, sequenceId());
  });
}

static napi_value reqOrderInsert(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcInputOrderField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, OrderRef));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectChar(env, object, req, OrderPriceType));
    CHECK(GetObjectChar(env, object, req, Direction));
    CHECK(GetObjectString(env, object, req, CombOffsetFlag));
    CHECK(GetObjectString(env, object, req, CombHedgeFlag));
    CHECK(GetObjectDouble(env, object, req, LimitPrice));
    CHECK(GetObjectInt32(env, object, req, VolumeTotalOriginal));
    CHECK(GetObjectChar(env, object, req, TimeCondition));
    CHECK(GetObjectString(env, object, req, GTDDate));
    CHECK(GetObjectChar(env, object, req, VolumeCondition));
    CHECK(GetObjectInt32(env, object, req, MinVolume));
    CHECK(GetObjectChar(env, object, req, ContingentCondition));
    CHECK(GetObjectDouble(env, object, req, StopPrice));
    CHECK(GetObjectChar(env, object, req, ForceCloseReason));
    CHECK(GetObjectInt32(env, object, req, IsAutoSuspend));
    CHECK(GetObjectString(env, object, req, BusinessUnit));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectInt32(env, object, req, UserForceClose));
    CHECK(GetObjectInt32(env, object, req, IsSwapOrder));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, CurrencyID));
    CHECK(GetObjectString(env, object, req, ClientID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, IPAddress));

    return trader->api->ReqOrderInsert(&req, sequenceId());
  });
}

static napi_value reqParkedOrderInsert(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcParkedOrderField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, OrderRef));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectChar(env, object, req, OrderPriceType));
    CHECK(GetObjectChar(env, object, req, Direction));
    CHECK(GetObjectString(env, object, req, CombOffsetFlag));
    CHECK(GetObjectString(env, object, req, CombHedgeFlag));
    CHECK(GetObjectDouble(env, object, req, LimitPrice));
    CHECK(GetObjectInt32(env, object, req, VolumeTotalOriginal));
    CHECK(GetObjectChar(env, object, req, TimeCondition));
    CHECK(GetObjectString(env, object, req, GTDDate));
    CHECK(GetObjectChar(env, object, req, VolumeCondition));
    CHECK(GetObjectInt32(env, object, req, MinVolume));
    CHECK(GetObjectChar(env, object, req, ContingentCondition));
    CHECK(GetObjectDouble(env, object, req, StopPrice));
    CHECK(GetObjectChar(env, object, req, ForceCloseReason));
    CHECK(GetObjectInt32(env, object, req, IsAutoSuspend));
    CHECK(GetObjectString(env, object, req, BusinessUnit));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectInt32(env, object, req, UserForceClose));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, ParkedOrderID));
    CHECK(GetObjectChar(env, object, req, UserType));
    CHECK(GetObjectChar(env, object, req, Status));
    CHECK(GetObjectInt32(env, object, req, ErrorID));
    CHECK(GetObjectString(env, object, req, ErrorMsg));
    CHECK(GetObjectInt32(env, object, req, IsSwapOrder));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, CurrencyID));
    CHECK(GetObjectString(env, object, req, ClientID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, IPAddress));

    return trader->api->ReqParkedOrderInsert(&req, sequenceId());
  });
}

static napi_value reqParkedOrderAction(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcParkedOrderActionField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectInt32(env, object, req, OrderActionRef));
    CHECK(GetObjectString(env, object, req, OrderRef));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectInt32(env, object, req, FrontID));
    CHECK(GetObjectInt32(env, object, req, SessionID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, OrderSysID));
    CHECK(GetObjectChar(env, object, req, ActionFlag));
    CHECK(GetObjectDouble(env, object, req, LimitPrice));
    CHECK(GetObjectInt32(env, object, req, VolumeChange));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, ParkedOrderActionID));
    CHECK(GetObjectChar(env, object, req, UserType));
    CHECK(GetObjectChar(env, object, req, Status));
    CHECK(GetObjectInt32(env, object, req, ErrorID));
    CHECK(GetObjectString(env, object, req, ErrorMsg));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, IPAddress));

    return trader->api->ReqParkedOrderAction(&req, sequenceId());
  });
}

static napi_value reqOrderAction(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcInputOrderActionField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectInt32(env, object, req, OrderActionRef));
    CHECK(GetObjectString(env, object, req, OrderRef));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectInt32(env, object, req, FrontID));
    CHECK(GetObjectInt32(env, object, req, SessionID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, OrderSysID));
    CHECK(GetObjectChar(env, object, req, ActionFlag));
    CHECK(GetObjectDouble(env, object, req, LimitPrice));
    CHECK(GetObjectInt32(env, object, req, VolumeChange));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, IPAddress));

    return trader->api->ReqOrderAction(&req, sequenceId());
  });
}

static napi_value reqQryMaxOrderVolume(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryMaxOrderVolumeField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectChar(env, object, req, Direction));
    CHECK(GetObjectChar(env, object, req, OffsetFlag));
    CHECK(GetObjectChar(env, object, req, HedgeFlag));
    CHECK(GetObjectInt32(env, object, req, MaxVolume));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryMaxOrderVolume(&req, sequenceId());
  });
}

static napi_value reqSettlementInfoConfirm(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcSettlementInfoConfirmField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ConfirmDate));
    CHECK(GetObjectString(env, object, req, ConfirmTime));
    CHECK(GetObjectInt32(env, object, req, SettlementID));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, CurrencyID));

    return trader->api->ReqSettlementInfoConfirm(&req, sequenceId());
  });
}

static napi_value reqRemoveParkedOrder(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcRemoveParkedOrderField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ParkedOrderID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));

    return trader->api->ReqRemoveParkedOrder(&req, sequenceId());
  });
}

static napi_value reqRemoveParkedOrderAction(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcRemoveParkedOrderActionField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ParkedOrderActionID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));

    return trader->api->ReqRemoveParkedOrderAction(&req, sequenceId());
  });
}

static napi_value reqExecOrderInsert(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcInputExecOrderField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExecOrderRef));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectInt32(env, object, req, Volume));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectString(env, object, req, BusinessUnit));
    CHECK(GetObjectChar(env, object, req, OffsetFlag));
    CHECK(GetObjectChar(env, object, req, HedgeFlag));
    CHECK(GetObjectChar(env, object, req, ActionType));
    CHECK(GetObjectChar(env, object, req, PosiDirection));
    CHECK(GetObjectChar(env, object, req, ReservePositionFlag));
    CHECK(GetObjectChar(env, object, req, CloseFlag));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, CurrencyID));
    CHECK(GetObjectString(env, object, req, ClientID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, IPAddress));

    return trader->api->ReqExecOrderInsert(&req, sequenceId());
  });
}

static napi_value reqExecOrderAction(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcInputExecOrderActionField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectInt32(env, object, req, ExecOrderActionRef));
    CHECK(GetObjectString(env, object, req, ExecOrderRef));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectInt32(env, object, req, FrontID));
    CHECK(GetObjectInt32(env, object, req, SessionID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, ExecOrderSysID));
    CHECK(GetObjectChar(env, object, req, ActionFlag));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, IPAddress));

    return trader->api->ReqExecOrderAction(&req, sequenceId());
  });
}

static napi_value reqForQuoteInsert(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcInputForQuoteField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ForQuoteRef));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, IPAddress));

    return trader->api->ReqForQuoteInsert(&req, sequenceId());
  });
}

static napi_value reqQuoteInsert(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcInputQuoteField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, QuoteRef));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectDouble(env, object, req, AskPrice));
    CHECK(GetObjectDouble(env, object, req, BidPrice));
    CHECK(GetObjectInt32(env, object, req, AskVolume));
    CHECK(GetObjectInt32(env, object, req, BidVolume));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectString(env, object, req, BusinessUnit));
    CHECK(GetObjectChar(env, object, req, AskOffsetFlag));
    CHECK(GetObjectChar(env, object, req, BidOffsetFlag));
    CHECK(GetObjectChar(env, object, req, AskHedgeFlag));
    CHECK(GetObjectChar(env, object, req, BidHedgeFlag));
    CHECK(GetObjectString(env, object, req, AskOrderRef));
    CHECK(GetObjectString(env, object, req, BidOrderRef));
    CHECK(GetObjectString(env, object, req, ForQuoteSysID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, ClientID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, IPAddress));
    CHECK(GetObjectString(env, object, req, ReplaceSysID));

    return trader->api->ReqQuoteInsert(&req, sequenceId());
  });
}

static napi_value reqQuoteAction(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcInputQuoteActionField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectInt32(env, object, req, QuoteActionRef));
    CHECK(GetObjectString(env, object, req, QuoteRef));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectInt32(env, object, req, FrontID));
    CHECK(GetObjectInt32(env, object, req, SessionID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, QuoteSysID));
    CHECK(GetObjectChar(env, object, req, ActionFlag));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, ClientID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, IPAddress));

    return trader->api->ReqQuoteAction(&req, sequenceId());
  });
}

static napi_value reqBatchOrderAction(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcInputBatchOrderActionField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectInt32(env, object, req, OrderActionRef));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectInt32(env, object, req, FrontID));
    CHECK(GetObjectInt32(env, object, req, SessionID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, IPAddress));

    return trader->api->ReqBatchOrderAction(&req, sequenceId());
  });
}

static napi_value reqOptionSelfCloseInsert(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcInputOptionSelfCloseField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, OptionSelfCloseRef));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectInt32(env, object, req, Volume));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectString(env, object, req, BusinessUnit));
    CHECK(GetObjectChar(env, object, req, HedgeFlag));
    CHECK(GetObjectChar(env, object, req, OptSelfCloseFlag));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, CurrencyID));
    CHECK(GetObjectString(env, object, req, ClientID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, IPAddress));

    return trader->api->ReqOptionSelfCloseInsert(&req, sequenceId());
  });
}

static napi_value reqOptionSelfCloseAction(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcInputOptionSelfCloseActionField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectInt32(env, object, req, OptionSelfCloseActionRef));
    CHECK(GetObjectString(env, object, req, OptionSelfCloseRef));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectInt32(env, object, req, FrontID));
    CHECK(GetObjectInt32(env, object, req, SessionID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, OptionSelfCloseSysID));
    CHECK(GetObjectChar(env, object, req, ActionFlag));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, IPAddress));

    return trader->api->ReqOptionSelfCloseAction(&req, sequenceId());
  });
}

static napi_value reqCombActionInsert(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcInputCombActionField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, CombActionRef));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectChar(env, object, req, Direction));
    CHECK(GetObjectInt32(env, object, req, Volume));
    CHECK(GetObjectChar(env, object, req, CombDirection));
    CHECK(GetObjectChar(env, object, req, HedgeFlag));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, MacAddress));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectInt32(env, object, req, FrontID));
    CHECK(GetObjectInt32(env, object, req, SessionID));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, IPAddress));

    return trader->api->ReqCombActionInsert(&req, sequenceId());
  });
}

static napi_value reqQryOrder(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryOrderField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, OrderSysID));
    CHECK(GetObjectString(env, object, req, InsertTimeStart));
    CHECK(GetObjectString(env, object, req, InsertTimeEnd));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryOrder(&req, sequenceId());
  });
}

static napi_value reqQryTrade(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryTradeField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, TradeID));
    CHECK(GetObjectString(env, object, req, TradeTimeStart));
    CHECK(GetObjectString(env, object, req, TradeTimeEnd));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryTrade(&req, sequenceId());
  });
}

static napi_value reqQryInvestorPosition(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryInvestorPositionField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryInvestorPosition(&req, sequenceId());
  });
}

static napi_value reqQryTradingAccount(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryTradingAccountField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, CurrencyID));
    CHECK(GetObjectChar(env, object, req, BizType));
    CHECK(GetObjectString(env, object, req, AccountID));

    return trader->api->ReqQryTradingAccount(&req, sequenceId());
  });
}

static napi_value reqQryInvestor(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryInvestorField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));

    return trader->api->ReqQryInvestor(&req, sequenceId());
  });
}

static napi_value reqQryTradingCode(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryTradingCodeField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, ClientID));
    CHECK(GetObjectChar(env, object, req, ClientIDType));
    CHECK(GetObjectString(env, object, req, InvestUnitID));

    return trader->api->ReqQryTradingCode(&req, sequenceId());
  });
}

static napi_value reqQryInstrumentMarginRate(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryInstrumentMarginRateField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectChar(env, object, req, HedgeFlag));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryInstrumentMarginRate(&req, sequenceId());
  });
}

static napi_value reqQryInstrumentCommissionRate(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryInstrumentCommissionRateField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryInstrumentCommissionRate(&req, sequenceId());
  });
}

static napi_value reqQryExchange(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryExchangeField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, ExchangeID));

    return trader->api->ReqQryExchange(&req, sequenceId());
  });
}

static napi_value reqQryProduct(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryProductField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectChar(env, object, req, ProductClass));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, ProductID));

    return trader->api->ReqQryProduct(&req, sequenceId());
  });
}

static napi_value reqQryInstrument(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryInstrumentField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, ExchangeInstID));
    CHECK(GetObjectString(env, object, req, ProductID));

    return trader->api->ReqQryInstrument(&req, sequenceId());
  });
}

static napi_value reqQryDepthMarketData(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryDepthMarketDataField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryDepthMarketData(&req, sequenceId());
  });
}

static napi_value reqQryTraderOffer(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryTraderOfferField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, ParticipantID));
    CHECK(GetObjectString(env, object, req, TraderID));

    return trader->api->ReqQryTraderOffer(&req, sequenceId());
  });
}

static napi_value reqQrySettlementInfo(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQrySettlementInfoField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, TradingDay));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, CurrencyID));

    return trader->api->ReqQrySettlementInfo(&req, sequenceId());
  });
}

static napi_value reqQryTransferBank(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryTransferBankField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BankID));
    CHECK(GetObjectString(env, object, req, BankBrchID));

    return trader->api->ReqQryTransferBank(&req, sequenceId());
  });
}

static napi_value reqQryInvestorPositionDetail(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryInvestorPositionDetailField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryInvestorPositionDetail(&req, sequenceId());
  });
}

static napi_value reqQryNotice(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryNoticeField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));

    return trader->api->ReqQryNotice(&req, sequenceId());
  });
}

static napi_value reqQrySettlementInfoConfirm(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQrySettlementInfoConfirmField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, CurrencyID));

    return trader->api->ReqQrySettlementInfoConfirm(&req, sequenceId());
  });
}

static napi_value reqQryInvestorPositionCombineDetail(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryInvestorPositionCombineDetailField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, CombInstrumentID));

    return trader->api->ReqQryInvestorPositionCombineDetail(&req, sequenceId());
  });
}

static napi_value reqQryCFMMCTradingAccountKey(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryCFMMCTradingAccountKeyField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));

    return trader->api->ReqQryCFMMCTradingAccountKey(&req, sequenceId());
  });
}

static napi_value reqQryEWarrantOffset(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryEWarrantOffsetField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryEWarrantOffset(&req, sequenceId());
  });
}

static napi_value reqQryInvestorProductGroupMargin(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryInvestorProductGroupMarginField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectChar(env, object, req, HedgeFlag));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, ProductGroupID));

    return trader->api->ReqQryInvestorProductGroupMargin(&req, sequenceId());
  });
}

static napi_value reqQryExchangeMarginRate(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryExchangeMarginRateField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectChar(env, object, req, HedgeFlag));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryExchangeMarginRate(&req, sequenceId());
  });
}

static napi_value reqQryExchangeMarginRateAdjust(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryExchangeMarginRateAdjustField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectChar(env, object, req, HedgeFlag));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryExchangeMarginRateAdjust(&req, sequenceId());
  });
}

static napi_value reqQryExchangeRate(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryExchangeRateField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, FromCurrencyID));
    CHECK(GetObjectString(env, object, req, ToCurrencyID));

    return trader->api->ReqQryExchangeRate(&req, sequenceId());
  });
}

static napi_value reqQrySecAgentACIDMap(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQrySecAgentACIDMapField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, CurrencyID));

    return trader->api->ReqQrySecAgentACIDMap(&req, sequenceId());
  });
}

static napi_value reqQryProductExchRate(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryProductExchRateField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, ProductID));

    return trader->api->ReqQryProductExchRate(&req, sequenceId());
  });
}

static napi_value reqQryProductGroup(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryProductGroupField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, ProductID));

    return trader->api->ReqQryProductGroup(&req, sequenceId());
  });
}

static napi_value reqQryMMInstrumentCommissionRate(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryMMInstrumentCommissionRateField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryMMInstrumentCommissionRate(&req, sequenceId());
  });
}

static napi_value reqQryMMOptionInstrCommRate(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryMMOptionInstrCommRateField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryMMOptionInstrCommRate(&req, sequenceId());
  });
}

static napi_value reqQryInstrumentOrderCommRate(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryInstrumentOrderCommRateField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryInstrumentOrderCommRate(&req, sequenceId());
  });
}

static napi_value reqQrySecAgentTradingAccount(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryTradingAccountField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, CurrencyID));
    CHECK(GetObjectChar(env, object, req, BizType));
    CHECK(GetObjectString(env, object, req, AccountID));

    return trader->api->ReqQrySecAgentTradingAccount(&req, sequenceId());
  });
}

static napi_value reqQrySecAgentCheckMode(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQrySecAgentCheckModeField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));

    return trader->api->ReqQrySecAgentCheckMode(&req, sequenceId());
  });
}

static napi_value reqQrySecAgentTradeInfo(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQrySecAgentTradeInfoField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, BrokerSecAgentID));

    return trader->api->ReqQrySecAgentTradeInfo(&req, sequenceId());
  });
}

static napi_value reqQryOptionInstrTradeCost(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryOptionInstrTradeCostField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectChar(env, object, req, HedgeFlag));
    CHECK(GetObjectDouble(env, object, req, InputPrice));
    CHECK(GetObjectDouble(env, object, req, UnderlyingPrice));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryOptionInstrTradeCost(&req, sequenceId());
  });
}

static napi_value reqQryOptionInstrCommRate(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryOptionInstrCommRateField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryOptionInstrCommRate(&req, sequenceId());
  });
}

static napi_value reqQryExecOrder(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryExecOrderField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, ExecOrderSysID));
    CHECK(GetObjectString(env, object, req, InsertTimeStart));
    CHECK(GetObjectString(env, object, req, InsertTimeEnd));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryExecOrder(&req, sequenceId());
  });
}

static napi_value reqQryForQuote(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryForQuoteField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InsertTimeStart));
    CHECK(GetObjectString(env, object, req, InsertTimeEnd));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryForQuote(&req, sequenceId());
  });
}

static napi_value reqQryQuote(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryQuoteField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, QuoteSysID));
    CHECK(GetObjectString(env, object, req, InsertTimeStart));
    CHECK(GetObjectString(env, object, req, InsertTimeEnd));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryQuote(&req, sequenceId());
  });
}

static napi_value reqQryOptionSelfClose(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryOptionSelfCloseField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, OptionSelfCloseSysID));
    CHECK(GetObjectString(env, object, req, InsertTimeStart));
    CHECK(GetObjectString(env, object, req, InsertTimeEnd));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryOptionSelfClose(&req, sequenceId());
  });
}

static napi_value reqQryInvestUnit(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryInvestUnitField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));

    return trader->api->ReqQryInvestUnit(&req, sequenceId());
  });
}

static napi_value reqQryCombInstrumentGuard(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryCombInstrumentGuardField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryCombInstrumentGuard(&req, sequenceId());
  });
}

static napi_value reqQryCombAction(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryCombActionField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryCombAction(&req, sequenceId());
  });
}

static napi_value reqQryTransferSerial(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryTransferSerialField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, BankID));
    CHECK(GetObjectString(env, object, req, CurrencyID));

    return trader->api->ReqQryTransferSerial(&req, sequenceId());
  });
}

static napi_value reqQryAccountregister(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryAccountregisterField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, BankID));
    CHECK(GetObjectString(env, object, req, BankBranchID));
    CHECK(GetObjectString(env, object, req, CurrencyID));

    return trader->api->ReqQryAccountregister(&req, sequenceId());
  });
}

static napi_value reqQryContractBank(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryContractBankField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, BankID));
    CHECK(GetObjectString(env, object, req, BankBrchID));

    return trader->api->ReqQryContractBank(&req, sequenceId());
  });
}

static napi_value reqQryParkedOrder(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryParkedOrderField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryParkedOrder(&req, sequenceId());
  });
}

static napi_value reqQryParkedOrderAction(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryParkedOrderActionField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryParkedOrderAction(&req, sequenceId());
  });
}

static napi_value reqQryTradingNotice(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryTradingNoticeField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));

    return trader->api->ReqQryTradingNotice(&req, sequenceId());
  });
}

static napi_value reqQryBrokerTradingParams(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryBrokerTradingParamsField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, CurrencyID));
    CHECK(GetObjectString(env, object, req, AccountID));

    return trader->api->ReqQryBrokerTradingParams(&req, sequenceId());
  });
}

static napi_value reqQryBrokerTradingAlgos(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryBrokerTradingAlgosField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryBrokerTradingAlgos(&req, sequenceId());
  });
}

static napi_value reqQueryCFMMCTradingAccountToken(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQueryCFMMCTradingAccountTokenField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, InvestUnitID));

    return trader->api->ReqQueryCFMMCTradingAccountToken(&req, sequenceId());
  });
}

static napi_value reqFromBankToFutureByFuture(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcReqTransferField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, TradeCode));
    CHECK(GetObjectString(env, object, req, BankID));
    CHECK(GetObjectString(env, object, req, BankBranchID));
    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, BrokerBranchID));
    CHECK(GetObjectString(env, object, req, TradeDate));
    CHECK(GetObjectString(env, object, req, TradeTime));
    CHECK(GetObjectString(env, object, req, BankSerial));
    CHECK(GetObjectString(env, object, req, TradingDay));
    CHECK(GetObjectInt32(env, object, req, PlateSerial));
    CHECK(GetObjectChar(env, object, req, LastFragment));
    CHECK(GetObjectInt32(env, object, req, SessionID));
    CHECK(GetObjectString(env, object, req, CustomerName));
    CHECK(GetObjectChar(env, object, req, IdCardType));
    CHECK(GetObjectString(env, object, req, IdentifiedCardNo));
    CHECK(GetObjectChar(env, object, req, CustType));
    CHECK(GetObjectString(env, object, req, BankAccount));
    CHECK(GetObjectString(env, object, req, BankPassWord));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, Password));
    CHECK(GetObjectInt32(env, object, req, InstallID));
    CHECK(GetObjectInt32(env, object, req, FutureSerial));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectChar(env, object, req, VerifyCertNoFlag));
    CHECK(GetObjectString(env, object, req, CurrencyID));
    CHECK(GetObjectDouble(env, object, req, TradeAmount));
    CHECK(GetObjectDouble(env, object, req, FutureFetchAmount));
    CHECK(GetObjectChar(env, object, req, FeePayFlag));
    CHECK(GetObjectDouble(env, object, req, CustFee));
    CHECK(GetObjectDouble(env, object, req, BrokerFee));
    CHECK(GetObjectString(env, object, req, Message));
    CHECK(GetObjectString(env, object, req, Digest));
    CHECK(GetObjectChar(env, object, req, BankAccType));
    CHECK(GetObjectString(env, object, req, DeviceID));
    CHECK(GetObjectChar(env, object, req, BankSecuAccType));
    CHECK(GetObjectString(env, object, req, BrokerIDByBank));
    CHECK(GetObjectString(env, object, req, BankSecuAcc));
    CHECK(GetObjectChar(env, object, req, BankPwdFlag));
    CHECK(GetObjectChar(env, object, req, SecuPwdFlag));
    CHECK(GetObjectString(env, object, req, OperNo));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectInt32(env, object, req, TID));
    CHECK(GetObjectChar(env, object, req, TransferStatus));
    CHECK(GetObjectString(env, object, req, LongCustomerName));

    return trader->api->ReqFromBankToFutureByFuture(&req, sequenceId());
  });
}

static napi_value reqFromFutureToBankByFuture(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcReqTransferField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, TradeCode));
    CHECK(GetObjectString(env, object, req, BankID));
    CHECK(GetObjectString(env, object, req, BankBranchID));
    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, BrokerBranchID));
    CHECK(GetObjectString(env, object, req, TradeDate));
    CHECK(GetObjectString(env, object, req, TradeTime));
    CHECK(GetObjectString(env, object, req, BankSerial));
    CHECK(GetObjectString(env, object, req, TradingDay));
    CHECK(GetObjectInt32(env, object, req, PlateSerial));
    CHECK(GetObjectChar(env, object, req, LastFragment));
    CHECK(GetObjectInt32(env, object, req, SessionID));
    CHECK(GetObjectString(env, object, req, CustomerName));
    CHECK(GetObjectChar(env, object, req, IdCardType));
    CHECK(GetObjectString(env, object, req, IdentifiedCardNo));
    CHECK(GetObjectChar(env, object, req, CustType));
    CHECK(GetObjectString(env, object, req, BankAccount));
    CHECK(GetObjectString(env, object, req, BankPassWord));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, Password));
    CHECK(GetObjectInt32(env, object, req, InstallID));
    CHECK(GetObjectInt32(env, object, req, FutureSerial));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectChar(env, object, req, VerifyCertNoFlag));
    CHECK(GetObjectString(env, object, req, CurrencyID));
    CHECK(GetObjectDouble(env, object, req, TradeAmount));
    CHECK(GetObjectDouble(env, object, req, FutureFetchAmount));
    CHECK(GetObjectChar(env, object, req, FeePayFlag));
    CHECK(GetObjectDouble(env, object, req, CustFee));
    CHECK(GetObjectDouble(env, object, req, BrokerFee));
    CHECK(GetObjectString(env, object, req, Message));
    CHECK(GetObjectString(env, object, req, Digest));
    CHECK(GetObjectChar(env, object, req, BankAccType));
    CHECK(GetObjectString(env, object, req, DeviceID));
    CHECK(GetObjectChar(env, object, req, BankSecuAccType));
    CHECK(GetObjectString(env, object, req, BrokerIDByBank));
    CHECK(GetObjectString(env, object, req, BankSecuAcc));
    CHECK(GetObjectChar(env, object, req, BankPwdFlag));
    CHECK(GetObjectChar(env, object, req, SecuPwdFlag));
    CHECK(GetObjectString(env, object, req, OperNo));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectInt32(env, object, req, TID));
    CHECK(GetObjectChar(env, object, req, TransferStatus));
    CHECK(GetObjectString(env, object, req, LongCustomerName));

    return trader->api->ReqFromFutureToBankByFuture(&req, sequenceId());
  });
}

static napi_value reqQueryBankAccountMoneyByFuture(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcReqQueryAccountField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, TradeCode));
    CHECK(GetObjectString(env, object, req, BankID));
    CHECK(GetObjectString(env, object, req, BankBranchID));
    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, BrokerBranchID));
    CHECK(GetObjectString(env, object, req, TradeDate));
    CHECK(GetObjectString(env, object, req, TradeTime));
    CHECK(GetObjectString(env, object, req, BankSerial));
    CHECK(GetObjectString(env, object, req, TradingDay));
    CHECK(GetObjectInt32(env, object, req, PlateSerial));
    CHECK(GetObjectChar(env, object, req, LastFragment));
    CHECK(GetObjectInt32(env, object, req, SessionID));
    CHECK(GetObjectString(env, object, req, CustomerName));
    CHECK(GetObjectChar(env, object, req, IdCardType));
    CHECK(GetObjectString(env, object, req, IdentifiedCardNo));
    CHECK(GetObjectChar(env, object, req, CustType));
    CHECK(GetObjectString(env, object, req, BankAccount));
    CHECK(GetObjectString(env, object, req, BankPassWord));
    CHECK(GetObjectString(env, object, req, AccountID));
    CHECK(GetObjectString(env, object, req, Password));
    CHECK(GetObjectInt32(env, object, req, FutureSerial));
    CHECK(GetObjectInt32(env, object, req, InstallID));
    CHECK(GetObjectString(env, object, req, UserID));
    CHECK(GetObjectChar(env, object, req, VerifyCertNoFlag));
    CHECK(GetObjectString(env, object, req, CurrencyID));
    CHECK(GetObjectString(env, object, req, Digest));
    CHECK(GetObjectChar(env, object, req, BankAccType));
    CHECK(GetObjectString(env, object, req, DeviceID));
    CHECK(GetObjectChar(env, object, req, BankSecuAccType));
    CHECK(GetObjectString(env, object, req, BrokerIDByBank));
    CHECK(GetObjectString(env, object, req, BankSecuAcc));
    CHECK(GetObjectChar(env, object, req, BankPwdFlag));
    CHECK(GetObjectChar(env, object, req, SecuPwdFlag));
    CHECK(GetObjectString(env, object, req, OperNo));
    CHECK(GetObjectInt32(env, object, req, RequestID));
    CHECK(GetObjectInt32(env, object, req, TID));
    CHECK(GetObjectString(env, object, req, LongCustomerName));

    return trader->api->ReqQueryBankAccountMoneyByFuture(&req, sequenceId());
  });
}

static napi_value reqQryClassifiedInstrument(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryClassifiedInstrumentField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, InstrumentID));
    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, ExchangeInstID));
    CHECK(GetObjectString(env, object, req, ProductID));
    CHECK(GetObjectChar(env, object, req, TradingType));
    CHECK(GetObjectChar(env, object, req, ClassType));

    return trader->api->ReqQryClassifiedInstrument(&req, sequenceId());
  });
}

static napi_value reqQryCombPromotionParam(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryCombPromotionParamField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, ExchangeID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryCombPromotionParam(&req, sequenceId());
  });
}

static napi_value reqQryRiskSettleInvstPosition(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryRiskSettleInvstPositionField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, InvestorID));
    CHECK(GetObjectString(env, object, req, InstrumentID));

    return trader->api->ReqQryRiskSettleInvstPosition(&req, sequenceId());
  });
}

static napi_value reqQryRiskSettleProductStatus(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](Trader *trader, napi_value object) {
    CThostFtdcQryRiskSettleProductStatusField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, ProductID));

    return trader->api->ReqQryRiskSettleProductStatus(&req, sequenceId());
  });
}

static bool processMessage(Trader *trader, const Message *message) {
  const char *eventName = TraderSpi::eventName(message->event);

  if (!eventName) {
    fprintf(stderr, "<Trader> Unknown message event %d\n", message->event);
    return true;
  }

  auto iter = trader->tsfns.find(eventName);

  if (iter != trader->tsfns.end()) {
    napi_threadsafe_function tsfn = iter->second;
    CHECK(napi_call_threadsafe_function(tsfn, (void *)message, napi_tsfn_blocking));
  }

  return ET_QUIT != message->event;
}

static void processThread(void *data) {
  Trader *trader = (Trader *)data;
  Message *message;
  bool isRunning = true;

  while (isRunning) {
    if (QUEUE_SUCCESS != trader->spi->poll(&message))
      continue;

    isRunning = processMessage(trader, message);
  }
}

static void traderFree(napi_env env, Trader *trader) {
  for (auto it = trader->tsfns.begin(); it != trader->tsfns.end(); ++it)
    napi_unref_threadsafe_function(env, it->second);

  trader->tsfns.clear();
  napi_delete_reference(trader->env, trader->wrapper);

  if (trader->api)
    trader->api->Release();

  if (trader->spi)
    delete trader->spi;

  delete trader;
}

static void callJs(napi_env env, napi_value js_cb, void *context, void *data) {
  Trader *trader = (Trader *)context;
  Message *message = (Message *)data;
  int event = message->event;
  napi_value undefined, argv[2];

  CHECK(napi_get_undefined(env, &undefined));
  CHECK(getTraderMessageValue(env, message, &argv[0]));
  CHECK(getTraderMessageOptions(env, message, &argv[1]));
  CHECK(napi_call_function(env, undefined, js_cb, 2, argv, nullptr));

  trader->spi->done(message);

  if (ET_QUIT == event)
    traderFree(env, trader);
}

static napi_value on(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_function};
  size_t argc = 2;
  napi_value argv[2], jsthis;
  napi_threadsafe_function tsfn;
  Trader *trader;
  char fname[64];

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  CHECK(checkValueTypes(env, argc, argv, types));

  CHECK(napi_create_threadsafe_function(env, argv[1], nullptr, argv[0], 0, 1, nullptr, nullptr, trader, callJs, &tsfn));
  CHECK(napi_ref_threadsafe_function(env, tsfn));

  CHECK(napi_get_value_string_utf8(env, argv[0], fname, sizeof(fname), nullptr));

  if (trader->tsfns.find(fname) != trader->tsfns.end())
    CHECK(napi_unref_threadsafe_function(env, trader->tsfns[fname]));

  trader->tsfns[fname] = tsfn;

  return jsthis;
}

static void traderDestructor(napi_env env, void *data, void *hint) {
  Trader *trader = (Trader *)data;

  if (!trader)
    return;

  if (trader->spi) {
    trader->spi->quit();
    uv_thread_join(&trader->thread);
  }

  if (trader->tsfns.find(TraderSpi::eventName(ET_QUIT)) == trader->tsfns.end())
    traderFree(env, trader);
}

static napi_value traderNew(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_string};
  size_t argc = 2;
  napi_value target, argv[2], jsthis;
  Trader *trader;
  char flowPath[260], frontAddr[64];

  CHECK(napi_get_new_target(env, info, &target));

  if (!target)
    return nullptr;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));

  CHECK(checkValueTypes(env, argc, argv, types));

  CHECK(napi_get_value_string_utf8(env, argv[0], flowPath, sizeof(flowPath), nullptr));
  CHECK(napi_get_value_string_utf8(env, argv[1], frontAddr, sizeof(frontAddr), nullptr));

  trader = new Trader();

  if (!trader) {
    napi_throw_error(env, nullptr, "Trader is out of memory");
    return nullptr;
  }

  trader->env = env;
  trader->spi = new TraderSpi();

  if (!trader->spi) {
    delete trader;
    napi_throw_error(env, nullptr, "Trader is out of memory");
    return nullptr;
  }

  if (0 != uv_thread_create(&trader->thread, processThread, trader)) {
    delete trader->spi;
    delete trader;
    napi_throw_error(env, nullptr, "Trader can not create thread");
    return nullptr;
  }

  trader->api = CThostFtdcTraderApi::CreateFtdcTraderApi(flowPath);

  if (!trader->api) {
    trader->spi->quit();
    uv_thread_join(&trader->thread);
    delete trader->spi;
    delete trader;
    napi_throw_error(env, nullptr, "Trader is out of memory");
    return nullptr;
  }

  trader->api->RegisterSpi(trader->spi);
  trader->api->SubscribePublicTopic(THOST_TERT_QUICK);
  trader->api->SubscribePrivateTopic(THOST_TERT_QUICK);
  trader->api->RegisterFront(frontAddr);
  trader->api->Init();

  CHECK(napi_wrap(env, jsthis, (void *)trader, traderDestructor, nullptr, &trader->wrapper));

  return jsthis;
}

napi_status defineTrader(napi_env env, napi_ref *constructor) {
  napi_property_descriptor props[] = {
      DECLARE_NAPI_METHOD(getApiVersion),
      DECLARE_NAPI_METHOD(getTradingDay),
      DECLARE_NAPI_METHOD(reqAuthenticate),
      DECLARE_NAPI_METHOD(reqUserLogin),
      DECLARE_NAPI_METHOD(reqUserLogout),
      DECLARE_NAPI_METHOD(reqUserPasswordUpdate),
      DECLARE_NAPI_METHOD(reqTradingAccountPasswordUpdate),
      DECLARE_NAPI_METHOD(reqUserAuthMethod),
      DECLARE_NAPI_METHOD(reqGenUserCaptcha),
      DECLARE_NAPI_METHOD(reqGenUserText),
      DECLARE_NAPI_METHOD(reqUserLoginWithCaptcha),
      DECLARE_NAPI_METHOD(reqUserLoginWithText),
      DECLARE_NAPI_METHOD(reqUserLoginWithOTP),
      DECLARE_NAPI_METHOD(reqOrderInsert),
      DECLARE_NAPI_METHOD(reqParkedOrderInsert),
      DECLARE_NAPI_METHOD(reqParkedOrderAction),
      DECLARE_NAPI_METHOD(reqOrderAction),
      DECLARE_NAPI_METHOD(reqQryMaxOrderVolume),
      DECLARE_NAPI_METHOD(reqSettlementInfoConfirm),
      DECLARE_NAPI_METHOD(reqRemoveParkedOrder),
      DECLARE_NAPI_METHOD(reqRemoveParkedOrderAction),
      DECLARE_NAPI_METHOD(reqExecOrderInsert),
      DECLARE_NAPI_METHOD(reqExecOrderAction),
      DECLARE_NAPI_METHOD(reqForQuoteInsert),
      DECLARE_NAPI_METHOD(reqQuoteInsert),
      DECLARE_NAPI_METHOD(reqQuoteAction),
      DECLARE_NAPI_METHOD(reqBatchOrderAction),
      DECLARE_NAPI_METHOD(reqOptionSelfCloseInsert),
      DECLARE_NAPI_METHOD(reqOptionSelfCloseAction),
      DECLARE_NAPI_METHOD(reqCombActionInsert),
      DECLARE_NAPI_METHOD(reqQryOrder),
      DECLARE_NAPI_METHOD(reqQryTrade),
      DECLARE_NAPI_METHOD(reqQryInvestorPosition),
      DECLARE_NAPI_METHOD(reqQryTradingAccount),
      DECLARE_NAPI_METHOD(reqQryInvestor),
      DECLARE_NAPI_METHOD(reqQryTradingCode),
      DECLARE_NAPI_METHOD(reqQryInstrumentMarginRate),
      DECLARE_NAPI_METHOD(reqQryInstrumentCommissionRate),
      DECLARE_NAPI_METHOD(reqQryExchange),
      DECLARE_NAPI_METHOD(reqQryProduct),
      DECLARE_NAPI_METHOD(reqQryInstrument),
      DECLARE_NAPI_METHOD(reqQryDepthMarketData),
      DECLARE_NAPI_METHOD(reqQryTraderOffer),
      DECLARE_NAPI_METHOD(reqQrySettlementInfo),
      DECLARE_NAPI_METHOD(reqQryTransferBank),
      DECLARE_NAPI_METHOD(reqQryInvestorPositionDetail),
      DECLARE_NAPI_METHOD(reqQryNotice),
      DECLARE_NAPI_METHOD(reqQrySettlementInfoConfirm),
      DECLARE_NAPI_METHOD(reqQryInvestorPositionCombineDetail),
      DECLARE_NAPI_METHOD(reqQryCFMMCTradingAccountKey),
      DECLARE_NAPI_METHOD(reqQryEWarrantOffset),
      DECLARE_NAPI_METHOD(reqQryInvestorProductGroupMargin),
      DECLARE_NAPI_METHOD(reqQryExchangeMarginRate),
      DECLARE_NAPI_METHOD(reqQryExchangeMarginRateAdjust),
      DECLARE_NAPI_METHOD(reqQryExchangeRate),
      DECLARE_NAPI_METHOD(reqQrySecAgentACIDMap),
      DECLARE_NAPI_METHOD(reqQryProductExchRate),
      DECLARE_NAPI_METHOD(reqQryProductGroup),
      DECLARE_NAPI_METHOD(reqQryMMInstrumentCommissionRate),
      DECLARE_NAPI_METHOD(reqQryMMOptionInstrCommRate),
      DECLARE_NAPI_METHOD(reqQryInstrumentOrderCommRate),
      DECLARE_NAPI_METHOD(reqQrySecAgentTradingAccount),
      DECLARE_NAPI_METHOD(reqQrySecAgentCheckMode),
      DECLARE_NAPI_METHOD(reqQrySecAgentTradeInfo),
      DECLARE_NAPI_METHOD(reqQryOptionInstrTradeCost),
      DECLARE_NAPI_METHOD(reqQryOptionInstrCommRate),
      DECLARE_NAPI_METHOD(reqQryExecOrder),
      DECLARE_NAPI_METHOD(reqQryForQuote),
      DECLARE_NAPI_METHOD(reqQryQuote),
      DECLARE_NAPI_METHOD(reqQryOptionSelfClose),
      DECLARE_NAPI_METHOD(reqQryInvestUnit),
      DECLARE_NAPI_METHOD(reqQryCombInstrumentGuard),
      DECLARE_NAPI_METHOD(reqQryCombAction),
      DECLARE_NAPI_METHOD(reqQryTransferSerial),
      DECLARE_NAPI_METHOD(reqQryAccountregister),
      DECLARE_NAPI_METHOD(reqQryContractBank),
      DECLARE_NAPI_METHOD(reqQryParkedOrder),
      DECLARE_NAPI_METHOD(reqQryParkedOrderAction),
      DECLARE_NAPI_METHOD(reqQryTradingNotice),
      DECLARE_NAPI_METHOD(reqQryBrokerTradingParams),
      DECLARE_NAPI_METHOD(reqQryBrokerTradingAlgos),
      DECLARE_NAPI_METHOD(reqQueryCFMMCTradingAccountToken),
      DECLARE_NAPI_METHOD(reqFromBankToFutureByFuture),
      DECLARE_NAPI_METHOD(reqFromFutureToBankByFuture),
      DECLARE_NAPI_METHOD(reqQueryBankAccountMoneyByFuture),
      DECLARE_NAPI_METHOD(reqQryClassifiedInstrument),
      DECLARE_NAPI_METHOD(reqQryCombPromotionParam),
      DECLARE_NAPI_METHOD(reqQryRiskSettleInvstPosition),
      DECLARE_NAPI_METHOD(reqQryRiskSettleProductStatus),
      DECLARE_NAPI_METHOD(on),
  };
  return defineClass(env, "Trader", traderNew, arraysize(props), props, constructor);
}

napi_value createTrader(napi_env env, napi_callback_info info) {
  Constructors *constructors = getConstructors(env);
  return constructors ? createInstance(env, info, constructors->trader, 2) : nullptr;
}
