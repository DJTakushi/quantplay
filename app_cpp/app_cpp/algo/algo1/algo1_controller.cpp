#include "algo1_controller.h"
#include "algo1.h"
#include "algo1_data_retriever.h"

algo1_controller::algo1_controller(sql::Connection* connection){
  algo = new algo1();
  retriever = new algo1_data_retriever(connection);
}
void algo1_controller::drop_datatable(){
  retriever->drop_datatable();
}

void algo1_controller::update_database_from_file(fs::path filepath){
  retriever->update_database_from_file(filepath);
}

int algo1_controller::update_data(int num){
  std::list<ohlcv*> data = retriever->get_next_data_from_database(num);
  algo->addData(data);
  int size = data.size();
  for(auto i : data){ delete i; } // cleanup data
  return size;
}

transaction* algo1_controller::get_transaction(){
  transaction* out = algo->process();

  return out; 
}
ohlcv* algo1_controller::get_latest_data(){
  return algo->get_latest_data();
}
