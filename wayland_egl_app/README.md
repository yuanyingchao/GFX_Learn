# Wayland EGL OpenGL 应用程序原理文档

## 1. 应用概述

本项目是一个基于 Wayland 显示服务器、EGL 和 OpenGL ES 3.0 的现代图形应用程序。它实现了一个在 Wayland 窗口中显示旋转彩色三角形的功能，采用了现代 OpenGL 渲染管线和 XDG Shell 协议。

## 2. 技术栈

- **Wayland**：现代显示服务器协议，替代传统 X11
- **EGL**：跨平台的图形渲染接口，负责连接 Wayland 和 OpenGL ES
- **OpenGL ES 3.0**：移动和嵌入式设备的现代 3D 图形 API
- **XDG Shell**：Wayland 上的标准窗口管理协议
- **CMake**：跨平台构建系统

## 3. 核心组件

### 3.1 Wayland 窗口系统

Wayland 是一个客户端-服务器架构的显示系统，主要组件包括：

- **wl_display**：Wayland 显示服务器连接
- **wl_registry**：Wayland 全局对象注册表
- **wl_compositor**：创建和管理 Wayland 表面
- **wl_surface**：渲染内容的基础单元
- **xdg_wm_base**：XDG Shell 协议的基础接口
- **xdg_surface**：XDG Shell 的表面包装器
- **xdg_toplevel**：顶级窗口接口，处理窗口状态

### 3.2 EGL 渲染桥接

EGL 是 OpenGL ES 和原生窗口系统之间的中间层，主要组件包括：

- **EGLDisplay**：EGL 显示连接
- **EGLConfig**：渲染配置（颜色深度、缓冲区类型等）
- **EGLContext**：OpenGL ES 上下文
- **EGLSurface**：渲染表面
- **wl_egl_window**：Wayland 特定的 EGL 窗口实现

### 3.3 OpenGL ES 渲染管线

采用现代 OpenGL ES 3.0 渲染管线，主要组件包括：

- **顶点着色器**：处理顶点位置和颜色
- **片段着色器**：处理像素颜色
- **着色器程序**：链接好的着色器集合
- **VBO (Vertex Buffer Object)**：存储顶点数据的缓冲区
- **属性和 Uniform**：将数据传递给着色器的机制

## 4. 初始化流程

应用程序的初始化遵循以下步骤：

### 4.1 Wayland 初始化

1. **连接到显示服务器**：`wl_display_connect(NULL)`
2. **获取全局注册表**：`wl_display_get_registry(display)`
3. **注册全局对象监听器**：监听 wl_compositor 和 xdg_wm_base
4. **轮询事件**：`wl_display_roundtrip(display)` 获取全局对象
5. **创建表面**：`wl_compositor_create_surface(compositor)`
6. **创建 XDG 表面**：`xdg_wm_base_get_xdg_surface(xdg_wm_base, surface)`
7. **创建顶级窗口**：`xdg_surface_get_toplevel(xdg_surface)`
8. **设置窗口属性**：标题、大小限制等
9. **注册事件监听器**：处理窗口配置、关闭等事件
10. **提交表面**：`wl_surface_commit(surface)` 应用初始配置

### 4.2 EGL 初始化

1. **获取 EGL 显示**：`eglGetDisplay((EGLNativeDisplayType)display)`
2. **初始化 EGL**：`eglInitialize(egl_display, &major, &minor)`
3. **选择 EGL 配置**：`eglChooseConfig()` 选择支持 OpenGL ES 2.0 的配置
4. **创建 EGL 上下文**：`eglCreateContext()` 创建 OpenGL ES 3.0 上下文
5. **创建 EGL 窗口**：`wl_egl_window_create(surface, width, height)`
6. **创建 EGL 表面**：`eglCreateWindowSurface()`
7. **绑定上下文和表面**：`eglMakeCurrent()`
8. **设置视口**：`glViewport(0, 0, width, height)`
9. **创建着色器程序**：编译链接顶点和片段着色器
10. **初始化顶点数据**：创建 VBO 并填充顶点位置和颜色

## 5. 渲染流程

渲染流程在主循环中执行，每次循环执行一次绘制：

### 5.1 清除缓冲区

```cpp
// 设置清除颜色（灰色背景）
glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
// 清除颜色和深度缓冲区
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

### 5.2 使用着色器程序

```cpp
glUseProgram(program);
```

### 5.3 设置旋转角度

```cpp
// 更新旋转角度（每帧增加1度）
static float rotation = 0.0f;
// 将角度转换为弧度并传递给着色器
glUniform1f(uRotation, rotation * 3.14159f / 180.0f);
rotation += 1.0f;
if (rotation >= 360.0f) rotation = 0.0f;
```

### 5.4 启用顶点属性

```cpp
glEnableVertexAttribArray(vPosition);
glEnableVertexAttribArray(vColor);
```

### 5.5 绑定 VBO 并设置属性指针

```cpp
// 位置数据
glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);

