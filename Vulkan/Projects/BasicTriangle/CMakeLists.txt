cmake_minimum_required(VERSION 3.16)
project(VulkanBasicTriangle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Vulkan
find_package(Vulkan REQUIRED)
if(NOT Vulkan_FOUND)
    message(FATAL_ERROR "Vulkan not found!")
endif()

# Find GLFW
find_package(glfw3 REQUIRED)
if(NOT glfw3_FOUND)
    message(FATAL_ERROR "GLFW not found!")
endif()

# Find GLM
find_package(glm REQUIRED)
if(NOT glm_FOUND)
    message(FATAL_ERROR "GLM not found!")
endif()

# Set output directory
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# Include directories
include_directories(${Vulkan_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/main.cpp
)

# Add executable
add_executable(basic_triangle ${SOURCES})

# Link libraries
target_link_libraries(basic_triangle
    ${Vulkan_LIBRARIES}
    glfw
    ${GLM_LIBRARIES}
)

# Copy shaders to output directory
file(GLOB SHADERS "shaders/*.vert" "shaders/*.frag")
foreach(SHADER ${SHADERS})
    file(COPY ${SHADER} DESTINATION ${OUTPUT_DIR}/shaders)
endforeach()
