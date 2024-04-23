#include "algo1_data_retriever.h"
#include "helpers.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
algo1_data_retriever::algo1_data_retriever(sql::Connection* connection,
    std::string table_name) : algo_data_retriever_i(connection,table_name){
  drop_datatable();
  create_datatable();
  std::tm tm{};
  tm.tm_year = 2000-1900;//2000
  tm.tm_mon = 1; //jan
  tm.tm_mday = 1;
  tm.tm_hour = 1;
  tm.tm_min = 1;
  tm.tm_sec = 1;
  latest_datapoint_ = std::mktime(&tm);
}

void algo1_data_retriever::create_datatable(){
  sql::Statement* stmnt =connection_->createStatement();
  std::string cmd = "CREATE TABLE IF NOT EXISTS "+table_name_+" (";
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

std::list<ohlcv*> algo1_data_retriever::get_next_data_from_database(
    int num) {
  std::list<ohlcv*> output;
  std::string cmd = "SELECT ";
  cmd += " timestamp, open, high, low, close, volume ";
  std::stringstream ss;
  ss << std::put_time(std::gmtime(&latest_datapoint_),TD_FORMAT);
  std::string tim = ss.str();
  cmd+="FROM "+table_name_+" WHERE timestamp > \""+tim+"\" ";
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

      std::string time_stamp_str = res->getString("timestamp").c_str();
      latest_datapoint_ = datetime_to_time_t(time_stamp_str);
      algo1_data* tmp = new algo1_data(latest_datapoint_,open,high,low,close,volume);
      output.push_back(tmp);
    }
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error querying table: " << e.what() << std::endl;
  }

  return output;
}
void algo1_data_retriever::add_data_to_database(std::list<algo1_data> data_list,
      std::string timezone_s){
      /** TODO : correct time_t usage to ALWAYS use correct UTC timezone **/
  sql:: Statement* stmnt =connection_->createStatement();
  std::string cmd = "INSERT INTO "+table_name_+" (";
  cmd+="timestamp, open, high, low, close, volume) VALUES ";
  for(auto data : data_list){
    std::string time_str;
    char time_char[100];
    const time_t time_ = data.get_time();
    std::strftime(time_char,sizeof(time_char),TD_FORMAT,std::localtime(&time_));


    cmd+="(CONVERT_TZ(\""+std::string(time_char)+"\",'"+timezone_s+"','UTC'),";
    cmd+=std::to_string(data.get_open()) +",";
    cmd+=std::to_string(data.get_high()) +",";
    cmd+=std::to_string(data.get_low()) +",";
    cmd+=std::to_string(data.get_close()) +",";
    cmd+=std::to_string(data.get_volume()) +"),";
  }
  cmd = cmd.substr(0,cmd.length()-1);//get rid of comma
  cmd += ";";
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
  else if(filepath.extension() == ".csv"){
    update_database_from_csv(str);
  }
}
void algo1_data_retriever::update_database_from_json(std::string j){
  nlohmann::json data = nlohmann::json::parse(j);

  std::string timezone_s = data["Meta Data"]["6. Time Zone"];

  data = data["Time Series (5min)"];
  std::list<algo1_data> data_list;
  for(auto i : data.items()){
    algo1_data d;

    time_t t = datetime_to_time_t(i.key());
    d.set_time(t);

    d.set_open(std::stod(std::string(i.value()["1. open"])));
    d.set_high(std::stod(std::string(i.value()["2. high"])));
    d.set_low(std::stod(std::string(i.value()["3. low"])));
    d.set_close(std::stod(std::string(i.value()["4. close"])));
    d.set_volume(std::stoi(std::string(i.value()["5. volume"])));
    data_list.push_back(d);
  }
  add_data_to_database(data_list,timezone_s);
}
void algo1_data_retriever::update_database_from_csv(std::string s){
  std::istringstream iss(s);
  std::list<algo1_data> data_list;
  for (std::string line; std::getline(iss, line); ){
    std::vector<std::string> items;
    while(true){
      std::string::size_type idx = line.find(",");
      if(idx != std::string::npos){
        items.push_back(line.substr(0,idx));
        line = line.substr(idx+1);
      }
      else{ // delimeter not found; push remainder 
        items.push_back(line);
        break;
      }
    }
    try{
      struct tm tm;
      std::string tm_str = items[0];

      //time is set to closing time; otherwise inonsistent hour will
      // produce inconsistent results
      tm_str += +" 17:00:00";
      strptime(tm_str.c_str(), "%m/%d/%Y %H:%M:%S", &tm);
      time_t t = mktime(&tm);  // t is now your desired time_t

      double open = std::stod(items[1]);
      double high = std::stod(items[2]);
      double low = std::stod(items[3]);
      double close = std::stod(items[6]);
      int volume = std::stoi(items[5]);
      data_list.push_back({t,open,high,low,close,volume});
    }
    catch (const std::exception &exc){
      // catch anything thrown within try block that derives from std::exception
      // std::cout << "exception : " << exc.what() <<std::endl;//annoying header
    }
  }
  add_data_to_database(data_list);
}