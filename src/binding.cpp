/*
 * binding.cpp
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "mdapi.h"
#include "napi_ctp.h"
#include "traderapi.h"
#include <string.h>

static void destructor(napi_env env, void *data, void *hint) {
  Constructors *constructors = (Constructors *)data;

  if (!constructors)
    return;

  if (constructors->marketData)
    CHECK(napi_delete_reference(env, constructors->marketData));

  if (constructors->trader)
    CHECK(napi_delete_reference(env, constructors->trader));

  free(constructors);
}

static napi_status defineConstructors(napi_env env) {
  Constructors *constructors = (Constructors *)malloc(sizeof(Constructors));

  if (!constructors) {
    napi_throw_error(env, nullptr, "Out of memory");
    return napi_object_expected;
  }

  memset(constructors, 0, sizeof(Constructors));

  CHECK(defineMarketData(env, &constructors->marketData));
  CHECK(defineTrader(env, &constructors->trader));

  return napi_set_instance_data(env, constructors, destructor, nullptr);
}

static napi_value getLastRequestId(napi_env env, napi_callback_info info) {
  napi_value value;
  CHECK(napi_create_int32(env, currentSequenceId(), &value));
  return value;
}

static napi_value resetRequestId(napi_env env, napi_callback_info info) {
  napi_value undefined;

  CHECK(napi_get_undefined(env, &undefined));
  setSequenceId(0);

  return undefined;
}

static napi_status defineMethods(napi_env env, napi_value exports) {
  napi_property_descriptor props[] = {
      DECLARE_NAPI_METHOD(createMarketData),
      DECLARE_NAPI_METHOD(createTrader),
      DECLARE_NAPI_METHOD(getLastRequestId),
      DECLARE_NAPI_METHOD(resetRequestId),
  };
  return napi_define_properties(env, exports, arraysize(props), props);
}

static napi_value init(napi_env env, napi_value exports) {
  CHECK(defineConstructors(env));
  CHECK(defineMethods(env, exports));

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
