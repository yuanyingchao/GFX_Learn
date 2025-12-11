# OpenGL 学习计划（初学者版）

## 一、学习目标
通过系统学习 OpenGL，掌握现代图形编程的基础知识和技能，能够独立开发简单的 3D 图形应用程序。

## 二、学习路径概述

| 阶段 | 主题 | 预计时间 |
|------|------|----------|
| 1 | OpenGL 基础概念与环境搭建 | 1-2 周 |
| 2 | 图形渲染流水线与基础图元 | 2-3 周 |
| 3 | 着色器编程与纹理映射 | 2-3 周 |
| 4 | 3D 变换与相机控制 | 2-3 周 |
| 5 | 光照与材质系统 | 2-3 周 |
| 6 | 高级主题与项目实践 | 4-6 周 |

## 三、详细学习计划

### 阶段 1：OpenGL 基础概念与环境搭建（1-2 周）

#### 学习内容
1. **图形编程基础概念**
   - 计算机图形学概述
   - OpenGL 是什么？它的历史和发展
   - 现代 OpenGL vs 传统 OpenGL
   - 渲染管线概述

2. **开发环境搭建**
   - C/C++ 基础复习
   - 安装开发工具（VSCode/GCC/CMake）
   - 配置 OpenGL 依赖（GLFW/GLEW/GLAD）
   - 第一个 OpenGL 程序：创建窗口

3. **基础窗口管理**
   - 窗口创建与配置
   - 输入处理（键盘、鼠标）
   - 渲染循环原理
   - 视口设置

#### 实践练习
- 运行并分析本地示例：`example01_window` - 窗口创建
- 添加窗口大小调整功能
- 实现基本的键盘输入处理

