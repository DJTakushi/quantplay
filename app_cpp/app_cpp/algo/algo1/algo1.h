#include <list>
#include "transaction.h"
#include "algo_i.h"
#include "algo1_data.h"
class algo1 : public algo_i{
  std::list<algo1_data> data_;
  bool bought = false;

  public:
  void addData(std::list<ohlcv*> data_list);
  transaction* process() override;
  ohlcv* get_latest_data();
};