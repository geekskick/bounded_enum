add_library(bounded_enum_lib INTERFACE)
target_include_directories(bounded_enum_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(bounded_enum_lib INTERFACE cxx_std_17)

include(GNUInstallDirs)
install(FILES bounded_enum.hpp DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

