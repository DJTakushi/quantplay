#include "algo_controller_i.h"
#include "algo1.h"
#include "algo1_data_retriever.h"
class algo1_controller : public algo_controller_i{
  algo1_data_retriever* retriever;
  algo1* algo;
public:
  algo1_controller();
  void update_data() = 0;
  void update_data_single() = 0;
  transaction* get_transaction() = 0;
};