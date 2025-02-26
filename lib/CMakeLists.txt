add_library("newtype" INTERFACE)

target_include_directories("newtype" INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)

target_compile_features("newtype" INTERFACE
  "cxx_std_20"
)

set_target_properties("newtype" PROPERTIES
  CMAKE_CXX_EXTENSIONS OFF
  CMAKE_CXX_STANDARD_REQUIRED YES
)

install(DIRECTORY "include/"
  TYPE INCLUDE
)

add_library("newtype::lib" ALIAS "newtype")
