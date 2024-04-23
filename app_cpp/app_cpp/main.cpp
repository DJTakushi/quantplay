#include "algo_manager.h"
#include <iostream>
int main(int argc, char** argv){
  sql::Driver* driver = sql::mariadb::get_driver_instance();

  sql::SQLString url("jdbc:mariadb://127.0.0.1:3306/quant");

  // Use a properties map for the other connection options
  sql::Properties properties({
        {"user", "root"},
        {"password", "example"},
    });

  // Establish Connection
  sql::Connection* sql_connection_ = driver->connect(url, properties);

  algo_manager* manager_ = new algo_manager(algo1_k,sql_connection_);
  manager_->update_database_from_file(fs::path("app_cpp/3_4_ige.csv"));
  manager_->process_all_by_update_data_step(1);
  manager_->all_snapshots_to_db();
  manager_->update_database_analysis();

  manager_->print_analysis();

  sql_connection_->close();
}