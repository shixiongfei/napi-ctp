/*
 * message_queue.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __MESSAGE_QUEUE_H__
#define __MESSAGE_QUEUE_H__

#include <queue>
#include <uv.h>

enum { QUEUE_FAILED = -1, QUEUE_TIMEOUT, QUEUE_SUCCESS };

typedef struct Message {
  int event;
  uintptr_t data;
} Message;

class MessageQueue {
public:
  MessageQueue();
  ~MessageQueue();

  void push(const Message &message);
  int pop(Message *message, unsigned int millisec);

private:
  uv_cond_t _cond;
  uv_mutex_t _mutex;
  int _waiting;
  std::queue<Message> _queue;
};

#endif /* __MESSAGE_QUEUE_H__ */
