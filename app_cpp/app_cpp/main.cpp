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

  algo_manager* manager_ = new algo_manager(sql_connection_);
  manager_->update_database_from_file(fs::path("app_cpp/intraday_ibm.json"));
  manager_->process(1);

  std::cout << "Snapshots :" << std::endl;
  manager_->print_snapshots();

  std::cout << "Days :" << std::endl;
  manager_->print_days();


  std::cout << "OHLCV Days :" << std::endl;
  manager_->print_ohlcv_days();

  sql_connection_->close();
}