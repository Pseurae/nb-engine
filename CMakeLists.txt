cmake_minimum_required(VERSION 3.8)
project(engine)

add_subdirectory(tonic)

add_executable(engine main.cpp)
target_link_libraries(engine PUBLIC tonic)
set_target_properties(engine PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)