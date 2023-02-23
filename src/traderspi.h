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

class TraderSpi : public CThostFtdcTraderSpi {
public:
  TraderSpi();
  virtual ~TraderSpi();
};

#endif /* __TRADERSPI_H__ */
