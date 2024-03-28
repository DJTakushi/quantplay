#include "snapshot.h"

class analyzer{
  protected:
  virtual std::vector<snapshot> get_day_snapshots() = 0;
  virtual std::vector<snapshot> get_snapshots() = 0;
  public:
  double compute_sharpe_ratio();
  std::vector<snapshot> get_max_drawdown_snapshots();
  double get_max_drawdown();
  double get_max_drawdown_duration();
  private:
  double calculate_max_drawdown(std::vector<snapshot> high_low);
};