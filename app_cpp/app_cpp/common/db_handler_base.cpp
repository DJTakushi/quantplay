#include <iostream>
#include "db_handler_base.h"

db_handler_base::db_handler_base(sql::Connection* conn, std::string table_name)
    : connection_(conn), table_name_(table_name) {}

void db_handler_base::drop_datatable(){
  sql::Statement* stmnt =connection_->createStatement();
  std::string cmd = "DROP TABLE "+table_name_+";";
  try{
    stmnt->executeUpdate(cmd);
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error dropping table: " << e.what() << std::endl;
  }
}