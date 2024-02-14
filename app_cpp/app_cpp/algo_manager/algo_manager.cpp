#include "algo_manager.h"

algo_manager::algo_manager(){
  algo1_controller_ = new algo1_controller();
  trader_ = new trader();
  portfolio_ = new portfolio(10000.0);
  recorder_ = new dayrecorder();
  session_ = new mysqlx::Session("mysqlx://root@127.0.0.1");
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