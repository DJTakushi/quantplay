#include "recorder_db.h"
#include "helpers.h"
#include <iostream>

recorder_db::recorder_db(sql::Connection* connection) : connection_(connection){
  drop_datatable();
  create_datatable();
}

ymd_date recorder_db::get_current_date(){
  /** returns 1900-01-01 if no date initialized**/
  ymd_date out{std::chrono::January/1/1900};
  if(portfolio_snapshots_.size()>0){
    out = portfolio_snapshots_.back().get_date();
  }
  return out;
}

void recorder_db::add_data(portfolio d){
  portfolio_snapshots_.push_back(d);
  add_data_to_database(d);
}
void recorder_db::add_data_to_database(portfolio d){
  /** TODO : correct time_t usage to ALWAYS use correct UTC timezone **/
  sql:: Statement* stmnt =connection_->createStatement();
  std::string cmd = "INSERT INTO "+table_name_+" (";
  cmd+="timestamp, balance, shares, value_current) VALUES( ";
  cmd+="\""+time_t_to_gmt_str(d.get_time()) +"\",";
  cmd+=std::to_string(d.get_balance()) +",";
  cmd+=std::to_string(d.get_shares()) +",";
  cmd+=std::to_string(d.get_portfolio_value()) +");";
  try{ stmnt->executeUpdate(cmd); }
  catch (sql::SQLException& e) {
    std::cerr << "Error altering table: " << e.what() << std::endl;
  }
  delete stmnt;
}
void recorder_db::print_portfolio_snapshots(){
  for(auto s : portfolio_snapshots_){
    s.print();
  }
}
void recorder_db::print_days(){
  std::vector<portfolio> v = get_day_portfolio_snapshots();
  for(auto i : v){
    i.print();
  }
}
std::vector<portfolio> recorder_db::get_portfolio_snapshots(){
  return portfolio_snapshots_;
}
std::vector<portfolio> recorder_db::get_day_portfolio_snapshots(){
  std::vector<portfolio> out;
  if(portfolio_snapshots_.size()>0){
    portfolio t(portfolio_snapshots_.front());
    for(auto i : portfolio_snapshots_){
      if(t.get_date() != i.get_date()){
        out.push_back(t);
        t = portfolio(i);
      }
      else{
        t.set_time(i.get_time());
      }
    }
    out.push_back(t);
  }
  return out;
}

void recorder_db::drop_datatable(){
  sql::Statement* stmnt =connection_->createStatement();
  std::string cmd = "DROP TABLE "+table_name_+";";
  try{
    stmnt->executeUpdate(cmd);
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error dropping table "<<table_name_<<" : ";
    std::cerr << e.what() << std::endl;
  }
}
void recorder_db::create_datatable(){
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