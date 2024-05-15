/*
 * traderapi.h
 *
 * Copyright (c) 2022-2024 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __TRADERAPI_H__
#define __TRADERAPI_H__

#include "napi_ctp.h"

napi_status defineTrader(napi_env env, napi_ref *constructor);
napi_value createTrader(napi_env env, napi_callback_info info);

#endif /* __TRADERAPI_H__ */
