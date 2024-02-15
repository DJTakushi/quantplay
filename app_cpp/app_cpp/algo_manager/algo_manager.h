#include "algo1_controller.h"
#include "trader.h"
#include "portfolio.h"
#include "dayrecorder.h"
#include <mariadb/conncpp.hpp>

class algo_manager{
  algo1_controller* algo1_controller_;
  trader* trader_;
  portfolio* portfolio_;
  dayrecorder* recorder_;
  sql::Connection* sql_connection_;
  public:
  algo_manager(sql::Connection* connection);
  void process();
};