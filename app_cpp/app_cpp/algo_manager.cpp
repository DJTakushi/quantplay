#include "algo1_controller.h"
#include "trader.h"
#include "portfolio.h"
#include "dayrecorder.h"
class algo_manager{
  algo1_controller* algo1_controller_;
  trader* trader_;
  portfolio* portfolio_;
  dayrecorder* recorder_;
  public:
  algo_manager(){
    algo1_controller_ = new algo1_controller();
    trader_ = new trader();
    portfolio_ = new portfolio(10000.0);
    recorder_ = new dayrecorder();
  };
  void process(){
    algo1_controller_->update_data();
    transaction* t = algo1_controller_->get_transaction();
    t = trader_->process_transaction(t);
    if(t->get_status() == kComplete)
      portfolio_->addTransaction(*t);
    double val = portfolio_->get_portfolio_value();
    recorder_->set_current_portfolio_value(val);
  };
};