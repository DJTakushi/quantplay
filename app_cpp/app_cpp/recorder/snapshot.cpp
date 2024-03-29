#include "snapshot.h"
#include <iostream>
#include <iomanip>
snapshot::snapshot(std::string tm,
                  double balance,
                  int shares,
                  double value) :
                  time_base(tm),
                  portfolio(balance,shares,value) {}
snapshot::snapshot(time_base * tb, portfolio* p): time_base(tb), portfolio(p){}
snapshot::snapshot(snapshot* s) : time_base(s), portfolio(s){}
void snapshot::print(){
  std::cout << std::put_time(std::localtime(&time_),"%c %Z") << " : ";
  std::cout << "balance : "<<std::to_string(get_balance())<<",";
  std::cout << "shares : "<<std::to_string(get_shares());
  std::cout << " at $"<<std::to_string(get_equity_value());
  std::cout << "("<<std::to_string(get_portfolio_value())<<") [";
  std::cout << std::to_string(get_portfolio_value())<<"]"<<std::endl;
}