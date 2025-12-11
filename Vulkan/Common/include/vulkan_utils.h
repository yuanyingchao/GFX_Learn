// vulkan_utils.h
// Vulkan工具类，提供通用的辅助函数和错误处理

#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

// 错误检查宏
#define VK_CHECK_RESULT(f) do { \
    VkResult res = (f); \
    if (res != VK_SUCCESS) { \
        std::cerr << "Vulkan错误: " << vkUtils::resultToString(res) << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
        throw std::runtime_error("Vulkan操作失败"); \
    } \
} while(0)

namespace vkUtils {

// 将VkResult转换为字符串
std::string resultToString(VkResult result);

// 打印Vulkan版本信息
void printVersion(uint32_t version);

// 检查扩展是否可用
bool isExtensionAvailable(const std::vector<VkExtensionProperties>& availableExtensions, const std::string& extensionName);

// 检查队列族是否支持特定的队列类型
bool checkQueueFamilySupport(const VkQueueFamilyProperties& queueFamily, VkQueueFlags flags);

// 查找支持特定队列类型的队列族
uint32_t findQueueFamilyIndex(const std::vector<VkQueueFamilyProperties>& queueFamilies, VkQueueFlags flags);

// 创建验证层调试回调
VkDebugUtilsMessengerEXT createDebugMessenger(VkInstance instance, VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo = nullptr);

// 销毁验证层调试回调
void destroyDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger);

// 调试回调函数
VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);

// 获取调试回调创建信息
VkDebugUtilsMessengerCreateInfoEXT getDebugMessengerCreateInfo();

} // namespace vkUtils
