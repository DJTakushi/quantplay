#include "algo_controller.h"

algo_controller::algo_controller(algo_i* algo, algo_data_retriever_i* retriever)
    : algo(algo), retriever(retriever){}

void algo_controller::drop_datatable(){
  retriever->drop_datatable();
}

int algo_controller::update_database_from_file(fs::path filepath, int no){
  return retriever->update_database_from_file(filepath, no);
}

int algo_controller::update_algo_data(int num){
  std::list<ohlcv*> data = retriever->get_next_data_from_database(num);
  algo->addData(data);
  int size = data.size();
  for(auto i : data){ delete i; } // cleanup data
  return size;
}

transaction* algo_controller::get_transaction(){
  transaction* out = algo->process();

  return out; 
}
ohlcv* algo_controller::get_latest_data_from_algo(){
  return algo->get_latest_algo_data();
}
