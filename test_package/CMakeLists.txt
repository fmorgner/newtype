cmake_minimum_required(VERSION "3.25")

project("TestPackage" CXX)

find_package("newtype")

add_executable("${PROJECT_NAME}"
  "main.cpp"
)

target_link_libraries("${PROJECT_NAME}" PRIVATE
  "newtype::newtype"
)
