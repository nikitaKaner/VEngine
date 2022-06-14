#pragma once

#ifndef GLFW_INCLUDE_VULKAN
    #define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>
#include <vector>

namespace VEngine::Vulkan {

    class Vulkan
    {
    public:
        Vulkan();
        ~Vulkan();

        void Init();
    private:
        /* Vulkan instance */
        void CreateVulkanInstance();
        bool CheckExtensionsSupport(const char** glfwExtensions, uint32_t& extensionsCount);
        bool CheckValidationLayersSupport(const std::vector<const char*>& validationLayers);

        VkInstance m_Instance;
    private:
        /* Physical device */
        void PickPhysicalDevice();
        bool IsDeviceSuitable(VkPhysicalDevice device);

        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
    };

}
