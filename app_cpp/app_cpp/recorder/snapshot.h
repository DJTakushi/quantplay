#pragma once
#include "ohlcv.h"
#include "portfolio.h"
struct snapshot : public ohlcv, public portfolio{
  snapshot(ohlcv * o, portfolio *p);
  void print();
};