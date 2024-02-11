#include <chrono>
typedef std::chrono::year_month_day ymd_date;
class daydata{
  ymd_date date_;
  double open_ = 0;
  double high_ = 0;
  double low_ = 0;
  double close_ = 0;
  double portfolio_ = 0;

public:
  daydata(ymd_date date);

  ymd_date get_date();

  void set_open(double open);
  double get_open();

  void set_high(double high);
  double get_high();

  void set_low(double low);
  double get_low();

  void set_close(double close);
  double get_close();

  void set_portfolio(double portfolio_val);
  double get_portfolio();
};