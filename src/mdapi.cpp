/*
 * mdapi.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "mdapi.h"
#include "mdmsg.h"
#include "mdspi.h"
#include "guard.h"
#include <string.h>
#include <map>
#include <string>
#include <functional>

typedef struct MarketData {
  napi_env env;
  napi_ref wrapper;
  uv_thread_t thread;
  MdSpi *spi;
  CThostFtdcMdApi *api;
  std::map<std::string, napi_threadsafe_function> tsfns;
} MarketData;

static napi_value getApiVersion(napi_env env, napi_callback_info info) {
  napi_value jsthis, version;
  MarketData *marketData;

  CHECK(napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&marketData));
  CHECK(napi_create_string_utf8(env, marketData->api->GetApiVersion(), NAPI_AUTO_LENGTH, &version));

  return version;
}

static napi_value getTradingDay(napi_env env, napi_callback_info info) {
  napi_value jsthis, tradingDay;
  MarketData *marketData;

  CHECK(napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&marketData));
  CHECK(napi_create_string_utf8(env, marketData->api->GetTradingDay(), NAPI_AUTO_LENGTH, &tradingDay));

  return tradingDay;
}

static napi_value callInstrumentIdsFunc(napi_env env, napi_callback_info info, const std::function<int(MarketData*, char**, int)> &func) {
  size_t argc = 1, size;
  uint32_t length;
  int result;
  napi_value argv, jsthis, retval, element;
  MarketData *marketData;

  CHECK(napi_get_cb_info(env, info, &argc, &argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&marketData));

  CHECK(checkIsStringArray(env, argv));
  CHECK(napi_get_array_length(env, argv, &length));

  if (length == 0) {
    CHECK(napi_create_int32(env, 0, &retval));
    return retval;
  }

  dynarray(char *, instrumentIds, length);
  memset(instrumentIds, 0, length * sizeof(char *));

  Defer([&instrumentIds, length]() {
    for (uint32_t i = 0; i < length; ++i)
      if (instrumentIds[i])
        free(instrumentIds[i]);
  });

  for (uint32_t i = 0; i < length; ++i) {
    CHECK(napi_get_element(env, argv, i, &element));
    CHECK(napi_get_value_string_utf8(env, element, nullptr, 0, &size));

    instrumentIds[i] = (char *)malloc(size + 1);

    if (!instrumentIds[i]) {
      napi_throw_error(env, nullptr, "Out of memory");
      CHECK(napi_get_undefined(env, &retval));
      return retval;
    }

    memset(instrumentIds[i], 0, size + 1);
    CHECK(napi_get_value_string_utf8(env, element, instrumentIds[i], size + 1, nullptr));
  }

  result = func(marketData, instrumentIds, length);
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value subscribeMarketData(napi_env env, napi_callback_info info) {
  return callInstrumentIdsFunc(env, info, [](MarketData *marketData, char **instrumentIds, int count) {
    return marketData->api->SubscribeMarketData(instrumentIds, count);
  });
}

static napi_value unsubscribeMarketData(napi_env env, napi_callback_info info) {
  return callInstrumentIdsFunc(env, info, [](MarketData *marketData, char **instrumentIds, int count) {
    return marketData->api->UnSubscribeMarketData(instrumentIds, count);
  });
}

static napi_value subscribeForQuoteRsp(napi_env env, napi_callback_info info) {
  return callInstrumentIdsFunc(env, info, [](MarketData *marketData, char **instrumentIds, int count) {
    return marketData->api->SubscribeForQuoteRsp(instrumentIds, count);
  });
}

static napi_value unsubscribeForQuoteRsp(napi_env env, napi_callback_info info) {
  return callInstrumentIdsFunc(env, info, [](MarketData *marketData, char **instrumentIds, int count) {
    return marketData->api->UnSubscribeForQuoteRsp(instrumentIds, count);
  });
}

static napi_value callRequestFunc(napi_env env, napi_callback_info info, const std::function<int(MarketData*, napi_value)> &func) {
  size_t argc = 1;
  int result;
  napi_value object, jsthis, retval;
  napi_valuetype valuetype;
  MarketData *marketData;

  CHECK(napi_get_cb_info(env, info, &argc, &object, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&marketData));

  CHECK(napi_typeof(env, object, &valuetype));

  if (valuetype == napi_undefined)
    CHECK(napi_create_object(env, &object));

  CHECK(checkIsObject(env, object));

  result = func(marketData, object);
  CHECK(napi_create_int32(env, result, &retval));

  return retval;
}

static napi_value reqUserLogin(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](MarketData *marketData, napi_value object) {
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

    return marketData->api->ReqUserLogin(&req, nextSequenceId());
  });
}

static napi_value reqUserLogout(napi_env env, napi_callback_info info) {
  return callRequestFunc(env, info, [&env](MarketData *marketData, napi_value object) {
    CThostFtdcUserLogoutField req;

    memset(&req, 0, sizeof(req));

    CHECK(GetObjectString(env, object, req, BrokerID));
    CHECK(GetObjectString(env, object, req, UserID));

    return marketData->api->ReqUserLogout(&req, nextSequenceId());
  });
}

static bool processMessage(MarketData *marketData, const Message *message) {
  const char *eventName = MdSpi::eventName(message->event);

  if (!eventName) {
    fprintf(stderr, "<Market Data> Unknown message event %d\n", message->event);
    return true;
  }

  auto iter = marketData->tsfns.find(eventName);

  if (iter != marketData->tsfns.end()) {
    napi_env env = marketData->env;
    napi_threadsafe_function tsfn = iter->second;
    CHECK(napi_call_threadsafe_function(tsfn, (void *)message, napi_tsfn_blocking));
  }

  return EM_QUIT != message->event;
}

static void processThread(void *data) {
  MarketData *marketData = (MarketData *)data;
  Message *message;
  bool isRunning = true;

  while (isRunning) {
    if (QUEUE_SUCCESS != marketData->spi->poll(&message))
      continue;

    isRunning = processMessage(marketData, message);
  }
}

static void marketDataFree(napi_env env, MarketData *marketData) {
  for (auto it = marketData->tsfns.begin(); it != marketData->tsfns.end(); ++it)
    napi_unref_threadsafe_function(env, it->second);

  marketData->tsfns.clear();
  napi_delete_reference(marketData->env, marketData->wrapper);

  if (marketData->api)
    marketData->api->Release();

  if (marketData->spi)
    delete marketData->spi;

  delete marketData;
}

static void callJs(napi_env env, napi_value js_cb, void *context, void *data) {
  MarketData *marketData = (MarketData *)context;
  Message *message = (Message *)data;
  int event = message->event;
  napi_value undefined, argv[2];

  CHECK(napi_get_undefined(env, &undefined));
  CHECK(getMarketDataMessageValue(env, message, &argv[0]));
  CHECK(getMarketDataMessageOptions(env, message, &argv[1]));
  CHECK(napi_call_function(env, undefined, js_cb, 2, argv, nullptr));

  marketData->spi->done(message);

  if (EM_QUIT == event)
    marketDataFree(env, marketData);
}

static napi_value on(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_function};
  size_t argc = 2;
  napi_value argv[2], jsthis;
  napi_threadsafe_function tsfn;
  MarketData *marketData;
  char fname[64];

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&marketData));

  CHECK(checkValueTypes(env, argc, argv, types));

  CHECK(napi_create_threadsafe_function(env, argv[1], nullptr, argv[0], 0, 1, nullptr, nullptr, marketData, callJs, &tsfn));
  CHECK(napi_ref_threadsafe_function(env, tsfn));

  CHECK(napi_get_value_string_utf8(env, argv[0], fname, sizeof(fname), nullptr));

  if (marketData->tsfns.find(fname) != marketData->tsfns.end())
    CHECK(napi_unref_threadsafe_function(env, marketData->tsfns[fname]));

  marketData->tsfns[fname] = tsfn;

  return jsthis;
}

static void marketDataDestructor(napi_env env, void *data, void *hint) {
  MarketData *marketData = (MarketData *)data;

  if (!marketData)
    return;

  if (marketData->spi) {
    marketData->spi->quit();
    uv_thread_join(&marketData->thread);
  }

  if (marketData->tsfns.find(MdSpi::eventName(EM_QUIT)) == marketData->tsfns.end())
    marketDataFree(env, marketData);
}

static napi_value marketDataNew(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_string};
  size_t argc = 2;
  napi_value target, argv[2], jsthis;
  MarketData *marketData;
  char flowMdPath[260], frontMdAddr[64];

  CHECK(napi_get_new_target(env, info, &target));

  if (!target) {
    CHECK(napi_get_undefined(env, &target));
    return target;
  }

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));

  CHECK(checkValueTypes(env, argc, argv, types));

  CHECK(napi_get_value_string_utf8(env, argv[0], flowMdPath, sizeof(flowMdPath), nullptr));
  CHECK(napi_get_value_string_utf8(env, argv[1], frontMdAddr, sizeof(frontMdAddr), nullptr));

  marketData = new MarketData();

  if (!marketData) {
    napi_throw_error(env, nullptr, "Market data is out of memory");
    return jsthis;
  }

  marketData->env = env;
  marketData->spi = new MdSpi();

  if (!marketData->spi) {
    delete marketData;
    napi_throw_error(env, nullptr, "Market data is out of memory");
    return jsthis;
  }

  if (0 != uv_thread_create(&marketData->thread, processThread, marketData)) {
    delete marketData->spi;
    delete marketData;
    napi_throw_error(env, nullptr, "Market data can not create thread");
    return jsthis;
  }

  marketData->api = CThostFtdcMdApi::CreateFtdcMdApi(flowMdPath);

  if (!marketData->api) {
    marketData->spi->quit();
    uv_thread_join(&marketData->thread);
    delete marketData->spi;
    delete marketData;
    napi_throw_error(env, nullptr, "Market data is out of memory");
    return jsthis;
  }

  marketData->api->RegisterSpi(marketData->spi);
  marketData->api->RegisterFront(frontMdAddr);
  marketData->api->Init();

  CHECK(napi_wrap(env, jsthis, (void *)marketData, marketDataDestructor, nullptr, &marketData->wrapper));

  return jsthis;
}

napi_status defineMarketData(napi_env env, napi_ref *constructor) {
  napi_property_descriptor props[] = {
      DECLARE_NAPI_METHOD(getApiVersion),
      DECLARE_NAPI_METHOD(getTradingDay),
      DECLARE_NAPI_METHOD(subscribeMarketData),
      DECLARE_NAPI_METHOD(unsubscribeMarketData),
      DECLARE_NAPI_METHOD(subscribeForQuoteRsp),
      DECLARE_NAPI_METHOD(unsubscribeForQuoteRsp),
      DECLARE_NAPI_METHOD(reqUserLogin),
      DECLARE_NAPI_METHOD(reqUserLogout),
      DECLARE_NAPI_METHOD(on),
  };
  return defineClass(env, "MarketData", marketDataNew, arraysize(props), props, constructor);
}

napi_value createMarketData(napi_env env, napi_callback_info info) {
  Constructors *constructors = getConstructors(env);
  return constructors ? createInstance(env, info, constructors->marketData, 2) : nullptr;
}
