#pragma once
#include "ohlcv.h"
#include <chrono>
typedef std::chrono::year_month_day ymd_date;
class daydata : public ohlcv{
  ymd_date date_;
  double portfolio_ = 0;

public:
  daydata(ymd_date date);
  daydata(ohlcv* o);

  ymd_date get_date();

  void set_portfolio(double portfolio_val);
  double get_portfolio();
  void print();
};