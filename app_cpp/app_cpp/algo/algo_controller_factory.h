#pragma once
#include "algo_controller.h"

class algo_controller_factory {
 public:
  static algo_controller_i* create_controller(algo_type_k type,
      sql::Connection* conn);
};