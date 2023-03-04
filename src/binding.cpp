/*
 * binding.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "mdapi.h"
#include "napi_ctp.h"
#include "traderapi.h"
#include <stdlib.h>
#include <string.h>

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

static napi_status defineConstructors(napi_env env) {
  napi_status status;
  Constructors *constructors = (Constructors *)malloc(sizeof(Constructors));

  if (!constructors) {
    napi_throw_error(env, "OutOfMemory", "Out of memory");
    return napi_object_expected;
  }

  memset(constructors, 0, sizeof(Constructors));

  status = defineMarketData(env, &constructors->marketData);
  assert(status == napi_ok);

  status = defineTrader(env, &constructors->trader);
  assert(status == napi_ok);

  return napi_set_instance_data(env, constructors, destructor, nullptr);
}

static napi_status defineMethods(napi_env env, napi_value exports) {
  napi_property_descriptor props[] = {
      DECLARE_NAPI_METHOD(createMarketData),
      DECLARE_NAPI_METHOD(createTrader),
  };
  return napi_define_properties(env, exports, arraysize(props), props);
}

static napi_value init(napi_env env, napi_value exports) {
  napi_status status;

  status = defineConstructors(env);
  assert(status == napi_ok);

  status = defineMethods(env, exports);
  assert(status == napi_ok);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
