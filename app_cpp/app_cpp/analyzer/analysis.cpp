#include "analysis.h"

analysis::  analysis(double sharpe, double drawdown, double drawdown_dur)
    : sharpe_ratio(sharpe),
    max_drawdown_percent(drawdown),
    max_drawdown_duration(drawdown_dur){}
