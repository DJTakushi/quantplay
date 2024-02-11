#include "algo.h"
#include <gtest/gtest.h>

class algoTest : public ::testing::Test, public algo{};
TEST_F(algoTest,no_data){
  order* output = process();
  EXPECT_EQ(nullptr,output);
}

TEST_F(algoTest,buy_once_nothing_afterwards){
  addData(0.0,0,0.0);
  order* output = process();
  EXPECT_NE(nullptr,output);
  EXPECT_EQ(buy,output->cmd_);
  EXPECT_EQ(0.0,output->val_);

  // get second order; should be null
  output = process();
  EXPECT_EQ(nullptr,output);
}