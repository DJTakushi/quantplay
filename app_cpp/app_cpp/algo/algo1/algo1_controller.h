#include <mariadb/conncpp.hpp>
#include "algo_controller_i.h"
#include "algo_data_retriever_i.h"
class algo1_controller : public algo_controller_i{
  algo_data_retriever_i* retriever;
public:
  algo1_controller(sql::Connection* connection);
  void drop_datatable();
  // void update_database();
  void update_database_from_file(fs::path filepath) override;
  int update_data(int num = -1);
  transaction* get_transaction();
  ohlcv* get_latest_data() override;
};