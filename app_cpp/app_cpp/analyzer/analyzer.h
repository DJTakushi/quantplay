#include "portfolio.h"

class analyzer{
  protected:
  virtual std::vector<portfolio> get_day_portfolio_snapshots() = 0;
  virtual std::vector<portfolio> get_portfolio_snapshots() = 0;
  public:
  double compute_sharpe_ratio();
  std::vector<portfolio> get_max_drawdown_portfolio_snapshots();
  double get_max_drawdown();
  double get_max_drawdown_duration();
  void print_analysis();
  private:
  double calculate_max_drawdown(std::vector<portfolio> high_low);
};