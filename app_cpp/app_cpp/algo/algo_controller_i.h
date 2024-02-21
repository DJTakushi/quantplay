#include "transaction.h"

class algo_controller_i{
public:
  virtual int update_data(int num = -1) = 0;
  virtual void update_data_single() = 0;
  virtual transaction* get_transaction() = 0;
};