// main.cpp
// Week 1: Getting Started with OpenGL

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// 窗口尺寸
const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

// 主函数
int main()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;

    // 初始化GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 设置GLFW窗口属性
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 使用核心模式
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // 窗口不可调整大小

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 苹果系统需要的额外设置
#endif

    // 创建GLFW窗口对象
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL - Week 1", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 设置glewExperimental为true，确保现代化的OpenGL功能正常工作
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // 设置视口尺寸
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // 游戏循环
    while (!glfwWindowShouldClose(window))
    {
        // 检查事件
        glfwPollEvents();

        // 清除颜色缓冲
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 交换缓冲
        glfwSwapBuffers(window);
    }

    // 清理GLFW资源
    glfwTerminate();
    return 0;
}
