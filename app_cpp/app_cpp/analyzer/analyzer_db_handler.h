#include "analysis.h"
#include <mariadb/conncpp.hpp>

class analyzer_db_handler {
  /** logs records for display later **/
 protected:
  sql::Connection* connection_;
  void drop_datatable();
  void clear_table_of_name();
  void create_datatable();
  std::string table_name_ = "analysis";
  std::string algo_name_;
  virtual analysis generate_analysis() = 0;
 public:
  analyzer_db_handler(sql::Connection* connection,std::string name);
  analyzer_db_handler();
  void insert_metrics(analysis a);
  void update_database_analysis();
};