include("FetchContent")

FetchContent_Declare(
  "Catch2"
  URL "https://github.com/catchorg/Catch2/archive/refs/tags/v3.7.0.zip"
  URL_HASH "SHA256=75b04c94471a70680f10f5d0d985bd1a96b8941d040d6a7bfd43f6c6b1de9daf"
  EXCLUDE_FROM_ALL
  FIND_PACKAGE_ARGS
  "3.7.0" EXACT
  COMPONENTS "Catch2WithMain"
)

FetchContent_MakeAvailable("Catch2")

include("Catch")

file(GLOB SOURCES
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
  CONFIGURE_DEPENDS
  "src/*.cpp"
)

add_executable("newtype_tests"
  ${SOURCES}
)

target_link_libraries("newtype_tests"
  "newtype::lib"
  "Catch2::Catch2WithMain"
)

target_compile_options("newtype_tests" PRIVATE
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-Wall>"
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-Wextra>"
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-Werror>"
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-pedantic-errors>"
  "$<$<CXX_COMPILER_ID:GNU>:-fconcepts-diagnostics-depth=5>"  
)

set_target_properties("newtype_tests" PROPERTIES
  CMAKE_CXX_EXTENSIONS OFF
  CMAKE_CXX_STANDARD_REQUIRED YES
)

catch_discover_tests("newtype_tests")
