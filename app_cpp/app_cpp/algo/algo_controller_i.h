#include "transaction.h"

class algo_controller_i{
public:
  virtual void update_data() = 0;
  virtual void update_data_single() = 0;
  virtual transaction* get_transaction() = 0;
};