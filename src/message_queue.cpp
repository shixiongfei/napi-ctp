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
#include <stdio.h>

MessageBuffer MessageQueue::_buffer(4096);

MessageQueue::MessageQueue() {
}

MessageQueue::~MessageQueue() {
}

bool MessageQueue::push(int event, int data, int requestId, int isLast) {
  Message *message = (Message *)_buffer.alloc(sizeof(Message));
  return push(message, event, data, 0, requestId, isLast);
}

int MessageQueue::pop(Message **message, unsigned int millisec) {
  if (!message)
    return QUEUE_FAILED;

  return _queue.wait_dequeue_timed(*message, std::chrono::milliseconds(millisec)) ? QUEUE_SUCCESS : QUEUE_TIMEOUT;
}

void MessageQueue::done(Message *message) {
  _buffer.dispose(message);
}

bool MessageQueue::push(Message *message, int event, uintptr_t data, uintptr_t rspInfo, int requestId, int isLast) {
  if (!message) {
    fprintf(stderr, "Push message failed, out of memory\n");
    return false;
  }

  message->event = event;
  message->isLast = isLast;
  message->requestId = requestId;
  message->data = data;
  message->rspInfo = rspInfo;

  return _queue.enqueue(message);
}
