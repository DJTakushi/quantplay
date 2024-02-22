#include <iostream>
#include "daydata.h"

daydata::daydata(ymd_date date) : date_(date){}
daydata::daydata(ohlcv* o) : ohlcv(o){
  std::chrono::time_point tp = std::chrono::system_clock::from_time_t(time_);
  ymd_date date(std::chrono::floor<std::chrono::days>(tp));
  date_=date;
}

ymd_date daydata::get_date(){return date_;}

void daydata::set_portfolio(double portfolio_val){portfolio_ = portfolio_val;}
double daydata::get_portfolio(){return portfolio_;}

void daydata::print(){
  std::cout << date_ << " : ";
  std::cout << portfolio_ <<std::endl;
}