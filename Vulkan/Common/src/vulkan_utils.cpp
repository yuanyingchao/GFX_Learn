// vulkan_utils.cpp
// Vulkan工具类实现

#include "../include/vulkan_utils.h"
#include <string>
#include <iostream>

namespace vkUtils {

// 将VkResult转换为字符串
std::string resultToString(VkResult result) {
    switch (result) {
#define STR(r) case VK_##r: return #r
        STR(SUCCESS);
        STR(NOT_READY);
        STR(TIMEOUT);
        STR(EVENT_SET);
        STR(EVENT_RESET);
        STR(INCOMPLETE);
        STR(ERROR_OUT_OF_HOST_MEMORY);
        STR(ERROR_OUT_OF_DEVICE_MEMORY);
        STR(ERROR_INITIALIZATION_FAILED);
        STR(ERROR_DEVICE_LOST);
        STR(ERROR_MEMORY_MAP_FAILED);
        STR(ERROR_LAYER_NOT_PRESENT);
        STR(ERROR_EXTENSION_NOT_PRESENT);
        STR(ERROR_FEATURE_NOT_PRESENT);
        STR(ERROR_INCOMPATIBLE_DRIVER);
        STR(ERROR_TOO_MANY_OBJECTS);
        STR(ERROR_FORMAT_NOT_SUPPORTED);
        STR(ERROR_SURFACE_LOST_KHR);
        STR(ERROR_NATIVE_WINDOW_IN_USE_KHR);
        STR(SUBOPTIMAL_KHR);
        STR(ERROR_OUT_OF_DATE_KHR);
        STR(ERROR_INCOMPATIBLE_DISPLAY_KHR);
        STR(ERROR_VALIDATION_FAILED_EXT);
        STR(ERROR_INVALID_SHADER_NV);
        STR(ERROR_INVALID_EXTERNAL_HANDLE_KHR);
        STR(ERROR_FRAGMENTATION_EXT);
        STR(ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR);
        STR(ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT);
        STR(THREAD_IDLE_KHR);
        STR(THREAD_DONE_KHR);
        STR(OPERATION_DEFERRED_KHR);
        STR(OPERATION_NOT_DEFERRED_KHR);
        STR(PIPELINE_COMPILE_REQUIRED_EXT);
#undef STR
        default: return "未知错误";
    }
}

// 打印Vulkan版本信息
void printVersion(uint32_t version) {
    uint32_t major = VK_VERSION_MAJOR(version);
    uint32_t minor = VK_VERSION_MINOR(version);
    uint32_t patch = VK_VERSION_PATCH(version);
    std::cout << "Vulkan版本: " << major << "." << minor << "." << patch << std::endl;
}

// 检查扩展是否可用
bool isExtensionAvailable(const std::vector<VkExtensionProperties>& availableExtensions, const std::string& extensionName) {
    for (const auto& extension : availableExtensions) {
        if (extensionName == extension.extensionName) {
            return true;
        }
    }
    return false;
}

// 检查队列族是否支持特定的队列类型
bool checkQueueFamilySupport(const VkQueueFamilyProperties& queueFamily, VkQueueFlags flags) {
    return (queueFamily.queueFlags & flags) == flags;
}

// 查找支持特定队列类型的队列族
uint32_t findQueueFamilyIndex(const std::vector<VkQueueFamilyProperties>& queueFamilies, VkQueueFlags flags) {
    for (uint32_t i = 0; i < queueFamilies.size(); i++) {
        if (checkQueueFamilySupport(queueFamilies[i], flags)) {
            return i;
        }
    }
    throw std::runtime_error("找不到支持所需队列类型的队列族");
}

// 创建验证层调试回调
VkDebugUtilsMessengerEXT createDebugMessenger(VkInstance instance, VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo) {
    // 获取创建调试回调的函数指针
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (!func) {
        throw std::runtime_error("无法加载vkCreateDebugUtilsMessengerEXT函数");
    }

    // 如果没有提供创建信息，使用默认值
    VkDebugUtilsMessengerCreateInfoEXT createInfo = pCreateInfo ? *pCreateInfo : getDebugMessengerCreateInfo();

    VkDebugUtilsMessengerEXT debugMessenger;
    VK_CHECK_RESULT(func(instance, &createInfo, nullptr, &debugMessenger));
    return debugMessenger;
}

// 销毁验证层调试回调
void destroyDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func) {
        func(instance, debugMessenger, nullptr);
    }
}

// 调试回调函数
VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    // 根据消息严重程度选择输出颜色
    std::cerr << "[Vulkan Debug]";

    switch (messageSeverity) {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        std::cerr << " [错误]";
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        std::cerr << " [警告]";
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        std::cerr << " [信息]";
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        std::cerr << " [详细]";
        break;
    default:
        std::cerr << " [未知]";
    }

    std::cerr << ": " << pCallbackData->pMessage << std::endl;

    // 如果是错误消息，可以选择终止程序
    // return messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT ? VK_TRUE : VK_FALSE;
    return VK_FALSE; // 继续程序执行
}

// 获取调试回调创建信息
VkDebugUtilsMessengerCreateInfoEXT getDebugMessengerCreateInfo() {
    return {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .pNext = nullptr,
        .flags = 0,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = debugCallback,
        .pUserData = nullptr
    };
}

} // namespace vkUtils
