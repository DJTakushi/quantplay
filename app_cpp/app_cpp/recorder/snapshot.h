#pragma once
#include "time_base.h"
#include "portfolio.h"
struct snapshot : public time_base, public portfolio{
  snapshot(std::string tm, double balance, int shares, double value);
  snapshot(time_base * tb, portfolio *p);
  snapshot(snapshot* s);
  void print();
};