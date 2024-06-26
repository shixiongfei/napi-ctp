/*
 * message_queue.h
 *
 * Copyright (c) 2022-2024 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __MESSAGE_QUEUE_H__
#define __MESSAGE_QUEUE_H__

#include "napi_ctp.h"
#include <queue>
#include <uv.h>

enum { QUEUE_FAILED = -1, QUEUE_TIMEOUT, QUEUE_SUCCESS };

class MessageQueue {
public:
  MessageQueue();
  ~MessageQueue();

  bool push(int event, int data, int requestId, int isLast);

  bool push(int event) { return push(event, 0, 0, Undefined); }
  bool push(int event, int data) { return push(event, data, 0, Undefined); }

  template <typename T>
  bool push(int event, T *data, CThostFtdcRspInfoField *pRspInfo, int requestId, int isLast) {
    int64_t timestamp = nowtick();
    size_t bufsize = sizeof(Message);

    if (data)
      bufsize += sizeof(T);

    if (pRspInfo && pRspInfo->ErrorID != 0)
      bufsize += sizeof(CThostFtdcRspInfoField);

    Message *message = (Message *)malloc(bufsize);
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

    return push(message, event, (uintptr_t)p, (uintptr_t)e, requestId, isLast, timestamp);
  }

  template <typename T>
  bool push(int event, T *data, int requestId, int isLast) { return push<T>(event, data, nullptr, requestId, isLast); }

  template <typename T>
  bool push(int event, T *data) { return push<T>(event, data, 0, Undefined); }

  template <typename T>
  bool push(int event, T *data, CThostFtdcRspInfoField *pRspInfo) { return push<T>(event, data, pRspInfo, 0, Undefined); }

  int pop(Message **message, unsigned int millisec);
  void done(Message *message);

private:
  bool push(Message *message, int event, uintptr_t data, uintptr_t rspInfo, int requestId, int isLast, int64_t timestamp);

private:
  uv_cond_t _cond;
  uv_mutex_t _mutex;
  volatile int _waiting;
  std::queue<Message *> _queue;
};

#endif /* __MESSAGE_QUEUE_H__ */
