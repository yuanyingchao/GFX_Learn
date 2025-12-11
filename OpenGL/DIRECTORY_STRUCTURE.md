# OpenGL 项目目录结构

本目录结构是为配合12周学习计划设计的，旨在帮助学习者系统地组织OpenGL学习内容和实践项目。

## 整体结构

```
OpenGL/
├── learning_plan/              # 学习计划文档
│   ├── comprehensive_opengl_learning_plan.md  # 12周详细学习计划
│   └── ...
├── Week1_GettingStarted/       # 第1周学习内容
├── Week2_Shaders/              # 第2周学习内容
├── Week3_VertexData/           # 第3周学习内容
├── Week4_Textures/             # 第4周学习内容
├── Week5_Transformations/      # 第5周学习内容
├── Week6_Lighting/             # 第6周学习内容
├── Week7_Framebuffers/         # 第7周学习内容
├── Week8_Shadows/              # 第8周学习内容
├── Week9_Instancing/           # 第9周学习内容
├── Week10_PBR/                 # 第10周学习内容
├── Week11_ComputeShaders/      # 第11周学习内容
├── Week12_Performance/         # 第12周学习内容
├── Projects/                   # 实践项目
│   ├── BasicRenderer/          # 基础渲染器项目
│   ├── AdvancedRenderer/       # 高级渲染器项目
│   ├── PBRRenderer/            # PBR渲染器项目
│   ├── ParticleSystem/         # 粒子系统项目
│   └── ShadowRenderer/         # 阴影渲染器项目
└── README.md                   # OpenGL目录说明
```

## 每周学习目录结构

每个WeekX目录都遵循相同的结构，便于学习者保持一致的开发习惯：

```
WeekX_TopicName/
├── src/              # 源代码文件
├── include/          # 头文件
├── shaders/          # GLSL着色器文件
├── resources/        # 资源文件（纹理、模型等）
├── CMakeLists.txt    # CMake构建脚本
└── README.md         # 本周学习内容说明
```

### 目录用途说明

1. **src/**
   - 主程序源代码文件（.cpp）
   - 核心功能实现
   - 示例程序

2. **include/**
   - 头文件（.h/.hpp）
   - 类定义
   - 函数声明
   - 常量定义

3. **shaders/**
   - 顶点着色器（.vert）
   - 片段着色器（.frag）
   - 几何着色器（.geom）
   - 计算着色器（.comp）

4. **resources/**
   - 纹理图片（.png/.jpg/.bmp）
   - 3D模型文件（.obj/.fbx）
   - 材质文件
   - 配置文件

## 实践项目目录结构

每个项目目录可以根据需要调整结构，但建议包含以下基本组件：

```
Projects/ProjectName/
├── src/              # 项目源代码
├── include/          # 项目头文件
├── shaders/          # 项目着色器
├── resources/        # 项目资源
├── libs/             # 第三方库
├── tests/            # 测试代码
├── docs/             # 项目文档
├── CMakeLists.txt    # 构建脚本
└── README.md         # 项目说明
```

## 使用建议

1. **按周学习**：每周重点学习对应的WeekX目录内容，完成示例程序和实践练习
2. **项目驱动**：在学习过程中，可以参考Projects目录中的项目结构，逐步构建自己的渲染器
3. **代码复用**：将通用功能（如着色器加载、纹理管理等）抽象成库，在后续学习中复用
4. **版本控制**：建议使用Git对代码进行版本控制，记录学习进度
5. **文档记录**：在每个目录的README.md中记录学习心得、遇到的问题和解决方案

## 示例程序结构

每个WeekX目录中都应该包含一个完整的示例程序，展示本周学习的核心知识点。示例程序应该：

- 使用现代OpenGL（3.3+ Core Profile）
- 遵循良好的代码风格
- 包含详细的注释
- 提供清晰的构建和运行说明

---

通过这种结构化的组织方式，您可以更系统地学习OpenGL，并逐步构建自己的渲染器项目。祝您学习愉快！
