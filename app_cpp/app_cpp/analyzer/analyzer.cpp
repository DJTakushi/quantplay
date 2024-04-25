#include <iostream>
#include <iomanip>
#include <numeric>
#include <math.h>
#include "analyzer.h"
analyzer::analyzer(sql::Connection* connection,algo_type_k type)
    : analyzer_db_handler(connection,type){}

double analyzer::compute_sharpe_ratio(){
  double output;
  std::vector<portfolio> data = get_day_portfolio_snapshots();
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
  output = double(sqrt(252))*mean/sd;
  if(isnan(output)){
    std::cout << "computed sharpe is nan;";
    std::cout << " returning sharpe_ratio of 0.0" <<std::endl;
    output = 0;
  }
  return output;
}
std::vector<portfolio> analyzer::get_max_drawdown_portfolio_snapshots(){
  /** return high/low pair of portfolios of max drawdown **/
  std::vector<portfolio> record_s;
  std::vector<portfolio> portfolios = get_portfolio_snapshots();
  if(portfolios.size()>0){
    portfolio local_low_s = portfolios.front();
    portfolio local_high_s = portfolios.front();
    record_s.push_back(portfolios.front());
    record_s.push_back(portfolios.front());
    for(auto i : portfolios){
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
double analyzer::calculate_max_drawdown(std::vector<portfolio> high_low){
  /** calculate max-drawdown of high/low portfolios of max drawdown **/
  double output = 0.0;
  if(high_low.size()==2){ // will be 0 if min/max detection failed
    double max = high_low[0].get_portfolio_value();
    double min = high_low[1].get_portfolio_value();
    output = (min-max)/max;
  }
  return output;
}
double analyzer::get_max_drawdown(){
  /** get max drawdown from portfolios of portfolio **/
  std::vector<portfolio> record_timepoints = get_max_drawdown_portfolio_snapshots();
  return calculate_max_drawdown(record_timepoints)*100.0;//get as percentage
}
double analyzer::get_max_drawdown_duration() {
  /** returns max-drawdown-duration in seconds **/
  double max_drawdown_dur = 0.0;
  std::vector<portfolio> portfolios = get_portfolio_snapshots();
  if(portfolios.size()>0){
    portfolio max_portfolio = portfolios.front();
    for(auto i : portfolios){
      double this_dur = difftime(i.get_time(),max_portfolio.get_time());
      max_drawdown_dur = std::max(max_drawdown_dur,this_dur);
      if(i.get_portfolio_value() >= max_portfolio.get_portfolio_value()){
        max_portfolio = i;
      }
    }
  }
  max_drawdown_dur/=(60*60*24); // convert seconds to days
  return max_drawdown_dur;
}
analysis analyzer::generate_analysis() {
  double sharpe_ratio = compute_sharpe_ratio();
  double max_drawdown = get_max_drawdown();
  double max_drawdown_duration = get_max_drawdown_duration();
  return analysis{sharpe_ratio,max_drawdown,max_drawdown_duration};
}

void analyzer::print_analysis(){
  double sharpe_ratio = compute_sharpe_ratio();
  std::cout << "Sharpe Ratio : " << std::fixed << std::setprecision(8);
  std::cout << sharpe_ratio <<std::endl;

  double max_drawdown = get_max_drawdown();
  std::cout << "Max Drawdown : %" << max_drawdown <<std::endl;

  double max_drawdown_duration = get_max_drawdown_duration();
  std::cout << "Max Drawdown Duration : "<< std::setprecision(2);
  std::cout << max_drawdown_duration << " days"<<std::endl;
}
void analyzer::update_database_analysis(){
  insert_metrics(generate_analysis());
}
