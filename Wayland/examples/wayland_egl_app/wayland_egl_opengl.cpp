/*
 * Wayland EGL OpenGL 示例应用 (使用 xdg_shell)
 * 编译命令: g++ wayland_egl_opengl.cpp -o wayland_egl_opengl -lwayland-client -lwayland-egl -lEGL -lGL -DWLR_USE_UNSTABLE
 * 运行命令: ./wayland_egl_opengl
 * 功能: 在Wayland窗口中绘制旋转的彩色三角形
 */

#include <wayland-client.h>
#include <wayland-egl.h>
#include <wayland-client-protocol.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <cstring>

// 包含XDG Shell协议头文件
#include "xdg-shell-client-protocol.h"

// 全局变量
static struct wl_display *display = NULL;
static struct wl_registry *registry = NULL;
static struct wl_compositor *compositor = NULL;
static struct wl_surface *surface = NULL;
static struct xdg_wm_base *xdg_wm_base = NULL;
static struct xdg_surface *xdg_surface = NULL;
static struct xdg_toplevel *xdg_toplevel = NULL;

static EGLDisplay egl_display = EGL_NO_DISPLAY;
static EGLConfig egl_config = NULL;
static EGLContext egl_context = EGL_NO_CONTEXT;
static EGLSurface egl_surface = EGL_NO_SURFACE;
static struct wl_egl_window *egl_window = NULL;

static int window_width = 800;
static int window_height = 600;
static volatile int running = 1;

// XDG Toplevel 处理函数
static void xdg_toplevel_handle_configure(void *data, struct xdg_toplevel *xdg_toplevel, int32_t width, int32_t height, struct wl_array *states) {
    // 处理窗口大小变化
    if (width > 0 && height > 0) {
        window_width = width;
        window_height = height;
        printf("窗口大小已更新: %dx%d\n", window_width, window_height);
        
        // 更新EGL窗口大小
        if (egl_window) {
            wl_egl_window_resize(egl_window, window_width, window_height, 0, 0);
        }
        
        // 更新视口
        glViewport(0, 0, window_width, window_height);
    }
}

static void xdg_toplevel_handle_close(void *data, struct xdg_toplevel *xdg_toplevel) {
    // 处理窗口关闭事件
    running = 0;
}

static void xdg_toplevel_handle_configure_bounds(void *data, struct xdg_toplevel *xdg_toplevel, int32_t width, int32_t height) {
    // 处理窗口边界配置事件
    // 这个回调函数在较新版本的XDG Shell协议中新增
    // 可以根据需要实现窗口边界约束逻辑
}

static const struct xdg_toplevel_listener xdg_toplevel_listener = {
    .configure = xdg_toplevel_handle_configure,
    .close = xdg_toplevel_handle_close,
    .configure_bounds = xdg_toplevel_handle_configure_bounds,
};

// XDG Surface 处理函数
static void xdg_surface_handle_configure(void *data, struct xdg_surface *xdg_surface, uint32_t serial) {
    xdg_surface_ack_configure(xdg_surface, serial);
}

static const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_handle_configure,
};

// XDG WM Base 处理函数
static void xdg_wm_base_handle_ping(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial) {
    xdg_wm_base_pong(xdg_wm_base, serial);
}

static const struct xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_handle_ping,
};

// Wayland 注册表处理函数
static void registry_handle_global(void *data, struct wl_registry *registry, uint32_t name, const char *interface, uint32_t version) {
    if (strcmp(interface, "wl_compositor") == 0) {
        compositor = static_cast<struct wl_compositor*>(wl_registry_bind(registry, name, &wl_compositor_interface, 4));
    } else if (strcmp(interface, "xdg_wm_base") == 0) {
        xdg_wm_base = static_cast<struct xdg_wm_base*>(wl_registry_bind(registry, name, &xdg_wm_base_interface, 4));
    }
}

static void registry_handle_global_remove(void *data, struct wl_registry *registry, uint32_t name) {
    // 不需要处理
}

static const struct wl_registry_listener registry_listener = {
    .global = registry_handle_global,
    .global_remove = registry_handle_global_remove,
};



// 信号处理函数
static void signal_handler(int signum) {
    running = 0;
}

