#include <list>
#include "helpers.h"
#include "ohlcv.h"
#include <mariadb/conncpp.hpp>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;
class algo2_data_retriever{
  sql::Connection* connection_;
  std::time_t latest_datapoint_;
  void add_data_to_database(std::list<ohlcv> data_list,
      std::string timezone_s = "US/Eastern");
  public:
  algo2_data_retriever(sql::Connection* connection);
  void drop_datatable();
  void create_datatable();
  std::list<ohlcv> get_next_data_from_database(int num = -1);
  // void update_database();//TODO
  void update_database_from_file(fs::path filepath);
  void update_database_from_json(std::string j);
  void update_database_from_csv(std::string s);
};