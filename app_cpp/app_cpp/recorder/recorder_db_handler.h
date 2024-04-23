#include <mariadb/conncpp.hpp>
#include "db_handler_base.h"
#include "portfolio.h"

class recorder_db_handler : public db_handler_base {
  /** logs records for display later **/
protected:
  void create_datatable();
public:
  recorder_db_handler(sql::Connection* connection,std::string table_name);
  void add_data_to_db(std::vector<portfolio> dv);
  std::vector<portfolio> get_portfolio_snapshots();
};