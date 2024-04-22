#include "portfolio.h"
#include "typedefs.h"
#include "recorder_db_handler.h"
#include <vector>
class recorder : public recorder_db_handler {
  /** logs records for display later **/
  std::vector<portfolio> portfolio_snapshots_;
public:
  recorder(sql::Connection* connection,std::string table_name);
  ymd_date get_current_date();
  void add_data(portfolio d);
  void print_portfolio_snapshots();
  void print_days();
  std::vector<portfolio> get_portfolio_snapshots();
  std::vector<portfolio> get_day_portfolio_snapshots();
  void all_snapshots_to_db();
};