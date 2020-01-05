cmake_minimum_required(VERSION "3.9.0")

project("newtype"
  VERSION "1.0.1"
  LANGUAGES CXX
  DESCRIPTION "A library of types and functions to create strong type aliases"
)

set(CMAKE_CXX_STANDARD "20")
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

include("CTest")
include("CMakePackageConfigHelpers")

# 'newtype' library

add_library("${PROJECT_NAME}" INTERFACE)

target_include_directories("${PROJECT_NAME}" INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS "${PROJECT_NAME}"
  EXPORT "${PROJECT_NAME}Targets"
  PUBLIC_HEADER DESTINATION "include"
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
  DESTINATION "include"
)

# 'newtype' tests

if(BUILD_TESTING)
  include("${PROJECT_SOURCE_DIR}/cmake/Modules/DiscoverTests.cmake")
  include("${PROJECT_SOURCE_DIR}/cmake/Modules/Conan.cmake")

  conan_check(REQUIRED)
  conan_add_remote(NAME "fmorgner-public" URL "https://api.bintray.com/conan/fmorgner/conan-public")
  conan_cmake_run(CONANFILE "conanfile.py"
    BASIC_SETUP
    CMAKE_TARGETS
    BUILD "missing"
    NO_OUTPUT_DIRS
  )

  add_executable("${PROJECT_NAME}_tests"
    "${PROJECT_SOURCE_DIR}/test/src/driver.cpp"

    "${PROJECT_SOURCE_DIR}/test/src/arithmetic_suite.cpp"
    "${PROJECT_SOURCE_DIR}/test/src/conversion_suite.cpp"
    "${PROJECT_SOURCE_DIR}/test/src/derivation_clause_suite.cpp"
    "${PROJECT_SOURCE_DIR}/test/src/equality_comparison_suite.cpp"
    "${PROJECT_SOURCE_DIR}/test/src/hash_suite.cpp"
    "${PROJECT_SOURCE_DIR}/test/src/io_operators_suite.cpp"
    "${PROJECT_SOURCE_DIR}/test/src/new_type_constructor_suite.cpp"
    "${PROJECT_SOURCE_DIR}/test/src/relational_operators_suite.cpp"
    )

  target_include_directories("${PROJECT_NAME}_tests" PRIVATE
    "${PROJECT_SOURCE_DIR}/test/include"
  )

  target_link_libraries("${PROJECT_NAME}_tests"
    "newtype"
    "CONAN_PKG::CUTE"
    "CONAN_PKG::lyra"
  )

  target_compile_options("${PROJECT_NAME}_tests" PRIVATE
    "-Wall"
    "-Wextra"
    "-Werror"
    "-pedantic-errors"
  )

  discover_tests(TARGET "${PROJECT_NAME}_tests")

  add_custom_target("run_all_tests"
    COMMAND ${CMAKE_CTEST_COMMAND} "--output-on-failure"
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS "newtype_tests"
    COMMENT "Running unit tests"
  )
endif()

# 'newtype' docs

option(BUILD_DOCS "Build the library documentation" OFF)

if(BUILD_DOCS)
  find_program(PIPENV_EXE NAMES "pipenv3" "pipenv")
  if(NOT PIPENV_EXE)
    message(FATAL_ERROR "Could not find pipenv")
  endif()

  execute_process(COMMAND "${PIPENV_EXE}" "install"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/doc"
    OUTPUT_QUIET
  )

  set(DOC_SOURCES
    "${PROJECT_SOURCE_DIR}/doc/src/index.rst"
    "${PROJECT_SOURCE_DIR}/doc/src/conf.py"
    "${PROJECT_SOURCE_DIR}/examples/src/basic_usage.cpp"
    "${PROJECT_SOURCE_DIR}/examples/src/basic_usage_with_show.cpp"
    "${PROJECT_SOURCE_DIR}/examples/src/basic_usage_with_read.cpp"
  )

  add_custom_target("docs"
    DEPENDS "${PROJECT_BINARY_DIR}/doc/html/index.html" "${PROJECT_BINARY_DIR}/doc/man/newtype.3"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/doc"
    COMMENT "Building documentation"
  )

  add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/doc/html/index.html"
    COMMAND "${PIPENV_EXE}" "run" "sphinx-build" "-b" "singlehtml" "${PROJECT_SOURCE_DIR}/doc/src" "${PROJECT_BINARY_DIR}/doc/html" ">/dev/null"
    DEPENDS ${DOC_SOURCES}
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/doc"
    COMMENT "Compiling HTML documentation"
  )

  add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/doc/man/newtype.3"
    COMMAND "${PIPENV_EXE}" "run" "sphinx-build" "-b" "man" "${PROJECT_SOURCE_DIR}/doc/src" "${PROJECT_BINARY_DIR}/doc/man" ">/dev/null"
    DEPENDS ${DOC_SOURCES}
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/doc"
    COMMENT "Compiling man pages"
  )

  add_dependencies("${PROJECT_NAME}" "docs")

  install(DIRECTORY "${PROJECT_BINARY_DIR}/doc/html"
    DESTINATION "share/doc/${PROJECT_NAME}"
    PATTERN ".nojekyll" EXCLUDE
    PATTERN ".buildinfo" EXCLUDE
    PATTERN ".doctrees" EXCLUDE
    PATTERN "objects.inv" EXCLUDE
  )

  install(FILES "${PROJECT_BINARY_DIR}/doc/man/${PROJECT_NAME}.3"
    DESTINATION "share/man/man3"
  )
endif()

# 'newtype' examples

option(BUILD_EXAMPLES "Build the library examples" OFF)

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

# CMake support files

write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    COMPATIBILITY "AnyNewerVersion"
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
)

install(FILES
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  DESTINATION "lib/cmake/${PROJECT_NAME}"
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/doc/src/"
  DESTINATION "share/doc/newtype"
)

install(EXPORT "${PROJECT_NAME}Targets"
  DESTINATION "lib/cmake/${PROJECT_NAME}"
)
