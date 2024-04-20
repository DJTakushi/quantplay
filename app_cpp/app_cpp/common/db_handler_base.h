#pragma once
#include <mariadb/conncpp.hpp>

class db_handler_base {
 protected:
  sql::Connection* connection_;
 public:
  db_handler_base(sql::Connection* conn) : connection_(conn) {}
  virtual void drop_datatable() = 0;
  virtual void create_datatable() = 0;
};