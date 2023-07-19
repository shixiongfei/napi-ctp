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
#include "mdspi.h"
#include "ctpmsg.h"

static const MessageFuncs messageFuncs = {
    {EM_QUIT,                       msgQuit},
    {EM_FRONTCONNECTED,             msgFrontConnected},
    {EM_FRONTDISCONNECTED,          msgFrontDisconnected},
    {EM_HEARTBEATWARNING,           msgHeartBeatWarning},
    {EM_RSPUSERLOGIN,               rspUserLogin},
    {EM_RSPUSERLOGOUT,              rspUserLogout},
    {EM_RSPQRYMULTICASTINSTRUMENT,  rspQryMulticastInstrument},
    {EM_RSPERROR,                   rspError},
    {EM_RSPSUBMARKETDATA,           rspSubMarketData},
    {EM_RSPUNSUBMARKETDATA,         rspUnSubMarketData},
    {EM_RSPSUBFORQUOTERSP,          rspSubForQuote},
    {EM_RSPUNSUBFORQUOTERSP,        rspUnSubForQuote},
    {EM_RTNDEPTHMARKETDATA,         rtnDepthMarketData},
    {EM_RTNFORQUOTERSP,             rtnForQuote},
};

napi_status getMarketDataMessageValue(napi_env env, const Message *message, napi_value *result) {
  return getMessageValue(env, messageFuncs, message, result);
}

napi_status getMarketDataMessageOptions(napi_env env, const Message *message, napi_value *result) {
  return getMessageOptions(env, message, result);
}
