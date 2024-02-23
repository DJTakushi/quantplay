#include "dayrecorder.h"

dayrecorder::dayrecorder(){}

ymd_date dayrecorder::get_current_date(){
  /** returns 1900-01-01 if no date initialized**/
  ymd_date out{std::chrono::January/1/1900};
  if(snapshots_.size()>0){
    out = snapshots_.back()->get_date();
  }
  return out;
}

void dayrecorder::add_data(snapshot* d){
  snapshots_.push_back(d);
}
void dayrecorder::print_snapshots(){
  for(auto s : snapshots_){
    s->print();
  }
}
void dayrecorder::print_days(){
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