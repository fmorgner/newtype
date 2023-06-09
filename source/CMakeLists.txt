cmake_minimum_required(VERSION "3.25.0")

project("newtype"
  LANGUAGES CXX
  DESCRIPTION "A library of types and functions to create strong type aliases"
)

enable_testing()

# Project Options

option(BUILD_EXAMPLES "Build the library examples" OFF)

# Project Components

add_subdirectory("doc")
add_subdirectory("examples")
add_subdirectory("lib")
add_subdirectory("tests")