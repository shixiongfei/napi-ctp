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
#include "napi_ctp.h"
#include "traderapi.h"
#include "mdapi.h"

static napi_value init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor props[] = {
    {"createTrader", 0, createTrader, 0, 0, 0, napi_default, 0},
    {"createMarketData", 0, createMarketData, 0, 0, 0, napi_default, 0}
  };

  status = napi_define_properties(env, exports, arraySize(props), props);
  assert(status == napi_ok);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
