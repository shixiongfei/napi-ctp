/*
 * napi_ctp.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __NAPI_CTP_H__
#define __NAPI_CTP_H__

#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include <assert.h>
#include <node_api.h>

#ifdef _MSC_VER
#include <malloc.h>
#define dynarray(type, name, size)                                             \
  type *name = (type *)_alloca((size) * sizeof(type))
#else
#define dynarray(type, name, size) type name[size]
#endif

typedef struct Constructors {
  napi_ref marketData;
  napi_ref trader;
} Constructors;

typedef struct Message {
  int event;
  uintptr_t data;
} Message;

#define arraysize(a) ((int)(sizeof(a) / sizeof(*a)))

typedef napi_status (*MessageValueFunc)(napi_env env, const Message *message,
                                        napi_value *result);

#define DECLARE_NAPI_METHOD_(name, method)                                     \
  { name, 0, method, 0, 0, 0, napi_default, 0 }
#define DECLARE_NAPI_METHOD(method) DECLARE_NAPI_METHOD_(#method, method)

int sequenceId();

Constructors *getConstructors(napi_env env);

napi_status defineClass(napi_env env, const char *name,
                        napi_callback constructor, size_t propertyCount,
                        const napi_property_descriptor *properties,
                        napi_ref *result);

napi_value createInstance(napi_env env, napi_callback_info info,
                          napi_ref constructor, size_t argc);

napi_status checkIsStringArray(napi_env env, napi_value value, bool *result);

napi_status objectSetString(napi_env env, napi_value object, const char *name,
                            const char *string);

napi_status objectSetInt32(napi_env env, napi_value object, const char *name,
                           int32_t number);

napi_status objectSetUint32(napi_env env, napi_value object, const char *name,
                            uint32_t number);

napi_status objectSetInt64(napi_env env, napi_value object, const char *name,
                           int64_t number);

napi_status objectSetDouble(napi_env env, napi_value object, const char *name,
                            double number);

#define ObjectString(env, object, record, name)                                \
  objectSetString(env, object, #name, (const char *)record->name)

#define ObjectInt32(env, object, record, name)                                 \
  objectSetInt32(env, object, #name, record->name)

#define ObjectUint32(env, object, record, name)                                \
  objectSetUint32(env, object, #name, record->name)

#define ObjectInt64(env, object, record, name)                                 \
  objectSetInt64(env, object, #name, record->name)

#define ObjectDouble(env, object, record, name)                                \
  objectSetDouble(env, object, #name, record->name)

template <typename T> static inline uintptr_t copyData(T *data) {
  T *p = (T *)malloc(sizeof(T));

  if (!p)
    return 0;

  *p = *data;
  return (uintptr_t)p;
}

template <typename T> static inline T *MessageData(const Message *message) {
  return (T *)message->data;
}

#endif /* __NAPI_CTP_H__ */
