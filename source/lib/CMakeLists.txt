add_library("${PROJECT_NAME}" INTERFACE)

target_include_directories("${PROJECT_NAME}" INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)

target_compile_features("${PROJECT_NAME}" INTERFACE
  "cxx_std_20"
)

install(TARGETS "${PROJECT_NAME}"
  EXPORT "${PROJECT_NAME}Targets"
  PUBLIC_HEADER DESTINATION "include"
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
  DESTINATION "include"
)

add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS "${PROJECT_NAME}")
