# CMakeLists.txt for OpenGL BasicRenderer
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(OpenGL_BasicRenderer VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找依赖
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# 设置包含目录
include_directories(
    /usr/include/glm
)

# 添加可执行文件
add_executable(basic_renderer src/main.cpp)

# 链接必要的库
target_link_libraries(basic_renderer
    glfw
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

# 设置输出目录
set_target_properties(basic_renderer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 复制着色器文件到构建目录
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
