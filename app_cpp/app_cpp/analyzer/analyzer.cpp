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
double analyzer::compute_max_drawdown(){
  double output = 0.0;
  std::vector<snapshot> snapshots = get_snapshots();
  if(snapshots.size()>0){
    snapshot low_snapshot = snapshots.front();
    snapshot high_snapshot = snapshots.front();
    for(auto i : snapshots){
      if(i.get_portfolio_value() < low_snapshot.get_portfolio_value()){
        low_snapshot = i;
        // TODO : try reogranizing var instantiations to optimize performance
        double max = high_snapshot.get_portfolio_value();
        double min = low_snapshot.get_portfolio_value();
        double drawdown = (min-max)/max;
        output = std::min(output,drawdown);
      }
      if(i.get_portfolio_value() > high_snapshot.get_portfolio_value()){
        high_snapshot = i;
        low_snapshot = i;
      }
    }
  }
  return output;
}
double analyzer::compute_max_drawdown_duration() {
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
