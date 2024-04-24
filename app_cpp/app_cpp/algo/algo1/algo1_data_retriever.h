#include "algo_data_retriever_i.h"
#include "algo1_data.h"

class algo1_data_retriever : public algo_data_retriever_i {
  std::time_t latest_datapoint_;
  void add_data_to_database(std::list<algo1_data> data_list,
      std::string timezone_s = "US/Eastern");
 public:
  algo1_data_retriever(sql::Connection* connection, std::string table_name);
  void create_datatable() override;
  std::list<ohlcv*> get_next_data_from_database(int num = -1) override;
  // void update_database();//TODO
  int update_database_from_file(fs::path filepath, int no = -1) override;
  int update_database_from_json(fs::path filepath, int no = -1);
  int update_database_from_csv(fs::path filepath, int no = -1);
};