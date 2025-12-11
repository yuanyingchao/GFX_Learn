# Week 1: Getting Started with OpenGL

## 本周核心知识点

1. **OpenGL 概述**
   - 什么是OpenGL？
   - OpenGL 3.3+ Core Profile 与立即模式的区别
   - OpenGL的渲染管线简介

2. **环境搭建**
   - GLFW库的使用（创建窗口、上下文管理）
   - GLEW库的使用（加载OpenGL扩展）
   - CMake构建系统的配置

3. **窗口创建与上下文管理**
   - GLFW窗口的创建和属性设置
   - OpenGL上下文的初始化
   - 视口设置
   - 基本的游戏循环

4. **OpenGL错误处理**
   - 如何检测和处理OpenGL错误
   - 调试技巧

## 示例程序说明

### main.cpp

这是本周的示例程序，展示了如何使用GLFW和GLEW创建一个简单的OpenGL窗口。程序包含以下功能：

- 初始化GLFW和GLEW
- 创建800x600像素的窗口
- 设置OpenGL 3.3 Core Profile
- 实现基本的游戏循环
- 清除颜色缓冲并设置背景色

## 如何构建和运行

### 构建步骤

1. 创建构建目录：
   ```bash
   mkdir build
   cd build
   ```

2. 运行CMake：
   ```bash
   cmake ..
   ```

3. 编译程序：
   ```bash
   make
   ```

### 运行程序

```bash
./bin/week1
```

## 预期结果

运行程序后，你应该会看到一个800x600像素的窗口，背景色为深青色（RGB: 0.2, 0.3, 0.3）。窗口标题为"LearnOpenGL - Week 1"。

## 练习建议

1. **修改窗口属性**
   - 尝试修改窗口的尺寸
   - 尝试启用窗口的可调整大小功能
   - 修改窗口标题

2. **修改背景颜色**
   - 尝试使用不同的颜色作为背景
   - 尝试使用渐变背景（提示：需要使用着色器）

3. **添加事件处理**
   - 添加键盘事件处理，例如按ESC键关闭窗口
   - 添加鼠标事件处理

4. **扩展游戏循环**
   - 添加帧率限制
   - 添加delta时间计算

## 推荐资源

- [LearnOpenGL](https://learnopengl.com/) - 中文/英文教程
- [OpenGL官方文档](https://www.opengl.org/documentation/)
- [GLFW文档](https://www.glfw.org/docs/)
- [GLEW文档](http://glew.sourceforge.net/)

## 下周预告

第2周将学习**着色器编程**，包括：
- GLSL基础语法
- 顶点着色器和片段着色器
- 着色器程序的创建和使用
- 制服变量和属性变量
