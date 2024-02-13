#include <list>
#include "transaction.h"
#include "algo_i.h"
#include "algo1_data.h"
class algo1 : public algo_i{
  std::list<algo1_data> data_;

  public:
  void addData(std::list<algo1_data> data_list);
  transaction* process();
};