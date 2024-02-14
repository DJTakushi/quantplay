#include "algo1_controller.h"
#include "trader.h"
#include "portfolio.h"
#include "dayrecorder.h"
#include <mysqlx/xdevapi.h>

class algo_manager{
  algo1_controller* algo1_controller_;
  trader* trader_;
  portfolio* portfolio_;
  dayrecorder* recorder_;
  mysqlx::Session* session_;
  public:
  algo_manager();
  void process();
};