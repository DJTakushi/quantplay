#include "transaction.h"
#include <vector>
class trader{
  std::vector<transaction> transactions_;

  public:
  trader(){};
  transaction* process_transaction(transaction* t);
};