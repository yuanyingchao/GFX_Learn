#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>

// 窗口尺寸
const int WIDTH = 800;
const int HEIGHT = 600;

// 粒子数量
const int MAX_PARTICLES = 1000;

// 粒子结构体
struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 color;
    float life;
    float size;
};

// 着色器程序ID
GLuint shaderProgram;

// VAO和VBO
GLuint VAO, VBO;

// 粒子数组
std::vector<Particle> particles;

// 随机数生成器
std::mt19937 gen; // 随机数生成器
std::uniform_real_distribution<float> rand_float(-1.0f, 1.0f);
std::uniform_real_distribution<float> rand_color(0.0f, 1.0f);

// 函数声明
std::string readShaderFile(const char* filePath);
GLuint compileShader(GLenum type, const char* source);
GLuint createShaderProgram(const char* vertexPath, const char* fragmentPath);
void setupBuffers();
void updateParticles(float deltaTime);
void render();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// 读取着色器文件
std::string readShaderFile(const char* filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// 编译着色器
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
        return 0;
    }
    return shader;
}

// 创建着色器程序
GLuint createShaderProgram(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode = readShaderFile(vertexPath);
    std::string fragmentCode = readShaderFile(fragmentPath);
    
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
    
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Program linking failed: " << infoLog << std::endl;
        return 0;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return program;
}

// 初始化粒子
void initParticle(Particle& particle) {
    particle.position = glm::vec3(0.0f, 0.0f, 0.0f);
    particle.velocity = glm::vec3(rand_float(gen) * 0.5f, rand_float(gen) * 0.5f + 1.0f, rand_float(gen) * 0.5f);
    particle.color = glm::vec3(rand_color(gen), rand_color(gen), rand_color(gen));
    particle.life = 1.0f;
    particle.size = 0.02f + rand_float(gen) * 0.03f;
}

// 初始化所有粒子
void initParticles() {
    particles.resize(MAX_PARTICLES);
    for (auto& particle : particles) {
        initParticle(particle);
    }
}

// 设置缓冲区
void setupBuffers() {
    // 创建VAO和VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    // 粒子位置、颜色和大小数据
    struct ParticleData {
        glm::vec3 position;
        glm::vec3 color;
        float size;
    };
    
    // 分配VBO内存（但不填充数据，因为粒子数据会动态更新）
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleData) * MAX_PARTICLES, NULL, GL_DYNAMIC_DRAW);
    
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (void*)offsetof(ParticleData, color));
    glEnableVertexAttribArray(1);
    
    // 大小属性
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (void*)offsetof(ParticleData, size));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// 更新粒子
void updateParticles(float deltaTime) {
    for (auto& particle : particles) {
        // 更新生命值
        particle.life -= deltaTime * 0.5f;
        
        // 如果粒子死亡，重新初始化
        if (particle.life <= 0.0f) {
            initParticle(particle);
        } else {
            // 更新位置
            particle.position += particle.velocity * deltaTime;
            
            // 应用重力
            particle.velocity.y -= 9.8f * deltaTime;
        }
    }
}

// 渲染
void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 使用着色器程序
    glUseProgram(shaderProgram);
    
    // 设置视图矩阵
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    
    // 设置投影矩阵
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    
    // 更新VBO数据
    struct ParticleData {
        glm::vec3 position;
        glm::vec3 color;
        float size;
    };
    
    std::vector<ParticleData> particleData(MAX_PARTICLES);
    for (int i = 0; i < MAX_PARTICLES; ++i) {
        particleData[i].position = particles[i].position;
        particleData[i].color = particles[i].color;
        particleData[i].size = particles[i].size;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(ParticleData) * MAX_PARTICLES, particleData.data());
    
    // 渲染粒子
    glBindVertexArray(VAO);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE); // 加法混合，用于粒子效果
    glDrawArrays(GL_POINTS, 0, MAX_PARTICLES);
    glDisable(GL_BLEND);
    glBindVertexArray(0);
}

// 窗口大小变化回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// 处理输入
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // 初始化GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // 设置GLFW窗口属性
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Particle System", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // 设置当前上下文
    glfwMakeContextCurrent(window);
    
    // 设置窗口大小变化回调
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // 初始化GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    // 创建着色器程序
    shaderProgram = createShaderProgram(
        "shaders/vertex.glsl",
        "shaders/fragment.glsl"
    );
    
    if (!shaderProgram) {
        std::cerr << "Failed to create shader program" << std::endl;
        return -1;
    }
    
    // 初始化粒子
    initParticles();
    
    // 设置缓冲区
    setupBuffers();
    
    // 启用深度测试
    glEnable(GL_DEPTH_TEST);
    
    // 记录上一帧时间
    float lastTime = glfwGetTime();
    
    // 主循环
    while (!glfwWindowShouldClose(window)) {
        // 计算 deltaTime
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        
        // 处理输入
        processInput(window);
        
        // 更新粒子
        updateParticles(deltaTime);
        
        // 渲染
        render();
        
        // 交换缓冲区
        glfwSwapBuffers(window);
        
        // 处理事件
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
