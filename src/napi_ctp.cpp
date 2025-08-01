/*
 * napi_ctp.cpp
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "napi_ctp.h"
#include "is_utf8.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>

#define safe_localtime(time, tm) localtime_s(tm, time)
#else
#include <iconv.h>
#include <sys/time.h>

#define safe_localtime(time, tm) localtime_r(time, tm)
#endif

#include <atomic>

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

  if (napi_ok == napi_get_and_clear_last_exception(env, &exception))
    napi_fatal_exception(env, exception);

  fprintf(stderr, "NAPI check status = %d, file: %s, line: %d\n", status, file, line);
}

static std::atomic<int> sequenceLastId(1);

void setSequenceId(int seqid) {
  sequenceLastId = seqid;
}

int nextSequenceId(void) {
  return sequenceLastId.fetch_add(1);
}

int currentSequenceId(void) {
  return sequenceLastId;
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
  switch (type) {
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
  switch (type) {
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

static const char *toUTF8(const char *codepage, const char *mbstr, int len, char *utf8str) {
#ifndef _WIN32
  iconv_t cd;
  size_t inlen = len, outlen = len * sizeof(int) + 1;
  char *inbuffer = (char *)mbstr;
  char *outbuffer = utf8str;

  cd = iconv_open("UTF-8//TRANSLIT", codepage);

  if (((iconv_t)(-1)) == cd) {
    fprintf(stderr, "The iconv library is invalid, conversion to utf8 encoding failed, the original string will be used instead\n");
    return mbstr;
  }

  iconv(cd, &inbuffer, &inlen, &outbuffer, &outlen);
  iconv_close(cd);

  return utf8str;
#else
  int wlen;

  dynarray(wchar_t, wcstr, len + 1);
  memset(wcstr, 0, (len + 1) * sizeof(wchar_t));

  wlen = MultiByteToWideChar(CP_ACP, 0, mbstr, len, wcstr, len + 1);
  WideCharToMultiByte(CP_UTF8, 0, wcstr, wlen, utf8str, len * sizeof(int) + 1, nullptr, nullptr);

  return utf8str;
#endif
}

napi_status objectSetString(napi_env env, napi_value object, const char *name, const char *string) {
  napi_value value;
  int len = (int)strlen(string);

  if (is_utf8(string, len))
    CHECK(napi_create_string_utf8(env, string, NAPI_AUTO_LENGTH, &value));
  else {
    int utf8len = len * sizeof(int) + 1;

    dynarray(char, utf8str, utf8len);
    memset(utf8str, 0, utf8len);

    CHECK(napi_create_string_utf8(env, toUTF8("GB18030", string, len, utf8str), NAPI_AUTO_LENGTH, &value));
  }

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

#define equal(a, b) (fabs((a) - (b)) < DBL_EPSILON)

static double rounding(double number, int precision) {
  if (precision == 0)
    return round(number);

  double factor = pow(10.0, precision);
  double value = number * factor;
  double rounded = round(value);

  return equal(fabs(value - rounded), 0.5)
             ? (round(value / 2.0) * 2.0) / factor
             : rounded / factor;
}

napi_status objectSetDouble(napi_env env, napi_value object, const char *name, double number) {
  napi_value value;

  if (!equal(number, DBL_MAX))
    number = rounding(number, 5);

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

#define NIGHT_TRADING_TIME 30000

static void adjustActionDay(CThostFtdcDepthMarketDataField *pDepthMarketData) {
  struct tm tm;
  long sec;
  char actionDay[9] = {0};

  hrtime(&sec, nullptr);

  time_t time = (time_t)sec;
  safe_localtime(&time, &tm);

  int nowTime = tm.tm_hour * 10000 + tm.tm_min * 100 + tm.tm_sec;

  if (nowTime < NIGHT_TRADING_TIME) {
    char hour[] = {pDepthMarketData->UpdateTime[0], pDepthMarketData->UpdateTime[1], '\0'};
    char minute[] = {pDepthMarketData->UpdateTime[3], pDepthMarketData->UpdateTime[4], '\0'};
    char second[] = {pDepthMarketData->UpdateTime[6], pDepthMarketData->UpdateTime[7], '\0'};
    int updateTime = atoi(hour) * 10000 + atoi(minute) * 100 + atoi(second);

    if (updateTime > NIGHT_TRADING_TIME) {
      time -= (tm.tm_hour + 1) * 3600;
      safe_localtime(&time, &tm);
    }
  }

  strftime(actionDay, sizeof(actionDay), "%Y%m%d", &tm);
  strncpy(pDepthMarketData->ActionDay, actionDay, sizeof(pDepthMarketData->ActionDay));
}

CThostFtdcDepthMarketDataField *adjustDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
  if (pDepthMarketData)
    adjustActionDay(pDepthMarketData);

  return pDepthMarketData;
}
