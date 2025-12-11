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

// 创建一个简单的2x2纹理数据
unsigned char textureData[] = {
    255, 0, 0, 255,   0, 255, 0, 255,   // 第一行：红色，绿色
    0, 0, 255, 255,   255, 255, 0, 255    // 第二行：蓝色，黄色
};

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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Example 10: Texture", NULL, NULL);
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
    
    // 顶点数据：矩形，包含位置和纹理坐标
    float vertices[] = {
        // 位置              // 纹理坐标
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // 右上角
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // 右下角
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // 左下角
       -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // 左上角
    };
    
    // 索引数据：使用6个索引绘制两个三角形
    unsigned int indices[] = {
        0, 1, 3,  // 第一个三角形
        1, 2, 3   // 第二个三角形
    };
    
    // 创建顶点缓冲对象(VBO)
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    // 创建元素缓冲对象(EBO)
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    
    // 创建顶点数组对象(VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    
    // 绑定VAO
    glBindVertexArray(VAO);
    
    // 将VBO绑定到GL_ARRAY_BUFFER目标
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // 将顶点数据复制到VBO中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 将EBO绑定到GL_ELEMENT_ARRAY_BUFFER目标
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    // 将索引数据复制到EBO中
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // 设置顶点属性指针：位置属性（位置0）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 设置顶点属性指针：纹理坐标属性（位置1）
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // 解绑VBO（VAO仍然绑定着EBO）
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    // 创建纹理对象
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // 设置纹理过滤参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // 创建纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // 顶点着色器源代码
    const char* vertexShaderSource = "#version 330 core\n" 
    "layout (location = 0) in vec3 aPos;\n" 
    "layout (location = 1) in vec2 aTexCoord;\n" 
    "out vec2 TexCoord;\n" 
    "void main()\n" 
    "{\n" 
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" 
    "   TexCoord = aTexCoord;\n" 
    "}\0";
    
    // 片段着色器源代码
    const char* fragmentShaderSource = "#version 330 core\n" 
    "out vec4 FragColor;\n" 
    "in vec2 TexCoord;\n" 
    "uniform sampler2D ourTexture;\n" 
    "void main()\n" 
    "{\n" 
    "   FragColor = texture(ourTexture, TexCoord);\n" 
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
        
        // 绑定纹理
        glBindTexture(GL_TEXTURE_2D, texture);
        
        // 使用着色器程序
        glUseProgram(shaderProgram);
        
        // 绑定VAO
        glBindVertexArray(VAO);
        
        // 使用EBO绘制矩形
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        // 交换颜色缓冲
        glfwSwapBuffers(window);
        // 检查并调用事件
        glfwPollEvents();
    }
    
    // 清理资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glDeleteTextures(1, &texture);
    
    // 终止GLFW
    glfwTerminate();
    return 0;
}