#### 推荐资源
- [Learn OpenGL](https://learnopengl.com/) - 入门首选
- [OpenGL 编程指南（红宝书）](https://www.pearson.com/store/p/opengl-programming-guide/P100001405006/9780134495491) - 经典教材
- 本地示例：`/home/sean/Code/GFX_Learn/opengl_basics/example01_window.cpp`

### 阶段 2：图形渲染流水线与基础图元（2-3 周）

#### 学习内容
1. **渲染流水线详解**
   - 顶点输入阶段
   - 顶点着色器
   - 图元装配
   - 几何着色器
   - 光栅化
   - 片段着色器
   - 测试与混合

2. **顶点数据管理**
   - VBO（顶点缓冲对象）
   - VAO（顶点数组对象）
   - EBO/IBO（索引缓冲对象）
   - 数据布局与属性配置

3. **基础图元绘制**
   - 点、线、三角形
   - 绘制模式与参数
   - 基本形状构建（矩形、三角形带等）

#### 实践练习
- 运行并分析本地示例：`example02_point` - 点绘制
- 运行并分析本地示例：`example03_line` - 线绘制
- 运行并分析本地示例：`example04_triangle` - 三角形绘制
- 运行并分析本地示例：`example06_vbo` - VBO使用
- 运行并分析本地示例：`example07_vao` - VAO使用
- 运行并分析本地示例：`example08_ebo` - EBO使用

#### 推荐资源
- [Learn OpenGL - 渲染流水线](https://learnopengl.com/Getting-started/Rendering-Pipeline)
- [OpenGL 编程指南 - 第 2 章 基本图元](https://www.pearson.com/store/p/opengl-programming-guide/P100001405006/9780134495491)
- 本地示例：`/home/sean/Code/GFX_Learn/opengl_basics/example02_point.cpp` 到 `example08_ebo.cpp`

### 阶段 3：着色器编程与纹理映射（2-3 周）

#### 学习内容
1. **GLSL 着色器语言**
   - 语言基础与语法
   - 数据类型与变量
   - 函数与控制流
   - 输入输出变量

2. **顶点着色器**
   - 顶点变换
   - 传递数据到片段着色器

3. **片段着色器**
   - 颜色计算
   - 渐变效果
   - 基本光照模型

4. **纹理映射**
   - 纹理坐标系统
   - 纹理加载与绑定
   - 纹理采样与过滤
   - 多纹理应用

#### 实践练习
- 运行并分析本地示例：`example05_color_triangle` - 彩色三角形
- 运行并分析本地示例：`example09_shaders` - 着色器编程
- 运行并分析本地示例：`example10_texture` - 纹理映射
- 修改着色器实现不同的颜色效果
- 尝试加载不同的纹理图片

#### 推荐资源
- [Learn OpenGL - 着色器](https://learnopengl.com/Getting-started/Shaders)
- [Learn OpenGL - 纹理](https://learnopengl.com/Getting-started/Textures)
- 本地示例：`/home/sean/Code/GFX_Learn/opengl_basics/example05_color_triangle.cpp`, `example09_shaders.cpp`, `example10_texture.cpp`

### 阶段 4：3D 变换与相机控制（2-3 周）

#### 学习内容
1. **坐标系统**
   - 局部空间
   - 世界空间
   - 观察空间
   - 裁剪空间
   - 屏幕空间

2. **矩阵变换**
   - 模型矩阵（Model Matrix）
   - 视图矩阵（View Matrix）
   - 投影矩阵（Projection Matrix）
   - 矩阵乘法顺序

3. **相机控制**
   - 欧拉角与万向锁
   - 自由相机实现
   - 轨道相机实现
   - 键盘和鼠标控制

#### 实践练习
- 实现 3D 变换（平移、旋转、缩放）
- 创建透视投影和正交投影
- 实现第一人称和第三人称相机

#### 推荐资源
- [Learn OpenGL - 变换](https://learnopengl.com/Getting-started/Transformations)
- [Learn OpenGL - 坐标系统](https://learnopengl.com/Getting-started/Coordinate-Systems)

### 阶段 5：光照与材质系统（2-3 周）

#### 学习内容
1. **基础光照模型**
   - 环境光（Ambient Light）
   - 漫反射光（Diffuse Light）
   - 镜面反射光（Specular Light）
   - Phong 光照模型

2. **材质与光照贴图**
   - 材质属性
   - 漫反射贴图（Diffuse Map）
   - 高光贴图（Specular Map）
   - 法线贴图（Normal Map）

3. **高级光照技术**
   - 方向光（Directional Light）
   - 点光源（Point Light）
   - 聚光灯（Spotlight）
   - 多光源系统

#### 实践练习
- 实现 Phong 光照模型
- 应用各种光照贴图
- 创建多光源场景

#### 推荐资源
- [Learn OpenGL - 光照](https://learnopengl.com/Lighting/Basic-Lighting)
- [Learn OpenGL - 材质](https://learnopengl.com/Lighting/Materials)

### 阶段 6：高级主题与项目实践（4-6 周）

#### 学习内容
1. **高级渲染技术**
   - 深度测试与遮挡剔除
   - 混合与透明度
   - 抗锯齿
   - 阴影映射（Shadow Mapping）

2. **模型加载**
   - 3D 模型文件格式（OBJ、FBX 等）
   - 使用 Assimp 库加载模型
   - 骨骼动画基础

3. **粒子系统**
   - 粒子系统原理
   - GPU 加速粒子
   - 效果实现（火焰、烟雾、爆炸等）

4. **项目实践**
   - 选择一个感兴趣的项目（如简单游戏、3D 编辑器等）
   - 应用所学知识实现项目
   - 优化与调试

#### 实践练习
- 实现阴影映射
- 加载并渲染复杂 3D 模型
- 创建粒子效果系统
- 完成一个完整的项目

#### 推荐资源
- [Learn OpenGL - 高级光照](https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping)
- [Learn OpenGL - 模型加载](https://learnopengl.com/Model-Loading/Model)

## 四、学习建议

1. **理论与实践结合**：每学习一个概念，都要编写代码实践验证
2. **循序渐进**：不要急于学习高级主题，打好基础很重要
3. **阅读优秀代码**：学习别人的实现方式，理解不同的编程思路
4. **参与社区**：加入 OpenGL 相关的论坛和社区，遇到问题及时求助
5. **项目驱动学习**：通过实际项目巩固所学知识

## 五、常用工具与库

1. **开发环境**：VSCode、CLion、Visual Studio
2. **构建工具**：CMake、Make
3. **OpenGL 上下文**：GLFW、SDL
4. **OpenGL 扩展**：GLEW、GLAD
5. **数学库**：GLM
6. **图像加载**：stb_image
7. **模型加载**：Assimp

## 六、学习资源汇总

1. **网站教程**
   - Learn OpenGL: https://learnopengl.com/
   - OpenGL Tutorial: http://www.opengl-tutorial.org/
   - Arcane Engine Tutorials: https://arcaneframework.com/

2. **视频教程**
   - The Cherno: https://www.youtube.com/c/TheChernoProject
   - ThinMatrix: https://www.youtube.com/user/ThinMatrix

3. **书籍**
   - 《OpenGL 编程指南》（红宝书）
   - 《OpenGL 超级宝典》
   - 《Real-Time Rendering》（实时渲染，进阶阅读）

4. **文档**
   - OpenGL 官方文档: https://www.opengl.org/documentation/
   - GLFW 文档: https://www.glfw.org/documentation.html
   - GLM 文档: https://glm.g-truc.net/0.9.9/index.html

## 七、项目创意

1. **2D 游戏引擎**：实现简单的 2D 游戏渲染引擎
2. **3D 模型查看器**：支持加载和查看各种 3D 模型
3. **简单游戏**：如 Minecraft 克隆、赛车游戏等
4. **可视化工具**：数据可视化、粒子效果演示
5. **实时渲染器**：实现高级渲染效果的演示程序

---

**学习提示**：OpenGL 学习需要耐心和实践，遇到困难不要放弃。坚持按照计划学习，多写代码，多做项目，你会逐步掌握这项强大的图形编程技术！
