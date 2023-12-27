#include "portfolio.h"
#include <iostream>

portfolio::portfolio(double starting_balance){
  balance_ = starting_balance;
}
double portfolio::get_balance(){
  return balance_;
}
double portfolio::get_equity_value(){
  return shares_*value_current_;
}
double portfolio::get_portfolio_value(){
  return balance_+get_equity_value();
}
int portfolio::get_shares(){
  return shares_;
}
void portfolio::set_current_value(double val){
  value_current_ = val;
}
void portfolio::addTransaction(transaction t){
  transactions_.push_back(t);
  switch(t.get_type()){
    case transactionType::kBuy:
      shares_+=1;
      balance_-=t.get_value();
      break;
    case transactionType::kSell:
      shares_-=1;
      balance_+=t.get_value();
      break;
    default:
      std::cout << "unrecognized type"<<std::endl;

  }
}