cmake_minimum_required(VERSION 3.10)

project(PBRRenderer)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# 查找OpenGL
find_package(OpenGL REQUIRED)

# 查找GLFW
find_package(glfw3 REQUIRED)

# 查找GLM
find_package(glm REQUIRED)

# 查找GLEW
find_package(GLEW REQUIRED)

# 包含目录
include_directories(${OpenGL_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

# 源文件
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# 可执行文件
add_executable(pbr_renderer ${SOURCES})

# 链接库
target_link_libraries(pbr_renderer OpenGL::GL glfw GLEW::GLEW)

# 复制着色器文件到输出目录
file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/shaders/*)
file(COPY ${SHADERS} DESTINATION ${CMAKE_BINARY_DIR}/bin/shaders)
