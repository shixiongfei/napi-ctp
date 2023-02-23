/*
 * mdapi.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __MDAPI_H__
#define __MDAPI_H__

#include "napi_ctp.h"

napi_value createMarketData(napi_env env, napi_callback_info info);

#endif /* __MDAPI_H__ */
