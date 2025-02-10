/*
 * spievent.cpp
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "spievent.h"
#include <stdio.h>

MessageBuffer SpiEvent::_buffer(4096);

SpiEvent::SpiEvent(napi_env env, const std::unordered_map<int, napi_threadsafe_function> *tsfns)
    : _env(env), _tsfns(tsfns) {
}

SpiEvent::~SpiEvent() {
}

void SpiEvent::done(Message *message) {
  _buffer.dispose(message);
}

void SpiEvent::push(int event) {
  push(event, 0, 0, Undefined);
}

void SpiEvent::push(int event, int data) {
  push(event, data, 0, Undefined);
}

void SpiEvent::push(int event, int data, int requestId, int isLast) {
  auto iter = _tsfns->find(event);

  if (iter == _tsfns->end())
    return;

  Message *message = (Message *)_buffer.alloc(sizeof(Message));
  push(iter->second, message, event, data, 0, requestId, isLast);
}

void SpiEvent::push(napi_threadsafe_function tsfn, Message *message, int event, uintptr_t data, uintptr_t rspInfo, int requestId, int isLast) {
  if (!message) {
    fprintf(stderr, "Push message failed, out of memory\n");
    return;
  }

  message->event = event;
  message->isLast = isLast;
  message->requestId = requestId;
  message->data = data;
  message->rspInfo = rspInfo;

  napi_env env = _env;
  CHECK(napi_call_threadsafe_function(tsfn, (void *)message, napi_tsfn_blocking));
}
