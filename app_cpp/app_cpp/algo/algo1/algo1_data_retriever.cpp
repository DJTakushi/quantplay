#include "algo1_data_retriever.h"
#include <iostream>
algo1_data_retriever::algo1_data_retriever(sql::Connection* connection)
    : connection_(connection){
  create_database();
}

void algo1_data_retriever::create_database(){
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
    std::cerr << "Error altering table: " << e.what() << std::endl;
  }
}

std::list<algo1_data> algo1_data_retriever::get_data(){
  std::list<algo1_data> output;

  return output;
}
void algo1_data_retriever::update_database(){
}