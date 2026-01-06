add_executable("newtype_tests")

target_sources("newtype_tests" PRIVATE
  "src/arithmetic.cpp"
  "src/constructors.cpp"
  "src/conversion.cpp"
  "src/derivation_clause.cpp"
  "src/equality_comparison.cpp"
  "src/hash.cpp"
  "src/io_operators.cpp"
  "src/iterable.cpp"
  "src/relational_operators.cpp"
  "src/threeway_comparison.cpp"
)

target_link_libraries("newtype_tests" PRIVATE
  "newtype::lib"
  "Catch2::Catch2WithMain"
)

target_compile_options("newtype_tests" PRIVATE
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-Wall>"
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-Wextra>"
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-Werror>"
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-pedantic-errors>"
)

set_target_properties("newtype_tests" PROPERTIES
  CMAKE_CXX_EXTENSIONS OFF
  CMAKE_CXX_STANDARD_REQUIRED YES
)

catch_discover_tests("newtype_tests")
