project(tonic-tests)

set(FILES graphics.cpp)

foreach(FILE ${FILES})
get_filename_component(FILENAME ${FILE} NAME_WLE)
add_executable(${FILENAME} ${FILE})
target_link_libraries(${FILENAME} PUBLIC tonic)
set_target_properties(${FILENAME} PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)
endforeach()