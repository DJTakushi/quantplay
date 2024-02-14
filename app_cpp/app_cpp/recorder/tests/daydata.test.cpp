#include "daydata.h"
#include <gtest/gtest.h>

TEST(daydataTest,daydata_constructor) {
  ymd_date ymd{std::chrono::July/1/2021};
  daydata* dd = new daydata(ymd);
  EXPECT_EQ(std::chrono::year(2021),dd->get_date().year());
  EXPECT_EQ(std::chrono::month(7),dd->get_date().month());
  EXPECT_EQ(std::chrono::day(1),dd->get_date().day());
}
// TODO: test other getters and setters