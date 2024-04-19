#include "algo1.h"

void algo1::addData(std::list<ohlcv*> data_list){
  /** data will be added in chronological order */
  for(auto data : data_list){
    ohlcv* p = data;
    algo1_data* d_cast = dynamic_cast<algo1_data*>(p);
    data_.push_back(d_cast);
  }
}

transaction* algo1::process(){
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
ohlcv* algo1::get_latest_data(){
  return new algo1_data(data_.back());
}
