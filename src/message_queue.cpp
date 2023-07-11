/*
 * message_queue.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "message_queue.h"

MessageQueue::MessageQueue() : _waiting(0) {
  uv_cond_init(&_cond);
  uv_mutex_init_recursive(&_mutex);
}

MessageQueue::~MessageQueue() {
  uv_cond_destroy(&_cond);
  uv_mutex_destroy(&_mutex);
}

void MessageQueue::push(int event, uintptr_t data) {
  Message *message = (Message *)malloc(sizeof(Message));

  message->event = event;
  message->data = data;

  uv_mutex_lock(&_mutex);

  _queue.push(message);

  if (_waiting > 0)
    uv_cond_signal(&_cond);

  uv_mutex_unlock(&_mutex);
}

int MessageQueue::pop(Message **message, unsigned int millisec) {
  int ret;

  if (!message)
    return QUEUE_FAILED;

  uv_mutex_lock(&_mutex);

  while (_queue.empty()) {
    _waiting += 1;
    ret = uv_cond_timedwait(&_cond, &_mutex, (uint64_t)millisec * 1000 * 1000);
    _waiting -= 1;

    if (ret != 0) {
      uv_mutex_unlock(&_mutex);
      return ret == UV_ETIMEDOUT ? QUEUE_TIMEOUT : QUEUE_FAILED;
    }
  }

  *message = _queue.front();
  _queue.pop();

  uv_mutex_unlock(&_mutex);

  return QUEUE_SUCCESS;
}
