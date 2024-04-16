#include "algo_controller_i.h"
#include "algo2.h"
#include "algo2_data_retriever.h"
#include <mariadb/conncpp.hpp>
class algo2_controller : public algo_controller_i{
  algo2_data_retriever* retriever;
  algo2* algo;
public:
  algo2_controller(sql::Connection* connection);
  void drop_datatable();
  // void update_database();
  void update_database_from_file(fs::path filepath);
  int update_data(int num = -1);
  void update_data_single();
  transaction* get_transaction();
  ohlcv* get_latest_data();
};