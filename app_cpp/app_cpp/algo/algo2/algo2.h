#include <list>
#include "transaction.h"
#include "algo_i.h"
#include "ohlcv.h"
class algo2 : public algo_i{
  std::list<ohlcv> data_;
  bool bought = false;

  public:
  void addData(std::list<ohlcv> data_list);
  transaction* process();
  ohlcv* get_latest_data();
};