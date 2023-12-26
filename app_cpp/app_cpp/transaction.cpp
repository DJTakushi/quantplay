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