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

  sql_connection_->close();
  std::cout << "done." <<std::endl;
}