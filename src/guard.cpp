/*
 * guard.cpp
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#include "guard.h"

Guard::Guard(const std::function<void(void)> &func) : _func(func) {}

Guard::~Guard() { _func(); }
