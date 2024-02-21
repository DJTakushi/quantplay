#include <iostream>
#include "daydata.h"

daydata::daydata(ymd_date date) : date_(date){}

ymd_date daydata::get_date(){return date_;}

void daydata::set_portfolio(double portfolio_val){portfolio_ = portfolio_val;}
double daydata::get_portfolio(){return portfolio_;}

void daydata::print(){
  std::cout << date_ << " : ";
  std::cout << portfolio_ <<std::endl;
}