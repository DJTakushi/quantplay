#include "algo_data_retriever_i.h"
#include "ohlcv.h"

namespace fs = std::filesystem;
class algo2_data_retriever : public algo_data_retriever_i {
  std::time_t latest_datapoint_;
  void add_data_to_database(std::list<ohlcv> data_list,
      std::string timezone_s = "US/Eastern");
  public:
  algo2_data_retriever(sql::Connection* connection, std::string table_name);
  void create_datatable() override;
  std::list<ohlcv*> get_next_data_from_database(int num = -1) override;
  // void update_database();//TODO
  int update_database_from_file(fs::path filepath, int no = -1) override;
  void update_database_from_json(std::string j);
  void update_database_from_csv(std::string s);
};