#include "algo2.h"

void algo2::addData(std::list<ohlcv*> data_list){
  /** data will be added in chronological order */
  for(auto data : data_list) data_.push_back(data);
}

transaction* algo2::process(){
  /** buy and hold; buy at first available instance and do nothing after**/
  transaction* output = NULL;

  if(!bought){
    if(data_.size() > 0){
      /** create order! **/
      std::time_t tm = data_.front().time_;
      output = new transaction(tm,data_.front().close_, kBuy);
      bought = true;
    }
  }
  return output;
}
ohlcv* algo2::get_latest_algo_data(){
  return new ohlcv(data_.back());
}
