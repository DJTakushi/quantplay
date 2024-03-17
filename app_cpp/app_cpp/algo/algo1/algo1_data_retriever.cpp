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
  cmd+="timestamp TIMESTAMP, ";
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

std::list<algo1_data> algo1_data_retriever::get_data(int num){
  std::list<algo1_data> output;
  std::string cmd = "SELECT ";
  cmd += " timestamp, open, high, low, close, volume ";
  std::stringstream ss;
  ss << std::put_time(std::gmtime(&latest_datapoint_),TD_FORMAT);
  std::string tim = ss.str();
  cmd+="FROM algo1 WHERE timestamp > \""+tim+"\" ";
  cmd+= "ORDER BY timestamp";
  if(num > 0){
    cmd+=" LIMIT "+std::to_string(num);
  }
  cmd+=";";
  sql::Statement* stmnt =connection_->createStatement();
  try{
    std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(cmd));
    while (res->next()){
      double open = res->getDouble("open");
      double high = res->getDouble("high");
      double low = res->getDouble("low");
      double close = res->getDouble("close");
      int volume = res->getInt("volume");

      std::tm tm{};
      strptime(res->getString("timestamp"), TD_FORMAT, &tm);
      latest_datapoint_ = timegm(&tm);
      algo1_data tmp(latest_datapoint_,open,high,low,close,volume);
      output.push_back(tmp);
    }
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error querying table: " << e.what() << std::endl;
  }

  return output;
}
void algo1_data_retriever::add_data_to_database(algo1_data data,
      std::string timezone_s){
      /** TODO : correct time_t usage to ALWAYS use correct UTC timezone **/
  std::string time_str;
  char time_char[100];
  const time_t time_ = data.get_time();
  std::strftime(time_char,sizeof(time_char),TD_FORMAT,std::localtime(&time_));

  sql:: Statement* stmnt =connection_->createStatement();
  std::string cmd = "INSERT INTO algo1 (";
  cmd+="timestamp, open, high, low, close, volume) VALUES (";
  cmd+="CONVERT_TZ(\""+std::string(time_char)+"\",'"+timezone_s+"','UTC'),";
  cmd+=std::to_string(data.get_open()) +",";
  cmd+=std::to_string(data.get_high()) +",";
  cmd+=std::to_string(data.get_low()) +",";
  cmd+=std::to_string(data.get_close()) +",";
  cmd+=std::to_string(data.get_volume()) +")";

  try{ stmnt->executeUpdate(cmd); }
  catch (sql::SQLException& e) {
    std::cerr << "Error altering table: " << e.what() << std::endl;
  }
  delete stmnt;
}

void algo1_data_retriever::update_database_from_file(fs::path filepath){
  std::ifstream inFile;
  inFile.open(filepath.string()); //open the input file

  std::stringstream strStream;
  strStream << inFile.rdbuf(); //read the file
  std::string str = strStream.str(); //str holds the content of the file
  if(filepath.extension() == ".json"){
    update_database_from_json(str);
  }
}
void algo1_data_retriever::update_database_from_json(std::string j){
  nlohmann::json data = nlohmann::json::parse(j);

  std::string timezone_s = data["Meta Data"]["6. Time Zone"];

  data = data["Time Series (5min)"];
  for(auto i : data.items()){
    algo1_data d;

    const char *time_details = i.key().c_str();
    struct tm tm;
    strptime(time_details, TD_FORMAT, &tm);
    time_t t = mktime(&tm);  // t is now your desired time_t
    d.set_time(t);

    d.set_open(std::stod(std::string(i.value()["1. open"])));
    d.set_high(std::stod(std::string(i.value()["2. high"])));
    d.set_low(std::stod(std::string(i.value()["3. low"])));
    d.set_close(std::stod(std::string(i.value()["4. close"])));
    d.set_volume(std::stoi(std::string(i.value()["5. volume"])));
    add_data_to_database(d,timezone_s);
  }
}