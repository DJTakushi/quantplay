cmake_minimum_required(VERSION 3.27.4)

project(app_cpp VERSION 0.0.0)

# library creation
add_library(${PROJECT_NAME}
  transaction.cpp
  transaction.h
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
add_executable(${PROJECT_NAME}_tests
  transaction.test.cpp
)
target_link_libraries(${PROJECT_NAME}_tests
  GTest::gtest_main
  ${PROJECT_NAME}
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)