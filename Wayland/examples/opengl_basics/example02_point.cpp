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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Example 02: Point", NULL, NULL);
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
    
    // 顶点数据：窗口中心的一个点
    float vertices[] = {
        0.0f, 0.0f, 0.0f  // 点的位置
    };
    
    // 创建顶点缓冲对象(VBO)
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    // 将VBO绑定到GL_ARRAY_BUFFER目标
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // 将顶点数据复制到VBO中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 创建顶点数组对象(VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    
    // 绑定VAO
    glBindVertexArray(VAO);
    
    // 设置顶点属性指针：位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 解绑VBO和VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    // 顶点着色器源代码
    const char* vertexShaderSource = "#version 330 core\n" 
    "layout (location = 0) in vec3 aPos;\n" 
    "void main()\n" 
    "{\n" 
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" 
    "   gl_PointSize = 10.0; // 设置点的大小\n" 
    "}\0";
    
    // 片段着色器源代码
    const char* fragmentShaderSource = "#version 330 core\n" 
    "out vec4 FragColor;\n" 
    "void main()\n" 
    "{\n" 
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // 橙色\n" 
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
        
        // 绑定VAO
        glBindVertexArray(VAO);
        
        // 绘制点
        glDrawArrays(GL_POINTS, 0, 1);
        
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