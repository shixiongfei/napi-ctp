/*
 * mdmsg.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "mdmsg.h"

napi_status getMarketDataMessageValue(napi_env env, const Message *message,
                                      napi_value *result) {
  napi_status status;

  status = napi_create_string_utf8(env, "Message", NAPI_AUTO_LENGTH, result);
  return status;
}
