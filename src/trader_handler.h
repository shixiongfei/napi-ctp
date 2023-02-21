/*
 * trader_handler.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __TRADER_HANDLER_H__
#define __TRADER_HANDLER_H__

#include "ThostFtdcTraderApi.h"

class TraderHandler : public CThostFtdcTraderSpi {
public:
  TraderHandler();
  virtual ~TraderHandler();

private:
  CThostFtdcTraderApi *m_pAPI;
};

#endif /* __TRADER_HANDLER_H__ */
