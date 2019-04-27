add_library(bounded_enum_lib INTERFACE)
target_include_directories(bounded_enum_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

include(GNUInstallDirs)
install(FILES bounded_enum.hpp DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

