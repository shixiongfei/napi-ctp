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

typedef struct Trader {
  napi_env env;
  napi_ref wrapper;
} Trader;

static napi_value getApiVersion(napi_env env, napi_callback_info info) {
  return nullptr;
}

static void traderDestructor(napi_env env, void *data, void *hint) {}

static napi_value traderNew(napi_env env, napi_callback_info info) {
  return nullptr;
}

napi_status defineTrader(napi_env env, napi_ref *constructor) {
  napi_property_descriptor props[] = {
      DECLARE_NAPI_METHOD(getApiVersion),
  };
  return defineClass(env, "Trader", traderNew, arraysize(props), props,
                     constructor);
}

napi_value createTrader(napi_env env, napi_callback_info info) {
  Constructors *constructors = getConstructors(env);
  return constructors ? createInstance(env, info, constructors->trader, 2)
                      : nullptr;
}
