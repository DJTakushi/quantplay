#pragma once
#include <filesystem>
#include <mariadb/conncpp.hpp>
#include "algo_i.h"
#include "algo_data_retriever_i.h"
#include "ohlcv.h"
#include "transaction.h"

namespace fs = std::filesystem;

class algo_controller_i{
 public:
  virtual int update_data(int num = -1) = 0;
  virtual transaction* get_transaction() = 0;
  virtual void update_database_from_file(fs::path filepath) = 0;
  virtual ohlcv* get_latest_data() = 0;
};

class algo_controller : public algo_controller_i{
 protected:
  algo_i* algo;
  algo_data_retriever_i* retriever;
 public:
  algo_controller(algo_i* algo, algo_data_retriever_i* retriever);
  void drop_datatable();
  // void update_database();
  void update_database_from_file(fs::path filepath) override;
  int update_data(int num = -1);
  transaction* get_transaction();
  ohlcv* get_latest_data() override;
};