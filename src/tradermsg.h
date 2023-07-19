/*
 * tradermsg.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __TRADERMSG_H__
#define __TRADERMSG_H__

#include "napi_ctp.h"

napi_status getTraderMessageValue(napi_env env, const Message *message, napi_value *result);
napi_status getTraderMessageOptions(napi_env env, const Message *message, napi_value *result);

#endif /* __TRADERMSG_H__ */
