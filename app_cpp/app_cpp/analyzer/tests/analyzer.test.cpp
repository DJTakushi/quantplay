#include "analyzer.h"
#include <gtest/gtest.h>

class analyzer_dummy : public analyzer {
  public:
  std::vector<snapshot> day_snapshots_;
  std::vector<snapshot> snapshots_;
  std::vector<snapshot> get_day_snapshots() override {
    return day_snapshots_;
  };
  std::vector<snapshot> get_snapshots() override {
    return snapshots_;
  }
};


class analyzerTest : public ::testing::Test, public analyzer_dummy{};
TEST_F(analyzerTest,investopedia_example){
  // https://www.investopedia.com/terms/m/maximum-drawdown-mdd.asp#:~:text=Key%20Takeaways,down%20movements%20could%20be%20volatile.
  snapshots_.push_back({"2000-01-01 00:00:00",0,0,0,0,0,0,1,500000});
  snapshots_.push_back({"2000-01-02 00:00:00",0,0,0,0,0,0,1,750000});
  snapshots_.push_back({"2000-01-03 00:00:00",0,0,0,0,0,0,1,400000});
  snapshots_.push_back({"2000-01-04 00:00:00",0,0,0,0,0,0,1,600000});
  snapshots_.push_back({"2000-01-05 00:00:00",0,0,0,0,0,0,1,350000});
  snapshots_.push_back({"2000-01-06 00:00:00",0,0,0,0,0,0,1,800000});
  EXPECT_DOUBLE_EQ(-0.53333333333333333,compute_max_drawdown());
}
