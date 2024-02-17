#include <iostream>
#include <iomanip>
#include "transaction.h"
transaction::transaction(std::time_t time, double value,
                          transactionType type){
  time_ = time;
  value_ = value;
  type_ = type;
}

void transaction::print(){
  std::cout << std::asctime(std::localtime(&time_)) << " : ";
  switch(type_){
    case transactionType::kBuy:
      std::cout << "buy";
      break;
    case transactionType::kSell:
      std::cout << "sell";
      break;
    default:
      std::cout << "unknown(?)";
  }
  std::cout <<" at " << std::fixed << std::setprecision(3)<<value_<<std::endl;
}

std::time_t transaction::get_time(){return time_;}
double transaction::get_value(){return value_;}
transactionType transaction::get_type(){return type_;}
transactionStatus transaction::get_status(){return status_;};
void transaction::set_status(transactionStatus s){status_=s;};