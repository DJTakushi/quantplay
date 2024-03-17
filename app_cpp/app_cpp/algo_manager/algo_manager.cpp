#include "algo_manager.h"
#include <iostream>
algo_manager::algo_manager(sql::Connection* connection) :
    sql_connection_(connection){
  algo1_controller_ = new algo1_controller(connection);
  trader_ = new trader();
  portfolio_ = new portfolio(10000.0);
  recorder_ = new recorder();

  if (!sql_connection_) {
    std::cerr << "Invalid database connection" << std::endl;
    exit (EXIT_FAILURE);
  }
};
void algo_manager::process(int step){
  /** 1. update database (maybe) **/
  // update_database_from();//todo (maybe?)

  /** 2. data udpated */
  while(update_data(step)>0){
    /** 3. transaction generation from algo */
    transaction* t = get_transaction();

    /** 4.  transaction processed by trader */
    t = process_transaction(t);

    /** 5. transction logged in portfolio (if complete )*/
    log_transaction(t);

    /** 6. portfolio value recorded */
    ohlcv* d = new ohlcv(algo1_controller_->get_latest_data());
    portfolio_->set_current_value(d->get_close());
    recorder_->add_data(new snapshot(d,portfolio_));
  }
};
void algo_manager::update_database_from_file(std::string filepath){
  algo1_controller_->update_database_from_file(filepath);
}
int algo_manager::update_data(int num){
  return algo1_controller_->update_data(num);
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
void algo_manager::print_days(){
  recorder_->print_days();
}
void algo_manager::print_ohlcv_days(){
  recorder_->print_ohlcv_days();
}

void algo_manager::print_snapshots(){
  recorder_->print_snapshots();
}