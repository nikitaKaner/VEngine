#pragma once

#include <GLFW/glfw3.h>

#include <optional>

#include "Instance.hpp"
#include "Surface.hpp"

namespace VEngine {

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool IsComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class Device
    {
    public:
        Device(Instance* const instance, VkSurfaceKHR* const vulkanSurface);
        ~Device();
    private:
        void Init();
        void Cleanup();
    
        void PickPhysicalDevice();
        bool IsDeviceSuitable(const VkPhysicalDevice& physicalDevice);

        void CreateLogicalDevice();

        QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& physicalDevice);
    private:
        /* Physical device */
        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;

        /* Logical device */
        VkDevice m_Device = VK_NULL_HANDLE;

        /* Queue's */
        VkQueue m_GraphicsQueue;
        VkQueue m_PresentQueue;

        /* Injected dependencies */
        Instance* const m_Instance;
        VkSurfaceKHR* const m_VulkanSurface;
    };

}
