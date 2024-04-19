#include <filesystem>
#include "ohlcv.h"
#include "transaction.h"
#include "algo_i.h"

namespace fs = std::filesystem;

class algo_controller_i{
 protected:
  algo_i* algo;
 public:
  virtual int update_data(int num = -1) = 0;
  virtual transaction* get_transaction() = 0;
  virtual void update_database_from_file(fs::path filepath) = 0;
  virtual ohlcv* get_latest_data() = 0;
};