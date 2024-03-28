#pragma once
#include <ctime>
#include <string>
#define TD_FORMAT "%Y-%m-%d %H:%M:%S"

time_t datetime_to_time_t(std::string str);
std::string time_t_to_local_str(time_t t);
std::string time_t_to_gmt_str(time_t t);