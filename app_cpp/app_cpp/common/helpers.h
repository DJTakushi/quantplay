#pragma once
#include <ctime>
#include <string>
#define TD_FORMAT "%Y-%m-%d %H:%M:%S"

time_t datetime_to_time_t(std::string str);