# 现代 OpenGL 学习计划（12周）

为初学者到中级开发者设计的系统、循序渐进的OpenGL学习路径，涵盖从环境搭建到高级渲染技术的完整内容。本计划强调现代OpenGL（3.3+ Core Profile），避免使用立即模式（glBegin/glEnd）。

## 目录

- [第1周：环境搭建与基础概念](#第1周环境搭建与基础概念)
- [第2周：渲染管线与着色器编程](#第2周渲染管线与着色器编程)
- [第3周：顶点数据管理](#第3周顶点数据管理)
- [第4周：纹理映射](#第4周纹理映射)
- [第5周：3D变换与相机控制](#第5周3d变换与相机控制)
- [第6周：光照模型](#第6周光照模型)
- [第7周：帧缓冲与后处理](#第7周帧缓冲与后处理)
- [第8周：阴影映射](#第8周阴影映射)
- [第9周：实例化与几何着色器](#第9周实例化与几何着色器)
- [第10周：PBR材质系统](#第10周pbr材质系统)
- [第11周：计算着色器基础](#第11周计算着色器基础)
- [第12周：综合项目与性能优化](#第12周综合项目与性能优化)
- [调试与性能分析工具](#调试与性能分析工具)
- [学习资源汇总](#学习资源汇总)

## 第1周：环境搭建与基础概念

### 核心知识点
- 计算机图形学概述
- OpenGL历史与版本发展
- 现代OpenGL vs 传统OpenGL
- 开发环境搭建（GLFW/SDL/GLEW/GLAD）
- 窗口创建与配置
- 渲染循环原理
- 视口设置
- 基本错误处理

### 推荐资源
- **书籍**：《OpenGL编程指南（红宝书）》第11章
- **教程**：[Learn OpenGL - Getting Started](https://learnopengl.com/Getting-started/OpenGL)
- **视频**：The Cherno - OpenGL系列第1-3集

### 实践项目
- 创建一个基本的OpenGL窗口应用程序
- 实现窗口大小调整功能
- 添加基本的键盘输入处理
- 绘制一个简单的三角形（使用固定管线作为过渡）

## 第2周：渲染管线与着色器编程

### 核心知识点
- 渲染管线详解（从顶点输入到片段输出）
- GLSL语言基础（语法、变量类型、函数）
- 顶点着色器与片段着色器结构
- 着色器编译与链接
- Uniform变量与属性(Attribute)变量
- 简单的颜色渐变效果

### 推荐资源
- **书籍**：《OpenGL编程指南（红宝书）》第3-4章
- **教程**：[Learn OpenGL - Shaders](https://learnopengl.com/Getting-started/Shaders)
- **视频**：ThinMatrix - OpenGL 3D Game Tutorials第1-3集

### 实践项目
- 编写第一个顶点和片段着色器
- 实现彩色三角形渐变效果
- 使用Uniform变量控制颜色
- 实现简单的2D图形渲染

## 第3周：顶点数据管理

### 核心知识点
- VAO（顶点数组对象）
- VBO（顶点缓冲对象）
- EBO/IBO（索引缓冲对象）
- 顶点数据布局与属性配置
- 数据类型与大小计算
- 批量绘制技术

### 推荐资源
- **书籍**：《OpenGL编程指南（红宝书）》第5章
- **教程**：[Learn OpenGL - Hello Triangle](https://learnopengl.com/Getting-started/Hello-Triangle)
- **文档**：[OpenGL Wiki - Vertex Specification](https://www.khronos.org/opengl/wiki/Vertex_Specification)

### 实践项目
- 使用VAO/VBO绘制多个三角形
- 使用EBO绘制四边形和复杂形状
- 实现一个简单的2D形状库

## 第4周：纹理映射

### 核心知识点
- 纹理坐标系统
- 纹理加载与图像格式
- 纹理过滤与环绕方式
- 多重纹理应用
- 纹理单元与采样器
- MIP映射

### 推荐资源
- **书籍**：《OpenGL编程指南（红宝书）》第6章
- **教程**：[Learn OpenGL - Textures](https://learnopengl.com/Getting-started/Textures)
- **库**：stb_image（用于图像加载）

### 实践项目
- 加载并应用纹理到3D对象
- 实现纹理混合效果
- 创建一个简单的纹理图集系统

## 第5周：3D变换与相机控制

### 核心知识点
- 坐标系统（局部、世界、观察、裁剪、屏幕）
- 矩阵变换（平移、旋转、缩放）
- 模型矩阵、视图矩阵、投影矩阵
- 矩阵乘法顺序
- 相机控制（欧拉角、自由相机）
- GLM数学库使用

### 推荐资源
- **书籍**：《OpenGL编程指南（红宝书）》第7章
- **教程**：[Learn OpenGL - Transformations](https://learnopengl.com/Getting-started/Transformations)
- **教程**：[Learn OpenGL - Coordinate Systems](https://learnopengl.com/Getting-started/Coordinate-Systems)

### 实践项目
- 实现3D变换演示程序
- 创建第一人称和第三人称相机
- 实现透视投影和正交投影切换

## 第6周：光照模型

### 核心知识点
- Phong光照模型
- 环境光、漫反射光、镜面反射光
- 材质系统
- 光照贴图（漫反射贴图、高光贴图）
- 多光源系统（方向光、点光源、聚光灯）

### 推荐资源
- **书籍**：《OpenGL编程指南（红宝书）》第8章
- **教程**：[Learn OpenGL - Basic Lighting](https://learnopengl.com/Lighting/Basic-Lighting)
- **教程**：[Learn OpenGL - Materials](https://learnopengl.com/Lighting/Materials)

### 实践项目
- 实现Phong光照模型
- 创建多光源场景
- 应用各种光照贴图

## 第7周：帧缓冲与后处理

### 核心知识点
- 帧缓冲（Framebuffer）创建与配置
- 渲染缓冲（Renderbuffer）
- 离屏渲染
- 后处理效果（模糊、灰度、边缘检测）
- 多重采样抗锯齿（MSAA）

### 推荐资源
- **书籍**：《OpenGL编程指南（红宝书）》第10章
- **教程**：[Learn OpenGL - Framebuffers](https://learnopengl.com/Advanced-OpenGL/Framebuffers)
- **教程**：[Learn OpenGL - Advanced Lighting](https://learnopengl.com/Advanced-Lighting/Bloom)

### 实践项目
- 实现基本的帧缓冲系统
- 创建后处理效果链
- 实现Bloom发光效果

## 第8周：阴影映射

### 核心知识点
- 阴影映射原理
- 深度贴图生成
- 阴影采样与PCF滤波
- 阴影 acne与peter panning问题解决
- 软阴影实现

### 推荐资源
- **书籍**：《OpenGL编程指南（红宝书）》第11章
- **教程**：[Learn OpenGL - Shadow Mapping](https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping)
- **视频**：Games202 - 实时渲染入门第8讲

### 实践项目
- 实现基本的阴影映射
- 解决阴影映射的常见问题
- 添加软阴影效果

## 第9周：实例化与几何着色器

### 核心知识点
- 实例化渲染原理
- glDrawArraysInstanced/glDrawElementsInstanced
- 实例化数组
- 几何着色器基础
- 点精灵、线扩展
- GPU生成几何数据

### 推荐资源
- **书籍**：《OpenGL编程指南（红宝书）》第12章
- **教程**：[Learn OpenGL - Instancing](https://learnopengl.com/Advanced-OpenGL/Instancing)
- **教程**：[Learn OpenGL - Geometry Shader](https://learnopengl.com/Advanced-OpenGL/Geometry-Shader)

### 实践项目
- 使用实例化渲染大量对象
- 实现粒子系统
- 使用几何着色器生成复杂形状

## 第10周：PBR材质系统

### 核心知识点
- 基于物理的渲染（PBR）原理
- 金属度/粗糙度工作流
- 环境贴图与IBL（Image-Based Lighting）
- HDR环境映射
- BRDF（双向反射分布函数）

### 推荐资源
- **教程**：[Learn OpenGL - PBR](https://learnopengl.com/PBR/Theory)
- **论文**：Physically Based Rendering in Filament
- **视频**：Games202 - 实时渲染入门第10讲

### 实践项目
- 实现基础PBR材质系统
- 创建HDR环境映射
- 实现IBL（基于图像的光照）

## 第11周：计算着色器基础

### 核心知识点
- 计算着色器概念与用途
- 工作组与局部尺寸
- 共享内存与同步
- 计算着色器与图形管线交互
- 简单的GPGPU应用

### 推荐资源
- **书籍**：《OpenGL编程指南（红宝书）》第13章
- **教程**：[Learn OpenGL - Compute Shader](https://learnopengl.com/Advanced-OpenGL/Compute-Shader)
- **文档**：[OpenGL Wiki - Compute Shader](https://www.khronos.org/opengl/wiki/Compute_Shader)

### 实践项目
- 实现一个简单的计算着色器
- 使用计算着色器加速粒子系统
- 实现GPU上的图像处理

## 第12周：综合项目与性能优化

### 核心知识点
- OpenGL性能分析方法
- 常见性能瓶颈与优化技巧
- 渲染管线优化
- 资源管理与内存优化
- 多线程渲染基础

### 推荐资源
- **书籍**：《OpenGL编程指南（红宝书）》第14章
- **教程**：[Learn OpenGL - Advanced Lighting](https://learnopengl.com/Advanced-OpenGL/Anti-Aliasing)
- **文档**：[OpenGL Performance Tips](https://www.khronos.org/opengl/wiki/Performance)

### 实践项目
- 开发一个完整的3D渲染应用
- 实现性能分析与优化
- 添加高级渲染效果组合

## 调试与性能分析建议

### 调试工具
- **RenderDoc**：跨平台的图形调试工具，支持OpenGL、Vulkan等
- **gDEBugger**：OpenGL调试与性能分析工具
- **NVIDIA Nsight**：NVIDIA提供的专业图形调试工具
- **AMD Radeon GPU Profiler**：AMD提供的GPU分析工具

### 性能分析建议
1. **渲染时间测量**：使用`glBeginQuery(GL_TIME_ELAPSED, query)`和`glEndQuery`测量渲染时间
2. **帧率统计**：实现简单的帧率计数器
3. **资源使用监控**：监控纹理、缓冲区等资源的使用情况
4. **瓶颈分析**：使用性能分析工具确定渲染管线中的瓶颈
5. **优化策略**：
   - 减少绘制调用（使用实例化、批处理）
   - 优化着色器（减少分支、使用纹理 atlases）
   - 合理使用深度测试和剔除
   - 实现LOD（细节层次）系统

## 学习资源汇总

### 核心书籍
- 《OpenGL编程指南（红宝书）》第9版 - Dave Shreiner
- 《OpenGL SuperBible》第7版 - Graham Sellers
- 《Real-Time Rendering》第4版 - Tomas Akenine-Möller

### 在线教程
- [Learn OpenGL](https://learnopengl.com/) - Joey de Vries（最推荐的现代OpenGL教程）
- [OpenGL Tutorial](http://www.opengl-tutorial.org/) - Arnaud Masserann
- [Arcane Engine Tutorials](https://arcaneframework.com/)

### 视频教程
- The Cherno - OpenGL系列（YouTube）
- ThinMatrix - OpenGL 3D Game Tutorials（YouTube）
- Games202 - 实时渲染入门（网易云课堂）

### 文档与参考
- [OpenGL官方文档](https://www.opengl.org/documentation/)
- [OpenGL Wiki](https://www.khronos.org/opengl/wiki/)
- [GLFW文档](https://www.glfw.org/documentation.html)
- [GLM文档](https://glm.g-truc.net/0.9.9/index.html)

### 社区与论坛
- [OpenGL.org论坛](https://community.khronos.org/c/opengl)
- [Reddit r/opengl](https://www.reddit.com/r/opengl/)
- [Stack Overflow OpenGL标签](https://stackoverflow.com/questions/tagged/opengl)

---

## 学习建议

1. **理论与实践结合**：每学习一个概念，立即编写代码验证
2. **循序渐进**：不要急于学习高级主题，打好基础是关键
3. **阅读优秀代码**：学习开源项目的实现方式
4. **参与社区**：遇到问题及时求助，分享你的学习成果
5. **坚持练习**：每天保持一定的编程时间
6. **项目驱动学习**：通过实际项目巩固所学知识

祝你学习愉快！OpenGL是一项强大的技能，掌握它将为你打开计算机图形学的大门。
