# CMakeLists.txt for Vulkan Stage 1: Instance and Device

cmake_minimum_required(VERSION 3.10)

# 项目名称
project(VulkanStage1 VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Vulkan库
find_package(Vulkan REQUIRED)

# 查找GLFW库
find_package(glfw3 REQUIRED)

# 添加Common目录的头文件路径
include_directories(${PROJECT_SOURCE_DIR}/../Common/include)

# 添加可执行文件
add_executable(vulkan_stage1 
    src/main.cpp
    ../Common/src/vulkan_utils.cpp
)

# 链接库
target_link_libraries(vulkan_stage1 
    Vulkan::Vulkan
    glfw
)

# 设置输出目录
set_target_properties(vulkan_stage1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
)

# 复制着色器文件到输出目录
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/bin/shaders)

# 复制资源文件到输出目录
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/bin/resources)
