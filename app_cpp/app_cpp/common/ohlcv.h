#pragma once
#include "typedefs.h"
#include <ctime>
struct ohlcv{
  std::time_t time_;
  double open_ = 0;
  double high_ = 0;
  double low_ = 0;
  double close_ = 0;
  int volume_ = 0;
  ohlcv(){};
  ohlcv(std::time_t t, double o, double h, double l, double c, int v);
  ohlcv(ohlcv* o);
  void set_open(double open);
  double get_open();

  void set_high(double high);
  double get_high();

  void set_low(double low);
  double get_low();

  void set_close(double close);
  double get_close();

  void set_volume(int vol);
  int get_volume(); 

  void set_time(time_t t);
  time_t get_time();

  ymd_date get_date();

  void print_ohlcv();
};