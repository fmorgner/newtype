function(add_example NAME)
  add_executable("ex_${NAME}" "src/${NAME}.cpp")
  target_link_libraries("ex_${NAME}" "${PROJECT_NAME}")
endfunction()

add_example("basic_usage")
add_example("basic_usage_with_show")
add_example("basic_usage_with_read")

install(DIRECTORY "src/"
  TYPE DOC
)
