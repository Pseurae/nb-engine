find_package(OpenGL REQUIRED)
find_package(Python REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

execute_process(COMMAND ${Python_EXECUTABLE} gl3w/gl3w_gen.py --root ${PROJECT_BINARY_DIR}/external/gl3w WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external/gl3w)

add_library(gl3w INTERFACE)
target_sources(gl3w PUBLIC ${PROJECT_BINARY_DIR}/external/gl3w/src/gl3w.c)
target_include_directories(gl3w INTERFACE ${PROJECT_BINARY_DIR}/external/gl3w/include)

target_link_libraries(gl3w INTERFACE OpenGL::GL OpenGL::GLU ${CMAKE_DL_LIBS})