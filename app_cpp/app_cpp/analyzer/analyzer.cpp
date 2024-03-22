#include "analyzer.h"

double analyzer::compute_sharpe_ratio(){
  double output;
  std::vector<snapshot> data = get_day_snapshots();
  std::vector<double> excess_daily_return;
  for(size_t i =0; i <  data.size();i++){
    if(i>0){//skip first
      double previous_day = data[i-1].get_portfolio_value();
      double this_day = data[i].get_portfolio_value();
      double this_return = this_day - previous_day;
      double excess_return = this_return - 0.04/252.0;//TODO; make configurable
      excess_daily_return.push_back(excess_return);
    }
  }
  return output;
}