// 颜色数据
glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
```

### 5.6 绘制三角形

```cpp
glDrawArrays(GL_TRIANGLES, 0, 3);
```

### 5.7 禁用顶点属性

```cpp
glDisableVertexAttribArray(vPosition);
glDisableVertexAttribArray(vColor);
```

### 5.8 交换缓冲区

```cpp
eglSwapBuffers(egl_display, egl_surface);
```

## 6. 着色器实现

### 6.1 顶点着色器

```glsl
attribute vec4 vPosition;
attribute vec4 vColor;
varying vec4 fColor;
uniform float uRotation;

void main() {
    float cosA = cos(uRotation);
    float sinA = sin(uRotation);
    
    // 构建旋转矩阵
    mat4 rotation = mat4(
        cosA, -sinA, 0.0, 0.0,
        sinA, cosA, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    
    // 应用旋转并设置最终位置
    gl_Position = rotation * vPosition;
    
    // 传递颜色到片段着色器
    fColor = vColor;
}
```

### 6.2 片段着色器

```glsl
precision mediump float;
varying vec4 fColor;

void main() {
    // 直接使用顶点着色器传递过来的颜色
    gl_FragColor = fColor;
}
```

## 7. 事件处理

应用程序处理以下主要事件：

### 7.1 窗口配置事件

```cpp
static void xdg_toplevel_handle_configure(void *data, struct xdg_toplevel *xdg_toplevel, int32_t width, int32_t height, struct wl_array *states) {
    // 处理窗口大小变化
    if (width > 0 && height > 0) {
        window_width = width;
        window_height = height;
        
        // 更新EGL窗口大小
        if (egl_window) {
            wl_egl_window_resize(egl_window, window_width, window_height, 0, 0);
        }
        
        // 更新视口
        glViewport(0, 0, window_width, window_height);
    }
}
```

### 7.2 窗口关闭事件

```cpp
static void xdg_toplevel_handle_close(void *data, struct xdg_toplevel *xdg_toplevel) {
    running = 0;
}
```

### 7.3 Ping 事件

```cpp
static void xdg_wm_base_handle_ping(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial) {
    xdg_wm_base_pong(xdg_wm_base, serial);
}
```

### 7.4 XDG Surface 配置事件

```cpp
static void xdg_surface_handle_configure(void *data, struct xdg_surface *xdg_surface, uint32_t serial) {
    xdg_surface_ack_configure(xdg_surface, serial);
}
```

## 8. 资源管理

应用程序在退出前会清理所有资源：

### 8.1 OpenGL 资源清理

```cpp
if (vbo[0] != 0) {
    glDeleteBuffers(2, vbo);
}
if (program != 0) {
    glDeleteProgram(program);
}
```

### 8.2 EGL 资源清理

```cpp
if (egl_surface != EGL_NO_SURFACE) {
    eglDestroySurface(egl_display, egl_surface);
}
if (egl_context != EGL_NO_CONTEXT) {
    eglDestroyContext(egl_display, egl_context);
}
if (egl_display != EGL_NO_DISPLAY) {
    eglTerminate(egl_display);
}
if (egl_window != NULL) {
    wl_egl_window_destroy(egl_window);
}
```

### 8.3 Wayland 资源清理

```cpp
if (surface != NULL) {
    wl_surface_destroy(surface);
}
if (xdg_wm_base != NULL) {
    xdg_wm_base_destroy(xdg_wm_base);
}
if (compositor != NULL) {
    wl_compositor_destroy(compositor);
}
if (registry != NULL) {
    wl_registry_destroy(registry);
}
if (display != NULL) {
    wl_display_disconnect(display);
}
```

## 9. 主循环

应用程序的主循环持续运行直到用户退出：

```cpp
while (running) {
    // 处理 Wayland 事件
    int ret = wl_display_dispatch(display);
    if (ret < 0) {
        break;
    }
    
    // 绘制
    draw();
    
    // 刷新 Wayland 显示
    wl_surface_commit(surface);
    wl_display_flush(display);
    
    // 短暂休眠以控制帧率（约60fps）
    struct timespec ts = {0, 16666666};
    nanosleep(&ts, NULL);
}
```

## 10. 性能优化

应用程序实现了以下性能优化：

1. **使用 VBO**：减少 CPU 和 GPU 之间的数据传输
2. **现代渲染管线**：避免使用已废弃的立即模式
3. **帧率控制**：使用 nanosleep 控制约60fps帧率
4. **资源清理**：确保所有资源都被正确释放
5. **事件驱动**：只在需要时更新窗口大小

## 11. 编译和运行

### 11.1 编译

```bash
cd build
make
```

### 11.2 运行

```bash
./wayland_egl_opengl
```

## 12. 总结

本应用程序展示了如何使用现代图形 API 在 Wayland 系统上创建一个简单的 OpenGL ES 应用。它实现了：

- Wayland 窗口系统的完整集成
- EGL 与 OpenGL ES 的正确配置
- 现代 OpenGL ES 3.0 渲染管线的使用
- 着色器编程和 VBO 技术
- 旋转动画的实现
- 完整的资源管理和事件处理

该应用程序可以作为 Wayland 和 OpenGL ES 开发的基础模板，用于学习和扩展更复杂的图形应用。