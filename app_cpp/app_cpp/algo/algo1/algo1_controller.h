#include "algo_controller_i.h"
#include "algo1.h"
#include "algo1_data_retriever.h"
#include <mariadb/conncpp.hpp>
class algo1_controller : public algo_controller_i{
  algo1_data_retriever* retriever;
  algo1* algo;
public:
  algo1_controller(sql::Connection* connection);
  void drop_datatable();
  void update_database();
  int update_data(int num = -1);
  void update_data_single();
  transaction* get_transaction();
  ohlcv* get_latest_data();
};