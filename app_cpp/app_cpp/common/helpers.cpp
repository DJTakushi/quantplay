#include "helpers.h"
#include <iomanip>
#include <sstream>

time_t datetime_to_time_t(std::string str){
  struct tm tm;
  tm.tm_isdst=-1;//"negative if no information is available."
  strptime(str.c_str(), TD_FORMAT, &tm);
  time_t t = mktime(&tm);  // t is now your desired time_t
  return t;
}

std::string time_t_to_local_str(time_t t) {
  std::stringstream ss;
  ss << std::put_time(std::localtime(&t),TD_FORMAT);
  return ss.str();
}

std::string time_t_to_gmt_str(time_t t) {
  std::stringstream ss;
  ss << std::put_time(std::gmtime(&t),TD_FORMAT);
  return ss.str();
}