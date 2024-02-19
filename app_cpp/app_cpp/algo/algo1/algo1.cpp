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
      std::time_t tm = data_.front().time_;
      output = new transaction(tm,data_.front().close_, kBuy);
      bought = true;
    }
  }
  return output;
}
daydata algo1::get_latest_day_data(){
  time_t t = data_.back().time_;
  tm tm = *localtime(&t);
  std::chrono::year::year y(tm.tm_year);

  ymd_date date(tm.tm_year,tm.tm_month,tm.tm_day);
  daydata out;
  out.set_open()
  return data_.back();
}
