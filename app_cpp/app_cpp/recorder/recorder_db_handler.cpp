#include "recorder_db_handler.h"
#include "helpers.h"
#include <iostream>

recorder_db_handler::recorder_db_handler(sql::Connection* connection,
    std::string table_name) : db_handler_base(connection,table_name) {
  drop_datatable();
  create_datatable();
}

void recorder_db_handler::add_data_to_db(std::vector<portfolio> dv){
  /** TODO : correct time_t usage to ALWAYS use correct UTC timezone **/
  sql:: Statement* stmnt =connection_->createStatement();
  std::string cmd = "INSERT INTO "+table_name_+" (";
  cmd+="timestamp, balance, shares, value_current) VALUES ";
  for(auto d : dv){

    cmd+="(\""+time_t_to_gmt_str(d.get_time()) +"\",";
    cmd+=std::to_string(d.get_balance()) +",";
    cmd+=std::to_string(d.get_shares()) +",";
    cmd+=std::to_string(d.get_portfolio_value()) +"),";
  }
  cmd = cmd.substr(0,cmd.length()-1);//get rid of comma
  cmd += ";";
  try{ stmnt->executeUpdate(cmd); }
  catch (sql::SQLException& e) {
    std::cerr << "Error altering table: " << e.what() << std::endl;
  }
  delete stmnt;
}
std::vector<portfolio> recorder_db_handler::get_portfolio_snapshots(){
  std::vector<portfolio> output;
  std::string cmd = "SELECT ";
  cmd += " timestamp, balance, shares, value_current ";
  cmd+="FROM "+table_name_+" ORDER BY timestamp;";
  sql::Statement* stmnt =connection_->createStatement();
  try{
    std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(cmd));
    while (res->next()){
      std::string time_stamp_str = res->getString("timestamp").c_str();
      time_t time_tmp = datetime_to_time_t(time_stamp_str);
      double balance_tmp = res->getDouble("balance");
      uint shares_tmp = res->getDouble("shares");
      double value_curent_tmp = res->getDouble("value_current");

      output.push_back(portfolio(res->getString("timestamp").c_str(),balance_tmp,shares_tmp,value_curent_tmp));
    }
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error querying table: " << e.what() << std::endl;
  }
  return output;
}

void recorder_db_handler::create_datatable(){
  sql::Statement* stmnt =connection_->createStatement();
  std::string cmd = "CREATE TABLE IF NOT EXISTS "+table_name_+" (";
  cmd+="timestamp TIMESTAMP, ";
  cmd+="balance float(2), ";
  cmd+="shares float(2), ";
  cmd+="value_current float(2));";
  try{
    stmnt->executeUpdate(cmd);
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error creating table " << table_name_ << " : ";
    std::cerr << e.what() << std::endl;
  }
}