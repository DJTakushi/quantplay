#pragma once
#include <list>
#include "ohlcv.h"
#include "transaction.h"
class algo_i{
  public:
  virtual transaction* process() = 0;
  virtual void addData(std::list<ohlcv*> data_list) = 0;
  virtual ohlcv* get_latest_data() = 0;
};