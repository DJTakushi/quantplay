#include "algo1_data_retriever.h"
#include <iostream>
algo1_data_retriever::algo1_data_retriever(sql::Connection* connection)
    : connection_(connection){}

void algo1_data_retriever::create_database(){
  sql::Statement* stmnt =connection_->createStatement();
  try{
    stmnt->executeUpdate("");
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