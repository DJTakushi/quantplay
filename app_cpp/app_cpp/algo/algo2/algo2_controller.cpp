#include "algo2_controller.h"

algo2_controller::algo2_controller(sql::Connection* connection){
  algo = new algo2();
  retriever = new algo2_data_retriever(connection);
}
void algo2_controller::drop_datatable(){
  retriever->drop_datatable();
}

void algo2_controller::update_database_from_file(fs::path filepath){
  retriever->update_database_from_file(filepath);
}

int algo2_controller::update_data(int num){
  std::list<ohlcv> data = retriever->get_next_data_from_database(num);
  algo->addData(data);
  return data.size();
}

void algo2_controller::update_data_single(){
}

transaction* algo2_controller::get_transaction(){
  transaction* out = algo->process();

  return out; 
}
ohlcv* algo2_controller::get_latest_data(){
  return algo->get_latest_data();
}
