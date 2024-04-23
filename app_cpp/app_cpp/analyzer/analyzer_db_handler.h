#include <mariadb/conncpp.hpp>
#include "analysis.h"
#include "algo_types.h"
#include "db_handler_base.h"

class analyzer_db_handler : public db_handler_base {
  /** logs records for display later **/
 protected:
  void clear_table_of_name();
  void create_datatable();
  std::string algo_name_;
  virtual analysis generate_analysis() = 0;
 public:
  analyzer_db_handler(sql::Connection* connection,algo_type_k type);
  void insert_metrics(analysis a);
  void update_database_analysis();
};