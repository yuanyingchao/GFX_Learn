cmake_minimum_required(VERSION 3.16)

project(QtWaylandExample VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找Qt包和必要的组件
find_package(Qt5 REQUIRED COMPONENTS Widgets Core)

# 添加可执行文件
add_executable(qt_wayland_app main.cpp)

# 链接Qt库
target_link_libraries(qt_wayland_app PRIVATE Qt5::Widgets Qt5::Core)

# 设置安装选项
install(TARGETS qt_wayland_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 添加Wayland支持
if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client)
    pkg_check_modules(WAYLAND_EGL REQUIRED wayland-egl)
    
    target_include_directories(qt_wayland_app PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIRS} ${WAYLAND_EGL_INCLUDE_DIRS})
    target_link_libraries(qt_wayland_app PRIVATE ${WAYLAND_CLIENT_LIBRARIES} ${WAYLAND_EGL_LIBRARIES})
    target_compile_definitions(qt_wayland_app PRIVATE QT_WAYLAND_SUPPORT)
endif()
