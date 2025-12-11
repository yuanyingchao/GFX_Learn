cmake_minimum_required(VERSION 3.12)
project(vulkan_raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# 查找Vulkan库
find_package(Vulkan REQUIRED)

# 查找GLFW库
find_package(glfw3 REQUIRED)

# 查找GLM库
find_package(glm REQUIRED)

# 包含头文件
include_directories(
    ${Vulkan_INCLUDE_DIRS}
    ${glfw3_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
)

# 源文件
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# 创建可执行文件
add_executable(ray_tracer ${SOURCES})

# 链接库
target_link_libraries(ray_tracer
    ${Vulkan_LIBRARIES}
    glfw
    ${GLM_LIBRARIES}
)

# 复制着色器文件到输出目录
add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:ray_tracer>/shaders
    DEPENDS ray_tracer
)
