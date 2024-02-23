#include "snapshot.h"
#include "typedefs.h"
#include <vector>
class dayrecorder{
  /** logs records for display later **/
protected:
  std::vector<snapshot*> snapshots_;
public:
  dayrecorder();
  ymd_date get_current_date();
  void add_data(snapshot* d);
  void print_snapshots();
  void print_days();
};