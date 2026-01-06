function(newtype_add_example SOURCE_FILE)
  get_filename_component(NAME "${SOURCE_FILE}" NAME_WE)

  add_executable("ex_${NAME}")

  target_sources("ex_${NAME}" PRIVATE
    ${SOURCE_FILE}
  )

  target_link_libraries("ex_${NAME}" PRIVATE
    "newtype::lib"
  )

  target_compile_options("ex_${NAME}" PRIVATE
    "$<$<CXX_COMPILER_ID:GNU,Clang>:-Wall>"
    "$<$<CXX_COMPILER_ID:GNU,Clang>:-Wextra>"
    "$<$<CXX_COMPILER_ID:GNU,Clang>:-Werror>"
    "$<$<CXX_COMPILER_ID:GNU,Clang>:-pedantic-errors>"
  )

  set_target_properties("ex_${NAME}" PROPERTIES
    CMAKE_CXX_EXTENSIONS OFF
    CMAKE_CXX_STANDARD_REQUIRED YES
  )
endfunction()
