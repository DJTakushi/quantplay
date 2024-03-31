#include "algo_manager.h"
#include <gtest/gtest.h>

class algo1Test_demo : public ::testing::Test{};

TEST_F(algo1Test_demo, algo1_test_real){
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
  manager_->update_database_from_file(fs::path("app_cpp/3_4_ige.csv"));
  manager_->process(1);

  // confirm number of data loaded
  std::vector<portfolio> portfolios = manager_->get_day_portfolio_snapshots();
  EXPECT_EQ(1504,portfolios.size());

  double sharpe_ratio = manager_->compute_sharpe_ratio();
  EXPECT_DOUBLE_EQ(0.78931753834485100000,sharpe_ratio);

  double max_drawdown = manager_->get_max_drawdown();
  EXPECT_DOUBLE_EQ(-0.31178396072013098,max_drawdown);
  sql_connection_->close();
}