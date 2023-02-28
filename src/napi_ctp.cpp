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

#include "napi_ctp.h"
#include "mdapi.h"
#include "traderapi.h"
#include <stdlib.h>
#include <string.h>

static void destructor(napi_env env, void *data, void *hint) {
  napi_status status;
  Constructors *constructors = (Constructors *)data;

  if (!constructors)
    return;

  if (constructors->marketData) {
    status = napi_delete_reference(env, constructors->marketData);
    assert(status == napi_ok);
  }

  if (constructors->trader) {
    status = napi_delete_reference(env, constructors->trader);
    assert(status == napi_ok);
  }

  free(constructors);
}

static napi_status defineConstructors(napi_env env) {
  napi_status status;
  Constructors *constructors = (Constructors *)malloc(sizeof(Constructors));

  if (!constructors) {
    napi_throw_error(env, "OutOfMemory", "Out of memory");
    return napi_object_expected;
  }

  memset(constructors, 0, sizeof(Constructors));

  status = defineMarketData(env, &constructors->marketData);
  assert(status == napi_ok);

  status = defineTrader(env, &constructors->trader);
  assert(status == napi_ok);

  return napi_set_instance_data(env, constructors, destructor, nullptr);
}

static napi_status defineMethods(napi_env env, napi_value exports) {
  napi_property_descriptor props[] = {
      NAPI_DEFINE_METHOD(createTrader),
      NAPI_DEFINE_METHOD(createMarketData),
  };
  return napi_define_properties(env, exports, arraysize(props), props);
}

static napi_value init(napi_env env, napi_value exports) {
  napi_status status;

  status = defineConstructors(env);
  assert(status == napi_ok);

  status = defineMethods(env, exports);
  assert(status == napi_ok);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)

static long volatile sequenceLastId = 0;

int sequenceId() {
#ifdef _MSC_VER
  return (int)InterlockedIncrement(&sequenceLastId);
#else
  return (int)__sync_add_and_fetch(&sequenceLastId, 1);
#endif
}

Mutex::Mutex() {
#ifdef _WIN32
  InitializeCriticalSection(&_mutex);
#else
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&_mutex, &attr);
  pthread_mutexattr_destroy(&attr);
#endif
}

Mutex::~Mutex() {
#ifdef _WIN32
  DeleteCriticalSection(&_mutex);
#else
  pthread_mutex_destroy(&_mutex);
#endif
}

void Mutex::lock() {
#ifdef _WIN32
  EnterCriticalSection(&_mutex);
#else
  pthread_mutex_lock(&_mutex);
#endif
}

bool Mutex::tryLock() {
#ifdef _WIN32
  return TRUE == TryEnterCriticalSection(&_mutex);
#else
  return 0 == pthread_mutex_trylock(&_mutex);
#endif
}

void Mutex::unlock() {
#ifdef _WIN32
  LeaveCriticalSection(&_mutex);
#else
  pthread_mutex_unlock(&_mutex);
#endif
}

Constructors *getConstructors(napi_env env) {
  napi_status status;
  Constructors *constructors;

  status = napi_get_instance_data(env, (void **)&constructors);
  assert(status == napi_ok);

  return constructors;
}

napi_status defineClass(napi_env env, const char *name,
                        napi_callback constructor, size_t propertyCount,
                        const napi_property_descriptor *properties,
                        napi_ref *result) {
  napi_status status;
  napi_value cons;

  status = napi_define_class(env, name, NAPI_AUTO_LENGTH, constructor, nullptr,
                             propertyCount, properties, &cons);
  assert(status == napi_ok);

  return napi_create_reference(env, cons, 1, result);
}

napi_value createInstance(napi_env env, napi_callback_info info,
                          napi_ref constructor, size_t argc) {
  napi_status status;
  napi_value cons, instance;

  status = napi_get_reference_value(env, constructor, &cons);
  assert(status == napi_ok);

  if (argc > 0) {
    dynarray(napi_value, args, argc);

    status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    assert(status == napi_ok);

    status = napi_new_instance(env, cons, argc, args, &instance);
    assert(status == napi_ok);
  } else {
    status = napi_new_instance(env, cons, 0, nullptr, &instance);
    assert(status == napi_ok);
  }

  return instance;
}
