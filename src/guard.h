/*
 * guard.h
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __GUARD_H__
#define __GUARD_H__

#include <functional>

#define __QUOTE__(name, id) name##id
#define _QUOTE(name, id) __QUOTE__(name, id)

class DeferGuard {
public:
  inline DeferGuard(const std::function<void(void)> &func)
      : _func(func) {
  }
  inline ~DeferGuard() {
    _func();
  }

private:
  std::function<void(void)> _func;
};

#define Defer DeferGuard _QUOTE(__guard_, __LINE__)

#endif /* __GUARD_H__ */
