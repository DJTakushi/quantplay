#include "ohlcv.h"
ohlcv::ohlcv(std::time_t t, double o, double h, double l, double c, int v)
    :time_(t),open_(o),high_(h),low_(l),close_(c),volume_(v){};

ohlcv::ohlcv(ohlcv* o){
  set_time(o->get_time());
  set_open(o->get_open());
  set_high(o->get_high());
  set_low(o->get_low());
  set_close(o->get_close());
}

void ohlcv::set_open(double open){open_=open;}
double ohlcv::get_open(){return open_;}

void ohlcv::set_high(double high){high_=high;}
double ohlcv::get_high(){return high_;}

void ohlcv::set_low(double low){low_=low;}
double ohlcv::get_low(){return low_;}

void ohlcv::set_close(double close){close_=close;}
double ohlcv::get_close(){return close_;}

void ohlcv::set_volume(int vol){volume_=vol;}
int ohlcv::get_volume(){return volume_;}; 

void ohlcv::set_time(std::time_t t){time_=t;}
std::time_t ohlcv::get_time(){return time_;}

ymd_date ohlcv::get_date(){
  std::chrono::time_point tp = std::chrono::system_clock::from_time_t(time_);
  return std::chrono::floor<std::chrono::days>(tp);
}