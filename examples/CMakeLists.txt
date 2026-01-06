newtype_add_example("src/basic_usage.cpp")
newtype_add_example("src/basic_usage_with_show.cpp")
newtype_add_example("src/basic_usage_with_read.cpp")

install(DIRECTORY "src/"
  TYPE DOC
)
