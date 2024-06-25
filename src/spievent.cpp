/*
 * spievent.cpp
 *
 * Copyright (c) 2022-2024 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "spievent.h"

SpiEvent::SpiEvent(const std::map<int, napi_threadsafe_function> *tsfns)
  : _tsfns(tsfns) {}

SpiEvent::~SpiEvent() {
  Message *msg;

  while (QUEUE_SUCCESS == poll(&msg, 0))
    done(msg);
}

int SpiEvent::poll(Message **message, unsigned int millisec) {
  return _msgq.pop(message, millisec);
}

void SpiEvent::done(Message *message) {
  _msgq.done(message);
}

void SpiEvent::quit(int event, int nCode) {
  _msgq.push(event, nCode);
}

void SpiEvent::push(int event) {
  if (shouldPushEvent(event))
    _msgq.push(event);
}

void SpiEvent::push(int event, int data) {
  if (shouldPushEvent(event))
    _msgq.push(event, data);
}
