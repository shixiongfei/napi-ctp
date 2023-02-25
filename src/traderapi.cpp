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

static napi_value getApiVersion(napi_env env, napi_callback_info info) {
  return nullptr;
}

static napi_value traderNew(napi_env env, napi_callback_info info) {
  return nullptr;
}

napi_status defineTrader(napi_env env, napi_ref *constructor) {
  napi_status status;
  napi_value cons;
  napi_property_descriptor props[] = {
      {"getApiVersion", 0, getApiVersion, 0, 0, 0, napi_default, 0},
  };

  status = napi_define_class(env, "Trader", NAPI_AUTO_LENGTH, traderNew,
                             nullptr, arraySize(props), props, &cons);
  assert(status == napi_ok);

  return napi_create_reference(env, cons, 1, constructor);
}

napi_value createTrader(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value cons, instance;
  Constructors *constructors;

  status = napi_get_instance_data(env, (void **)&constructors);
  assert(status == napi_ok);

  if (!constructors)
    return nullptr;

  status = napi_get_reference_value(env, constructors->trader, &cons);
  assert(status == napi_ok);

  status = napi_new_instance(env, cons, 0, nullptr, &instance);
  assert(status == napi_ok);

  return instance;
}