// 初始化 Wayland
static int init_wayland() {
    // 连接到 Wayland 显示服务器
    display = wl_display_connect(NULL);
    if (!display) {
        fprintf(stderr, "无法连接到 Wayland 显示服务器\n");
        return -1;
    }

    // 获取注册表
    registry = wl_display_get_registry(display);
    if (!registry) {
        fprintf(stderr, "无法获取 Wayland 注册表\n");
        return -1;
    }

    // 注册注册表监听器
    wl_registry_add_listener(registry, &registry_listener, NULL);

    // 轮询事件以获取全局对象
    wl_display_roundtrip(display);

    if (!compositor) {
        fprintf(stderr, "未找到 wl_compositor\n");
        return -1;
    }

    if (!xdg_wm_base) {
        fprintf(stderr, "未找到 xdg_wm_base\n");
        return -1;
    }

    // 创建表面
    surface = wl_compositor_create_surface(compositor);
    if (!surface) {
        fprintf(stderr, "无法创建 Wayland 表面\n");
        return -1;
    }

    // 创建 XDG 表面
    xdg_surface = xdg_wm_base_get_xdg_surface(xdg_wm_base, surface);
    if (!xdg_surface) {
        fprintf(stderr, "无法创建 XDG 表面\n");
        return -1;
    }

    // 创建 XDG 顶级表面
    xdg_toplevel = xdg_surface_get_toplevel(xdg_surface);
    if (!xdg_toplevel) {
        fprintf(stderr, "无法创建 XDG 顶级表面\n");
        return -1;
    }

    // 设置窗口标题
    xdg_toplevel_set_title(xdg_toplevel, "Wayland EGL OpenGL Example");

    // 设置窗口大小提示
    xdg_toplevel_set_min_size(xdg_toplevel, window_width, window_height);
    xdg_toplevel_set_max_size(xdg_toplevel, window_width * 2, window_height * 2);

    // 注册监听器
    xdg_wm_base_add_listener(xdg_wm_base, &xdg_wm_base_listener, NULL);
    xdg_surface_add_listener(xdg_surface, &xdg_surface_listener, NULL);
    xdg_toplevel_add_listener(xdg_toplevel, &xdg_toplevel_listener, NULL);

    // 提交表面
    wl_surface_commit(surface);

    return 0;
}

// 简单的着色器代码
const char* vertex_shader_code = "\n"
    "attribute vec4 vPosition;\n"
    "attribute vec4 vColor;\n"
    "varying vec4 fColor;\n"
    "uniform float uRotation;\n"
    "void main() {\n"
    "    float cosA = cos(uRotation);\n"
    "    float sinA = sin(uRotation);\n"
    "    mat4 rotation = mat4(\n"
    "        cosA, -sinA, 0.0, 0.0,\n"
    "        sinA, cosA, 0.0, 0.0,\n"
    "        0.0, 0.0, 1.0, 0.0,\n"
    "        0.0, 0.0, 0.0, 1.0\n"
    "    );\n"
    "    gl_Position = rotation * vPosition;\n"
    "    fColor = vColor;\n"
    "}\n";

const char* fragment_shader_code = "\n"
    "precision mediump float;\n"
    "varying vec4 fColor;\n"
    "void main() {\n"
    "    gl_FragColor = fColor;\n"
    "}\n";

// 全局变量用于着色器程序和缓冲区
static GLuint program = 0;
static GLuint vbo[2] = {0}; // vbo[0] = positions, vbo[1] = colors
static GLuint vPosition = 0;
static GLuint vColor = 0;
static GLuint uRotation = 0;

// 创建并编译着色器
static GLuint create_shader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0) {
            char* infoLog = (char*)malloc(infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            fprintf(stderr, "着色器编译错误: %s\n", infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}

// 创建着色器程序
static GLuint create_program(const char* vertex_code, const char* fragment_code) {
    GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_code);
    if (vertex_shader == 0) return 0;
    
    GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_code);
    if (fragment_shader == 0) {
        glDeleteShader(vertex_shader);
        return 0;
    }
    
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0) {
            char* infoLog = (char*)malloc(infoLen);
            glGetProgramInfoLog(program, infoLen, NULL, infoLog);
            fprintf(stderr, "着色器程序链接错误: %s\n", infoLog);
            free(infoLog);
        }
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        glDeleteProgram(program);
        return 0;
    }
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    return program;
}

// 初始化顶点数据
static void init_vertex_data() {
    // 三角形顶点位置
    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f, 1.0f, // 顶部
       -0.5f, -0.5f, 0.0f, 1.0f, // 左下角
        0.5f, -0.5f, 0.0f, 1.0f  // 右下角
    };
    
    // 三角形顶点颜色
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f, // 红色
        0.0f, 1.0f, 0.0f, 1.0f, // 绿色
        0.0f, 0.0f, 1.0f, 1.0f  // 蓝色
    };
    
    // 创建顶点缓冲对象
    glGenBuffers(2, vbo);
    
    // 绑定位置缓冲
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 绑定颜色缓冲
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    
    // 获取着色器属性和uniform位置
    vPosition = glGetAttribLocation(program, "vPosition");
    vColor = glGetAttribLocation(program, "vColor");
    uRotation = glGetUniformLocation(program, "uRotation");
}

