#include "transaction.h"
#include <gtest/gtest.h>

TEST(TransactionTest,constructor){
  std::tm tm{}; // Zero initialise
  tm.tm_year = 2020 - 1900; // 2020
  tm.tm_mon = 2 - 1; // February
  tm.tm_mday = 15; // 15th
  tm.tm_hour = 10;
  tm.tm_min = 15;
  tm.tm_isdst = 0; // Not daylight saving
  std::time_t time = std::mktime(&tm);
  transaction* t = new transaction(time,12.34,"doot");

  EXPECT_EQ(time, t->get_time());
  EXPECT_DOUBLE_EQ(12.34,t->get_value());
  EXPECT_EQ("doot",t->get_transaction());
}