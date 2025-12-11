# Vulkan学习路线图

## 面向对象
具备C++基础和基本图形学知识的开发者

## 学习目标
从零开始构建对Vulkan底层机制的理解，掌握现代图形API的核心概念和最佳实践

## 学习计划（14周）

### 阶段一：Vulkan基础与环境搭建（第1-2周）

#### 第1周：Vulkan概述与环境搭建

**核心目标**：理解Vulkan的基本概念和架构，搭建开发环境

**学习内容**：
1. Vulkan架构与设计理念
2. Vulkan与OpenGL的区别
3. 开发环境搭建（GLFW/SDL, Vulkan SDK, CMake）
4. 验证层的使用（VK_LAYER_KHRONOS_validation）
5. Vulkan API基础结构

**推荐资源**：
- [Vulkan Tutorial](https://vulkan-tutorial.com/)
- [Vulkan Specification](https://www.khronos.org/registry/vulkan/specs/1.3-extensions/html/vkspec.html)
- [Vulkan Guide](https://vkguide.dev/)

**实践项目**：
- 初始化Vulkan实例
- 启用验证层
- 打印Vulkan设备信息

**评估标准**：
- 成功初始化Vulkan实例
- 正确启用验证层
- 能够查询和打印系统中的Vulkan设备信息

#### 第2周：设备选择与内存管理基础

**核心目标**：学习如何选择物理设备和创建逻辑设备，理解Vulkan内存模型

**学习内容**：
1. 物理设备选择标准（特性、扩展、队列族）
2. 逻辑设备创建
3. Vulkan内存模型
4. 内存类型与属性
5. 内存分配基础

**推荐资源**：
- [Vulkan内存管理](https://developer.nvidia.com/vulkan-memory-management)
- [Vulkan Cookbook](https://www.packtpub.com/product/vulkan-cookbook/9781786469809)

**实践项目**：
- 实现物理设备选择逻辑
- 创建逻辑设备
- 查询内存属性
- 分配和管理简单内存块

**评估标准**：
- 能够根据需求选择合适的物理设备
- 成功创建逻辑设备
- 理解不同内存类型的用途

### 阶段二：核心渲染机制（第3-6周）

#### 第3周：交换链与表面

**核心目标**：理解并实现Vulkan交换链，掌握图像呈现机制

**学习内容**：
1. 表面（Surface）创建
2. 交换链（Swapchain）创建与配置
3. 交换链图像格式与颜色空间
4. 交换链重建机制

**推荐资源**：
- [Vulkan Tutorial - Swap Chain](https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain)
- [Sascha Willems Vulkan Examples](https://github.com/SaschaWillems/Vulkan/tree/master/examples/swapchain)

**实践项目**：
- 创建窗口表面
- 配置并创建交换链
- 实现交换链重建功能

**评估标准**：
- 成功创建交换链
- 能够处理窗口大小变化时的交换链重建

#### 第4周：命令缓冲区与同步原语

**核心目标**：学习命令缓冲区和命令池的使用，掌握同步机制

**学习内容**：
1. 命令池（Command Pool）创建
2. 命令缓冲区（Command Buffer）分配与录制
3. 命令缓冲区提交与执行
4. 信号量（Semaphore）与 fences
5. 渲染同步机制

**推荐资源**：
- [Vulkan Tutorial - Command Buffers](https://vulkan-tutorial.com/Drawing_a_triangle/Drawing/Command_buffers)
- [Vulkan同步原语详解](https://www.khronos.org/blog/vulkan-synchronization-explained)

**实践项目**：
- 创建命令池和命令缓冲区
- 录制简单的绘制命令
- 实现基本的同步机制
- 绘制一个彩色背景

**评估标准**：
- 能够创建和录制命令缓冲区
- 理解并正确使用同步原语
- 成功绘制彩色背景

#### 第5周：图形管线

**核心目标**：掌握Vulkan图形管线的创建和配置

**学习内容**：
1. 图形管线架构
2. 着色器模块创建与编译
3. 管线布局与渲染流程
4. 固定功能阶段配置
5. 动态状态管理

**推荐资源**：
- [Vulkan Tutorial - Graphics Pipeline](https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics)
- [GLSL着色器编写指南](https://www.khronos.org/opengl/wiki/Core_Language_(GLSL))

**实践项目**：
- 编写简单的顶点和片段着色器
- 创建完整的图形管线
- 绘制一个彩色三角形

**评估标准**：
- 能够创建和配置完整的图形管线
- 成功编译和使用GLSL着色器
- 绘制出彩色三角形

#### 第6周：顶点数据与缓冲区

**核心目标**：学习如何在Vulkan中管理和绘制顶点数据

**学习内容**：
1. 顶点缓冲区创建
2. 索引缓冲区创建
3. 缓冲区内存分配策略
4. 数据上传到GPU
5. 顶点输入描述

**推荐资源**：
- [Vulkan Tutorial - Vertex Input](https://vulkan-tutorial.com/Drawing_a_triangle/Vertex_buffers)
- [Vulkan内存最佳实践](https://developer.amd.com/wordpress/media/2013/12/Vulkan-Memory-Management.pdf)

**实践项目**：
- 创建顶点和索引缓冲区
- 上传顶点数据到GPU
- 绘制一个四边形

**评估标准**：
- 能够创建和管理顶点缓冲区
- 理解顶点输入描述的配置
- 成功绘制四边形

### 阶段三：资源管理与高级渲染（第7-10周）

#### 第7周：描述符集与Uniform缓冲

**核心目标**：掌握Vulkan的资源绑定机制

**学习内容**：
1. 描述符集（Descriptor Set）与描述符池（Descriptor Pool）
2. Uniform缓冲对象（UBO）
3. 管线布局（Pipeline Layout）
4. 描述符集更新与绑定

**推荐资源**：
- [Vulkan Tutorial - Descriptor Sets](https://vulkan-tutorial.com/Uniform_buffers/Descriptor_sets)
- [Vulkan Descriptor Set最佳实践](https://gpuopen.com/vulkan-descriptor-set-tips/)

**实践项目**：
- 创建Uniform缓冲
- 配置描述符集和描述符池
- 使用Uniform缓冲传递变换矩阵
- 实现简单的旋转动画

**评估标准**：
- 能够创建和管理描述符集
- 理解Uniform缓冲的使用
- 实现三角形的旋转动画

#### 第8周：纹理与采样器

**核心目标**：学习如何在Vulkan中使用纹理

**学习内容**：
1. 纹理图像创建
2. 采样器（Sampler）配置
3. 纹理坐标与UV映射
4. 图像布局转换
5. MIP映射

**推荐资源**：
- [Vulkan Tutorial - Textures](https://vulkan-tutorial.com/Texture_mapping/Images)
- [Vulkan纹理加载指南](https://github.com/SaschaWillems/Vulkan/tree/master/examples/texture)

**实践项目**：
- 加载纹理图像
- 创建纹理资源和采样器
- 实现纹理映射
- 绘制带纹理的立方体

**评估标准**：
- 能够加载和使用纹理
- 理解图像布局转换的重要性
- 成功绘制带纹理的立方体

#### 第9周：内存管理高级话题与VMA

**核心目标**：掌握高级内存管理技巧，使用VMA库简化内存管理

**学习内容**：
1. Vulkan Memory Allocator (VMA) 库
2. 内存池与子分配
3. 内存预算与统计
4. 资源生命周期管理
5. 性能优化考虑

**推荐资源**：
- [VMA官方文档](https://gpuopen.com/vulkan-memory-allocator/)
- [VMA GitHub仓库](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator)

**实践项目**：
- 集成VMA库到项目中
- 使用VMA管理所有内存分配
- 实现资源池化
- 优化内存使用

**评估标准**：
- 能够集成和使用VMA库
- 理解内存池的优势
- 优化内存分配策略

#### 第10周：多Pass渲染与帧缓冲区

**核心目标**：学习离屏渲染和多Pass渲染技术

**学习内容**：
1. 帧缓冲区（Framebuffer）创建
2. 渲染目标与附件
3. 多Pass渲染流程
4. 后处理效果
5. 渲染到纹理

**推荐资源**：
- [Vulkan Tutorial - Framebuffers](https://vulkan-tutorial.com/Render_pass/Framebuffers)
- [Sascha Willems - Framebuffer Examples](https://github.com/SaschaWillems/Vulkan/tree/master/examples/framebuffer)

**实践项目**：
- 创建离屏帧缓冲区
- 实现简单的后处理效果（如灰度转换）
- 绘制带后处理的3D场景

**评估标准**：
- 能够创建和使用帧缓冲区
- 实现基本的后处理效果
- 理解多Pass渲染流程

### 阶段四：高级功能与优化（第11-14周）

#### 第11周：动态Uniform与Push Constants

**核心目标**：学习更高效的Uniform数据更新机制

**学习内容**：
1. 动态Uniform缓冲区
2. Push Constants
3. 性能比较与适用场景
4. 混合使用策略

**推荐资源**：
- [Vulkan动态Uniform](https://www.khronos.org/blog/vulkan-dynamic-uniform-buffers)
- [Vulkan Push Constants](https://vkguide.dev/docs/chapter-3/push_constants/)

**实践项目**：
- 实现动态Uniform缓冲区
- 使用Push Constants传递小型数据
- 比较不同方法的性能

**评估标准**：
- 能够使用动态Uniform和Push Constants
- 理解它们的性能特点
- 选择合适的Uniform更新策略

#### 第12周：多线程渲染与命令缓冲区录制

**核心目标**：学习如何利用多线程提高Vulkan应用性能

**学习内容**：
1. 多线程命令缓冲区录制
2. 线程安全考虑
3. 命令池与线程关联
4. 并行渲染策略
5. 同步与资源访问控制

**推荐资源**：
- [Vulkan多线程最佳实践](https://developer.nvidia.com/blog/vulkan-dos-donts/)
- [Vulkan多线程渲染](https://gpuopen.com/vulkan-multi-threading/)

**实践项目**：
- 实现多线程命令缓冲区录制
- 并行处理场景渲染
- 优化多线程同步

**评估标准**：
- 能够实现多线程命令缓冲区录制
- 理解多线程渲染的同步问题
- 提高应用性能

#### 第13周：高级渲染技术（PBR）

**核心目标**：学习基于物理的渲染（PBR）技术

**学习内容**：
1. PBR理论基础
2. 金属度-粗糙度工作流
3. 环境贴图与IBL
4. PBR着色器实现

**推荐资源**：
- [Physically Based Rendering in Vulkan](https://learnopengl.com/PBR/Theory)
- [Sascha Willems PBR Example](https://github.com/SaschaWillems/Vulkan/tree/master/examples/pbr)

**实践项目**：
- 实现PBR材质系统
- 创建PBR着色器
- 渲染带PBR材质的3D模型

**评估标准**：
- 理解PBR理论
- 能够实现PBR着色器
- 渲染出真实感的3D模型

#### 第14周：阴影映射与级联阴影

**核心目标**：学习实时阴影技术

**学习内容**：
1. 阴影映射原理
2. 深度纹理与阴影采样
3. 级联阴影映射（CSM）
4. 阴影质量优化

**推荐资源**：
- [Vulkan阴影映射](https://vkguide.dev/docs/chapter-7/shadow_mapping/)
- [Cascaded Shadow Maps教程](https://developer.nvidia.com/gpugems/gpugems3/part-ii-light-and-shadows/chapter-8-cascaded-shadow-maps)

**实践项目**：
- 实现基本阴影映射
- 实现级联阴影映射
- 优化阴影质量

**评估标准**：
- 能够实现基本阴影映射
- 理解级联阴影映射的工作原理
- 渲染出高质量的阴影效果

### 阶段五：进阶方向（可选）

#### 射线追踪（Vulkan RT）
- Vulkan光线追踪扩展
- 加速结构（AS）构建
- 射线生成着色器
- 实时光线追踪应用

#### 多GPU渲染
- 多设备同步
- 分布式渲染策略
- 跨设备资源共享

#### Android Vulkan开发
- Android Vulkan环境搭建
- 移动设备优化
- 触摸输入处理

## 推荐资源

### 官方文档
- [Vulkan Specification](https://www.khronos.org/registry/vulkan/specs/1.3-extensions/html/vkspec.html)
- [Vulkan API参考](https://www.khronos.org/registry/vulkan/)

### 教程
- [Vulkan Tutorial](https://vulkan-tutorial.com/) - 最全面的Vulkan入门教程
- [Vulkan Guide](https://vkguide.dev/) - 现代化的Vulkan学习资源
- [Sascha Willems Vulkan Examples](https://github.com/SaschaWillems/Vulkan) - 丰富的示例代码

### 书籍
- [Learning Vulkan](https://www.packtpub.com/product/learning-vulkan/9781786469809)
- [Vulkan Programming Guide](https://www.amazon.com/Vulkan-Programming-Guide-Official-Learning/dp/0134464546)
- [Mastering Graphics Programming with Vulkan](https://www.packtpub.com/product/mastering-graphics-programming-with-vulkan/9781838826964)

### 工具
- [RenderDoc](https://renderdoc.org/) - 图形调试工具
- [Vulkan Validation Layers](https://vulkan.lunarg.com/doc/sdk/latest/windows/validation_layers.html) - 错误检查工具
- [GLSLangValidator](https://github.com/KhronosGroup/glslang) - GLSL着色器编译器

## 学习建议

1. **重视基础**：Vulkan是显式API，基础概念必须扎实
2. **错误处理**：始终启用验证层，认真处理所有返回的VkResult
3. **代码组织**：将Vulkan代码封装成类，保持良好的结构
4. **性能意识**：从一开始就考虑内存和计算效率
5. **实践为主**：多写代码，通过项目巩固知识
6. **阅读源码**：学习优秀的Vulkan项目源码

## 评估标准

每阶段结束时，应该能够：
- 理解并解释该阶段的核心概念
- 独立完成实践项目
- 解决常见的Vulkan错误
- 理解最佳实践和性能优化

## 最终目标

完成本学习路线后，您将能够：
- 从零开始创建完整的Vulkan应用
- 理解Vulkan的底层工作原理
- 实现高效的现代图形渲染
- 解决复杂的图形编程问题
- 为进一步学习高级图形技术打下坚实基础
