cmake_minimum_required (VERSION 3.1)
project (glen)

# The main executable
add_executable(glen
  src/main.cpp
        src/application.h
        src/application.cpp
        src/GlenConstants.h
        src/GLError.cpp
        src/GLError.h
        src/MiscHelper.cpp
        src/MiscHelper.h
        src/AppState.h
)

set_property(TARGET glen PROPERTY CXX_STANDARD 20)
target_compile_options(glen PRIVATE -Wall)

add_definitions(-DGLEW_STATIC)
add_subdirectory(dependencies/glfw EXCLUDE_FROM_ALL)
add_subdirectory(dependencies/glew EXCLUDE_FROM_ALL)
add_subdirectory(dependencies/glm EXCLUDE_FROM_ALL)

target_link_libraries(glen
  PRIVATE glfw
  PRIVATE libglew_static
  PRIVATE glm
)

target_include_directories(glen
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src
  PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/spdlog
  PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/stb
)