// 初始化 EGL
static int init_egl() {
    EGLint major, minor;
    EGLint count;
    // 配置EGL，使用OpenGL ES
    EGLint config_attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_NONE
    };
    // 使用OpenGL ES 3.0版本的上下文配置
    EGLint context_attribs[] = {
        EGL_CONTEXT_MAJOR_VERSION, 3,
        EGL_CONTEXT_MINOR_VERSION, 0,
        EGL_NONE
    };

    // 获取 EGL 显示
    egl_display = eglGetDisplay((EGLNativeDisplayType)display);
    if (egl_display == EGL_NO_DISPLAY) {
        fprintf(stderr, "无法获取 EGL 显示\n");
        return -1;
    }

    // 初始化 EGL
    if (!eglInitialize(egl_display, &major, &minor)) {
        fprintf(stderr, "无法初始化 EGL\n");
        return -1;
    }

    printf("EGL 版本: %d.%d\n", major, minor);

    // 选择 EGL 配置
    if (!eglChooseConfig(egl_display, config_attribs, &egl_config, 1, &count) || count == 0) {
        fprintf(stderr, "无法选择 EGL 配置\n");
        return -1;
    }

    // 创建 EGL 上下文
    egl_context = eglCreateContext(egl_display, egl_config, EGL_NO_CONTEXT, context_attribs);
    if (egl_context == EGL_NO_CONTEXT) {
        fprintf(stderr, "无法创建 EGL 上下文\n");
        return -1;
    }

    // 创建 EGL 窗口
    egl_window = wl_egl_window_create(surface, window_width, window_height);
    if (!egl_window) {
        fprintf(stderr, "无法创建 EGL 窗口\n");
        return -1;
    }

    // 创建 EGL 表面
    egl_surface = eglCreateWindowSurface(egl_display, egl_config, (EGLNativeWindowType)egl_window, NULL);
    if (egl_surface == EGL_NO_SURFACE) {
        fprintf(stderr, "无法创建 EGL 表面\n");
        return -1;
    }

    // 绑定 EGL 上下文和表面
    if (!eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context)) {
        fprintf(stderr, "无法绑定 EGL 上下文和表面\n");
        return -1;
    }

    // 设置视口
    glViewport(0, 0, window_width, window_height);

    // OpenGL ES 3.2使用现代管线，不需要设置传统矩阵
    // 直接使用默认状态即可
    
    // 检查OpenGL版本
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    
    printf("OpenGL 版本: %s\n", version);
    printf("OpenGL 渲染器: %s\n", renderer);
    printf("OpenGL 供应商: %s\n", vendor);
    
    // 创建着色器程序
    program = create_program(vertex_shader_code, fragment_shader_code);
    if (program == 0) {
        fprintf(stderr, "无法创建着色器程序\n");
        return -1;
    }
    
    // 初始化顶点数据
    init_vertex_data();
    
    // 启用深度测试
    glEnable(GL_DEPTH_TEST);
    
    return 0;
}

// 绘制函数 - 使用OpenGL ES兼容的方式
static void draw() {
    static float rotation = 0.0f;
    
    // 清除颜色和深度缓冲区
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 使用着色器程序
    glUseProgram(program);
    
    // 设置旋转角度uniform
    glUniform1f(uRotation, rotation * 3.14159f / 180.0f);
    
    // 启用顶点属性
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);
    
    // 绘制位置
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
    // 绘制颜色
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
    // 绘制三角形
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // 禁用顶点属性
    glDisableVertexAttribArray(vPosition);
    glDisableVertexAttribArray(vColor);
    
    // 交换缓冲区显示绘制内容
    eglSwapBuffers(egl_display, egl_surface);
    
    // 更新旋转角度
    rotation += 1.0f;
    if (rotation >= 360.0f) {
        rotation = 0.0f;
    }
}

// 清理资源
static void cleanup() {
    // 清理OpenGL资源
    if (vbo[0] != 0) {
        glDeleteBuffers(2, vbo);
    }
    if (program != 0) {
        glDeleteProgram(program);
    }
    
    // 销毁 EGL 表面和上下文
    if (egl_surface != EGL_NO_SURFACE) {
        eglDestroySurface(egl_display, egl_surface);
    }
    if (egl_context != EGL_NO_CONTEXT) {
        eglDestroyContext(egl_display, egl_context);
    }
    if (egl_display != EGL_NO_DISPLAY) {
        eglTerminate(egl_display);
    }
    
    // 销毁 EGL 窗口
    if (egl_window != NULL) {
        wl_egl_window_destroy(egl_window);
    }
    
    // 销毁 Wayland 资源
    if (xdg_toplevel != NULL) {
        // XDG toplevel 没有显式的销毁函数，会在 surface 销毁时自动清理
    }
    if (xdg_surface != NULL) {
        // XDG surface 没有显式的销毁函数，会在 surface 销毁时自动清理
    }
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
}

// 主函数
int main(int argc, char **argv) {
    // 设置信号处理
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    printf("启动 Wayland EGL OpenGL 示例应用\n");
    
    // 初始化 Wayland
    if (init_wayland() != 0) {
        fprintf(stderr, "Wayland 初始化失败\n");
        cleanup();
        return EXIT_FAILURE;
    }
    
    // 提交表面以应用初始配置
    wl_surface_commit(surface);
    
    // 初始化 EGL
    if (init_egl() != 0) {
        fprintf(stderr, "EGL 初始化失败\n");
        cleanup();
        return EXIT_FAILURE;
    }
    
    printf("应用初始化成功，窗口大小: %dx%d\n", window_width, window_height);
    printf("按 Ctrl+C 退出应用\n");
    
    // 主循环
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
        
        // 短暂休眠以控制帧率
        struct timespec ts = {0, 16666666}; // 约60fps
        nanosleep(&ts, NULL);
    }
    
    printf("退出应用...\n");
    
    // 清理资源
    cleanup();
    
    return EXIT_SUCCESS;
}