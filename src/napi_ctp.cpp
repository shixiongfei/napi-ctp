/*
 * napi_ctp.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "napi_ctp.h"
#include "traderapi.h"
#include "mdapi.h"

static void destructor(napi_env env, void *data, void *hint) {
  napi_status status;
  Constructors *constructors = (Constructors *)data;

  if (!constructors)
    return;

  if (constructors->marketData) {
    status = napi_delete_reference(env, constructors->marketData);
    assert(status == napi_ok);
  }

  if (constructors->trader) {
    status = napi_delete_reference(env, constructors->trader);
    assert(status == napi_ok);
  }

  free(constructors);
}

static napi_value init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor props[] = {
    {"createTrader", 0, createTrader, 0, 0, 0, napi_default, 0},
    {"createMarketData", 0, createMarketData, 0, 0, 0, napi_default, 0}
  };
  Constructors *constructors = (Constructors *)malloc(sizeof(Constructors));

  if (!constructors) {
    napi_throw_error(env, "OutOfMemory", "Out of memory");
    return nullptr;
  }

  memset(constructors, 0, sizeof(Constructors));

  status = defineMarketData(env, &constructors->marketData);
  assert(status == napi_ok);

  status = defineTrader(env, &constructors->trader);
  assert(status == napi_ok);

  status = napi_define_properties(env, exports, arraySize(props), props);
  assert(status == napi_ok);

  status = napi_set_instance_data(env, constructors, destructor, nullptr);
  assert(status == napi_ok);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
