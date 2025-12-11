#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Example 07: Multiple VAOs", NULL, NULL);
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
    
    // 第一个三角形的顶点数据
    float vertices1[] = {
        -0.9f, -0.5f, 0.0f,  // 左下角
        -0.0f, -0.5f, 0.0f,  // 右下角
        -0.45f, 0.5f, 0.0f,  // 顶部
    };
    
    // 第二个三角形的顶点数据
    float vertices2[] = {
        0.0f, -0.5f, 0.0f,   // 左下角
        0.9f, -0.5f, 0.0f,   // 右下角
        0.45f, 0.5f, 0.0f,   // 顶部
    };
    
    // 创建两个VBO
    unsigned int VBOs[2];
    glGenBuffers(2, VBOs);
    
    // 创建两个VAO
    unsigned int VAOs[2];
    glGenVertexArrays(2, VAOs);
    
    // 设置第一个VAO
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 设置第二个VAO
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 解绑VAO和VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // 顶点着色器源代码
    const char* vertexShaderSource = "#version 330 core\n" 
    "layout (location = 0) in vec3 aPos;\n" 
    "void main()\n" 
    "{\n" 
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" 
    "}\0";
    
    // 片段着色器源代码
    const char* fragmentShaderSource1 = "#version 330 core\n" 
    "out vec4 FragColor;\n" 
    "void main()\n" 
    "{\n" 
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n" // 橙色
    "}\0";
    
    // 第二个片段着色器（不同颜色）
    const char* fragmentShaderSource2 = "#version 330 core\n" 
    "out vec4 FragColor;\n" 
    "void main()\n" 
    "{\n" 
    "   FragColor = vec4(0.2f, 0.5f, 1.0f, 1.0f); \n"  // 蓝色
    "}\0";
    
    // 创建两个着色器程序
    unsigned int shaderProgram1, shaderProgram2;
    
    // 第一个着色器程序
    shaderProgram1 = glCreateProgram();
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);
    
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
    
    // 第二个着色器程序
    shaderProgram2 = glCreateProgram();
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);
    
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    
    // 删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);
    
    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 处理输入
        processInput(window);
        
        // 渲染指令
        // 设置清除颜色为蓝色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清除颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 绘制第一个三角形
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // 绘制第二个三角形
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // 交换颜色缓冲
        glfwSwapBuffers(window);
        // 检查并调用事件
        glfwPollEvents();
    }
    
    // 清理资源
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram1);
    glDeleteProgram(shaderProgram2);
    
    // 终止GLFW
    glfwTerminate();
    return 0;
}