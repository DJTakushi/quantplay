#include "algo1_controller.h"

algo1_controller::algo1_controller(){
  algo = new algo1();
  retriever = new algo1_data_retriever();
}

void algo1_controller::update_data(){
  algo->addData(retriever->get_data());
}

void algo1_controller::update_data_single(){
}

transaction* algo1_controller::get_transaction(){
  transaction* out = NULL;

  return out; 
}
