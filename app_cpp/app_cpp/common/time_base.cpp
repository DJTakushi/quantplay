#include "time_base.h"
#include "helpers.h"

time_base::time_base() {};
time_base::time_base(std::time_t t) : time_(t) {};
time_base::time_base(std::string t) : time_(datetime_to_time_t(t)) {};
time_base::time_base(time_base * t) {
  time_ = t->get_time();
}

void time_base::set_time(std::time_t t){time_=t;}
std::time_t time_base::get_time(){return time_;}

ymd_date time_base::get_date(){
  std::chrono::time_point tp = std::chrono::system_clock::from_time_t(time_);
  return std::chrono::floor<std::chrono::days>(tp);
}