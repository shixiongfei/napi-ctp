/*
 * mdspi.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __MDSPI_H__
#define __MDSPI_H__

#include "napi_ctp.h"

class MdSpi : public CThostFtdcMdSpi {
public:
  MdSpi();
  virtual ~MdSpi();
};

#endif /* __MDSPI_H__ */
