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
#include "mdspi.h"
#include <stdlib.h>

typedef struct MarketData {
  napi_env env;
  napi_ref wrapper;
  MdSpi *spi;
  CThostFtdcMdApi *api;
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
  return nullptr;
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

static void marketDataDestructor(napi_env env, void *data, void *hint) {
  MarketData *marketData = (MarketData *)data;

  if (!marketData)
    return;

  if (marketData->api)
    marketData->api->Release();

  if (marketData->spi)
    delete marketData->spi;

  napi_delete_reference(marketData->env, marketData->wrapper);
  free(marketData);
}

static napi_value marketDataNew(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value target, args[2], jsthis;
  napi_valuetype valuetype;
  size_t argc = 2, bytes;
  MarketData *marketData;
  char flowMdPath[260], frontMdAddr[64];

  status = napi_get_new_target(env, info, &target);
  assert(status == napi_ok);

  if (!target)
    return nullptr;

  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  status = napi_typeof(env, args[0], &valuetype);
  assert(status == napi_ok);

  if (valuetype != napi_string) {
    napi_throw_error(env, "TypeError", "The parameter 1 should be a string");
    return nullptr;
  }

  status = napi_typeof(env, args[1], &valuetype);
  assert(status == napi_ok);

  if (valuetype != napi_string) {
    napi_throw_error(env, "TypeError", "The parameter 2 should be a string");
    return nullptr;
  }

  status = napi_get_value_string_utf8(env, args[0], flowMdPath,
                                      sizeof(flowMdPath), &bytes);
  assert(status == napi_ok);

  status = napi_get_value_string_utf8(env, args[1], frontMdAddr,
                                      sizeof(frontMdAddr), &bytes);
  assert(status == napi_ok);

  marketData = (MarketData *)malloc(sizeof(MarketData));

  if (!marketData) {
    napi_throw_error(env, "OutOfMemory", "Out of memory");
    return nullptr;
  }

  marketData->spi = new MdSpi();

  if (!marketData->spi) {
    free(marketData);
    napi_throw_error(env, "OutOfMemory", "Out of memory");
    return nullptr;
  }

  marketData->api = CThostFtdcMdApi::CreateFtdcMdApi(flowMdPath);

  if (!marketData->api) {
    delete marketData->spi;
    free(marketData);
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
      NAPI_DEFINE_METHOD(getApiVersion),
      NAPI_DEFINE_METHOD(subscribeMarketData),
      NAPI_DEFINE_METHOD(unsubscribeMarketData),
      NAPI_DEFINE_METHOD(subscribeForQuoteRsp),
      NAPI_DEFINE_METHOD(unsubscribeForQuoteRsp),
      NAPI_DEFINE_METHOD(userLogin),
      NAPI_DEFINE_METHOD(userLogout),
  };
  return defineClass(env, "MarketData", marketDataNew, arraysize(props), props,
                     constructor);
}

napi_value createMarketData(napi_env env, napi_callback_info info) {
  Constructors *constructors = getConstructors(env);
  return constructors ? createInstance(env, info, constructors->marketData, 2)
                      : nullptr;
}
