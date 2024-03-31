#include "trader.h"

transaction* trader::process_transaction(transaction* t){
  /** process trade, add status, and return **/
  if(t != NULL){
    // TODO: something better
    t->set_status(kComplete);
    transactions_.push_back(*t);
  }
  return t;
}