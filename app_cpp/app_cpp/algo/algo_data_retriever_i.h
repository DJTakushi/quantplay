#pragma once
#include <ctime>
#include <filesystem>
#include <list>
#include "db_handler_base.h"
#include "helpers.h"
#include "ohlcv.h"

namespace fs = std::filesystem;

class algo_data_retriever_i : public db_handler_base {
 public:
  algo_data_retriever_i(sql::Connection* conn, std::string table_name)
      : db_handler_base(conn,table_name) {}
  virtual void create_datatable() = 0;
  virtual std::list<ohlcv*> get_next_data_from_database(int num = -1) = 0;

  // return # of data entries added to DB for type1 simulations
  virtual int update_database_from_file(fs::path filepath, int no = -1) = 0;
};