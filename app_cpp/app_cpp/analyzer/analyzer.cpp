#include "analyzer.h"
#include <numeric>
#include <math.h>
double analyzer::compute_sharpe_ratio(){
  double output;
  std::vector<snapshot> data = get_day_snapshots();
  std::vector<double> excess_daily_return;
  for(size_t i =0; i <  data.size();i++){
    if(i>0){//skip first; no previous_day
      double previous_day = data[i-1].get_portfolio_value();
      double this_day = data[i].get_portfolio_value();
      double daily_return = (this_day - previous_day)/previous_day;
      double excess_return = daily_return - 0.04/252.0;//TODO; make configurable
      excess_daily_return.push_back(excess_return);
    }
  }
  double summation = std::reduce(excess_daily_return.begin(),
                                excess_daily_return.end());
  double mean = summation/excess_daily_return.size();

  double var = 0.0; //variance
  for(size_t n = 0; n < excess_daily_return.size(); n++ ) {
    var += (excess_daily_return[n] - mean) * (excess_daily_return[n] - mean);
  }
  double samples = excess_daily_return.size() - 1; // sample variance used
  var /= samples;
  double sd = double(sqrt(var));

  return double(sqrt(252))*mean/sd;
}
std::vector<snapshot> analyzer::get_max_drawdown_snapshots(){
  /** return high/low pair of snapshots of max drawdown **/
  std::vector<snapshot> record_s;
  std::vector<snapshot> snapshots = get_snapshots();
  if(snapshots.size()>0){
    snapshot local_low_s = snapshots.front();
    snapshot local_high_s = snapshots.front();
    record_s.push_back(snapshots.front());
    record_s.push_back(snapshots.front());
    for(auto i : snapshots){
      if(i.get_portfolio_value() < local_low_s.get_portfolio_value()){
        local_low_s = i;
        double drawdown = calculate_max_drawdown({local_high_s,local_low_s});
        if(drawdown < calculate_max_drawdown(record_s)){
          record_s[0] = local_high_s;
          record_s[1] = local_low_s;
        }
      }
      if(i.get_portfolio_value() > local_high_s.get_portfolio_value()){
        local_high_s = i;
        local_low_s = i;
      }
    }
  }
  return record_s;
}
double analyzer::calculate_max_drawdown(std::vector<snapshot> high_low){
  /** calculate max-drawdown of high/low snapshots of max drawdown **/
  double output = 0.0;
  if(high_low.size()==2){ // will be 0 if min/max detection failed
    double max = high_low[0].get_portfolio_value();
    double min = high_low[1].get_portfolio_value();
    output = (min-max)/max;
  }
  return output;
}
double analyzer::get_max_drawdown(){
  /** get max drawdown from snapshots of portfolio **/
  std::vector<snapshot> record_timepoints = get_max_drawdown_snapshots();
  return calculate_max_drawdown(record_timepoints);
}
double analyzer::get_max_drawdown_duration() {
  /** returns max-drawdown-duration in seconds **/
  double max_drawdown_dur = 0.0;
  std::vector<snapshot> snapshots = get_snapshots();
  if(snapshots.size()>0){
    snapshot max_snapshot = snapshots.front();
    for(auto i : snapshots){
      double this_dur = difftime(i.get_time(),max_snapshot.get_time());
      max_drawdown_dur = std::max(max_drawdown_dur,this_dur);
      if(i.get_portfolio_value() >= max_snapshot.get_portfolio_value()){
        max_snapshot = i;
      }
    }
  }
  return max_drawdown_dur;
}
