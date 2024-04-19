#include "algo_types.h"
#include "portfolio.h"
#include "analyzer_db_handler.h"

class analyzer : public analyzer_db_handler {
 protected:
  virtual std::vector<portfolio> get_day_portfolio_snapshots() = 0;
  virtual std::vector<portfolio> get_portfolio_snapshots() = 0;
  analysis generate_analysis() override;
 public:
  analyzer(sql::Connection* connection,algo_type_k type);
  analyzer();
  double compute_sharpe_ratio();
  std::vector<portfolio> get_max_drawdown_portfolio_snapshots();
  double get_max_drawdown();
  double get_max_drawdown_duration();
  void print_analysis();
 private:
  double calculate_max_drawdown(std::vector<portfolio> high_low);
};