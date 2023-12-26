cmake_minimum_required(VERSION 3.27.4)

project(app_cpp VERSION 0.0.0)

add_executable(${PROJECT_NAME}
  main.cpp
  transaction.cpp
  transaction.h
)
target_include_directories(${PROJECT_NAME}
  PRIVATE
  "${PROJECT_SOURCE_DIR}"
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)