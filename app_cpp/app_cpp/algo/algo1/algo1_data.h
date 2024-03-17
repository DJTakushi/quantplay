#pragma once
#include "ohlcv.h"
#include <ctime>
struct algo1_data : public ohlcv{
  algo1_data(std::time_t time,
              double open,
              double high,
              double low,
              double close,
              int volume)
              : ohlcv(time,open,high,low,close,volume){};
  algo1_data(algo1_data* d):ohlcv(d){}
  algo1_data():ohlcv(){};
};