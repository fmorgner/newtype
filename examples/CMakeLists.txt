file(GLOB SOURCES
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
  CONFIGURE_DEPENDS
  "src/*.cpp"
)

foreach(EXAMPLE IN LISTS SOURCES)
  get_filename_component(NAME "${EXAMPLE}" NAME_WE)
  add_executable("ex_${NAME}" "${EXAMPLE}")
  target_link_libraries("ex_${NAME}" "newtype::newtype")
endforeach()

install(DIRECTORY "src/"
  TYPE DOC
)
