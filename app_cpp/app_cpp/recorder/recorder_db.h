#include "recorder.h"
#include <mariadb/conncpp.hpp>

class recorder_db : public recorder {
  /** logs records for display later **/
protected:
  std::vector<portfolio> portfolio_snapshots_;
  sql::Connection* connection_;
public:
  recorder_db(sql::Connection* connection);
  ymd_date get_current_date();
  void add_data(portfolio d);
  void print_portfolio_snapshots();
  void print_days();
  std::vector<portfolio> get_portfolio_snapshots();
  std::vector<portfolio> get_day_portfolio_snapshots();
};