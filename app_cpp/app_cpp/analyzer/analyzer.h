#include "snapshot.h"

class analyzer{
  protected:
  virtual std::vector<snapshot> get_day_snapshots() = 0;
  public:
  double compute_sharpe_ratio();
};