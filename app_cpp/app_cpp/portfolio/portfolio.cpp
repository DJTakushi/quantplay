#include "portfolio.h"
#include <iostream>

portfolio::portfolio(double starting_balance){
  balance_ = starting_balance;
}
portfolio::portfolio(double bal, int shares, double val) :
    balance_(bal), shares_(shares), value_current_(val){}

portfolio::portfolio(portfolio* p){
  balance_=p->get_balance();
  shares_=p->get_shares();
  value_current_=p->value_current_;
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