/*
 * guard.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __GUARD_H__
#define __GUARD_H__

#include <functional>
#include <uv.h>

#define __QUOTE__(name, id) name##id
#define _QUOTE(name, id) __QUOTE__(name, id)

class DeferGuard {
public:
  inline DeferGuard(const std::function<void(void)> &func) : _func(func) {}
  inline ~DeferGuard() { _func(); }

private:
  std::function<void(void)> _func;
};

#define Defer DeferGuard _QUOTE(__guard_, __LINE__)

class LockGuard {
public:
  inline LockGuard(uv_mutex_t &mutex) : _mutex(&mutex) { uv_mutex_lock(_mutex); }
  inline LockGuard(uv_mutex_t *mutex) : _mutex(mutex) { uv_mutex_lock(_mutex); }
  inline ~LockGuard() { uv_mutex_unlock(_mutex); }

private:
  uv_mutex_t *_mutex;
};

#define AutoLock LockGuard _QUOTE(__lock_, __LINE__)

#endif /* __GUARD_H__ */
