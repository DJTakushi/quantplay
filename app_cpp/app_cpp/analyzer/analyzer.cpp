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