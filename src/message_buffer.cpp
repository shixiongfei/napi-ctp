/*
 * message_buffer.cpp
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "message_buffer.h"

#define bufferEntry(buffer) ((char *)buffer - sizeof(int))
#define bufferOffset(buffer) ((char *)buffer + sizeof(int))

MessageBuffer::MessageBuffer(size_t size)
    : _block_size(size), _mem_size(size - sizeof(int)) {
}

MessageBuffer::~MessageBuffer() {
  void *buffer = nullptr;

  while (_buffers.try_dequeue(buffer)) {
    free(bufferEntry(buffer));
    buffer = nullptr;
  }
}

void *MessageBuffer::alloc(size_t size) {
  static thread_local moodycamel::ConsumerToken token(_buffers);
  void *buffer = nullptr;

  if (size > _mem_size)
    return allocBlock(size + sizeof(int));

  if (!_buffers.try_dequeue(token, buffer))
    return allocBlock(_block_size);

  return bufferOffset(buffer);
}

void MessageBuffer::free(void *buffer) {
  static thread_local moodycamel::ProducerToken token(_buffers);
  void *entry = bufferEntry(buffer);
  int block_size = *(int *)entry;

  if (block_size != _block_size) {
    free(entry);
    return;
  }

  _buffers.enqueue(token, entry);
}

void *MessageBuffer::allocBlock(size_t block_size) {
  void *buffer = malloc(block_size);
  *(int *)buffer = block_size;
  return bufferOffset(buffer);
}
