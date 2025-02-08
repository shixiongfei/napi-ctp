/*
 * spievent.h
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __SPIEVENT_H__
#define __SPIEVENT_H__

#include "message_buffer.h"
#include "napi_ctp.h"
#include <map>

class SpiEvent {
public:
  SpiEvent(napi_env env, const std::map<int, napi_threadsafe_function> *tsfns);
  virtual ~SpiEvent();

  void done(Message *message);

protected:
  void push(int event);
  void push(int event, int data);
  void push(int event, int data, int requestId, int isLast);

  template <typename T>
  void push(int event, T *data, CThostFtdcRspInfoField *pRspInfo, int requestId, int isLast) {
    auto iter = _tsfns->find(event);

    if (iter == _tsfns->end())
      return;

    size_t bufsize = sizeof(Message);

    if (data)
      bufsize += sizeof(T);

    if (pRspInfo && pRspInfo->ErrorID != 0)
      bufsize += sizeof(CThostFtdcRspInfoField);

    Message *message = (Message *)_buffer.alloc(bufsize);
    T *p = (T *)(message + 1);
    CThostFtdcRspInfoField *e = (CThostFtdcRspInfoField *)(p + 1);

    if (message && data)
      *p = *data;
    else
      p = nullptr;

    if (message && pRspInfo && pRspInfo->ErrorID != 0)
      *e = *pRspInfo;
    else
      e = nullptr;

    push(iter->second, message, event, (uintptr_t)p, (uintptr_t)e, requestId, isLast);
  }

  template <typename T>
  void push(int event, T *data, int requestId, int isLast) {
    push<T>(event, data, nullptr, requestId, isLast);
  }

  template <typename T>
  void push(int event, T *data) {
    push<T>(event, data, 0, Undefined);
  }

  template <typename T>
  void push(int event, T *data, CThostFtdcRspInfoField *pRspInfo) {
    push<T>(event, data, pRspInfo, 0, Undefined);
  }

private:
  void push(napi_threadsafe_function tsfn, Message *message, int event, uintptr_t data, uintptr_t rspInfo, int requestId, int isLast);

private:
  static MessageBuffer _buffer;

private:
  napi_env _env;
  const std::map<int, napi_threadsafe_function> *_tsfns;
};

#endif /* __SPIEVENT_H__ */
