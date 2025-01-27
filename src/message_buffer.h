/*
 * message_buffer.h
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __MESSAGE_BUFFER_H__
#define __MESSAGE_BUFFER_H__

#include "concurrentqueue.h"

class MessageBuffer {
public:
  MessageBuffer(size_t size);
  ~MessageBuffer();

  void *alloc(size_t size);
  void dispose(void *buffer);

private:
  void *allocBlock(size_t block_size);

private:
  size_t _block_size, _mem_size;
  moodycamel::ConcurrentQueue<void *> _buffers;
};

#endif /* __MESSAGE_BUFFER_H__ */
