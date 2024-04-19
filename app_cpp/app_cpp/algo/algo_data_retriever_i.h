#pragma once
#include <ctime>
#include <filesystem>
#include <list>
#include <mariadb/conncpp.hpp>
#include "helpers.h"
#include "ohlcv.h"

namespace fs = std::filesystem;

class algo_data_retriever_i {
 public:
  virtual void drop_datatable() = 0;
  virtual void create_datatable() = 0;
  virtual std::list<ohlcv*> get_next_data_from_database(int num = -1) = 0;
  virtual void update_database_from_file(fs::path filepath) = 0;
};