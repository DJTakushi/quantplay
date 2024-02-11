cmake_minimum_required(VERSION 3.27.4)

project(app_cpp VERSION 0.0.0)

# library creation
add_library(${PROJECT_NAME}
  daydata.h
  daydata.cpp
  dayrecorder.h
  dayrecorder.cpp
  transaction.cpp
  transaction.h
  portfolio.h
  portfolio.cpp
  algo.h
  algo.cpp
)
target_include_directories(${PROJECT_NAME}
  PRIVATE
  "${PROJECT_SOURCE_DIR}"
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

# main executable
add_executable(main
  main.cpp
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
  tests/daydata.test.cpp
  tests/dayrecorder.test.cpp
  tests/portfolio.test.cpp
  tests/transaction.test.cpp
)
set_property(TARGET tests PROPERTY CXX_STANDARD 20)
target_include_directories(tests
  PRIVATE
  "${PROJECT_SOURCE_DIR}"
)
target_link_libraries(tests
  GTest::gtest_main
  ${PROJECT_NAME}
)

include(GoogleTest)
gtest_discover_tests(tests)