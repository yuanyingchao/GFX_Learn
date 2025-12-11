#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>

// 窗口大小
const int WIDTH = 800;
const int HEIGHT = 600;

// 回调函数：窗口大小改变时调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // 设置视口大小
    glViewport(0, 0, width, height);
}

// 回调函数：处理键盘输入
void processInput(GLFWwindow* window) {
    // 如果按下ESC键，关闭窗口
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // 初始化GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }
    
    // 设置GLFW的窗口提示：使用OpenGL 3.3核心模式
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // 创建窗口对象
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Example 01: Window", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // 将窗口的上下文设置为当前线程的上下文
    glfwMakeContextCurrent(window);
    
    // 设置窗口大小改变的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // 初始化GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // 设置视口大小
    glViewport(0, 0, WIDTH, HEIGHT);
    int i = 0;
    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 处理输入
        processInput(window);
        
        // 渲染指令
        // 设置清除颜色为蓝色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清除颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 交换颜色缓冲
        glfwSwapBuffers(window);
        // 检查并调用事件
        glfwPollEvents();

        i++;
        printf("=================loop=====================%d\n", i);
    }
    
    // 终止GLFW
    glfwTerminate();
    return 0;
}