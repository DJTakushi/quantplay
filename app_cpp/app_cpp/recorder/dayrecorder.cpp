#include "dayrecorder.h"

dayrecorder::dayrecorder(){}

ymd_date dayrecorder::get_current_date(){
  /** returns 1900-01-01 if no date initialized**/
  ymd_date out{std::chrono::January/1/1900};
  if(days_.size()>0){
    out = days_.back()->get_date();
  }
  return out;
}

void dayrecorder::start_new_day(ymd_date date){
  days_.push_back(new daydata(date));
}

void dayrecorder::set_current_open(double open){
  if(days_.size()>0){
    days_.back()->set_open(open);
  }
}

void dayrecorder::set_current_close(double close){
  if(days_.size()>0){
    days_.back()->set_close(close);
  }
}

void dayrecorder::set_current_portfolio_value(double portfolio_value){
  if(days_.size()>0){
    days_.back()->set_portfolio(portfolio_value);
  }
}
void dayrecorder::add_data(daydata d){
  if(get_current_date() != d.get_date()){
    start_new_day(d.get_date());
  }
  set_current_open(d.get_open());
  set_current_close(d.get_high());
  set_current_portfolio_value(d.get_portfolio());
}
void dayrecorder::print(){
  for(auto day : days_){
    day->print();
  }
}