#include "snapshot.h"
#include "typedefs.h"
#include <vector>
class recorder{
  /** logs records for display later **/
protected:
  std::vector<snapshot*> snapshots_;
public:
  recorder();
  ymd_date get_current_date();
  void add_data(snapshot* d);
  void print_snapshots();
  void print_days();
  void print_ohlcv_days();
  std::vector<snapshot> get_day_snapshots();
};