# Stage 1: Vulkan 实例与设备初始化

## 阶段目标

1. 理解 Vulkan 的基本概念和架构
2. 掌握 Vulkan 实例的创建和配置
3. 学习物理设备选择和逻辑设备创建
4. 理解验证层的使用和重要性
5. 熟悉 Vulkan 的错误处理机制

## 学习内容

### 1. Vulkan 概述

Vulkan 是一种跨平台的 3D 图形和计算 API，由 Khronos Group 开发。它提供了对图形硬件的直接控制，允许开发者实现高性能的图形应用。

Vulkan 的主要特点：
- 显式控制：所有操作都需要显式请求
- 低开销：减少驱动程序的猜测和开销
- 多线程友好：设计用于现代多核处理器
- 跨平台：支持 Windows、Linux、macOS、Android 等

### 2. 环境搭建

本阶段使用以下库：
- **Vulkan SDK**：提供 Vulkan API 和工具链
- **GLFW**：用于窗口创建和管理
- **CMake**：跨平台构建系统

### 3. 示例程序说明

#### main.cpp

示例程序展示了 Vulkan 实例和设备初始化的完整流程：

1. **GLFW 初始化**：创建窗口但不创建 OpenGL 上下文
2. **验证层检查**：确保所需的验证层可用
3. **扩展检查**：获取 GLFW 所需的扩展并添加调试扩展
4. **Vulkan 实例创建**：使用指定的应用信息、验证层和扩展创建实例
5. **调试信使创建**：设置调试回调以捕获 Vulkan 错误和警告
6. **物理设备枚举**：列出系统中的所有 Vulkan 设备
7. **设备选择**：优先选择独立显卡，否则选择第一个可用设备
8. **逻辑设备创建**：使用选定的物理设备创建逻辑设备
9. **队列获取**：获取图形队列用于后续渲染操作

### 4. 关键概念解释

#### 实例 (Instance)

Vulkan 实例是应用程序与 Vulkan 库之间的连接。它负责：
- 应用程序信息的注册
- 验证层的启用
- 全局扩展的启用
- 物理设备的枚举

#### 物理设备 (Physical Device)

物理设备代表系统中的一个实际 GPU。它包含：
- 设备属性（名称、类型、版本等）
- 设备功能（支持的图形特性）
- 设备内存属性
- 队列族（执行命令的硬件队列）

#### 逻辑设备 (Logical Device)

逻辑设备是应用程序与物理设备交互的接口。它负责：
- 队列的创建和管理
- 设备扩展的启用
- 资源的创建和管理

#### 验证层 (Validation Layers)

验证层提供运行时检查，帮助开发者发现和修复 Vulkan API 使用中的错误。它们：
- 检查 API 调用的正确性
- 验证资源状态和参数
- 提供详细的错误和警告信息

#### 队列族 (Queue Family)

队列族代表 GPU 上可执行特定类型命令的硬件队列。常见的队列类型包括：
- 图形队列（VK_QUEUE_GRAPHICS_BIT）
- 计算队列（VK_QUEUE_COMPUTE_BIT）
- 传输队列（VK_QUEUE_TRANSFER_BIT）

## 如何构建和运行

### 构建步骤

1. 创建构建目录：
   ```bash
   mkdir build
   cd build
   ```

2. 运行 CMake：
   ```bash
   cmake ..
   ```

3. 编译程序：
   ```bash
   make
   ```

### 运行程序

```bash
./bin/vulkan_stage1
```

## 预期结果

运行程序后，你将看到：

1. 窗口创建成功
2. 可用的验证层列表
3. 需要的扩展列表
4. Vulkan 实例创建成功
5. 调试信使创建成功
6. 系统中的 Vulkan 设备信息
7. 选中的设备信息
8. 逻辑设备和图形队列创建成功

窗口标题为 "Vulkan Stage 1"，大小为 800x600 像素。

## 练习建议

1. **修改应用信息**：尝试修改 `appInfo` 结构体中的应用名称、版本等信息
2. **添加更多扩展**：尝试启用其他 Vulkan 扩展并观察结果
3. **设备选择策略**：修改设备选择逻辑，例如优先选择具有最大内存的设备
4. **错误处理**：尝试注释掉错误检查宏，观察程序在出现错误时的行为
5. **窗口属性**：尝试修改窗口大小、标题等属性

## 推荐资源

- [Vulkan Tutorial - 实例创建](https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Instance)
- [Vulkan Specification - Instance](https://www.khronos.org/registry/vulkan/specs/1.3-extensions/html/vkspec.html#devsandqueues-instances)
- [Vulkan Guide - 实例和设备](https://vkguide.dev/docs/chapter-1/vulkan_init/)
- [GLFW 文档](https://www.glfw.org/documentation.html)

## 下一阶段

Stage 2: 设备内存管理

在下一阶段，我们将学习 Vulkan 的内存模型、内存类型和内存分配策略。
