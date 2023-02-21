/*
 * md_handler.h
 *
 * Copyright (c) 2022, 2023 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

#ifndef __MD_HANDLER_H__
#define __MD_HANDLER_H__

#include "ThostFtdcMdApi.h"

class MDHandler : public CThostFtdcMdSpi {
public:
  MDHandler();
  virtual ~MDHandler();

private:
  CThostFtdcMdApi *m_pAPI;
};

#endif /* __MD_HANDLER_H__ */
