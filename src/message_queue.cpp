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
#include "guard.h"

MessageQueue::MessageQueue() : _waiting(0) {
  uv_cond_init(&_cond);
  uv_mutex_init_recursive(&_mutex);
}

MessageQueue::~MessageQueue() {
  uv_cond_destroy(&_cond);
  uv_mutex_destroy(&_mutex);
}

void MessageQueue::push(short event, uintptr_t data, int requestId, short isLast) {
  Message *message = (Message *)malloc(sizeof(Message));
  assert(message != nullptr);

  message->event = event;
  message->isLast = isLast;
  message->requestId = requestId;
  message->timestamp = (int64_t)(hrtime(nullptr, nullptr) * 1000.0);
  message->data = data;

  {
    AutoLock(_mutex);

    _queue.push(message);

    if (_waiting > 0)
      uv_cond_signal(&_cond);
  }
}

int MessageQueue::pop(Message **message, unsigned int millisec) {
  int ret;

  if (!message)
    return QUEUE_FAILED;

  {
    AutoLock(_mutex);

    while (_queue.empty()) {
      _waiting += 1;
      ret = uv_cond_timedwait(&_cond, &_mutex, (uint64_t)millisec * 1000 * 1000);
      _waiting -= 1;

      if (ret != 0)
        return ret == UV_ETIMEDOUT ? QUEUE_TIMEOUT : QUEUE_FAILED;
    }

    *message = _queue.front();
    _queue.pop();
  }

  return QUEUE_SUCCESS;
}

void MessageQueue::done(Message *message, bool isFreeData) {
  if (isFreeData)
    freeData(message->data);

  free(message);
}
