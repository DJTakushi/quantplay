#include <list>
#include "algo1_data.h"
#include <mariadb/conncpp.hpp>
#include <ctime>
#define TD_FORMAT "%Y-%m-%d %H:%M:%S"
class algo1_data_retriever{
  sql::Connection* connection_;
  std::time_t latest_datapoint_;
  void add_data_to_database(algo1_data data,
      std::string timezone_s = "US/Eastern");
  public:
  algo1_data_retriever(sql::Connection* connection);
  void drop_datatable();
  void create_datatable();
  std::list<algo1_data> get_data(int num = -1);
  // void update_database();//TODO
  void update_database_from_file(std::string filepath);
  void update_database_from_json(std::string j);
};