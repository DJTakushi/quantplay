#include <iostream>
#include <iomanip>
#include "transaction.h"
transaction::transaction(std::time_t time, double value,
                          std::string transaction){
  time_ = time;
  value_ = value;
  transaction_ = transaction;
}

void transaction::print(){
  std::cout << std::asctime(std::localtime(&time_)) << " : ";
  std::cout << transaction_;
  std::cout <<" at " << std::setprecision(3)<<value_<<std::endl;
}

std::time_t transaction::get_time(){return time_;}
double transaction::get_value(){return value_;}
std::string transaction::get_transaction(){return transaction_;}