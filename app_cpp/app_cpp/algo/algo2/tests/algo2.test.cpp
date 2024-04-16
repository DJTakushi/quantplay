#include "algo2.h"
#include <gtest/gtest.h>

class algo2Test : public ::testing::Test, public algo2{};
TEST_F(algo2Test,no_data){
  transaction* output = process();
  EXPECT_EQ(nullptr,output);
}

TEST_F(algo2Test,buy_once_nothing_afterwards){
  std::list<ohlcv> data = {ohlcv(time(NULL),0.0,0.0,0.0,0.0,0)};
  addData(data);
  transaction* output = process();
  EXPECT_NE(nullptr,output);
  EXPECT_EQ(kBuy,output->get_type());
  EXPECT_EQ(0.0,output->get_value());

  // get second order; should be null
  output = process();
  EXPECT_EQ(nullptr,output);
}