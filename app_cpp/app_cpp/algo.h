#include <list>
#include "order.h"
class algo{
  struct algo_data{
    /** data for algo **/
    double open_= 0.0;
    double close_ = 0.0;
    int volume_ = 0;
    algo_data(double open, double close, int volume) : open_(open),
                                                      close_(close),
                                                      volume_(volume){}
  };
  std::list<algo_data> data_;

  public:
  void addData(double open, double close, int volume);
  order* process();
};