struct analysis {
  double sharpe_ratio;
  double max_drawdown_percent;
  double max_drawdown_duration;
  analysis(double sharpe, double drawdown, double drawdown_dur);
};