/*
 * spievent.h
 *
 * Copyright (c) 2022-2024 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __SPIEVENT_H__
#define __SPIEVENT_H__

#include "message_queue.h"
#include "napi_ctp.h"
#include <map>

class SpiEvent {
public:
  SpiEvent(const std::map<int, napi_threadsafe_function> *tsfns);
  virtual ~SpiEvent();

  int poll(Message **message, unsigned int millisec = UINT_MAX);
  void done(Message *message);

protected:
  void quit(int event, int nCode = 0);

  void push(int event);
  void push(int event, int data);

  template <typename T>
  void push(int event, T *data, CThostFtdcRspInfoField *pRspInfo, int requestId, int isLast) {
    if (shouldPushEvent(event))
      _msgq.push<T>(event, data, pRspInfo, requestId, isLast);
  }

  template <typename T>
  void push(int event, T *data, int requestId, int isLast) {
    if (shouldPushEvent(event))
      _msgq.push<T>(event, data, requestId, isLast);
  }

  template <typename T>
  void push(int event, T *data) {
    if (shouldPushEvent(event))
      _msgq.push<T>(event, data);
  }

  template <typename T>
  void push(int event, T *data, CThostFtdcRspInfoField *pRspInfo) {
    if (shouldPushEvent(event))
      _msgq.push<T>(event, data, pRspInfo);
  }

private:
  bool shouldPushEvent(int event) { return _tsfns->find(event) != _tsfns->end(); }

private:
  const std::map<int, napi_threadsafe_function> *_tsfns;
  MessageQueue _msgq;
};

#endif /* __SPIEVENT_H__ */
