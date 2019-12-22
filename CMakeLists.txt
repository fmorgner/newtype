cmake_minimum_required(VERSION "3.9.0")

project("newtype"
  VERSION "0.0.1"
  LANGUAGES CXX
  DESCRIPTION "A library to create new types based on existing ones."
)

set(CMAKE_CXX_STANDARD "20")
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

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

    "${PROJECT_SOURCE_DIR}/test/src/derivation_clause_suite.cpp"
    "${PROJECT_SOURCE_DIR}/test/src/new_type_constructor_suite.cpp"
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

  add_custom_target("docs" ALL
    DEPENDS "${PROJECT_BINARY_DIR}/doc/html/index.html" "${PROJECT_BINARY_DIR}/doc/man/newtype.3"
  )

  add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/doc/html/index.html"
    COMMAND "${PIPENV_EXE}" "run" "sphinx-build" "-b" "singlehtml" "${PROJECT_SOURCE_DIR}/doc/src" "${PROJECT_BINARY_DIR}/doc/html" ">/dev/null"
    DEPENDS "${PROJECT_SOURCE_DIR}/doc/src/index.rst" "${PROJECT_SOURCE_DIR}/doc/src/conf.py"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/doc"
    COMMENT "Compiling HTML documentation"
  )

  add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/doc/man/newtype.3"
    COMMAND "${PIPENV_EXE}" "run" "sphinx-build" "-b" "man" "${PROJECT_SOURCE_DIR}/doc/src" "${PROJECT_BINARY_DIR}/doc/man" ">/dev/null"
    DEPENDS "${PROJECT_SOURCE_DIR}/doc/src/index.rst" "${PROJECT_SOURCE_DIR}/doc/src/conf.py"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/doc"
    COMMENT "Compiling man pages"
  )

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

install(EXPORT "${PROJECT_NAME}Targets"
  DESTINATION "lib/cmake/${PROJECT_NAME}"
)
