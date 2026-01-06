cmake_minimum_required(VERSION "3.30.0")

project("newtype"
  LANGUAGES CXX
  DESCRIPTION "A library of types and functions to create strong type aliases"
  VERSION "2.0.0"
)

# Project Options

option(NEWTYPE_BUILD_DOCS      "Build the library documentation" OFF)
option(NEWTYPE_BUILD_EXAMPLES  "Build the library examples" OFF)
option(NEWTYPE_BUILD_TESTS     "Build the library tests" OFF)

# Project Dependencies

include("FetchContent")

if(NEWTYPE_BUILD_TESTS)
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
endif()

# Project Components

add_subdirectory("lib")

if(NEWTYPE_BUILD_DOCS)
  add_subdirectory("doc")
endif()

if(NEWTYPE_BUILD_EXAMPLES)
  include("cmake/Modules/AddExample.cmake")
  add_subdirectory("examples")
endif()

if(NEWTYPE_BUILD_TESTS)
  enable_testing()
  add_subdirectory("tests")
endif()