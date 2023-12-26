#include <ctime>
#include <string>

class transaction{
  std::time_t time_;
  double value_;
  std::string transaction_ = "";

public:
  transaction(std::time_t time, double value, std::string transaction);
  void print();
  std::time_t get_time();
  double get_value();
  std::string get_transaction();
};