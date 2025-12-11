# CMakeLists.txt for Week1_GettingStarted
# 使用现代CMake语法（要求CMake版本3.10或更高）
cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(Week1_GettingStarted VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找GLFW库
find_package(glfw3 3.3 REQUIRED)

# 查找GLEW库
find_package(GLEW REQUIRED)

# 查找OpenGL库
find_package(OpenGL REQUIRED)

# 添加可执行文件
add_executable(week1 main.cpp)

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 链接库
target_link_libraries(week1 glfw GLEW::GLEW OpenGL::GL)

# 设置输出目录
set_target_properties(week1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
)

# 复制着色器文件到输出目录
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/bin/shaders)

# 如果有资源文件，也可以复制它们
# file(COPY ${PROJECT_SOURCE_DIR}/resources/ DESTINATION ${PROJECT_BINARY_DIR}/bin/resources/)
