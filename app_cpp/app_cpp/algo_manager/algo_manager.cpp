#include "algo_manager.h"
#include <iostream>
algo_manager::algo_manager(sql::Connection* connection) :
    sql_connection_(connection){
  algo1_controller_ = new algo1_controller();
  trader_ = new trader();
  portfolio_ = new portfolio(10000.0);
  recorder_ = new dayrecorder();

  if (!sql_connection_) {
    std::cerr << "Invalid database connection" << std::endl;
    exit (EXIT_FAILURE);
  }
};
void algo_manager::process(){
  /** 1. data udpated */
  algo1_controller_->update_data();

  /** 2. transaction generation from algo */
  transaction* t = algo1_controller_->get_transaction();

  /** 3.  transaction processed by trader */
  t = trader_->process_transaction(t);

  /** 4. transction logged in portfolio (if complete )*/
  if(t->get_status() == kComplete)
    portfolio_->addTransaction(*t);

  /** 5. portfolio value recorded */
  double val = portfolio_->get_portfolio_value();
  recorder_->set_current_portfolio_value(val);
};