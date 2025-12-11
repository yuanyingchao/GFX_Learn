# OpenGL 基础示例集合

这是一个为初学者准备的OpenGL基础示例集合，包含10个从简单到复杂的OpenGL程序，涵盖了OpenGL的核心概念和基本功能。

## 环境要求

- C++ 编译器 (GCC/Clang)
- OpenGL 3.3+ 
- GLFW 库 (用于窗口创建和输入处理)
- GLEW 或 GLAD (用于OpenGL函数加载)

## 安装依赖

### Ubuntu/Debian
```bash
sudo apt-get install -y libglfw3-dev libglew-dev
```

## 编译和运行

### 使用Makefile编译

```bash
make all      # 编译所有示例
make clean    # 清理编译结果
make example01 # 编译单个示例
```

### 运行单个示例

```bash
./example01
```

### 运行所有示例（每个示例显示1秒）

```bash
make run_all
```

## 示例列表

### 1. 基本窗口创建和颜色清除
- **文件**: `example01_window.cpp`
- **功能**: 创建OpenGL窗口，设置背景颜色并清除窗口
- **核心概念**: 窗口创建、OpenGL上下文初始化、颜色清除

### 2. 绘制一个简单的点
- **文件**: `example02_point.cpp`
- **功能**: 在窗口中心绘制一个点
- **核心概念**: 顶点数据、基本图元绘制(POINTS)

### 3. 绘制一条直线
- **文件**: `example03_line.cpp`
- **功能**: 绘制一条从窗口左上角到右下角的直线
- **核心概念**: 多点绘制、基本图元绘制(LINES)

### 4. 绘制一个三角形
- **文件**: `example04_triangle.cpp`
- **功能**: 绘制一个白色三角形
- **核心概念**: 三角形绘制、基本图元绘制(TRIANGLES)

### 5. 彩色三角形
- **文件**: `example05_color_triangle.cpp`
- **功能**: 绘制一个彩色三角形，每个顶点有不同颜色
- **核心概念**: 颜色属性、颜色插值

### 6. 使用VBO绘制多个三角形
- **文件**: `example06_vbo.cpp`
- **功能**: 使用顶点缓冲对象(VBO)绘制多个三角形
- **核心概念**: 顶点缓冲对象(VBO)、批量绘制

### 7. 使用VAO管理顶点数据
- **文件**: `example07_vao.cpp`
- **功能**: 使用顶点数组对象(VAO)管理顶点数据和属性
- **核心概念**: 顶点数组对象(VAO)、属性指针

### 8. 使用EBO绘制矩形
- **文件**: `example08_ebo.cpp`
- **功能**: 使用索引缓冲对象(EBO)绘制一个矩形
- **核心概念**: 索引缓冲对象(EBO)、减少重复顶点数据

### 9. 基本着色器程序
- **文件**: `example09_shaders.cpp`
- **功能**: 使用自定义着色器程序绘制彩色三角形
- **核心概念**: 着色器程序、顶点着色器、片段着色器

### 10. 纹理映射基础
- **文件**: `example10_texture.cpp`
- **功能**: 加载并显示一个纹理图片
- **核心概念**: 纹理加载、纹理坐标、纹理采样

## 学习建议

1. 从第一个示例开始，逐步理解每个概念
2. 尝试修改代码中的参数，观察结果变化
3. 阅读代码中的注释，理解每个函数的作用
4. 参考OpenGL官方文档，深入学习相关概念

## 参考资料

- [OpenGL 官方文档](https://www.opengl.org/documentation/)
- [Learn OpenGL](https://learnopengl.com/)
- [GLFW 文档](https://www.glfw.org/documentation.html)
- [GLEW 文档](http://glew.sourceforge.net/)
# OpenGL 基础示例集合

这个目录包含了一系列的OpenGL基础示例程序，用于学习和理解OpenGL的核心概念和编程技术。

## 环境要求

- Linux 操作系统
- g++ 编译器
- GLFW 库
- GLEW 库
- OpenGL 3.3 或更高版本

## 安装依赖

在 Ubuntu/Debian 系统上，可以使用以下命令安装依赖：

```bash
sudo apt-get update
sudo apt-get install build-essential libglfw3-dev libglew-dev
```

## 编译和运行

### 编译所有示例

```bash
make
```

### 运行特定示例

```bash
./example01_window
```

### 清理编译产物

```bash
make clean
```

## 示例列表

1. **example01_window** - 创建一个OpenGL窗口
2. **example02_point** - 绘制一个点
3. **example03_line** - 绘制一条线
4. **example04_triangle** - 绘制一个三角形
5. **example05_color_triangle** - 绘制一个彩色三角形
6. **example06_vbo** - 使用VBO绘制多个三角形
7. **example07_vao** - 使用多个VAO
8. **example08_ebo** - 使用EBO绘制矩形
9. **example09_shaders** - 使用uniform变量的着色器
10. **example10_texture** - 使用纹理

## 学习资源

- [OpenGL 官方文档](https://www.opengl.org/documentation/)
- [Learn OpenGL](https://learnopengl.com/)
- [GLFW 官方文档](https://www.glfw.org/documentation.html)
- [GLEW 官方文档](http://glew.sourceforge.net/)

## 注意事项

- 这些示例使用OpenGL 3.3核心模式
- 示例代码中包含详细的注释，帮助理解各个部分的功能
- 每个示例都专注于演示一个特定的OpenGL概念