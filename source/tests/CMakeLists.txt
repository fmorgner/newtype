find_package("Catch2" "3.1"
  COMPONENTS "Catch2WithMain"
  REQUIRED
)

include("CTest")
include("Catch")

file(GLOB SOURCES
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
  CONFIGURE_DEPENDS
  "src/*.cpp"
)


add_executable("${PROJECT_NAME}_tests"
  ${SOURCES}
)

target_link_libraries("${PROJECT_NAME}_tests"
  "${PROJECT_NAME}::${PROJECT_NAME}"
  "Catch2::Catch2WithMain"
)

target_compile_options("${PROJECT_NAME}_tests" PRIVATE
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-Wall>"
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-Wextra>"
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-Werror>"
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-pedantic-errors>"
  "$<$<CXX_COMPILER_ID:GNU>:-fconcepts-diagnostics-depth=5>"  
)

catch_discover_tests("${PROJECT_NAME}_tests")
