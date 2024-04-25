#include <iostream>
#include <signal.h>
#include <thread>
#include "algo_manager.h"
static volatile bool active = false;
void de_activate(int param){ active = false; }

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

  signal(SIGINT, de_activate);
  active = true;
  auto process_loop = std::thread([manager_]() {
    while(active){
      std::cout << "processing...  "<<std::endl;
      manager_->update_database_from_file(fs::path("app_cpp/3_4_ige.csv"),1);
      manager_->process_all_by_update_data_step();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  });
  process_loop.join();

  manager_->all_snapshots_to_db();
  manager_->update_database_analysis();

  manager_->print_analysis();// TODO :remove

  sql_connection_->close();
}