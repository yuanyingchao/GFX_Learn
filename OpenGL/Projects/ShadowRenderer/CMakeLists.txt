cmake_minimum_required(VERSION 3.10)
project(ShadowRenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 查找依赖
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

# 包含头文件
include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

# 源文件
set(SOURCES
    src/main.cpp
)

# 可执行文件
add_executable(shadow_renderer ${SOURCES})

# 链接库
target_link_libraries(shadow_renderer OpenGL::GL glfw GLEW::GLEW)

# 复制着色器文件到输出目录
add_custom_command(
    TARGET shadow_renderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:shadow_renderer>/shaders
)
