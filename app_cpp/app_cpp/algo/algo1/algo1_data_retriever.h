#include <list>
#include "algo1_data.h"
#include <mariadb/conncpp.hpp>
class algo1_data_retriever{
  sql::Connection* connection_;
  public:
  algo1_data_retriever(sql::Connection* connection);
  void create_database();
  std::list<algo1_data> get_data();
  void update_database();
};