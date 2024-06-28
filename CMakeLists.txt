cmake_minimum_required (VERSION 3.1)
project (glen)

add_executable(glen
  src/main.cpp
        src/Application/Application.h
        src/Application/Application.cpp
        src/Utils/GlenConstants.h
        src/Error/GLError.cpp
        src/Error/GLError.h
        src/Utils/MiscHelper.h
        src/Application/AppState.h
        src/Shader/Shader.cpp
        src/Shader/Shader.h
        src/Utils/MiscHelper.cpp
        src/Utils/MiscHelper.tpp
        src/Texture/Texture.cpp
        src/Texture/Texture.h
)

set_property(TARGET glen PROPERTY CXX_STANDARD 20)
target_compile_options(glen PRIVATE -Wall)

add_compile_definitions(-DGLEW_STATIC STB_IMAGE_IMPLEMENTATION)
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
