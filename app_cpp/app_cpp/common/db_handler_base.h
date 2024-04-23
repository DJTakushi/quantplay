#pragma once
#include <mariadb/conncpp.hpp>

class db_handler_base {
 protected:
  sql::Connection* connection_;
  std::string table_name_;
 public:
  db_handler_base(sql::Connection* conn, std::string table_name);
  virtual void drop_datatable();
  virtual void create_datatable() = 0;
};