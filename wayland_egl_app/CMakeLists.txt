cmake_minimum_required(VERSION 3.10)
project(wayland_egl_app)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 使用pkg-config查找依赖
find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client)
pkg_check_modules(WAYLAND_EGL REQUIRED wayland-egl)
pkg_check_modules(EGL REQUIRED egl)
pkg_check_modules(GLES REQUIRED glesv2)

# 查找wayland-scanner工具
find_program(WAYLAND_SCANNER wayland-scanner)
if(NOT WAYLAND_SCANNER)
    message(FATAL_ERROR "wayland-scanner not found")
endif()

# 查找wayland-protocols路径
find_package(WaylandProtocols)
if(WaylandProtocols_FOUND)
    set(XDG_SHELL_PROTOCOL ${WaylandProtocols_DIR}/../../share/wayland-protocols/stable/xdg-shell/xdg-shell.xml)
else()
    # 如果没有找到WaylandProtocols包，尝试手动查找
    set(XDG_SHELL_PROTOCOL /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml)
    if(NOT EXISTS ${XDG_SHELL_PROTOCOL})
        message(FATAL_ERROR "Could not find xdg-shell.xml protocol file")
    endif()
endif()

# 生成xdg-shell客户端协议文件
set(XDG_SHELL_CLIENT_PROTOCOL_H ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-client-protocol.h)
set(XDG_SHELL_CLIENT_PROTOCOL_C ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-client-protocol.c)

add_custom_command(
    OUTPUT ${XDG_SHELL_CLIENT_PROTOCOL_H}
    COMMAND ${WAYLAND_SCANNER} client-header ${XDG_SHELL_PROTOCOL} ${XDG_SHELL_CLIENT_PROTOCOL_H}
    DEPENDS ${XDG_SHELL_PROTOCOL}
    COMMENT "Generating xdg-shell client header"
)

add_custom_command(
    OUTPUT ${XDG_SHELL_CLIENT_PROTOCOL_C}
    COMMAND ${WAYLAND_SCANNER} private-code ${XDG_SHELL_PROTOCOL} ${XDG_SHELL_CLIENT_PROTOCOL_C}
    DEPENDS ${XDG_SHELL_PROTOCOL} ${XDG_SHELL_CLIENT_PROTOCOL_H}
    COMMENT "Generating xdg-shell client code"
)

# 添加可执行文件
add_executable(wayland_egl_opengl
    wayland_egl_opengl.cpp
    ${XDG_SHELL_CLIENT_PROTOCOL_C}
)

# 包含头文件目录
target_include_directories(wayland_egl_opengl
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${WAYLAND_CLIENT_INCLUDE_DIRS}
    ${WAYLAND_EGL_INCLUDE_DIRS}
    ${EGL_INCLUDE_DIRS}
    ${GLES_INCLUDE_DIRS}
)

# 链接必要的库
target_link_libraries(wayland_egl_opengl
    ${WAYLAND_CLIENT_LIBRARIES}
    ${WAYLAND_EGL_LIBRARIES}
    ${EGL_LIBRARIES}
    ${GLES_LIBRARIES}
)

# 设置编译选项
target_compile_options(wayland_egl_opengl
    PRIVATE
    ${WAYLAND_CLIENT_CFLAGS_OTHER}
    ${WAYLAND_EGL_CFLAGS_OTHER}
    ${EGL_CFLAGS_OTHER}
    ${GLES_CFLAGS_OTHER}
)

# 清理目标
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Cleaning all generated files"
)
