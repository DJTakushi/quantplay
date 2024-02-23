#include "recorder.h"
#include <gtest/gtest.h>
class recorder_wrapper : public recorder{
public:
  std::vector<daydata*> get_days_vector(){
    return days_;
  }
};
TEST(datarecorderTest,datarecorder_constructor) {
  recorder_wrapper dc;
  // no-dates default confirmatino
  EXPECT_EQ(std::chrono::year(1900),dc.get_current_date().year());
  EXPECT_EQ(std::chrono::month(1),dc.get_current_date().month());
  EXPECT_EQ(std::chrono::day(1),dc.get_current_date().day());

  // add a date & confirm date
  dc.start_new_day({std::chrono::July/1/2021});
  EXPECT_EQ(1,dc.get_days_vector().size());
  EXPECT_EQ(std::chrono::year(2021),dc.get_current_date().year());
  EXPECT_EQ(std::chrono::month(07),dc.get_current_date().month());
  EXPECT_EQ(std::chrono::day(01),dc.get_current_date().day());

  // confirm defaults
  daydata* last_day = dc.get_days_vector().back();
  EXPECT_EQ(0,last_day->get_open());
  EXPECT_EQ(0,last_day->get_close());
  EXPECT_EQ(0,last_day->get_portfolio());

  // set daydata values
  dc.set_current_open(1.23);
  dc.set_current_close(4.56);
  dc.set_current_portfolio_value(12.74);

  // confirm datadata values
  EXPECT_EQ(1.23,last_day->get_open());
  EXPECT_EQ(4.56,last_day->get_close());
  EXPECT_EQ(12.74,last_day->get_portfolio());

  // create a new-er date & confirm date
  dc.start_new_day({std::chrono::July/2/2021});
  EXPECT_EQ(2,dc.get_days_vector().size());
  EXPECT_EQ(std::chrono::year(2021),dc.get_current_date().year());
  EXPECT_EQ(std::chrono::month(07),dc.get_current_date().month());
  EXPECT_EQ(std::chrono::day(02),dc.get_current_date().day());

  // confirm defaults are set
  last_day = dc.get_days_vector().back();
  EXPECT_EQ(0,last_day->get_open());
  EXPECT_EQ(0,last_day->get_close());
  EXPECT_EQ(0,last_day->get_portfolio());

}