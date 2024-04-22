#pragma once
#include <mariadb/conncpp.hpp>

class db_handler_base {
 protected:
  sql::Connection* connection_;
  std::string table_name_;
 public:
  db_handler_base(sql::Connection* conn, std::string table_name) :
      connection_(conn), table_name_(table_name) {}
  virtual void drop_datatable() = 0;
  virtual void create_datatable() = 0;
};