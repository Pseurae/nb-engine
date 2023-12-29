cmake_minimum_required(VERSION 3.8)
project(libnb)

add_library(libnb STATIC
  source/ECS/Entity.cpp
  source/ECS/Manager.cpp
  source/test.cpp
)

target_link_libraries(libnb PUBLIC tonic)
target_include_directories(libnb PUBLIC include)
set_target_properties(libnb PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)
