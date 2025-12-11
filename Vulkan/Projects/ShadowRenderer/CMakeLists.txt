cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(ShadowRenderer VERSION 1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Vulkan
find_package(Vulkan REQUIRED)

# 查找GLFW
find_package(glfw3 REQUIRED)

# 查找GLM
find_package(glm REQUIRED)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 包含头文件
include_directories(
    ${Vulkan_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    include
)

# 指定源文件
set(SOURCES
    src/main.cpp
)

# 创建可执行文件
add_executable(shadow_renderer ${SOURCES})

# 复制着色器文件到输出目录
file(GLOB SHADERS "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*")
file(COPY ${SHADERS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/)

# 链接库
target_link_libraries(shadow_renderer
    ${Vulkan_LIBRARIES}
    glfw
    ${GLM_LIBRARIES}
)
