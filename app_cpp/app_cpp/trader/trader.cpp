#include "trader.h"

transaction* trader::process_transaction(transaction* t){
  /** process trade, add status, and return **/

  // TODO: something better
  t->set_status(kComplete);
  return t;
}