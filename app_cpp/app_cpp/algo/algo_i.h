#include <list>
#include "transaction.h"
class algo_i{
  public:
  // virtual void addData(algo_data_i*) = 0;//interface datatype unsuitable
  virtual transaction* process() = 0;
};