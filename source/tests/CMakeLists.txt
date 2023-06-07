find_package("Catch2" "3.1"
  COMPONENTS "Catch2WithMain"
  REQUIRED
)

include("CTest")
include("Catch")

add_executable("${PROJECT_NAME}_tests"
  "src/arithmetic.cpp"
  # "src/conversion_suite.cpp"
  # "src/derivation_clause_suite.cpp"
  # "src/equality_comparison_suite.cpp"
  # "src/hash_suite.cpp"
  # "src/io_operators_suite.cpp"
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