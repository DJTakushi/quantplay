#include "algo1_controller.h"

algo1_controller::algo1_controller(sql::Connection* connection){
  algo = new algo1();
  retriever = new algo1_data_retriever(connection);
}
void algo1_controller::drop_datatable(){
  retriever->drop_datatable();
}

void algo1_controller::update_database(){
  retriever->update_database();
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
daydata algo1_controller::get_latest_day_data(){
  return algo->get_latest_day_data();
}
