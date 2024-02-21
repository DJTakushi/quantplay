#include "daydata.h"
#include <chrono>
#include <memory>
#include <vector>
class dayrecorder{
  /** logs daily metrics for display later **/
protected:
  std::vector<daydata*> days_;
public:
  dayrecorder();
  ymd_date get_current_date();
  void start_new_day(ymd_date date);
  void set_current_open(double open);
  void set_current_close(double close);
  void set_current_portfolio_value(double portfolio_value);
  void add_data(daydata d);
  void print();
};