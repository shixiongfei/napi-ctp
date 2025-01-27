/*
 * message_queue.cpp
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "message_queue.h"
#include "guard.h"
#include <chrono>

MessageBuffer MessageQueue::_buffer(4096);

MessageQueue::MessageQueue() {
}

MessageQueue::~MessageQueue() {
}

bool MessageQueue::push(int event, int data, int requestId, int isLast) {
  int64_t timestamp = nowtick();
  Message *message = (Message *)_buffer.alloc(sizeof(Message));

  return push(message, event, data, 0, requestId, isLast, timestamp);
}

int MessageQueue::pop(Message **message, unsigned int millisec) {
  static thread_local moodycamel::ConsumerToken token(_queue);

  if (!message)
    return QUEUE_FAILED;

  if (!_queue.wait_dequeue_timed(token, *message, std::chrono::milliseconds(millisec)))
    return QUEUE_TIMEOUT;

  if (*message)
    (*message)->elapsed = (int)(nowtick() - (*message)->timestamp);

  return QUEUE_SUCCESS;
}

void MessageQueue::done(Message *message) {
  _buffer.free(message);
}

bool MessageQueue::push(Message *message, int event, uintptr_t data, uintptr_t rspInfo, int requestId, int isLast, int64_t timestamp) {
  static thread_local moodycamel::ProducerToken token(_queue);

  if (!message) {
    fprintf(stderr, "Push message failed, out of memory\n");
    return false;
  }

  message->event = event;
  message->isLast = isLast;
  message->requestId = requestId;
  message->elapsed = -1;
  message->timestamp = timestamp;
  message->data = data;
  message->rspInfo = rspInfo;

  return _queue.enqueue(token, message);
}
