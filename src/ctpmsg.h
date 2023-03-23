/*
 * ctpmsg.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __CTPMSG_H__
#define __CTPMSG_H__

#include "napi_ctp.h"
#include <map>

typedef napi_status (*MessageFunc)(napi_env env, const Message *message, napi_value *result);
typedef std::map<int, MessageFunc> MessageFuncs;

napi_status getMessageValue(napi_env env, const MessageFuncs &messageFuncs, const Message *message, napi_value *result);

napi_status msgQuit(napi_env env, const Message *message, napi_value *result);
napi_status msgFrontConnected(napi_env env, const Message *message, napi_value *result);
napi_status msgFrontDisconnected(napi_env env, const Message *message, napi_value *result);
napi_status msgHeartBeatWarning(napi_env env, const Message *message, napi_value *result);
napi_status msgUserLogin(napi_env env, const Message *message, napi_value *result);
napi_status msgUserLogout(napi_env env, const Message *message, napi_value *result);
napi_status msgQryMulticastInstrument(napi_env env, const Message *message, napi_value *result);
napi_status msgError(napi_env env, const Message *message, napi_value *result);
napi_status msgSubMarketData(napi_env env, const Message *message, napi_value *result);
napi_status msgUnSubMarketData(napi_env env, const Message *message, napi_value *result);
napi_status msgSubForQuote(napi_env env, const Message *message, napi_value *result);
napi_status msgUnSubForQuote(napi_env env, const Message *message, napi_value *result);
napi_status msgDepthMarketData(napi_env env, const Message *message, napi_value *result);
napi_status msgForQuote(napi_env env, const Message *message, napi_value *result);

#endif /* __CTPMSG_H__ */
