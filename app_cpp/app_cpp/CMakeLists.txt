cmake_minimum_required(VERSION 3.27.4)

project(app_cpp VERSION 0.0.0)

# library creation
add_library(${PROJECT_NAME}
  trader/trader.cpp
  recorder/recorder.cpp
  recorder/snapshot.cpp
  common/transaction.cpp
  common/ohlcv.cpp
  portfolio/portfolio.cpp
  algo/algo1/algo1.cpp
  algo/algo1/algo1_data_retriever.cpp
  algo/algo1/algo1_controller.cpp
  algo_manager/algo_manager.cpp
  )
target_include_directories(${PROJECT_NAME}
  PRIVATE
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_SOURCE_DIR}/algo_manager"
  "${PROJECT_SOURCE_DIR}/algo"
  "${PROJECT_SOURCE_DIR}/algo/algo1"
  "${PROJECT_SOURCE_DIR}/common"
  "${PROJECT_SOURCE_DIR}/portfolio"
  "${PROJECT_SOURCE_DIR}/recorder"
  "${PROJECT_SOURCE_DIR}/trader"
)
find_library(mariadb mariadbcpp REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC ${mariadb})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

# main executable
add_executable(main
  main.cpp
)
target_include_directories(main
  PRIVATE
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_SOURCE_DIR}/algo_manager"
  "${PROJECT_SOURCE_DIR}/algo"
  "${PROJECT_SOURCE_DIR}/algo/algo1"
  "${PROJECT_SOURCE_DIR}/common"
  "${PROJECT_SOURCE_DIR}/portfolio"
  "${PROJECT_SOURCE_DIR}/recorder"
  "${PROJECT_SOURCE_DIR}/trader"
)
target_link_libraries(main
  ${PROJECT_NAME}
)
set_property(TARGET main PROPERTY CXX_STANDARD 20)

# unit-testing
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(tests
  portfolio/tests/portfolio.test.cpp
  common/tests/transaction.test.cpp
  algo/algo1/tests/algo1.test.cpp
)
set_property(TARGET tests PROPERTY CXX_STANDARD 20)
target_include_directories(tests
  PRIVATE
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_SOURCE_DIR}/algo"
  "${PROJECT_SOURCE_DIR}/algo/algo1"
  "${PROJECT_SOURCE_DIR}/common"
  "${PROJECT_SOURCE_DIR}/portfolio"
  "${PROJECT_SOURCE_DIR}/recorder"
  "${PROJECT_SOURCE_DIR}/trader"
)
target_link_libraries(tests
  GTest::gtest_main
  ${PROJECT_NAME}
)

include(GoogleTest)
gtest_discover_tests(tests)
configure_file(../../app/testdata/intraday_ibm.json intraday_ibm.json COPYONLY)
configure_file(../../quantitativetradingdemos/data/3_4_ige.csv 3_4_ige.csv COPYONLY)