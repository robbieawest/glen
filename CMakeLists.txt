cmake_minimum_required (VERSION 3.1)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS -m32)

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

add_compile_definitions(-DGLEW_STATIC)

set(dep ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
message("dep ${dep}")

target_link_directories(glen PRIVATE ${dep}/glew ${dep}/glfw)
target_link_libraries(glen PRIVATE glfw3 glew32s opengl32)
target_include_directories(glen PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${dep}/glew/include
        ${dep}/glfw/include
        ${dep}/spdlog
        ${dep}/stb
        ${dep}/glm
)
