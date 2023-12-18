cmake_minimum_required(VERSION 3.8)
project(tonic)

include(cmake/build_helpers.cmake)

add_subdirectory(external)

add_library(tonic STATIC 
  source/engine.cpp
  source/log.cpp
  
  source/core/time.cpp
  source/core/window.cpp

  source/graphics/framebuffer.cpp
  source/graphics/helpers.cpp
  source/graphics/renderapi.cpp
  source/graphics/shader.cpp
  source/graphics/texture.cpp
  source/graphics/vertex.cpp

  source/input/keyboard.cpp
  source/input/mouse.cpp
)
target_include_directories(tonic PUBLIC include/)
target_link_libraries(tonic PUBLIC gl3w glfw glm)
set_target_properties(tonic PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)
detectOS(tonic)
detectBuildType(tonic)
