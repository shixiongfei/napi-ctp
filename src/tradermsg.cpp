/*
 * tradermsg.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "tradermsg.h"
#include "ctpmsg.h"

static const std::map<int, MessageFunc> messageFuncs = {};

napi_status getTraderMessageValue(napi_env env, const Message *message, napi_value *result) {
  return getMessageValue(env, messageFuncs, message, result);
}
