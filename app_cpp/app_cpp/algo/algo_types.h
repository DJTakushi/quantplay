#pragma once
#include <cstdint>
#include <map>
#include <string>
enum algo_type_k {
  algo1_k = 0,
  algoMax_k=UINT16_MAX,
};

static std::map<int,std::string> algo_name{
  {algo1_k,"algo1"},
  {algoMax_k,"algo_default"}
};