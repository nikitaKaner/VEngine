#include "Device.hpp"

#include <vector>
#include <stdexcept>
#include <iostream>

#include <string>
#include <set>

namespace VEngine
{

    Device::Device(Instance *const instance, VkSurfaceKHR* const vulkanSurface)
        : m_Instance(instance), m_VulkanSurface(vulkanSurface)
    {
        Init();
    }

    Device::~Device()
    {
        Cleanup();
    }

    void Device::Init()
    {
        PickPhysicalDevice();
    }

    void Device::Cleanup()
    {
        vkDestroyDevice(m_Device, nullptr);
    }

    void Device::PickPhysicalDevice()
    {
        uint32_t physicalDeviceCount;
        vkEnumeratePhysicalDevices(m_Instance->GetVulkanInstance(), &physicalDeviceCount, nullptr);

        if (physicalDeviceCount == 0)
            throw std::runtime_error("Failed to find GPUs with Vulkan support!");

        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        vkEnumeratePhysicalDevices(m_Instance->GetVulkanInstance(), &physicalDeviceCount, physicalDevices.data());

        // TODO: Implement score based physica device picking system
        for (const auto &physicalDevice : physicalDevices)
        {
            if (IsDeviceSuitable(physicalDevice))
            {
                m_PhysicalDevice = physicalDevice;
                break;
            }
        }

        if (m_PhysicalDevice == VK_NULL_HANDLE)
            throw std::runtime_error("Failed to find suitable GPU!");
    }

    bool Device::IsDeviceSuitable(const VkPhysicalDevice &physicalDevice)
    {
        QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(physicalDevice);

        return true;
    }

    QueueFamilyIndices Device::FindQueueFamilies(const VkPhysicalDevice& physicalDevice)
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyPropertyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamiliesProperties;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, queueFamiliesProperties.data());

        int queueFamilyIndex = 0;
        for (const auto& queueFamilyProperties : queueFamiliesProperties)
        {
            if (queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                indices.graphicsFamily = queueFamilyIndex;

            VkBool32 presentSupported = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, *m_VulkanSurface, &presentSupported);

            if (presentSupported)
                indices.presentFamily = queueFamilyIndex;

            if (indices.IsComplete())
                break;

            queueFamilyIndex++;
        }

        return indices;
    }

    void Device::CreateLogicalDevice()
    {
        /* Specify the queues to be created */
        QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;

            queueCreateInfos.push_back(queueCreateInfo);
        }

        /* Creating the logical device */
        VkDeviceCreateInfo deviceCreateInfo{};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();

        VkPhysicalDeviceFeatures deviceFeatures{};
        deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

        if (vkCreateDevice(m_PhysicalDevice, &deviceCreateInfo, nullptr, &m_Device) != VK_SUCCESS)
            throw std::runtime_error("Failed to create logical device!");

        vkGetDeviceQueue(m_Device, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);
        vkGetDeviceQueue(m_Device, indices.presentFamily.value(), 0, &m_PresentQueue);
    }

}
