#include <mariadb/conncpp.hpp>
#include "db_handler_base.h"
#include "portfolio.h"

class recorder_db_handler : public db_handler_base {
  /** logs records for display later **/
protected:
  void drop_datatable();
  void create_datatable();
  std::string table_name_ = "recorder";
public:
  recorder_db_handler(sql::Connection* connection);
  void add_data_to_db(std::vector<portfolio> dv);
  std::vector<portfolio> get_portfolio_snapshots();
};