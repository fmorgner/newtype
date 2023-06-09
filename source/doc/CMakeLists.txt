find_package("Python3"
  REQUIRED
  COMPONENTS "Interpreter"
)

set(DOCENV_DIR "${PROJECT_BINARY_DIR}/docenv")

if(NOT EXISTS "${DOCENV_DIR}")
  message(STATUS "Creating Python virtual environment")
  execute_process(COMMAND "${Python3_EXECUTABLE}"
    "-m"
    "venv"
    "${DOCENV_DIR}"
    OUTPUT_QUIET
  )
  message(STATUS "Installing documentation requirements")
  execute_process(COMMAND
    "${DOCENV_DIR}/bin/python"
    "-m"
    "pip"
    "install"
    "-r"
    "${CMAKE_CURRENT_SOURCE_DIR}/requirements.txt"
    OUTPUT_QUIET
    )
else()
  message(STATUS "Reusing existing Python virtual environment")
endif()

file(GLOB SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
    "${PROJECT_SOURCE_DIR}/examples/src/*"
)

add_custom_target("docs"
    ALL
    DEPENDS
    "${CMAKE_CURRENT_BINARY_DIR}/html/index.html"
    "${CMAKE_CURRENT_BINARY_DIR}/man/newtype.3"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "Building documentation"
)

add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/html/index.html"
    COMMAND "${DOCENV_DIR}/bin/sphinx-build"
    "-b"
    "singlehtml"
    "-q"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_BINARY_DIR}/html"
    DEPENDS ${SOURCES}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "Compiling HTML documentation"
)

add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/man/newtype.3"
    COMMAND "${DOCENV_DIR}/bin/sphinx-build"
    "-b"
    "man"
    "-q"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_BINARY_DIR}/man"
    DEPENDS ${SOURCES}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "Compiling man page"
)

install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html"
  TYPE DOC
  PATTERN ".doctrees" EXCLUDE
  PATTERN ".buildinfo" EXCLUDE
  PATTERN ".nojekyll" EXCLUDE
)

install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/man/"
  TYPE MAN
  PATTERN ".doctrees" EXCLUDE
)
