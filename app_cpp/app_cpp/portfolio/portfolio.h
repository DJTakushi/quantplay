#pragma once
#include "transaction.h"
#include <vector>
class portfolio{
  std::vector<transaction> transactions_;
  double balance_ = 0;
  int shares_ = 0;
  double value_current_ = 0;

public:
  portfolio(double starting_balance);
  portfolio(double bal, int shares, double val);
  portfolio(portfolio* p);
  double get_balance();
  double get_equity_value();
  double get_portfolio_value();
  int get_shares();
  void set_current_value(double val);
  void addTransaction(transaction t);
};