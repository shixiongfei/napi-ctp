/*
 * mdapi.cpp
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "mdapi.h"
#include "guard.h"
#include "mdmsg.h"
#include "mdspi.h"
#include <functional>
#include <string.h>

typedef struct MarketData {
  napi_env env;
  napi_ref wrapper;
  MdSpi *spi;
  CThostFtdcMdApi *api;
  std::unordered_map<int, napi_threadsafe_function> tsfns;
} MarketData;

static napi_value getApiVersion(napi_env env, napi_callback_info info) {
  napi_value jsthis, version;
  MarketData *marketData;

  CHECK(napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&marketData));

  if (!marketData->api) {
    napi_value undefined;
    napi_throw_error(env, nullptr, "MdApi is closed");
    CHECK(napi_get_undefined(env, &undefined));
    return undefined;
  }

  CHECK(napi_create_string_utf8(env, marketData->api->GetApiVersion(), NAPI_AUTO_LENGTH, &version));

  return version;
}

static napi_value getTradingDay(napi_env env, napi_callback_info info) {
  napi_value jsthis, tradingDay;
  MarketData *marketData;

  CHECK(napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&marketData));

  if (!marketData->api) {
    napi_value undefined;
    napi_throw_error(env, nullptr, "MdApi is closed");
    CHECK(napi_get_undefined(env, &undefined));
    return undefined;
  }

  CHECK(napi_create_string_utf8(env, marketData->api->GetTradingDay(), NAPI_AUTO_LENGTH, &tradingDay));

  return tradingDay;
}

static napi_value callInstrumentIdsFunc(napi_env env, napi_callback_info info, const std::function<int(MarketData *, char **, int)> &func) {
  size_t argc = 1, size;
  uint32_t length;
  int result;
  napi_value argv, jsthis, retval, element;
  MarketData *marketData;

  CHECK(napi_get_cb_info(env, info, &argc, &argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&marketData));

  if (!marketData->api) {
    napi_throw_error(env, nullptr, "MdApi is closed");
    CHECK(napi_get_undefined(env, &retval));
    return retval;
  }

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

static napi_value callRequestFunc(napi_env env, napi_callback_info info, const std::function<int(MarketData *, napi_value)> &func) {
  size_t argc = 1;
  int result;
  napi_value object, jsthis, retval;
  MarketData *marketData;

  CHECK(napi_get_cb_info(env, info, &argc, &object, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&marketData));

  if (!marketData->api) {
    napi_throw_error(env, nullptr, "MdApi is closed");
    CHECK(napi_get_undefined(env, &retval));
    return retval;
  }

  if (isUndefined(env, object))
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
  napi_value undefined, argv[2];

  CHECK(napi_get_undefined(env, &undefined));
  CHECK(getMarketDataMessageValue(env, message, &argv[0]));
  CHECK(getMarketDataMessageOptions(env, message, &argv[1]));
  CHECK(napi_call_function(env, undefined, js_cb, 2, argv, nullptr));

  marketData->spi->done(message);
}

static napi_value on(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[2] = {napi_string, napi_function};
  size_t argc = 2;
  napi_value argv[2], jsthis;
  napi_threadsafe_function tsfn;
  MarketData *marketData;
  char eventName[64];
  int event;

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&marketData));

  CHECK(checkValueTypes(env, argc, argv, types));

  CHECK(napi_create_threadsafe_function(env, argv[1], nullptr, argv[0], 0, 1, nullptr, nullptr, marketData, callJs, &tsfn));
  CHECK(napi_ref_threadsafe_function(env, tsfn));

  CHECK(napi_get_value_string_utf8(env, argv[0], eventName, sizeof(eventName), nullptr));

  event = marketData->spi->eventFromName(eventName);

  if (marketData->tsfns.find(event) != marketData->tsfns.end())
    CHECK(napi_unref_threadsafe_function(env, marketData->tsfns[event]));

  marketData->tsfns[event] = tsfn;

  return jsthis;
}

static napi_value close(napi_env env, napi_callback_info info) {
  napi_value jsthis, undefined;
  MarketData *marketData;

  CHECK(napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr));
  CHECK(napi_unwrap(env, jsthis, (void **)&marketData));

  if (marketData->api) {
    marketData->api->Release();
    marketData->api = nullptr;
  }

  CHECK(napi_get_undefined(env, &undefined));
  return undefined;
}

static void marketDataDestructor(napi_env env, void *data, void *hint) {
  MarketData *marketData = (MarketData *)data;

  if (!marketData)
    return;

  marketDataFree(env, marketData);
}

static napi_value marketDataNew(napi_env env, napi_callback_info info) {
  static const napi_valuetype types[1] = {napi_string};
  size_t argc = 2;
  napi_value target, argv[2], jsthis, element;
  MarketData *marketData;
  char flowMdPath[260], frontMdAddr[64];
  uint32_t length;
  bool isArray;

  CHECK(napi_get_new_target(env, info, &target));

  if (!target) {
    CHECK(napi_get_undefined(env, &target));
    return target;
  }

  CHECK(napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr));

  CHECK(checkValueTypes(env, 1, argv, types));
  CHECK(napi_get_value_string_utf8(env, argv[0], flowMdPath, sizeof(flowMdPath), nullptr));

  CHECK(napi_is_array(env, argv[1], &isArray));

  if (isArray)
    CHECK(checkIsStringArray(env, argv[1]));
  else
    CHECK(napi_get_value_string_utf8(env, argv[1], frontMdAddr, sizeof(frontMdAddr), nullptr));

  marketData = new MarketData();

  if (!marketData) {
    napi_throw_error(env, nullptr, "Market data is out of memory");
    return jsthis;
  }

  marketData->env = env;

  marketData->api = CThostFtdcMdApi::CreateFtdcMdApi(flowMdPath);

  if (!marketData->api) {
    delete marketData;
    napi_throw_error(env, nullptr, "Market data is out of memory");
    return jsthis;
  }

  marketData->spi = new MdSpi(marketData->api, marketData->env, &marketData->tsfns);

  if (!marketData->spi) {
    marketData->api->Release();
    delete marketData;
    napi_throw_error(env, nullptr, "Market data is out of memory");
    return jsthis;
  }

  marketData->api->RegisterSpi(marketData->spi);

  if (isArray) {
    CHECK(napi_get_array_length(env, argv[1], &length));

    for (uint32_t i = 0; i < length; ++i) {
      CHECK(napi_get_element(env, argv[1], i, &element));
      CHECK(napi_get_value_string_utf8(env, element, frontMdAddr, sizeof(frontMdAddr), nullptr));

      marketData->api->RegisterFront(frontMdAddr);
    }
  } else
    marketData->api->RegisterFront(frontMdAddr);

  marketData->api->Init();

  CHECK(napi_wrap(env, jsthis, (void *)marketData, marketDataDestructor, nullptr, &marketData->wrapper));

  return jsthis;
}

napi_status defineMarketData(napi_env env, napi_value *constructor) {
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
      DECLARE_NAPI_METHOD(close),
  };
  return napi_define_class(env, "MarketData", NAPI_AUTO_LENGTH, marketDataNew, nullptr, arraysize(props), props, constructor);
}

napi_value createMarketData(napi_env env, napi_callback_info info) {
  Constructors *constructors = getConstructors(env);
  return constructors ? createInstance(env, info, constructors->marketData, 2) : nullptr;
}
