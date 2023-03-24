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
    {EM_RSPUSERLOGIN,               msgUserLogin},
    {EM_RSPUSERLOGOUT,              msgUserLogout},
    {EM_RSPQRYMULTICASTINSTRUMENT,  msgQryMulticastInstrument},
    {EM_RSPERROR,                   msgError},
    {EM_RSPSUBMARKETDATA,           msgSubMarketData},
    {EM_RSPUNSUBMARKETDATA,         msgUnSubMarketData},
    {EM_RSPSUBFORQUOTERSP,          msgSubForQuote},
    {EM_RSPUNSUBFORQUOTERSP,        msgUnSubForQuote},
    {EM_RTNDEPTHMARKETDATA,         msgDepthMarketData},
    {EM_RTNFORQUOTERSP,             msgForQuote},
};

napi_status getMarketDataMessageValue(napi_env env, const Message *message, napi_value *result) {
  return getMessageValue(env, messageFuncs, message, result);
}
