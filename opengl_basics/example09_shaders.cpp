#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Example 09: Shaders with Uniform", NULL, NULL);
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
    
    // 顶点数据：三角形
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // 左下角
         0.5f, -0.5f, 0.0f,  // 右下角
         0.0f,  0.5f, 0.0f   // 顶部
    };
    
    // 创建顶点缓冲对象(VBO)
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    // 创建顶点数组对象(VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    
    // 绑定VAO
    glBindVertexArray(VAO);
    
    // 将VBO绑定到GL_ARRAY_BUFFER目标
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // 将顶点数据复制到VBO中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 设置顶点属性指针：位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 解绑VBO和VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    // 顶点着色器源代码（使用uniform变量控制位置）
    const char* vertexShaderSource = "#version 330 core\n" 
    "layout (location = 0) in vec3 aPos;\n" 
    "uniform float xOffset; // 用于控制三角形在X轴上的偏移量\n" 
    "void main()\n" 
    "{\n" 
    "   gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);\n" 
    "}\0";
    
    // 片段着色器源代码（使用uniform变量控制颜色）
    const char* fragmentShaderSource = "#version 330 core\n" 
    "uniform vec4 ourColor; // 用于控制三角形的颜色\n" 
    "out vec4 FragColor;\n" 
    "void main()\n" 
    "{\n" 
    "   FragColor = ourColor;\n" 
    "}\0";
    
    // 创建顶点着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // 创建片段着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    // 创建着色器程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // 删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 处理输入
        processInput(window);
        
        // 渲染指令
        // 设置清除颜色为蓝色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清除颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 使用着色器程序
        glUseProgram(shaderProgram);
        
        // 设置uniform变量：颜色（随时间变化）
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        
        // 设置uniform变量：X轴偏移量（随时间变化）
        float xOffset = (sin(timeValue * 0.5f) / 2.0f);
        int xOffsetLocation = glGetUniformLocation(shaderProgram, "xOffset");
        glUniform1f(xOffsetLocation, xOffset);
        
        // 绑定VAO
        glBindVertexArray(VAO);
        
        // 绘制三角形
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // 交换颜色缓冲
        glfwSwapBuffers(window);
        // 检查并调用事件
        glfwPollEvents();
    }
    
    // 清理资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
    // 终止GLFW
    glfwTerminate();
    return 0;
}