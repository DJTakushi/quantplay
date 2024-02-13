#pragma once
#include <ctime>
#include <string>
enum transactionType{
  kBuy = 0,
  kSell,
};
enum transactionStatus{
  kPending = 0,
  kComplete
};
class transaction{
  std::time_t time_;
  double value_;
  transactionType type_ = transactionType::kBuy;
  transactionStatus status_ = kPending;
public:
  transaction(std::time_t time, double value, transactionType type);
  void print();
  std::time_t get_time();
  double get_value();
  transactionType get_type();

  transactionStatus get_status();
  void set_status(transactionStatus s);
};