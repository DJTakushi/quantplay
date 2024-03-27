#include "snapshot.h"
#include <iostream>
#include <iomanip>
snapshot::snapshot(std::string tm,
                  double open,
                  double high,
                  double low,
                  double close,
                  int volume,
                  double balance,
                  int shares,
                  double value) :
                  ohlcv(tm,open,high,low,close,volume),
                  portfolio(balance,shares,value) {}
snapshot::snapshot(ohlcv * o, portfolio* p): ohlcv(o), portfolio(p){}
snapshot::snapshot(snapshot* s) : ohlcv(s), portfolio(s){}
void snapshot::print(){
  std::cout << std::put_time(std::localtime(&time_),"%c %Z") << " : ";
  std::cout << "balance : "<<std::to_string(get_balance())<<",";
  std::cout << "shares : "<<std::to_string(get_shares());
  std::cout << " at $"<<std::to_string(get_equity_value());
  std::cout << "("<<std::to_string(get_portfolio_value())<<") [";
  std::cout << std::to_string(get_portfolio_value())<<"]"<<std::endl;
}