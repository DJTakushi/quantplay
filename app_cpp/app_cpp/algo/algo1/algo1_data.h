#pragma once
#include <ctime>
struct algo1_data{
  std::time_t time_;
  double open_;
  double close_;
  int volume_;
  algo1_data(std::time_t time, double open, double close, int volume)
      : time_(time),
      open_(open),
      close_(close),
      volume_(volume){};
};