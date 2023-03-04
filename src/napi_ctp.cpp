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

#ifdef _WIN32
#include <Windows.h>
#endif

static long volatile sequenceLastId = 0;

int sequenceId() {
#ifdef _MSC_VER
  return (int)InterlockedIncrement(&sequenceLastId);
#else
  return (int)__sync_add_and_fetch(&sequenceLastId, 1);
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
