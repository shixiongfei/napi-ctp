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
#include <stdio.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <time.h>
#else
#include <iconv.h>
#include <sys/time.h>
#endif

#ifdef _WIN32
struct timezone {
  int tz_minuteswest; /* minutes W of Greenwich */
  int tz_dsttime;     /* type of dst correction */
};

static int gettimeofday(struct timeval *tv, struct timezone *tz) {
  static const uint64_t epoch = 116444736000000000ULL;
  static int tzflag = 0;
  FILETIME ft;
  ULARGE_INTEGER ui;
  uint64_t tmres;

  GetSystemTimeAsFileTime(&ft);

  ui.u.LowPart = ft.dwLowDateTime;
  ui.u.HighPart = ft.dwHighDateTime;

  /* convert into microseconds */
  tmres = (ui.QuadPart - epoch) / 10;

  tv->tv_sec = (long)(tmres / 1000000);
  tv->tv_usec = (long)(tmres % 1000000);

  if (tz) {
    if (!tzflag) {
      _tzset();
      tzflag = 1;
    }

    tz->tz_minuteswest = _timezone / 60;
    tz->tz_dsttime = _daylight;
  }

  return 0;
}
#endif

double hrtime(long *sec, long *usec) {
  struct timeval time;

  gettimeofday(&time, nullptr);

  if (sec)
    *sec = time.tv_sec;

  if (usec)
    *usec = time.tv_usec;

  return time.tv_sec + time.tv_usec / 1000000.0;
}

void checkStatus(napi_env env, napi_status status, const char *file, int line) {
  if (status == napi_ok)
    return;

  napi_value exception;

  assert(napi_get_and_clear_last_exception(env, &exception) == napi_ok);
  assert(napi_fatal_exception(env, exception) == napi_ok);

  fprintf(stderr, "Node-API check status = %d, file: %s, line: %d\n", status, file, line);
}

#ifdef _MSC_VER
#define atom_incr(p) InterlockedIncrement((LONG volatile *)(p))
#define atom_cas(p, o, n) ((o) == InterlockedCompareExchange((p), (n), (o)))
#else
#define atom_incr(p) __sync_add_and_fetch((p), 1)
#define atom_cas(p, o, n) __sync_bool_compare_and_swap((p), (o), (n))
#endif

#define atom_get(p, v)                                                         \
  do {                                                                         \
    *(v) = *(p);                                                               \
  } while (!atom_cas((p), *(v), *(v)))

static long volatile sequenceLastId = 0;

int nextSequenceId() {
  return (int)atom_incr(&sequenceLastId);
}

int currentSequenceId() {
  long sequenceId;
  atom_get(&sequenceLastId, &sequenceId);
  return (int)sequenceId;
}

bool isUndefined(napi_env env, napi_value value) {
  napi_valuetype valuetype;

  CHECK(napi_typeof(env, value, &valuetype));
  return valuetype == napi_undefined;
}

Constructors *getConstructors(napi_env env) {
  Constructors *constructors;

  CHECK(napi_get_instance_data(env, (void **)&constructors));
  return constructors;
}

napi_status defineClass(napi_env env, const char *name, napi_callback constructor, size_t propertyCount, const napi_property_descriptor *properties, napi_ref *result) {
  napi_value cons;

  CHECK(napi_define_class(env, name, NAPI_AUTO_LENGTH, constructor, nullptr, propertyCount, properties, &cons));
  return napi_create_reference(env, cons, 1, result);
}

