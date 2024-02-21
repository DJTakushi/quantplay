#pragma once
struct ohlcv{
  double open_ = 0;
  double high_ = 0;
  double low_ = 0;
  double close_ = 0;
  int volume_ = 0;
  ohlcv(){};
  ohlcv(double o, double h, double l, double c, int v):open_(o),high_(h),low_(l),close_(c),volume_(v){};

  void set_open(double open);
  double get_open();

  void set_high(double high);
  double get_high();

  void set_low(double low);
  double get_low();

  void set_close(double close);
  double get_close();
};