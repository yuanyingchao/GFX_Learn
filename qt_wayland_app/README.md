# Qt Wayland 图形渲染示例

这是一个基于Qt框架在Wayland平台上进行图形渲染的示例项目。

## 功能特性

- 在Wayland平台上使用Qt进行硬件加速图形渲染
- 实现了带有平滑旋转动画的彩色矩形
- 使用渐变色彩填充（红→黄→绿→蓝）
- 应用了抗锯齿渲染，确保图形边缘平滑
- 实时显示当前运行的平台信息

## 环境要求

- Ubuntu 22.04 LTS 或其他支持Wayland的Linux发行版
- Qt 5.15 或更高版本
- CMake 3.16 或更高版本
- Wayland显示服务器

## 安装依赖

### 1. 安装Qt开发环境

```bash
sudo apt-get install -y qt5-default qtbase5-dev qtbase5-dev-tools
```

### 2. 安装Wayland支持

```bash
sudo apt-get install -y wayland-protocols libwayland-dev libwayland-egl1-mesa
```

### 3. 安装Qt Wayland平台插件

```bash
sudo apt-get install -y qtwayland5
```

## 构建和运行

### 1. 创建构建目录

```bash
mkdir -p build
cd build
```

### 2. 使用CMake配置项目

```bash
cmake .. -DCMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt5
```

### 3. 编译项目

```bash
make
```

### 4. 运行应用程序

```bash
./qt_wayland_app
```

## 项目结构

```
qt_wayland_app/
├── CMakeLists.txt    # 项目配置文件
├── main.cpp          # 主程序代码
├── build/            # 构建目录
└── README.md         # 项目说明文档
```

## 技术实现

### 图形渲染

项目使用Qt的`QPainter`类进行图形绘制，主要实现了：

- **渐变色彩**：使用`QLinearGradient`创建从红色到蓝色的渐变效果
- **动画效果**：通过`QTimer`实现每50毫秒旋转5度的平滑动画
- **抗锯齿**：启用`QPainter::Antialiasing`渲染提示，提高图形质量

### Wayland集成

- 通过设置环境变量`QT_QPA_PLATFORM=wayland`强制应用程序使用Wayland平台
- 使用Qt的公共API检测和显示当前运行的平台信息

## 注意事项

1. 确保系统正在运行Wayland显示服务器，而不是X11
2. 如果遇到平台插件错误，请检查`qtwayland5`包是否正确安装
3. 项目已配置CMake自动处理MOC和UIC文件，无需手动运行
4. 动画效果可能会因系统性能而有所不同

## 许可证

本项目采用MIT许可证，可自由使用和修改。