napi_value createInstance(napi_env env, napi_callback_info info, napi_ref constructor, size_t argc) {
  napi_value cons, instance;

  CHECK(napi_get_reference_value(env, constructor, &cons));

  if (argc == 0) {
    CHECK(napi_new_instance(env, cons, 0, nullptr, &instance));
    return instance;
  }

  dynarray(napi_value, argv, argc);

  CHECK(napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
  CHECK(napi_new_instance(env, cons, argc, argv, &instance));

  return instance;
}

napi_status checkIsStringArray(napi_env env, napi_value value) {
  napi_value element;
  napi_valuetype valuetype;
  uint32_t length;
  bool isArray;

  CHECK(napi_is_array(env, value, &isArray));

  if (!isArray) {
    napi_throw_type_error(env, nullptr, "The parameter should be string an array");
    return napi_array_expected;
  }

  CHECK(napi_get_array_length(env, value, &length));

  for (uint32_t i = 0; i < length; ++i) {
    CHECK(napi_get_element(env, value, i, &element));
    CHECK(napi_typeof(env, element, &valuetype));

    if (valuetype != napi_string) {
      napi_throw_type_error(env, nullptr, "The parameter should be string an array");
      return napi_string_expected;
    }
  }

  return napi_ok;
}

napi_status checkIsObject(napi_env env, napi_value value) {
  napi_valuetype valuetype;

  CHECK(napi_typeof(env, value, &valuetype));

  if (valuetype != napi_object) {
    napi_throw_type_error(env, nullptr, "The parameter should be an object");
    return napi_object_expected;
  }

  return napi_ok;
}

static const char *getTypeString(napi_valuetype type) {
  switch(type) {
    case napi_undefined:
      return "undefined";
    case napi_null:
      return "null";
    case napi_boolean:
      return "boolean";
    case napi_number:
      return "number";
    case napi_string:
      return "string";
    case napi_symbol:
      return "symbol";
    case napi_object:
      return "object";
    case napi_function:
      return "function";
    case napi_external:
      return "external";
    case napi_bigint:
      return "bigint";
    default:
      return "<unknown type>";
  }
  return "<unknown type>";
}

static napi_status getTypeExpected(napi_valuetype type) {
  switch(type) {
    case napi_undefined:
      return napi_invalid_arg;
    case napi_null:
      return napi_invalid_arg;
    case napi_boolean:
      return napi_boolean_expected;
    case napi_number:
      return napi_number_expected;
    case napi_string:
      return napi_string_expected;
    case napi_symbol:
      return napi_name_expected;
    case napi_object:
      return napi_object_expected;
    case napi_function:
      return napi_function_expected;
    case napi_external:
      return napi_invalid_arg;
    case napi_bigint:
      return napi_bigint_expected;
    default:
      return napi_generic_failure;
  }
  return napi_generic_failure;
}

napi_status checkValueTypes(napi_env env, size_t argc, const napi_value *argv, const napi_valuetype *types) {
  napi_valuetype valuetype;

  for (size_t i = 0; i < argc; ++i) {
    CHECK(napi_typeof(env, argv[i], &valuetype));

    if (valuetype != types[i]) {
      char errors[64] = {0};

      snprintf(errors, sizeof(errors), "The parameter %d should be a %s", (int)i, getTypeString(types[i]));
      napi_throw_type_error(env, nullptr, errors);

      return getTypeExpected(types[i]);
    }
  }

  return napi_ok;
}

static char *toUTF8(const char *codepage, const char *mbstr, int len, char *utf8str) {
#ifndef _WIN32
  iconv_t cd;
  size_t inlen = len, outlen = len * sizeof(int);

  cd = iconv_open("UTF-8//TRANSLIT", codepage);

  if (((iconv_t)(-1)) == cd)
    return nullptr;

  iconv(cd, (char **)&mbstr, &inlen, &utf8str, &outlen);
  iconv_close(cd);

  return utf8str;
#else
  int wlen;

  dynarray(wchar_t, wcstr, len + 1);
  memset(wcstr, 0, (len + 1) * sizeof(wchar_t));

  wlen = MultiByteToWideChar(CP_ACP, 0, mbstr, len, wcstr, len + 1);
  WideCharToMultiByte(CP_UTF8, 0, wcstr, wlen, utf8str, len * sizeof(wchar_t), nullptr, nullptr);

  return utf8str;
#endif
}

napi_status objectSetString(napi_env env, napi_value object, const char *name, const char *string) {
  napi_value value;
  int len = (int)strlen(string);

  dynarray(char, utf8str, len * 6 + 1);
  memset(utf8str, 0, len * 6 + 1);
  toUTF8("GBK", string, len, utf8str);

  CHECK(napi_create_string_utf8(env, utf8str, NAPI_AUTO_LENGTH, &value));
  return napi_set_named_property(env, object, name, value);
}

napi_status objectSetInt32(napi_env env, napi_value object, const char *name, int32_t number) {
  napi_value value;

  CHECK(napi_create_int32(env, number, &value));
  return napi_set_named_property(env, object, name, value);
}

napi_status objectSetUint32(napi_env env, napi_value object, const char *name, uint32_t number) {
  napi_value value;

  CHECK(napi_create_uint32(env, number, &value));
  return napi_set_named_property(env, object, name, value);
}

napi_status objectSetInt64(napi_env env, napi_value object, const char *name, int64_t number) {
  napi_value value;

  CHECK(napi_create_int64(env, number, &value));
  return napi_set_named_property(env, object, name, value);
}

napi_status objectSetDouble(napi_env env, napi_value object, const char *name, double number) {
  napi_value value;

  CHECK(napi_create_double(env, number, &value));
  return napi_set_named_property(env, object, name, value);
}

napi_status objectSetChar(napi_env env, napi_value object, const char *name, char ch) {
  const char str[2] = {ch, 0};
  return objectSetString(env, object, name, str);
}

napi_status objectSetBoolean(napi_env env, napi_value object, const char *name, bool boolean) {
  napi_value value;

  CHECK(napi_get_boolean(env, boolean, &value));
  return napi_set_named_property(env, object, name, value);
}

napi_status objectSetBuffer(napi_env env, napi_value object, const char *name, const void *data, size_t len) {
  napi_value value;

  CHECK(napi_create_buffer_copy(env, len, data, nullptr, &value));
  return napi_set_named_property(env, object, name, value);
}

napi_status objectGetString(napi_env env, napi_value object, const char *name, char *buf, size_t bufsize, size_t *length) {
  napi_value value;
  bool hasProperty;

  CHECK(napi_has_named_property(env, object, name, &hasProperty));

  if (!hasProperty)
    return napi_ok;

  CHECK(napi_get_named_property(env, object, name, &value));

  if (isUndefined(env, value))
    return napi_ok;

  return napi_get_value_string_utf8(env, value, buf, bufsize, length);
}

napi_status objectGetInt32(napi_env env, napi_value object, const char *name, int32_t *number) {
  napi_value value;
  bool hasProperty;

  CHECK(napi_has_named_property(env, object, name, &hasProperty));

  if (!hasProperty)
    return napi_ok;

  CHECK(napi_get_named_property(env, object, name, &value));

  if (isUndefined(env, value))
    return napi_ok;

  return napi_get_value_int32(env, value, number);
}

napi_status objectGetUint32(napi_env env, napi_value object, const char *name, uint32_t *number) {
  napi_value value;
  bool hasProperty;

  CHECK(napi_has_named_property(env, object, name, &hasProperty));

  if (!hasProperty)
    return napi_ok;

  CHECK(napi_get_named_property(env, object, name, &value));

  if (isUndefined(env, value))
    return napi_ok;

  return napi_get_value_uint32(env, value, number);
}

napi_status objectGetInt64(napi_env env, napi_value object, const char *name, int64_t *number) {
  napi_value value;
  bool hasProperty;

  CHECK(napi_has_named_property(env, object, name, &hasProperty));

  if (!hasProperty)
    return napi_ok;

  CHECK(napi_get_named_property(env, object, name, &value));

  if (isUndefined(env, value))
    return napi_ok;

  return napi_get_value_int64(env, value, number);
}

napi_status objectGetDouble(napi_env env, napi_value object, const char *name, double *number) {
  napi_value value;
  bool hasProperty;

  CHECK(napi_has_named_property(env, object, name, &hasProperty));

  if (!hasProperty)
    return napi_ok;

  CHECK(napi_get_named_property(env, object, name, &value));

  if (isUndefined(env, value))
    return napi_ok;

  return napi_get_value_double(env, value, number);
}

napi_status objectGetChar(napi_env env, napi_value object, const char *name, char *ch) {
  char strbuf[8] = {0};
  size_t length = 0;

  CHECK(objectGetString(env, object, name, strbuf, arraysize(strbuf), &length));

  if (ch && length > 0)
    *ch = strbuf[0];

  return napi_ok;
}

napi_status objectGetBoolean(napi_env env, napi_value object, const char *name, bool *boolean) {
  napi_value value;
  bool hasProperty;

  CHECK(napi_has_named_property(env, object, name, &hasProperty));

  if (!hasProperty)
    return napi_ok;

  CHECK(napi_get_named_property(env, object, name, &value));

  if (isUndefined(env, value))
    return napi_ok;

  return napi_get_value_bool(env, value, boolean);
}
