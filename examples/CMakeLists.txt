add_executable(bounded_enum_example main.cpp)
set_target_properties(bounded_enum_example PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(bounded_enum_example PRIVATE bounded_enum_lib)