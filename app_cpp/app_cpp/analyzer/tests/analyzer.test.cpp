#include "analyzer.h"
#include <gtest/gtest.h>

class analyzer_dummy : public analyzer {
  std::vector<snapshot> get_day_snapshots() override {
    std::vector<snapshot> out;
    return out;
  };
  std::vector<snapshot> get_snapshots() override {
    std::vector<snapshot> out;
    return out;
  }
};


class analyzerTest : public ::testing::Test, public analyzer_dummy{};
TEST_F(analyzerTest,investopedia_example){

}
