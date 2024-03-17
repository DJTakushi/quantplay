#include "algo1_controller.h"

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
  std::list<algo1_data> data = retriever->get_data(num);
  algo->addData(data);
  return data.size();
}

void algo1_controller::update_data_single(){
}

transaction* algo1_controller::get_transaction(){
  transaction* out = algo->process();

  return out; 
}
ohlcv* algo1_controller::get_latest_data(){
  return algo->get_latest_data();
}
