#include "algo1.h"
#include <gtest/gtest.h>

class algo1Test : public ::testing::Test, public algo1{};
TEST_F(algo1Test,no_data){
  transaction* output = process();
  EXPECT_EQ(nullptr,output);
}

TEST_F(algo1Test,buy_once_nothing_afterwards){
  std::list<ohlcv*> data;
  algo1_data* t_data = new algo1_data(time(NULL),0.0,0.0,0.0,0.0,0);
  data.push_back(t_data);
  addData(data);
  transaction* output = process();
  EXPECT_NE(nullptr,output);
  EXPECT_EQ(kBuy,output->get_type());
  EXPECT_EQ(0.0,output->get_value());

  // get second order; should be null
  output = process();
  EXPECT_EQ(nullptr,output);
}