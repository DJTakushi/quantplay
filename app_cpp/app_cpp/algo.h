#include <list>
#include "order.h"
class algo{
  struct algo_data{
    /** data for algo **/
    double open_= 0.0;
    double close_ = 0.0;
    int volume_ = 0;
  };
  std::list<algo_data> data_;

  void addData(double open, double close, int volume);

  order* process();
};