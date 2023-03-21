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
#include <map>
#include <stdlib.h>
#include <string>

typedef struct MarketData {
  napi_env env;
  napi_ref wrapper;
  uv_thread_t thread;
  MdSpi *spi;
  CThostFtdcMdApi *api;
  std::map<std::string, napi_threadsafe_function> tsfns;
} MarketData;

static napi_value getApiVersion(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value jsthis, version;
  MarketData *marketData;

  status = napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr);
  assert(status == napi_ok);

  status = napi_unwrap(env, jsthis, (void **)&marketData);
  assert(status == napi_ok);

  status = napi_create_string_utf8(env, marketData->api->GetApiVersion(),
                                   NAPI_AUTO_LENGTH, &version);
  assert(status == napi_ok);

  return version;
}

static napi_value subscribeMarketData(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1, size;
  uint32_t length;
  int result;
  napi_value argv, jsthis, retval, element;
  napi_valuetype valuetype, elementType;
  MarketData *marketData;
  bool isArray;

  status = napi_get_cb_info(env, info, &argc, &argv, &jsthis, nullptr);
  assert(status == napi_ok);

  status = napi_unwrap(env, jsthis, (void **)&marketData);
  assert(status == napi_ok);

  status = napi_typeof(env, argv, &valuetype);
  assert(status == napi_ok);

  if (valuetype != napi_object) {
    napi_throw_error(env, "TypeError",
                     "The parameter should be a string array");
    return nullptr;
  }

  status = napi_is_array(env, argv, &isArray);
  assert(status == napi_ok);

  if (!isArray) {
    napi_throw_error(env, "TypeError",
                     "The parameter should be a string array");
    return nullptr;
  }

  status = napi_get_array_length(env, argv, &length);
  assert(status == napi_ok);

  if (length == 0) {
    status = napi_create_int32(env, 0, &retval);
    assert(status == napi_ok);

    return retval;
  }

  dynarray(char *, instrumentIds, length);

  for (uint32_t i = 0; i < length; ++i) {
    status = napi_get_element(env, argv, i, &element);
    assert(status == napi_ok);

    status = napi_typeof(env, element, &elementType);
    assert(status == napi_ok);

    if (elementType != napi_string) {
      napi_throw_error(env, "TypeError",
                       "The parameter should be a string array");
      return nullptr;
    }

    status = napi_get_value_string_utf8(env, element, nullptr, 0, &size);
    assert(status == napi_ok);

    instrumentIds[i] = (char *)malloc(size + 1);
    memset(instrumentIds[i], 0, size + 1);

    status = napi_get_value_string_utf8(env, element, instrumentIds[i],
                                        size + 1, &size);
    assert(status == napi_ok);
  }

  result = marketData->api->SubscribeMarketData(instrumentIds, length);

  for (uint32_t i = 0; i < length; ++i)
    free(instrumentIds[i]);

  status = napi_create_int32(env, result, &retval);
  assert(status == napi_ok);

  return retval;
}

