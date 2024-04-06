#include "recorder_db.h"

recorder_db::recorder_db(sql::Connection* connection) : connection_(connection)
{}

ymd_date recorder_db::get_current_date(){
  /** returns 1900-01-01 if no date initialized**/
  ymd_date out{std::chrono::January/1/1900};
  if(portfolio_snapshots_.size()>0){
    out = portfolio_snapshots_.back().get_date();
  }
  return out;
}

void recorder_db::add_data(portfolio d){
  portfolio_snapshots_.push_back(d);
}
void recorder_db::print_portfolio_snapshots(){
  for(auto s : portfolio_snapshots_){
    s.print();
  }
}
void recorder_db::print_days(){
  std::vector<portfolio> v = get_day_portfolio_snapshots();
  for(auto i : v){
    i.print();
  }
}
std::vector<portfolio> recorder_db::get_portfolio_snapshots(){
  return portfolio_snapshots_;
}
std::vector<portfolio> recorder_db::get_day_portfolio_snapshots(){
  std::vector<portfolio> out;
  if(portfolio_snapshots_.size()>0){
    portfolio t(portfolio_snapshots_.front());
    for(auto i : portfolio_snapshots_){
      if(t.get_date() != i.get_date()){
        out.push_back(t);
        t = portfolio(i);
      }
      else{
        t.set_time(i.get_time());
      }
    }
    out.push_back(t);
  }
  return out;
}
