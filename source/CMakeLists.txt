cmake_minimum_required(VERSION "3.25.0")

project("newtype"
  LANGUAGES CXX
  DESCRIPTION "A library of types and functions to create strong type aliases"
)

enable_testing()

# Project dependencies

find_package("Catch2" "3.1"
  COMPONENTS "Catch2WithMain"
  REQUIRED
)

include("Catch")

# Project Options

option(BUILD_EXAMPLES "Build the library examples" OFF)

# 'newtype' library

add_library("${PROJECT_NAME}" INTERFACE)

target_include_directories("${PROJECT_NAME}" INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_compile_features("${PROJECT_NAME}" INTERFACE
  "cxx_std_20"
)

install(TARGETS "${PROJECT_NAME}"
  EXPORT "${PROJECT_NAME}Targets"
  PUBLIC_HEADER DESTINATION "include"
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
  DESTINATION "include"
)

add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS "${PROJECT_NAME}")

# 'newtype' tests

add_executable("${PROJECT_NAME}_tests"
  "test/src/arithmetic.cpp"
  # "test/src/conversion_suite.cpp"
  # "test/src/derivation_clause_suite.cpp"
  # "test/src/equality_comparison_suite.cpp"
  # "test/src/hash_suite.cpp"
  # "test/src/io_operators_suite.cpp"
  # "test/src/iterable_suite.cpp"
  # "test/src/new_type_constructor_suite.cpp"
  # "test/src/relational_operators_suite.cpp"
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

# 'newtype' examples

if(BUILD_EXAMPLES)
  function(add_example NAME)
    add_executable("ex_${NAME}"
      "examples/src/${NAME}.cpp"
    )
    target_link_libraries("ex_${NAME}" "${PROJECT_NAME}")
  endfunction()

  add_example("basic_usage")
  add_example("basic_usage_with_show")
  add_example("basic_usage_with_read")
endif()
