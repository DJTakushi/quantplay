#include "algo1.h"

void algo1::addData(std::list<algo1_data> data_list){
  /** data will be added in chronological order */
  for(auto data : data_list) data_.push_back(data);
}

transaction* algo1::process(){
  /** buy and hold; buy at first available instance and do nothing after**/
  static bool bought = false;
  transaction* output = NULL;

  if(!bought){
    if(data_.size() > 0){
      /** create order! **/
      output = new transaction(std::time(nullptr),data_.back().close_, kBuy);
      bought = true;
    }
  }
  return output;
}