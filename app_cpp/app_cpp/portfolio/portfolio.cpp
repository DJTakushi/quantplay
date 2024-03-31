#include "portfolio.h"
#include <iostream>

portfolio::portfolio(double starting_balance){
  balance_ = starting_balance;
}
portfolio::portfolio(std::string tm, double bal, int shares, double val) :
    time_base(tm), balance_(bal), shares_(shares), value_current_(val){}

portfolio::portfolio(portfolio* p){
  time_ = p->get_time();
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
void portfolio::print(){
  std::cout << std::put_time(std::localtime(&time_),"%c %Z") << " : ";
  std::cout << "balance : "<<std::to_string(get_balance())<<",";
  std::cout << "shares : "<<std::to_string(get_shares());
  std::cout << " at $"<<std::to_string(get_equity_value());
  std::cout << "("<<std::to_string(get_portfolio_value())<<") [";
  std::cout << std::to_string(get_portfolio_value())<<"]"<<std::endl;
}