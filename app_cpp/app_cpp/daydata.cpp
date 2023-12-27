#include "daydata.h"

daydata::daydata(std::chrono::year_month_day date) : date_(date){}

std::chrono::year_month_day daydata::get_date(){return date_;}

void daydata::set_open(double open){open_=open;}
double daydata::get_open(){return open_;}

void daydata::set_high(double high){high_=high;}
double daydata::get_high(){return high_;}

void daydata::set_low(double low){low_=low;}
double daydata::get_low(){return low_;}

void daydata::set_close(double close){close_=close;}
double daydata::get_close(){return close_;}

void daydata::set_portfolio(double portfolio_val){portfolio_ = portfolio_val;}
double daydata::get_portfolio(){return portfolio_;}