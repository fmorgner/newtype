add_library("newtype" INTERFACE)

target_sources("newtype" PUBLIC
  FILE_SET HEADERS
  FILES
  "include/newtype/newtype.hpp"
  BASE_DIRS
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_include_directories("newtype" INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)

target_compile_features("newtype" INTERFACE
  "cxx_std_23"
)

set_target_properties("newtype" PROPERTIES
  CMAKE_CXX_EXTENSIONS OFF
  CMAKE_CXX_STANDARD_REQUIRED YES
)

install(DIRECTORY "include/"
  TYPE INCLUDE
)

add_library("newtype::lib" ALIAS "newtype")
