#include "algo.h"

void algo::addData(double open, double close, int volume){
  /** data will be added in chronological order */
  algo_data tmp(open,close,volume);
  data_.push_back(tmp);
}

order* algo::process(){
  /** buy and hold; buy at first available instance and do nothing after**/
  static bool bought = false;
  order* output = NULL;

  if(!bought){
    if(data_.size() > 0){
      /** create order! **/
      output = new order(buy,data_.back().close_);
      bought = true;
    }
  }
  return output;
}