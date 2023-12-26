#include <ctime>
#include <string>
enum class transactionType{
  kBuy = 0,
  kSell,
};
class transaction{
  std::time_t time_;
  double value_;
  transactionType type_ = transactionType::kBuy;

public:
  transaction(std::time_t time, double value, transactionType type);
  void print();
  std::time_t get_time();
  double get_value();
  transactionType get_type();
};