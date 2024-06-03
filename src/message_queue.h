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

  template <typename T>
  bool push(int event, T *data, int requestId, int isLast) {
    if (!data)
      return push(event, 0, requestId, isLast);

    int64_t timestamp = nowtick();
    Message *message = (Message *)malloc(sizeof(Message) + sizeof(T));
    T *p = (T *)(message + 1);

    if (message)
      *p = *data;

    return push(message, event, (uintptr_t)p, requestId, isLast, timestamp);
  }

  int pop(Message **message, unsigned int millisec);
  void done(Message *message);

private:
  bool push(Message *message, int event, uintptr_t data, int requestId, int isLast, int64_t timestamp);

private:
  uv_cond_t _cond;
  uv_mutex_t _mutex;
  volatile int _waiting;
  std::queue<Message *> _queue;
};

#endif /* __MESSAGE_QUEUE_H__ */
