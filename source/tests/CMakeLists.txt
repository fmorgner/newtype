find_package("Catch2" "3.1"
  COMPONENTS "Catch2WithMain"
  REQUIRED
)

include("CTest")
include("Catch")

add_executable("${PROJECT_NAME}_tests"
  "src/arithmetic.cpp"
  "src/conversion.cpp"
  "src/derivation_clause.cpp"
  "src/equality_comparison.cpp"
  "src/hash.cpp"
  "src/io_operators.cpp"
  # "src/iterable_suite.cpp"
  # "src/new_type_constructor_suite.cpp"
  # "src/relational_operators_suite.cpp"
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
)

catch_discover_tests("${PROJECT_NAME}_tests")
