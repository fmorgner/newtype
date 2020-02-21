cmake_minimum_required(VERSION "3.0")

project("TestPackage" CXX)

set(CMAKE_CXX_STANDARD "20")

include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup()

add_executable("test_package" "main.cpp")