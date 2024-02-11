#include "portfolio.h"
#include <gtest/gtest.h>

class portfolioTest : public ::testing::Test{
  public:
  portfolioTest() {}
};
TEST(PortfolioTest,portfolio_constructor) {
  portfolio* p = new portfolio(0.02);
  EXPECT_EQ(0.02, p->get_balance());
  EXPECT_EQ(0.02, p->get_portfolio_value());
  EXPECT_EQ(0.00, p->get_equity_value());
  EXPECT_EQ(0,p->get_shares());
}
TEST(PortfolioTest,portfolio_add_transaction) {
  portfolio* p = new portfolio(1000.0);
  EXPECT_EQ(1000.0, p->get_balance());

  p->set_current_value(50.0);
  p->addTransaction(transaction(std::time_t(),50.0,transactionType::kBuy));
  EXPECT_EQ(950.0, p->get_balance());
  EXPECT_EQ(1000.0, p->get_portfolio_value());
  EXPECT_EQ(50.0, p->get_equity_value());
  EXPECT_EQ(1,p->get_shares());

  p->set_current_value(60.0);
  EXPECT_EQ(950.0, p->get_balance());
  EXPECT_EQ(1010.0, p->get_portfolio_value());
  EXPECT_EQ(60.0, p->get_equity_value());
}