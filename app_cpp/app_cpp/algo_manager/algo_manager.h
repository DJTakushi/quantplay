#include "algo1_controller.h"
#include "trader.h"
#include "portfolio.h"
#include "recorder.h"
#include "snapshot.h"
#include <mariadb/conncpp.hpp>

class algo_manager{
  algo1_controller* algo1_controller_;
  trader* trader_;
  portfolio* portfolio_;
  recorder* recorder_;
  sql::Connection* sql_connection_;
  public:
  algo_manager(sql::Connection* connection);
  void process(int step = -1);
  void update_database();
  int update_data(int num = -1);
  void generate_transaction();
  transaction* get_transaction();
  transaction* process_transaction(transaction* t);
  void log_transaction(transaction* t);
  double get_portfolio_value();
  void print_days();
  void print_snapshots();
};