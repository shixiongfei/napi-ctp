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

static napi_value getApiVersion(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value marketDataNew(napi_env env, napi_callback_info info) {
  return nullptr;
}

napi_status defineMarketData(napi_env env, napi_ref *constructor) {
  napi_property_descriptor props[] = {
      {"getApiVersion", 0, getApiVersion, 0, 0, 0, napi_default, 0},
  };
  return defineClass(env, "MarketData", marketDataNew, arraySize(props), props,
                     constructor);
}

napi_value createMarketData(napi_env env, napi_callback_info info) {
  Constructors *constructors = getConstructors(env);
  return constructors ? createInstance(env, info, constructors->marketData)
                      : nullptr
}
