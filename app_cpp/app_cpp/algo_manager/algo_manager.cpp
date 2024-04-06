#include "algo_manager.h"
#include <iostream>
algo_manager::algo_manager(sql::Connection* connection) :
    sql_connection_(connection){
  algo1_controller_ = new algo1_controller(connection);
  trader_ = new trader();
  portfolio_ = new portfolio(42.09);
  recorder_ = new recorder_db();

  if (!sql_connection_) {
    std::cerr << "Invalid database connection" << std::endl;
    exit (EXIT_FAILURE);
  }
};
void algo_manager::process(int step){
  // TODO : add option to record with live timestamp when running live

  /** 1. update database (maybe) **/
  // update_database_from();//todo (maybe?)

  /** 2. data udpated */
  while(update_data(step)>0){
    /** 3. transaction generation from algo */
    transaction* t = get_transaction();

    /** 4.  transaction processed by trader */
    t = process_transaction(t);

    /** 5. transction logged in trader (if complete )*/
    log_transaction(t);

    /** 6. portfolio value recorded */
    ohlcv* d = new ohlcv(algo1_controller_->get_latest_data());
    portfolio_->set_current_value(d->get_close());
    portfolio_->set_time(d->get_time());
    recorder_->add_data(*portfolio_);
  }
};
void algo_manager::update_database_from_file(fs::path filepath){
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
std::vector<portfolio> algo_manager::get_portfolio_snapshots(){
 return recorder_->get_portfolio_snapshots();
}

std::vector<portfolio> algo_manager::get_day_portfolio_snapshots(){
  return recorder_->get_day_portfolio_snapshots();
}

void algo_manager::print_portfolio_snapshots(){
  recorder_->print_portfolio_snapshots();
}