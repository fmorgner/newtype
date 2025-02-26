cmake_minimum_required(VERSION "3.25.0")

project("newtype"
  LANGUAGES CXX
  DESCRIPTION "A library of types and functions to create strong type aliases"
  VERSION "1.2.0"
)

# Project Options

option(NEWTYPE_BUILD_DOCS "Build the library documentation" ON)
option(NEWTYPE_BUILD_EXAMPLES "Build the library examples" ON)
option(NEWTYPE_BUILD_TESTS "Build the library tests" ON)

# Project Components

add_subdirectory("lib")

if(NEWTYPE_BUILD_DOCS)
  add_subdirectory("doc")
endif()

if(NEWTYPE_BUILD_EXAMPLES)
  add_subdirectory("examples")
endif()

if(NEWTYPE_BUILD_TESTS)
  enable_testing()
  add_subdirectory("tests")
endif()