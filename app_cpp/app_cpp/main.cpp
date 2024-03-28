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
  // manager_->update_database_from_file(fs::path("app_cpp/intraday_ibm.json"));
  manager_->update_database_from_file(fs::path("app_cpp/3_4_ige.csv"));
  manager_->process(1);

  std::cout << "Snapshots :" << std::endl;
  manager_->print_snapshots();

  std::cout << "Days :" << std::endl;
  manager_->print_days();


  // std::cout << "OHLCV Days :" << std::endl;
  // manager_->print_ohlcv_days();

  double sharpe_ratio = manager_->compute_sharpe_ratio();
  double max_drawdown = manager_->compute_max_drawdown()*100.0;
  double max_drawdown_duration = manager_->compute_max_drawdown_duration();
  max_drawdown_duration /=(60*60*24);
  std::cout << "Sharpe Ratio : " <<std::to_string(sharpe_ratio)<<std::endl;
  std::cout << "max drawdown : %" <<std::to_string(max_drawdown)<<std::endl;
  std::cout << "max_drawdown duration : "<<std::to_string(max_drawdown_duration) << " days"<<std::endl;

  sql_connection_->close();
}