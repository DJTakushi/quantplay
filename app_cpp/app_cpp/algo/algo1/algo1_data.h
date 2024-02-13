#pragma once
struct algo1_data{
  double open_;
  double close_;
  int volume_;
  algo1_data(double open, double close, int volume) : open_(open),
                                                      close_(close),
                                                      volume_(volume){};
};