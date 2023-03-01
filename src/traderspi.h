/*
 * traderspi.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __TRADERSPI_H__
#define __TRADERSPI_H__

#include "napi_ctp.h"
#include <queue>

class TraderSpi : public CThostFtdcTraderSpi {
public:
  TraderSpi();
  virtual ~TraderSpi();

private:
  Mutex _mutex;
  std::queue<Message> _queue;
};

#endif /* __TRADERSPI_H__ */
