cmake_minimum_required(VERSION 3.16)
project(TexturedCube)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Vulkan库
find_package(Vulkan REQUIRED)

# 查找GLFW库
find_package(glfw3 REQUIRED)

# 查找GLM库
find_package(glm REQUIRED)

# 设置可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 添加可执行文件
add_executable(${PROJECT_NAME} src/main.cpp)

# 包含头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${Vulkan_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Vulkan_LIBRARIES}
    glfw
    glm::glm
)

# 复制着色器文件到构建目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)

# 设置构建目录下的shaders目录
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/shaders)