static napi_value unsubscribeMarketData(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value subscribeForQuoteRsp(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value unsubscribeForQuoteRsp(napi_env env,
                                         napi_callback_info info) {
  return nullptr;
}

static napi_value userLogin(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value userLogout(napi_env env, napi_callback_info info) {
  return nullptr;
}

static bool processMessage(MarketData *marketData, const Message &message) {
  const char *eventName = MdSpi::eventName(message.event);

  if (!eventName) {
    fprintf(stderr, "<Market Data> Unknown message event %d\n", message.event);
    return true;
  }

  auto iter = marketData->tsfns.find(eventName);

  if (iter != marketData->tsfns.end()) {
    napi_threadsafe_function tsfn = iter->second;
    napi_status status;

    status = napi_call_threadsafe_function(tsfn, (void *)&message,
                                           napi_tsfn_blocking);
    assert(status == napi_ok);
  }

  return EM_QUIT != message.event;
}

static void processThread(void *data) {
  MarketData *marketData = (MarketData *)data;
  Message message;
  bool isRunning = true;

  while (isRunning) {
    if (QUEUE_SUCCESS != marketData->spi->poll(&message))
      continue;

    isRunning = processMessage(marketData, message);
    marketData->spi->done(message);
  }
}

static void callJs(napi_env env, napi_value js_cb, void *context, void *data) {
  MarketData *marketData = (MarketData *)context;
  Message *message = (Message *)data;
  napi_status status;
  napi_value undefined, argv;

  status = napi_get_undefined(env, &undefined);
  assert(status == napi_ok);

  status = getMarketDataMessageValue(env, message, &argv);
  assert(status == napi_ok);

  status = napi_call_function(env, undefined, js_cb, 1, &argv, nullptr);
  assert(status == napi_ok);
}

static napi_value on(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 2, len;
  napi_value argv[2], jsthis;
  napi_valuetype valuetype;
  napi_threadsafe_function tsfn;
  MarketData *marketData;
  char fname[64];

  status = napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr);
  assert(status == napi_ok);

  status = napi_unwrap(env, jsthis, (void **)&marketData);
  assert(status == napi_ok);

  status = napi_typeof(env, argv[0], &valuetype);
  assert(status == napi_ok);

  if (valuetype != napi_string) {
    napi_throw_error(env, "TypeError", "The parameter 1 should be a string");
    return nullptr;
  }

  status = napi_typeof(env, argv[1], &valuetype);
  assert(status == napi_ok);

  if (valuetype != napi_function) {
    napi_throw_error(env, "TypeError", "The parameter 2 should be a function");
    return nullptr;
  }

  status = napi_create_threadsafe_function(env, argv[1], nullptr, argv[0], 0, 1,
                                           nullptr, nullptr, marketData, callJs,
                                           &tsfn);
  assert(status == napi_ok);

  status = napi_ref_threadsafe_function(env, tsfn);
  assert(status == napi_ok);

  status = napi_get_value_string_utf8(env, argv[0], fname, sizeof(fname), &len);
  assert(status == napi_ok);

  if (marketData->tsfns.find(fname) != marketData->tsfns.end()) {
    status = napi_unref_threadsafe_function(env, marketData->tsfns[fname]);
    assert(status == napi_ok);
  }

  marketData->tsfns[fname] = tsfn;

  return jsthis;
}

static void marketDataDestructor(napi_env env, void *data, void *hint) {
  MarketData *marketData = (MarketData *)data;

  if (!marketData)
    return;

  for (auto it = marketData->tsfns.begin(); it != marketData->tsfns.end(); ++it)
    napi_unref_threadsafe_function(env, it->second);

  marketData->tsfns.clear();

  if (marketData->spi) {
    marketData->spi->quit();
    uv_thread_join(&marketData->thread);
    delete marketData->spi;
  }

  if (marketData->api)
    marketData->api->Release();

  napi_delete_reference(marketData->env, marketData->wrapper);
  delete marketData;
}

static napi_value marketDataNew(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value target, argv[2], jsthis;
  napi_valuetype valuetype;
  size_t argc = 2, bytes;
  MarketData *marketData;
  char flowMdPath[260], frontMdAddr[64];

  status = napi_get_new_target(env, info, &target);
  assert(status == napi_ok);

  if (!target)
    return nullptr;

  status = napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr);
  assert(status == napi_ok);

  status = napi_typeof(env, argv[0], &valuetype);
  assert(status == napi_ok);

  if (valuetype != napi_string) {
    napi_throw_error(env, "TypeError", "The parameter 1 should be a string");
    return nullptr;
  }

  status = napi_typeof(env, argv[1], &valuetype);
  assert(status == napi_ok);

  if (valuetype != napi_string) {
    napi_throw_error(env, "TypeError", "The parameter 2 should be a string");
    return nullptr;
  }

  status = napi_get_value_string_utf8(env, argv[0], flowMdPath,
                                      sizeof(flowMdPath), &bytes);
  assert(status == napi_ok);

  status = napi_get_value_string_utf8(env, argv[1], frontMdAddr,
                                      sizeof(frontMdAddr), &bytes);
  assert(status == napi_ok);

  marketData = new MarketData();

  if (!marketData) {
    napi_throw_error(env, "OutOfMemory", "Out of memory");
    return nullptr;
  }

  marketData->spi = new MdSpi();

  if (!marketData->spi) {
    delete marketData;
    napi_throw_error(env, "OutOfMemory", "Out of memory");
    return nullptr;
  }

  if (0 != uv_thread_create(&marketData->thread, processThread, marketData)) {
    delete marketData->spi;
    delete marketData;
    napi_throw_error(env, "ThreadError", "Can not create thread");
    return nullptr;
  }

  marketData->api = CThostFtdcMdApi::CreateFtdcMdApi(flowMdPath);

  if (!marketData->api) {
    marketData->spi->quit();
    uv_thread_join(&marketData->thread);
    delete marketData->spi;
    delete marketData;
    napi_throw_error(env, "OutOfMemory", "Out of memory");
    return nullptr;
  }

  marketData->api->RegisterSpi(marketData->spi);
  marketData->api->RegisterFront(frontMdAddr);
  marketData->api->Init();

  marketData->env = env;
  status = napi_wrap(env, jsthis, (void *)marketData, marketDataDestructor,
                     nullptr, &marketData->wrapper);
  assert(status == napi_ok);

  return jsthis;
}

napi_status defineMarketData(napi_env env, napi_ref *constructor) {
  napi_property_descriptor props[] = {
      DECLARE_NAPI_METHOD(getApiVersion),
      DECLARE_NAPI_METHOD(subscribeMarketData),
      DECLARE_NAPI_METHOD(unsubscribeMarketData),
      DECLARE_NAPI_METHOD(subscribeForQuoteRsp),
      DECLARE_NAPI_METHOD(unsubscribeForQuoteRsp),
      DECLARE_NAPI_METHOD(userLogin),
      DECLARE_NAPI_METHOD(userLogout),
      DECLARE_NAPI_METHOD(on),
  };
  return defineClass(env, "MarketData", marketDataNew, arraysize(props), props,
                     constructor);
}

napi_value createMarketData(napi_env env, napi_callback_info info) {
  Constructors *constructors = getConstructors(env);
  return constructors ? createInstance(env, info, constructors->marketData, 2)
                      : nullptr;
}
