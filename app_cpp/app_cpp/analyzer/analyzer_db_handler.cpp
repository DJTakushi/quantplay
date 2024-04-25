#include <iostream>
#include "analyzer_db_handler.h"

analyzer_db_handler::analyzer_db_handler(sql::Connection* connection,
    algo_type_k type) : db_handler_base(connection,"analysis"){
  // drop_datatable();
  algo_name_ = algo_name[type];
  if(connection_ != NULL){
    create_datatable();
    clear_table_of_name();
  }
}

void analyzer_db_handler::clear_table_of_name(){
  sql::Statement* stmnt =connection_->createStatement();
  std::string cmd = "DELETE FROM "+table_name_+" WHERE ";
  cmd+="name = '"+ algo_name_+"';";
  try{ stmnt->executeUpdate(cmd); }
  catch (sql::SQLException& e) {
    std::cerr << "Error clearing table " << table_name_ << " : ";
    std::cerr << e.what() << std::endl;
  }
}

void analyzer_db_handler::create_datatable(){
  sql::Statement* stmnt =connection_->createStatement();
  std::string cmd = "CREATE TABLE IF NOT EXISTS "+table_name_+" (";
  cmd+="name VARCHAR(20), ";
  cmd+="sharpe_ratio float(8), ";
  cmd+="max_drawdown float(4), ";
  cmd+="max_drawdown_dur float(4));";
  try{ stmnt->executeUpdate(cmd); }
  catch (sql::SQLException& e) {
    std::cerr << "Error creating table " << table_name_ << " : ";
    std::cerr << e.what() << std::endl;
  }
}

void analyzer_db_handler::insert_metrics(analysis a) {
  sql:: Statement* stmnt =connection_->createStatement();
  std::string cmd = "INSERT INTO "+table_name_+" (";
  cmd+="name, sharpe_ratio, max_drawdown, max_drawdown_dur) VALUES ";
  cmd+="('"+algo_name_+"',";
  cmd+=std::to_string(a.sharpe_ratio) +",";
  cmd+=std::to_string(a.max_drawdown_percent) +",";
  cmd+=std::to_string(a.max_drawdown_duration) +");";
  try{ stmnt->executeUpdate(cmd); }
  catch (sql::SQLException& e) {
    std::cerr << "Error altering table: " << e.what() << std::endl;
  }
  delete stmnt;
}
double analyzer_db_handler::retrieve_sharpe_ratio(){
  double out = -999;
  std::string cmd = "SELECT sharpe_ratio FROM "+table_name_+" WHERE name = '" + algo_name_ + "';";
  sql::Statement* stmnt =connection_->createStatement();
  try {
    std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(cmd));
    res->next();
    out = res->getDouble("sharpe_ratio");
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error querying table: " << e.what() << std::endl;
  }
  return out;
}
double analyzer_db_handler::retrieve_max_drawdown(){
  double out = -999;
  std::string cmd = "SELECT max_drawdown FROM "+table_name_+" WHERE name = '" + algo_name_ + "';";
  sql::Statement* stmnt =connection_->createStatement();
  try {
    std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(cmd));
    res->next();
    out = res->getDouble("max_drawdown");
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error querying table: " << e.what() << std::endl;
  }
  return out;
}