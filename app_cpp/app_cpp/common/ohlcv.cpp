#include "ohlcv.h"
#include "helpers.h"
#include <iostream>
ohlcv::ohlcv(std::time_t t, double o, double h, double l, double c, int v)
    :time_(t),open_(o),high_(h),low_(l),close_(c),volume_(v){};

ohlcv::ohlcv(std::string t, double o, double h, double l, double c, int v) :
    open_(o),high_(h),low_(l),close_(c),volume_(v){
  time_ = datetime_to_time_t(t);
}

ohlcv::ohlcv(ohlcv* o){
  set_time(o->get_time());
  set_open(o->get_open());
  set_high(o->get_high());
  set_low(o->get_low());
  set_volume(o->get_volume());
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

void ohlcv::print_ohlcv(){
  std::cout << std::put_time(std::localtime(&time_),"%c %Z") << " :";
  std::cout << " open : "<<std::to_string(get_open())<<",";
  std::cout << " high : "<<std::to_string(get_high());
  std::cout << " low : "<<std::to_string(get_low());
  std::cout << " close : "<<std::to_string(get_close());
  std::cout << " volume : "<<std::to_string(get_volume())<<std::endl;
}