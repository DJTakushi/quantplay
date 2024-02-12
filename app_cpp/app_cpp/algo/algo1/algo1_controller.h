#include "algo_controller_i.h"

class algo1_controller : public algo_controller_i{

public:
  void update_data() = 0;
  void update_data_single() = 0;
  transaction* get_transaction() = 0;
};