// main.cpp
// Stage 1: Vulkan实例与设备初始化

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

// GLFW用于窗口创建
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// 自定义Vulkan工具类
#include "../../Common/include/vulkan_utils.h"

// 验证层名称
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

// 设备扩展名称
const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

// 应用信息
const VkApplicationInfo appInfo = {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pNext = nullptr,
    .pApplicationName = "Vulkan Stage 1",
    .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
    .pEngineName = "No Engine",
    .engineVersion = VK_MAKE_VERSION(1, 0, 0),
    .apiVersion = VK_API_VERSION_1_3
};

int main() {
    std::cout << "=== Vulkan Stage 1: 实例与设备初始化 ===" << std::endl;

    // 初始化GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW初始化失败" << std::endl;
        return -1;
    }

    // 不创建OpenGL上下文
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // 禁止调整窗口大小
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan Stage 1", nullptr, nullptr);
    if (!window) {
        std::cerr << "窗口创建失败" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 检查验证层是否可用
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    std::cout << "可用的验证层：" << std::endl;
    for (const auto& layer : availableLayers) {
        std::cout << "  - " << layer.layerName << std::endl;
    }

    // 检查所有需要的验证层是否可用
    bool allLayersAvailable = true;
    for (const auto& layerName : validationLayers) {
        bool layerAvailable = false;
        for (const auto& layer : availableLayers) {
            if (strcmp(layerName, layer.layerName) == 0) {
                layerAvailable = true;
                break;
            }
        }
        if (!layerAvailable) {
            std::cerr << "验证层不可用：" << layerName << std::endl;
            allLayersAvailable = false;
        }
    }

    if (!allLayersAvailable) {
        std::cerr << "一些验证层不可用，程序退出" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // 获取GLFW需要的扩展
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    // 添加调试扩展
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    std::cout << "需要的扩展：" << std::endl;
    for (const auto& extension : extensions) {
        std::cout << "  - " << extension << std::endl;
    }

    // 实例创建信息
    VkInstanceCreateInfo instanceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = static_cast<uint32_t>(validationLayers.size()),
        .ppEnabledLayerNames = validationLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
        .ppEnabledExtensionNames = extensions.data()
    };

    // 添加调试回调创建信息
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = vkUtils::getDebugMessengerCreateInfo();
    instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;

    // 创建Vulkan实例
    VkInstance instance;
    VK_CHECK_RESULT(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));
    std::cout << "✓ Vulkan实例创建成功" << std::endl;

    // 创建调试信使
    VkDebugUtilsMessengerEXT debugMessenger = vkUtils::createDebugMessenger(instance);
    std::cout << "✓ 调试信使创建成功" << std::endl;

    // 枚举物理设备
    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        std::cerr << "未找到支持Vulkan的GPU" << std::endl;
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data());

    std::cout << "找到 " << deviceCount << " 个支持Vulkan的设备：" << std::endl;

    // 选择合适的物理设备
    VkPhysicalDevice selectedDevice = VK_NULL_HANDLE;
    for (const auto& device : physicalDevices) {
        // 获取设备属性
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        // 获取设备功能
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        // 获取设备内存属性
        VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
        vkGetPhysicalDeviceMemoryProperties(device, &deviceMemoryProperties);

        // 打印设备信息
        std::cout << "\n设备名称：" << deviceProperties.deviceName << std::endl;
        vkUtils::printVersion(deviceProperties.apiVersion);
        
        // 检查设备类型
        std::string deviceTypeStr;
        switch (deviceProperties.deviceType) {
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            deviceTypeStr = "集成显卡";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            deviceTypeStr = "独立显卡";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            deviceTypeStr = "虚拟显卡";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            deviceTypeStr = "CPU";
            break;
        default:
            deviceTypeStr = "未知";
        }
        std::cout << "设备类型：" << deviceTypeStr << std::endl;

        // 获取队列族
        uint32_t queueFamilyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        // 查找图形队列族
        uint32_t graphicsQueueFamily = vkUtils::findQueueFamilyIndex(queueFamilies, VK_QUEUE_GRAPHICS_BIT);
        std::cout << "图形队列族索引：" << graphicsQueueFamily << std::endl;

        // 检查设备扩展
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        bool extensionsSupported = true;
        for (const auto& requiredExtension : deviceExtensions) {
            bool found = false;
            for (const auto& availableExtension : availableExtensions) {
                if (strcmp(requiredExtension, availableExtension.extensionName) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                extensionsSupported = false;
                break;
            }
        }

        // 如果是独立显卡且支持所有扩展，选择此设备
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && extensionsSupported) {
            selectedDevice = device;
            break;
        }
    }

    // 如果没有找到独立显卡，选择第一个可用设备
    if (selectedDevice == VK_NULL_HANDLE) {
        selectedDevice = physicalDevices[0];
        std::cout << "\n警告：未找到合适的独立显卡，使用第一个可用设备" << std::endl;
    }

    // 获取选中设备的属性
    VkPhysicalDeviceProperties selectedDeviceProperties;
    vkGetPhysicalDeviceProperties(selectedDevice, &selectedDeviceProperties);
    std::cout << "\n选中的设备：" << selectedDeviceProperties.deviceName << std::endl;

    // 获取队列族
    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(selectedDevice, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(selectedDevice, &queueFamilyCount, queueFamilies.data());

    // 查找图形队列族
    uint32_t graphicsQueueFamily = vkUtils::findQueueFamilyIndex(queueFamilies, VK_QUEUE_GRAPHICS_BIT);

    // 队列优先级
    float queuePriority = 1.0f;

    // 设备队列创建信息
    VkDeviceQueueCreateInfo queueCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .queueFamilyIndex = graphicsQueueFamily,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority
    };

    // 设备创建信息
    VkDeviceCreateInfo deviceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueCreateInfo,
        .enabledLayerCount = static_cast<uint32_t>(validationLayers.size()),
        .ppEnabledLayerNames = validationLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
        .ppEnabledExtensionNames = deviceExtensions.data(),
        .pEnabledFeatures = nullptr
    };

    // 创建逻辑设备
    VkDevice device;
    VK_CHECK_RESULT(vkCreateDevice(selectedDevice, &deviceCreateInfo, nullptr, &device));
    std::cout << "✓ 逻辑设备创建成功" << std::endl;

    // 获取图形队列
    VkQueue graphicsQueue;
    vkGetDeviceQueue(device, graphicsQueueFamily, 0, &graphicsQueue);
    std::cout << "✓ 图形队列获取成功" << std::endl;

    // 等待用户关闭窗口
    std::cout << "\n按窗口关闭按钮退出程序..." << std::endl;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    // 清理资源
    std::cout << "\n开始清理资源..." << std::endl;

    // 销毁逻辑设备
    vkDestroyDevice(device, nullptr);
    
    // 销毁调试信使
    vkUtils::destroyDebugMessenger(instance, debugMessenger);
    
    // 销毁Vulkan实例
    vkDestroyInstance(instance, nullptr);
    
    // 销毁窗口并终止GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "✓ 所有资源清理完成" << std::endl;
    std::cout << "=== Vulkan Stage 1 完成 ===" << std::endl;

    return 0;
}
