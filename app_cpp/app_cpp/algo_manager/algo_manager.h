#include "algo_controller.h"
#include "algo_types.h"
#include "trader.h"
#include "portfolio.h"
#include "recorder.h"
#include "analyzer.h"
#include <mariadb/conncpp.hpp>

class algo_manager : public analyzer{
  algo_controller_i* algo_controller_;
  trader* trader_;
  portfolio* portfolio_;
  recorder* recorder_;
  sql::Connection* sql_connection_;
  public:
  algo_manager(algo_type_k type, sql::Connection* conn);
  void process();
  void process_all_by_update_data_step(int step = -1);
  // void update_database(); //todo
  void update_database_from_file(fs::path filepath);
  int update_data(int num = -1);
  transaction* get_transaction();
  transaction* process_transaction(transaction* t);
  void log_transaction(transaction* t);
  void all_snapshots_to_db();
  double get_portfolio_value();
  void print_days();
  void print_portfolio_snapshots();
  std::vector<portfolio> get_portfolio_snapshots();
  std::vector<portfolio> get_day_portfolio_snapshots();
  // void save_data(fs::path filepath); //todo
  int step_cache_data=1; // data to cache before processing
  bool snapshot_auto_save_=false;  // save snapshots when generated?
};