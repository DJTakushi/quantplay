#include "algo1_data_retriever.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
algo1_data_retriever::algo1_data_retriever(sql::Connection* connection)
    : connection_(connection){
  drop_datatable();
  create_datatable();
  std::tm tm{};
  tm.tm_year = 2020-1900;//2020
  tm.tm_mon = 1; //jan
  tm.tm_mday = 1;
  tm.tm_hour = 1;
  tm.tm_min = 1;
  tm.tm_sec = 1;
  latest_datapoint_ = std::mktime(&tm);
}

void algo1_data_retriever::drop_datatable(){
  sql::Statement* stmnt =connection_->createStatement();
  std::string cmd = "DROP TABLE algo1;";
  try{
    stmnt->executeUpdate(cmd);
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error dropping table: " << e.what() << std::endl;
  }
}
void algo1_data_retriever::create_datatable(){
  sql::Statement* stmnt =connection_->createStatement();
  std::string cmd = "CREATE TABLE IF NOT EXISTS algo1 (";
  cmd+="datetime DATETIME, ";
  cmd+="open float(2), ";
  cmd+="high float(2), ";
  cmd+="low float(2), ";
  cmd+="close float(2), ";
  cmd+="volume int";
  cmd+=");";
  try{
    stmnt->executeUpdate(cmd);
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error creating table: " << e.what() << std::endl;
  }
}

std::list<algo1_data> algo1_data_retriever::get_data(){
  std::list<algo1_data> output;
  std::string cmd = "SELECT datetime, open, high, low, close, volume ";
  std::stringstream ss;
  ss << std::put_time(std::gmtime(&latest_datapoint_),"%Y-%M-%d %H:%M:%S");
  std::string tim = ss.str();
  cmd+="FROM algo1 WHERE datetime > \""+tim+"\";";
  sql::Statement* stmnt =connection_->createStatement();
  try{
    std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(cmd));
    // Loop over Result-set
    while (res->next()){
      // Retrieve Values and Print Contacts
      std::cout << "- "
        << res->getString("datetime")
        << " "
        << res->getString("open")
        << " <"
        << res->getString("high")
        << ">"
        << std::endl;
    }
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error querying table: " << e.what() << std::endl;
  }

  return output;
}
void algo1_data_retriever::update_database(){
  std::ifstream f("app_cpp/intraday_ibm.json");
  nlohmann::json data = nlohmann::json::parse(f);
  data = data["Time Series (5min)"];
  sql::Statement* stmnt =connection_->createStatement();
  for(auto i : data.items()){
    std::string cmd = "INSERT INTO algo1 (";
    cmd+="datetime, open, high, low, close, volume) VALUES (";
    cmd+="\""+i.key()+"\",";
    cmd+=std::string(i.value()["1. open"]) +",";
    cmd+=std::string(i.value()["2. high"]) +",";
    cmd+=std::string(i.value()["3. low"]) +",";
    cmd+=std::string(i.value()["4. close"]) +",";
    cmd+=std::string(i.value()["5. volume"]) +")";

    try{ stmnt->executeUpdate(cmd); }
    catch (sql::SQLException& e) {
      std::cerr << "Error altering table: " << e.what() << std::endl;
    }
  }
  delete stmnt;
}