#pragma once
#include "ohlcv.h"
#include <ctime>
struct algo1_data : public ohlcv{
  std::time_t time_;
  algo1_data(std::time_t time, double open, double high, double low, double close, int volume)
      : time_(time), ohlcv(open,high,low,close,volume){};
};