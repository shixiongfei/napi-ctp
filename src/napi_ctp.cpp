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
#include <node_api.h>

static napi_value ctp(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value value;

  status = napi_create_string_utf8(env, "NAPI-CTP", NAPI_AUTO_LENGTH, &value);
  assert(status == napi_ok);

  return value;
}

static napi_value init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor desc[] = {
    {"ctp", 0, ctp, 0, 0, 0, napi_default, 0}
  };

  status = napi_define_properties(env, exports, 1, desc);
  assert(status == napi_ok);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
