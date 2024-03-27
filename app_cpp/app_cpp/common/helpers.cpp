#include "helpers.h"

time_t datetime_to_time_t(std::string str){
  struct tm tm;
  strptime(str.c_str(), TD_FORMAT, &tm);
  time_t t = mktime(&tm);  // t is now your desired time_t
  return t;
}