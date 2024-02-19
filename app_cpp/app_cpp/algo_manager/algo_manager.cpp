#include "algo_manager.h"
#include <iostream>
algo_manager::algo_manager(sql::Connection* connection) :
    sql_connection_(connection){
  algo1_controller_ = new algo1_controller(connection);
  trader_ = new trader();
  portfolio_ = new portfolio(10000.0);
  recorder_ = new dayrecorder();

  if (!sql_connection_) {
    std::cerr << "Invalid database connection" << std::endl;
    exit (EXIT_FAILURE);
  }
};
void algo_manager::process(){
  /** 1. update database **/
  update_database();

  /** 2. data udpated */
  update_data();

  /** 3. transaction generation from algo */
  transaction* t = get_transaction();

  /** 4.  transaction processed by trader */
  t = process_transaction(t);

  /** 5. transction logged in portfolio (if complete )*/
  log_transaction(t);

  /** 6. portfolio value recorded */
  double val = get_portfolio_value();
  recorder_->set_current_portfolio_value(val);
};
void algo_manager::update_database(){
  algo1_controller_->update_database();
}
void algo_manager::update_data(){
  algo1_controller_->update_data();
}
transaction* algo_manager::get_transaction(){
  return algo1_controller_->get_transaction();
}
transaction* algo_manager::process_transaction(transaction* t){
  return trader_->process_transaction(t);
}
void algo_manager::log_transaction(transaction* t){
  if(t != NULL && t->get_status() == kComplete)
    portfolio_->addTransaction(*t);
}
double algo_manager::get_portfolio_value(){
  return portfolio_->get_portfolio_value();
}