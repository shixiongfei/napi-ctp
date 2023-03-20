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
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <iconv.h>
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
    dynarray(napi_value, argv, argc);

    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    assert(status == napi_ok);

    status = napi_new_instance(env, cons, argc, argv, &instance);
    assert(status == napi_ok);
  } else {
    status = napi_new_instance(env, cons, 0, nullptr, &instance);
    assert(status == napi_ok);
  }

  return instance;
}

static char *toUTF8(const char *codepage, const char *mbstr, int len,
                    char *utf8str) {
#ifndef _WIN32
  iconv_t cd;
  size_t inlen = len, outlen = len * sizeof(int);

  cd = iconv_open("UTF-8//TRANSLIT", codepage);

  if (((iconv_t)(-1)) == cd)
    return 0;

  iconv(cd, (char **)&mbstr, &inlen, &utf8str, &outlen);
  iconv_close(cd);

  return utf8str;
#else
  int wlen;
  dynarray(wchar_t, wcstr, len + 1);

  memset(wcstr, 0, (len + 1) * sizeof(wchar_t));

  wlen = MultiByteToWideChar(CP_ACP, 0, mbstr, len, wcstr, len + 1);
  WideCharToMultiByte(CP_UTF8, 0, wcstr, wlen, utf8str, len * sizeof(wchar_t),
                      NULL, NULL);
  return utf8str;
#endif
}

napi_status objectSetString(napi_env env, napi_value object, const char *name,
                            const char *string) {
  napi_status status;
  napi_value value;
  int len = (int)strlen(string);
  dynarray(char, utf8str, len * 6 + 1);

  status = napi_create_string_utf8(env, toUTF8("GBK", string, len, utf8str),
                                   NAPI_AUTO_LENGTH, &value);
  assert(status == napi_ok);

  return napi_set_named_property(env, object, name, value);
}

napi_status objectSetInt32(napi_env env, napi_value object, const char *name,
                           int32_t number) {
  napi_status status;
  napi_value value;

  status = napi_create_int32(env, number, &value);
  assert(status == napi_ok);

  return napi_set_named_property(env, object, name, value);
}

napi_status objectSetUint32(napi_env env, napi_value object, const char *name,
                            uint32_t number) {
  napi_status status;
  napi_value value;

  status = napi_create_uint32(env, number, &value);
  assert(status == napi_ok);

  return napi_set_named_property(env, object, name, value);
}

napi_status objectSetInt64(napi_env env, napi_value object, const char *name,
                           int64_t number) {
  napi_status status;
  napi_value value;

  status = napi_create_int64(env, number, &value);
  assert(status == napi_ok);

  return napi_set_named_property(env, object, name, value);
}

napi_status objectSetDouble(napi_env env, napi_value object, const char *name,
                            double number) {
  napi_status status;
  napi_value value;

  status = napi_create_double(env, number, &value);
  assert(status == napi_ok);

  return napi_set_named_property(env, object, name, value);
}
