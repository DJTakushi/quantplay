#include "analyzer.h"
#include "helpers.h"
#include <gtest/gtest.h>

class analyzer_dummy : public analyzer {
  public:
  std::vector<portfolio> day_portfolios_;
  std::vector<portfolio> portfolios_;
  std::vector<portfolio> get_day_portfolio_snapshots() override {
    return day_portfolios_;
  };
  std::vector<portfolio> get_portfolio_snapshots() override {
    return portfolios_;
  }
};


class analyzerTest : public ::testing::Test, public analyzer_dummy{};
TEST_F(analyzerTest,investopedia_example){
  // https://www.investopedia.com/terms/m/maximum-drawdown-mdd.asp#:~:text=Key%20Takeaways,down%20movements%20could%20be%20volatile.
  portfolios_.push_back({"2000-01-01 00:00:00",0,1,500000});
  portfolios_.push_back({"2000-01-02 00:00:00",0,1,750000});
  portfolios_.push_back({"2000-01-03 00:00:00",0,1,400000});
  portfolios_.push_back({"2000-01-04 00:00:00",0,1,600000});
  portfolios_.push_back({"2000-01-05 00:00:00",0,1,350000});
  portfolios_.push_back({"2000-01-06 00:00:00",0,1,800000});
  EXPECT_DOUBLE_EQ(-53.333333333333333,get_max_drawdown());
  EXPECT_DOUBLE_EQ(4,get_max_drawdown_duration());

  std::vector<portfolio> mdd_high_low = get_max_drawdown_portfolio_snapshots();
  portfolio high = mdd_high_low[0];
  EXPECT_DOUBLE_EQ(750000,high.get_portfolio_value());
  EXPECT_EQ("2000-01-02 00:00:00",time_t_to_local_str(high.get_time()));

  portfolio low = mdd_high_low[1];
  EXPECT_DOUBLE_EQ(350000,low.get_portfolio_value());
  EXPECT_EQ("2000-01-05 00:00:00",time_t_to_local_str(low.get_time()));
}
