#include "portfolio.h"
#include <mariadb/conncpp.hpp>

class recorder_db_handler {
  /** logs records for display later **/
protected:
  sql::Connection* connection_;
  void drop_datatable();
  void create_datatable();
  std::string table_name_ = "recorder";
public:
  recorder_db_handler(sql::Connection* connection);
  void add_data_to_db(std::vector<portfolio> dv);
  std::vector<portfolio> get_portfolio_snapshots();
};