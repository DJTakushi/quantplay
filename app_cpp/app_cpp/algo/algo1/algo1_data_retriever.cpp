#include "algo1_data_retriever.h"

algo1_data_retriever::algo1_data_retriever(sql::Connection* connection)
    : connection_(connection){}

void algo1_data_retriever::create_database(){

}

std::list<algo1_data> algo1_data_retriever::get_data(){
  std::list<algo1_data> output;

  return output;
}
void algo1_data_retriever::update_database(){
}