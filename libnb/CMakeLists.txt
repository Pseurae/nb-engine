cmake_minimum_required(VERSION 3.8)
project(libnb)

add_library(libnb STATIC
  source/test.cpp
)

target_link_libraries(libnb PUBLIC tonic)
set_target_properties(libnb PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)
