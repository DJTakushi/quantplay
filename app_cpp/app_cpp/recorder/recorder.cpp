#include "recorder.h"

recorder::recorder(){}

ymd_date recorder::get_current_date(){
  /** returns 1900-01-01 if no date initialized**/
  ymd_date out{std::chrono::January/1/1900};
  if(snapshots_.size()>0){
    out = snapshots_.back()->get_date();
  }
  return out;
}

void recorder::add_data(snapshot* d){
  snapshots_.push_back(d);
}
void recorder::print_snapshots(){
  for(auto s : snapshots_){
    s->print();
  }
}
void recorder::print_days(){
  if(snapshots_.size()>0){
    ymd_date ymd = snapshots_.front()->get_date();
    for(auto s : snapshots_){
      if(ymd!=s->get_date()){
        s->print();
        ymd=s->get_date();
      }
    }
    snapshots_.back()->print();
  }
}

void recorder::print_ohlcv_days(){
  std::vector<snapshot> v = get_day_snapshots();
  for(auto i : v){
    i.print_ohlcv();
  }
}
std::vector<snapshot> recorder::get_day_snapshots(){
  std::vector<snapshot> out;
  if(snapshots_.size()>0){
    snapshot t(snapshots_.front());
    for(auto i : snapshots_){
      if(t.get_date() != i->get_date()){
        out.push_back(t);
        t = snapshot(i);
      }
      else{
        t.set_high(std::max(t.get_high(),i->get_high()));
        t.set_low(std::min(t.get_low(),i->get_low()));
        t.set_close(i->get_close());
        t.set_volume(t.get_volume()+i->get_volume());
        t.set_time(i->get_time());
      }
    }
    out.push_back(t);
  }
  return out;
}
