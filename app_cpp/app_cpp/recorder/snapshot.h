#pragma once
#include "ohlcv.h"
#include "portfolio.h"
struct snapshot : public ohlcv, public portfolio{
  snapshot(std::string tm, double open, double high, double low, double close,
      int volume, double balance, int shares, double value);
  snapshot(ohlcv * o, portfolio *p);
  snapshot(snapshot* s);
  void print();
};