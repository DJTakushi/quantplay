#include <iostream>
#include "algo_manager.h"
#include "algo_controller_factory.h"
algo_manager::algo_manager(algo_type_k type, sql::Connection* conn) :
    sql_connection_(conn), analyzer(conn,type){
  algo_controller_ = algo_controller_factory::create_controller(type,conn);
  trader_ = new trader();
  portfolio_ = new portfolio(42.09);
  recorder_ = new recorder(conn,"recorder_"+algo_name[type]);

  if (!sql_connection_) {
    std::cerr << "Invalid database connection" << std::endl;
    exit (EXIT_FAILURE);
  }
};
void algo_manager::process() {
  /** 1. transaction generation from algo */
  transaction* t = get_transaction();

  /** 2.  transaction processed by trader */
  t = process_transaction(t);

  /** 3. transction logged in trader (if complete )*/
  log_transaction(t);

  /** 4. portfolio value recorded */
  ohlcv* d = new ohlcv(algo_controller_->get_latest_data_from_algo());
  portfolio_->set_current_value(d->get_close());
  portfolio_->set_time(d->get_time());
  recorder_->add_data(*portfolio_);
  if(snapshot_auto_save_){recorder_->add_data_to_db({*portfolio_});}
}
void algo_manager::process_all_by_update_data_step(int step){
  // TODO : add option to record with live timestamp when running live
  while(update_algo_data(step)>0){
    process();
  }
};
int algo_manager::update_database_from_file(fs::path filepath, int no){
  return algo_controller_->update_database_from_file(filepath, no);
}
int algo_manager::update_algo_data(int num){
  return algo_controller_->update_algo_data(num);
}
transaction* algo_manager::get_transaction(){
  return algo_controller_->get_transaction();
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

void algo_manager::all_snapshots_to_db() {
  recorder_->all_snapshots_to_db();
}