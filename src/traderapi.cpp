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
#include <map>
#include <stdlib.h>
#include <string>

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

static napi_value authenticate(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[5] = {napi_string, napi_string, napi_string, napi_string, napi_string};
  size_t argc = 5, len;
  int result;
  napi_value argv[5], jsthis, retval;
  Trader *trader;
  CThostFtdcReqAuthenticateField req;
  bool isTypesOk;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  CHECK(checkValueTypes(env, argc, argv, types, &isTypesOk));

  if (!isTypesOk)
    return nullptr;

  memset(&req, 0, sizeof(req));

  CHECK(napi_get_value_string_utf8(env, argv[0], req.BrokerID, sizeof(req.BrokerID), &len));
  CHECK(napi_get_value_string_utf8(env, argv[1], req.UserID, sizeof(req.UserID), &len));
  CHECK(napi_get_value_string_utf8(env, argv[2], req.UserProductInfo, sizeof(req.UserProductInfo), &len));
  CHECK(napi_get_value_string_utf8(env, argv[3], req.AuthCode, sizeof(req.AuthCode), &len));
  CHECK(napi_get_value_string_utf8(env, argv[4], req.AppID, sizeof(req.AppID), &len));

  result = trader->api->ReqAuthenticate(&req, sequenceId());
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value userLogin(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[3] = {napi_string, napi_string, napi_string};
  size_t argc = 3, len;
  int result;
  napi_value argv[3], jsthis, retval;
  Trader *trader;
  CThostFtdcReqUserLoginField req;
  bool isTypesOk;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  CHECK(checkValueTypes(env, argc, argv, types, &isTypesOk));

  if (!isTypesOk)
    return nullptr;

  memset(&req, 0, sizeof(req));

  CHECK(napi_get_value_string_utf8(env, argv[0], req.BrokerID, sizeof(req.BrokerID), &len));
  CHECK(napi_get_value_string_utf8(env, argv[1], req.UserID, sizeof(req.UserID), &len));
  CHECK(napi_get_value_string_utf8(env, argv[2], req.Password, sizeof(req.Password), &len));

  result = trader->api->ReqUserLogin(&req, sequenceId());
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value userLogout(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_string};
  size_t argc = 2, len;
  int result;
  napi_value argv[2], jsthis, retval;
  Trader *trader;
  CThostFtdcUserLogoutField req;
  bool isTypesOk;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  CHECK(checkValueTypes(env, argc, argv, types, &isTypesOk));

  if (!isTypesOk)
    return nullptr;

  memset(&req, 0, sizeof(req));

  CHECK(napi_get_value_string_utf8(env, argv[0], req.BrokerID, sizeof(req.BrokerID), &len));
  CHECK(napi_get_value_string_utf8(env, argv[1], req.UserID, sizeof(req.UserID), &len));

  result = trader->api->ReqUserLogout(&req, sequenceId());
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value userPasswordUpdate(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[4] = {napi_string, napi_string, napi_string, napi_string};
  size_t argc = 4, len;
  int result;
  napi_value argv[4], jsthis, retval;
  Trader *trader;
  CThostFtdcUserPasswordUpdateField req;
  bool isTypesOk;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  CHECK(checkValueTypes(env, argc, argv, types, &isTypesOk));

  if (!isTypesOk)
    return nullptr;

  memset(&req, 0, sizeof(req));

  CHECK(napi_get_value_string_utf8(env, argv[0], req.BrokerID, sizeof(req.BrokerID), &len));
  CHECK(napi_get_value_string_utf8(env, argv[1], req.UserID, sizeof(req.UserID), &len));
  CHECK(napi_get_value_string_utf8(env, argv[2], req.OldPassword, sizeof(req.OldPassword), &len));
  CHECK(napi_get_value_string_utf8(env, argv[3], req.NewPassword, sizeof(req.NewPassword), &len));

  result = trader->api->ReqUserPasswordUpdate(&req, sequenceId());
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value tradingAccountPasswordUpdate(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value userAuthMethod(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value genUserCaptcha(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value genUserText(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value userLoginWithCaptcha(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value userLoginWithText(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value userLoginWithOTP(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value orderInsert(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value parkedOrderInsert(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value parkedOrderAction(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value orderAction(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryMaxOrderVolume(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value settlementInfoConfirm(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_string};
  size_t argc = 2, len;
  int result;
  napi_value argv[2], jsthis, retval;
  Trader *trader;
  CThostFtdcSettlementInfoConfirmField req;
  bool isTypesOk;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  CHECK(checkValueTypes(env, argc, argv, types, &isTypesOk));

  if (!isTypesOk)
    return nullptr;

  memset(&req, 0, sizeof(req));

  CHECK(napi_get_value_string_utf8(env, argv[0], req.BrokerID, sizeof(req.BrokerID), &len));
  CHECK(napi_get_value_string_utf8(env, argv[1], req.InvestorID, sizeof(req.InvestorID), &len));

  result = trader->api->ReqSettlementInfoConfirm(&req, sequenceId());
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value removeParkedOrder(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value removeParkedOrderAction(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value execOrderInsert(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value execOrderAction(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value forQuoteInsert(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value quoteInsert(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value quoteAction(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value batchOrderAction(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value optionSelfCloseInsert(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value optionSelfCloseAction(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value combActionInsert(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryOrder(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_string};
  size_t argc = 2, len;
  int result;
  napi_value argv[2], jsthis, retval;
  Trader *trader;
  CThostFtdcQryOrderField req;
  bool isTypesOk;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  CHECK(checkValueTypes(env, argc, argv, types, &isTypesOk));

  if (!isTypesOk)
    return nullptr;

  memset(&req, 0, sizeof(req));

  CHECK(napi_get_value_string_utf8(env, argv[0], req.BrokerID, sizeof(req.BrokerID), &len));
  CHECK(napi_get_value_string_utf8(env, argv[1], req.InvestorID, sizeof(req.InvestorID), &len));

  result = trader->api->ReqQryOrder(&req, sequenceId());
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value qryTrade(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_string};
  size_t argc = 2, len;
  int result;
  napi_value argv[2], jsthis, retval;
  Trader *trader;
  CThostFtdcQryTradeField req;
  bool isTypesOk;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  CHECK(checkValueTypes(env, argc, argv, types, &isTypesOk));

  if (!isTypesOk)
    return nullptr;

  memset(&req, 0, sizeof(req));

  CHECK(napi_get_value_string_utf8(env, argv[0], req.BrokerID, sizeof(req.BrokerID), &len));
  CHECK(napi_get_value_string_utf8(env, argv[1], req.InvestorID, sizeof(req.InvestorID), &len));

  result = trader->api->ReqQryTrade(&req, sequenceId());
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value qryInvestorPosition(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_string};
  size_t argc = 2, len;
  int result;
  napi_value argv[2], jsthis, retval;
  Trader *trader;
  CThostFtdcQryInvestorPositionField req;
  bool isTypesOk;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  CHECK(checkValueTypes(env, argc, argv, types, &isTypesOk));

  if (!isTypesOk)
    return nullptr;

  memset(&req, 0, sizeof(req));

  CHECK(napi_get_value_string_utf8(env, argv[0], req.BrokerID, sizeof(req.BrokerID), &len));
  CHECK(napi_get_value_string_utf8(env, argv[1], req.InvestorID, sizeof(req.InvestorID), &len));

  result = trader->api->ReqQryInvestorPosition(&req, sequenceId());
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value qryTradingAccount(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_string};
  size_t argc = 2, len;
  int result;
  napi_value argv[2], jsthis, retval;
  Trader *trader;
  CThostFtdcQryTradingAccountField req;
  bool isTypesOk;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  CHECK(checkValueTypes(env, argc, argv, types, &isTypesOk));

  if (!isTypesOk)
    return nullptr;

  memset(&req, 0, sizeof(req));

  CHECK(napi_get_value_string_utf8(env, argv[0], req.BrokerID, sizeof(req.BrokerID), &len));
  CHECK(napi_get_value_string_utf8(env, argv[1], req.InvestorID, sizeof(req.InvestorID), &len));

  result = trader->api->ReqQryTradingAccount(&req, sequenceId());
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value qryInvestor(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryTradingCode(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryInstrumentMarginRate(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryInstrumentCommissionRate(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryExchange(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryProduct(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryInstrument(napi_env env, napi_callback_info info) {
  int result;
  napi_value jsthis, retval;
  Trader *trader;
  CThostFtdcQryInstrumentField req;

  CHECK(napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  memset(&req, 0, sizeof(req));

  result = trader->api->ReqQryInstrument(&req, sequenceId());
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value qryDepthMarketData(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryTraderOffer(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qrySettlementInfo(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryTransferBank(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryInvestorPositionDetail(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryNotice(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qrySettlementInfoConfirm(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryInvestorPositionCombineDetail(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryCFMMCTradingAccountKey(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryEWarrantOffset(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryInvestorProductGroupMargin(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryExchangeMarginRate(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryExchangeMarginRateAdjust(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryExchangeRate(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qrySecAgentACIDMap(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryProductExchRate(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryProductGroup(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryMMInstrumentCommissionRate(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryMMOptionInstrCommRate(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryInstrumentOrderCommRate(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qrySecAgentTradingAccount(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qrySecAgentCheckMode(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qrySecAgentTradeInfo(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryOptionInstrTradeCost(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryOptionInstrCommRate(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryExecOrder(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryForQuote(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryQuote(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryOptionSelfClose(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryInvestUnit(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryCombInstrumentGuard(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryCombAction(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryTransferSerial(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryAccountregister(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryContractBank(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryParkedOrder(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryParkedOrderAction(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryTradingNotice(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryBrokerTradingParams(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryBrokerTradingAlgos(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value queryCFMMCTradingAccountToken(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value fromBankToFutureByFuture(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value fromFutureToBankByFuture(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value queryBankAccountMoneyByFuture(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryClassifiedInstrument(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryCombPromotionParam(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryRiskSettleInvstPosition(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value qryRiskSettleProductStatus(napi_env env, napi_callback_info info) {
  return nullptr;
}

static bool processMessage(Trader *trader, const Message &message) {
  const char *eventName = TraderSpi::eventName(message.event);

  if (!eventName) {
    fprintf(stderr, "<Trader> Unknown message event %d\n", message.event);
    return true;
  }

  auto iter = trader->tsfns.find(eventName);

  if (iter != trader->tsfns.end()) {
    napi_threadsafe_function tsfn = iter->second;
    CHECK(napi_call_threadsafe_function(tsfn, (void *)&message, napi_tsfn_blocking));
  }

  return ET_QUIT != message.event;
}

static void processThread(void *data) {
  Trader *trader = (Trader *)data;
  Message message;
  bool isRunning = true;

  while (isRunning) {
    if (QUEUE_SUCCESS != trader->spi->poll(&message))
      continue;

    isRunning = processMessage(trader, message);
    trader->spi->done(message);
  }
}

static void callJs(napi_env env, napi_value js_cb, void *context, void *data) {
  // Trader *trader = (Trader *)context;
  Message *message = (Message *)data;
  napi_value undefined, argv;

  CHECK(napi_get_undefined(env, &undefined));
  CHECK(getTraderMessageValue(env, message, &argv));
  CHECK(napi_call_function(env, undefined, js_cb, 1, &argv, nullptr));
}

static napi_value on(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_function};
  size_t argc = 2, len;
  napi_value argv[2], jsthis;
  napi_threadsafe_function tsfn;
  Trader *trader;
  char fname[64];
  bool isTypesOk;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&trader));

  CHECK(checkValueTypes(env, argc, argv, types, &isTypesOk));

  if (!isTypesOk)
    return nullptr;

  CHECK(napi_create_threadsafe_function(env, argv[1], nullptr, argv[0], 0, 1, nullptr, nullptr, trader, callJs, &tsfn));
  CHECK(napi_ref_threadsafe_function(env, tsfn));

  CHECK(napi_get_value_string_utf8(env, argv[0], fname, sizeof(fname), &len));

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

  for (auto it = trader->tsfns.begin(); it != trader->tsfns.end(); ++it)
    napi_unref_threadsafe_function(env, it->second);

  trader->tsfns.clear();
  napi_delete_reference(trader->env, trader->wrapper);

  if (trader->spi)
    delete trader->spi;

  if (trader->api)
    trader->api->Release();

  delete trader;
}

static napi_value traderNew(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_string};
  size_t argc = 2, bytes;
  napi_value target, argv[2], jsthis;
  Trader *trader;
  char flowPath[260], frontAddr[64];
  bool isTypesOk;

  CHECK(napi_get_new_target(env, info, &target));

  if (!target)
    return nullptr;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));

  CHECK(checkValueTypes(env, argc, argv, types, &isTypesOk));

  if (!isTypesOk)
    return nullptr;

  CHECK(napi_get_value_string_utf8(env, argv[0], flowPath, sizeof(flowPath), &bytes));
  CHECK(napi_get_value_string_utf8(env, argv[1], frontAddr, sizeof(frontAddr), &bytes));

  trader = new Trader();

  if (!trader) {
    napi_throw_error(env, "OutOfMemory", "Trader is out of memory");
    return nullptr;
  }

  trader->env = env;
  trader->spi = new TraderSpi();

  if (!trader->spi) {
    delete trader;
    napi_throw_error(env, "OutOfMemory", "Trader is out of memory");
    return nullptr;
  }

  if (0 != uv_thread_create(&trader->thread, processThread, trader)) {
    delete trader->spi;
    delete trader;
    napi_throw_error(env, "ThreadError", "Trader can not create thread");
    return nullptr;
  }

  trader->api = CThostFtdcTraderApi::CreateFtdcTraderApi(flowPath);

  if (!trader->api) {
    trader->spi->quit();
    uv_thread_join(&trader->thread);
    delete trader->spi;
    delete trader;
    napi_throw_error(env, "OutOfMemory", "Trader is out of memory");
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
      DECLARE_NAPI_METHOD(authenticate),
      DECLARE_NAPI_METHOD(userLogin),
      DECLARE_NAPI_METHOD(userLogout),
      DECLARE_NAPI_METHOD(userPasswordUpdate),
      DECLARE_NAPI_METHOD(tradingAccountPasswordUpdate),
      DECLARE_NAPI_METHOD(userAuthMethod),
      DECLARE_NAPI_METHOD(genUserCaptcha),
      DECLARE_NAPI_METHOD(genUserText),
      DECLARE_NAPI_METHOD(userLoginWithCaptcha),
      DECLARE_NAPI_METHOD(userLoginWithText),
      DECLARE_NAPI_METHOD(userLoginWithOTP),
      DECLARE_NAPI_METHOD(orderInsert),
      DECLARE_NAPI_METHOD(parkedOrderInsert),
      DECLARE_NAPI_METHOD(parkedOrderAction),
      DECLARE_NAPI_METHOD(orderAction),
      DECLARE_NAPI_METHOD(qryMaxOrderVolume),
      DECLARE_NAPI_METHOD(settlementInfoConfirm),
      DECLARE_NAPI_METHOD(removeParkedOrder),
      DECLARE_NAPI_METHOD(removeParkedOrderAction),
      DECLARE_NAPI_METHOD(execOrderInsert),
      DECLARE_NAPI_METHOD(execOrderAction),
      DECLARE_NAPI_METHOD(forQuoteInsert),
      DECLARE_NAPI_METHOD(quoteInsert),
      DECLARE_NAPI_METHOD(quoteAction),
      DECLARE_NAPI_METHOD(batchOrderAction),
      DECLARE_NAPI_METHOD(optionSelfCloseInsert),
      DECLARE_NAPI_METHOD(optionSelfCloseAction),
      DECLARE_NAPI_METHOD(combActionInsert),
      DECLARE_NAPI_METHOD(qryOrder),
      DECLARE_NAPI_METHOD(qryTrade),
      DECLARE_NAPI_METHOD(qryInvestorPosition),
      DECLARE_NAPI_METHOD(qryTradingAccount),
      DECLARE_NAPI_METHOD(qryInvestor),
      DECLARE_NAPI_METHOD(qryTradingCode),
      DECLARE_NAPI_METHOD(qryInstrumentMarginRate),
      DECLARE_NAPI_METHOD(qryInstrumentCommissionRate),
      DECLARE_NAPI_METHOD(qryExchange),
      DECLARE_NAPI_METHOD(qryProduct),
      DECLARE_NAPI_METHOD(qryInstrument),
      DECLARE_NAPI_METHOD(qryDepthMarketData),
      DECLARE_NAPI_METHOD(qryTraderOffer),
      DECLARE_NAPI_METHOD(qrySettlementInfo),
      DECLARE_NAPI_METHOD(qryTransferBank),
      DECLARE_NAPI_METHOD(qryInvestorPositionDetail),
      DECLARE_NAPI_METHOD(qryNotice),
      DECLARE_NAPI_METHOD(qrySettlementInfoConfirm),
      DECLARE_NAPI_METHOD(qryInvestorPositionCombineDetail),
      DECLARE_NAPI_METHOD(qryCFMMCTradingAccountKey),
      DECLARE_NAPI_METHOD(qryEWarrantOffset),
      DECLARE_NAPI_METHOD(qryInvestorProductGroupMargin),
      DECLARE_NAPI_METHOD(qryExchangeMarginRate),
      DECLARE_NAPI_METHOD(qryExchangeMarginRateAdjust),
      DECLARE_NAPI_METHOD(qryExchangeRate),
      DECLARE_NAPI_METHOD(qrySecAgentACIDMap),
      DECLARE_NAPI_METHOD(qryProductExchRate),
      DECLARE_NAPI_METHOD(qryProductGroup),
      DECLARE_NAPI_METHOD(qryMMInstrumentCommissionRate),
      DECLARE_NAPI_METHOD(qryMMOptionInstrCommRate),
      DECLARE_NAPI_METHOD(qryInstrumentOrderCommRate),
      DECLARE_NAPI_METHOD(qrySecAgentTradingAccount),
      DECLARE_NAPI_METHOD(qrySecAgentCheckMode),
      DECLARE_NAPI_METHOD(qrySecAgentTradeInfo),
      DECLARE_NAPI_METHOD(qryOptionInstrTradeCost),
      DECLARE_NAPI_METHOD(qryOptionInstrCommRate),
      DECLARE_NAPI_METHOD(qryExecOrder),
      DECLARE_NAPI_METHOD(qryForQuote),
      DECLARE_NAPI_METHOD(qryQuote),
      DECLARE_NAPI_METHOD(qryOptionSelfClose),
      DECLARE_NAPI_METHOD(qryInvestUnit),
      DECLARE_NAPI_METHOD(qryCombInstrumentGuard),
      DECLARE_NAPI_METHOD(qryCombAction),
      DECLARE_NAPI_METHOD(qryTransferSerial),
      DECLARE_NAPI_METHOD(qryAccountregister),
      DECLARE_NAPI_METHOD(qryContractBank),
      DECLARE_NAPI_METHOD(qryParkedOrder),
      DECLARE_NAPI_METHOD(qryParkedOrderAction),
      DECLARE_NAPI_METHOD(qryTradingNotice),
      DECLARE_NAPI_METHOD(qryBrokerTradingParams),
      DECLARE_NAPI_METHOD(qryBrokerTradingAlgos),
      DECLARE_NAPI_METHOD(queryCFMMCTradingAccountToken),
      DECLARE_NAPI_METHOD(fromBankToFutureByFuture),
      DECLARE_NAPI_METHOD(fromFutureToBankByFuture),
      DECLARE_NAPI_METHOD(queryBankAccountMoneyByFuture),
      DECLARE_NAPI_METHOD(qryClassifiedInstrument),
      DECLARE_NAPI_METHOD(qryCombPromotionParam),
      DECLARE_NAPI_METHOD(qryRiskSettleInvstPosition),
      DECLARE_NAPI_METHOD(qryRiskSettleProductStatus),
      DECLARE_NAPI_METHOD(on),
  };
  return defineClass(env, "Trader", traderNew, arraysize(props), props, constructor);
}

napi_value createTrader(napi_env env, napi_callback_info info) {
  Constructors *constructors = getConstructors(env);
  return constructors ? createInstance(env, info, constructors->trader, 2) : nullptr;
}
