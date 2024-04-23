#include <iostream>
#include "algo_controller_factory.h"
#include "algo1.h"
#include "algo1_data_retriever.h"
#include "algo2.h"
#include "algo2_data_retriever.h"

algo_controller_i* algo_controller_factory::create_controller(algo_type_k type,
    sql::Connection* conn){
  algo_i* algo;
  algo_data_retriever_i* retriever;
  switch(type){
    case algo1_k:
      algo = new algo1();
      retriever = new algo1_data_retriever(conn,"data_"+algo_name[type]);
      break;
    case algo2_k:
      algo = new algo2();
      retriever = new algo2_data_retriever(conn,"data_"+algo_name[type]);
      break;
    default:
      std::cout<<"algo_controller_factory cannot find algo_type"<<std::endl;
      break;
  }
  return new algo_controller(algo,retriever);
}