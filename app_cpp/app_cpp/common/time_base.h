#pragma once
#include <ctime>
#include <string>
#include "typedefs.h"
struct time_base{
  std::time_t time_;

  time_base();
  time_base(std::time_t t);
  time_base(std::string t);
  time_base(time_base * t);

  void set_time(time_t t);
  time_t get_time();

  ymd_date get_date();
};