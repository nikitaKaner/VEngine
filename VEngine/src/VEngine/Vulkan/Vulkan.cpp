#include "Vulkan.hpp"

#include <stdexcept>
#include <iostream>
#include <cstring>

namespace VEngine::Vulkan {

    #ifdef VENGINE_DEBUG
    const bool enableValidationLayers = true;
    #else
    const bool enableValidationLayers = false;
    #endif

    Vulkan::Vulkan()
    {
        Init();
    }

    Vulkan::~Vulkan()
    {
        /* Destroy all other vulkan resources before destroying vulkan instance */

        vkDestroyInstance(m_Instance, nullptr);
    }

    void Vulkan::Init()
    {
        CreateVulkanInstance();
        PickPhysicalDevice();
    }

    void Vulkan::CreateVulkanInstance()
    {
        /* Create vulkan application info */
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "VEngine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "VEngine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        /* Create vulkan instance create info */
        VkInstanceCreateInfo instanceCreateInfo{};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo = &appInfo;

        /* Validation Layers */
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        if (enableValidationLayers)
        {
            if (!CheckValidationLayersSupport(validationLayers))
                throw std::runtime_error("One of validation layers is not supported!");

            instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            instanceCreateInfo.enabledLayerCount = 0;
        }

        /* Extensions */
        uint32_t glfwExtensionsCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

        if (!CheckExtensionsSupport(glfwExtensions, glfwExtensionsCount))
            throw std::runtime_error("One of required extensions is not supported!");

        instanceCreateInfo.enabledExtensionCount = glfwExtensionsCount;
        instanceCreateInfo.ppEnabledExtensionNames = glfwExtensions;

        /* Create vulkan instance */
        VkResult instanceCreationResult = vkCreateInstance(&instanceCreateInfo, nullptr, &m_Instance);
        if (instanceCreationResult != VK_SUCCESS)
            throw std::runtime_error("Failed to create vulkan instance! Error code");
    }

    bool Vulkan::CheckExtensionsSupport(const char** glfwExtensions, uint32_t& extensionsCount)
    {
        uint32_t propertyCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, nullptr);

        std::vector<VkExtensionProperties> properties(propertyCount);

        vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, properties.data());
        
        uint32_t i = 0;
        while (i < extensionsCount)
        {
            bool extensionSupported = false;
            for (const auto& property : properties)
            {
                if (strcmp(property.extensionName, glfwExtensions[i]) == 0)
                {
                    extensionSupported = true;
                    break;
                }
            }

            if (!extensionSupported)
                return false;

            i++;
        }

        return true;
    }

    bool Vulkan::CheckValidationLayersSupport(const std::vector<const char*>& validationLayers)
    {
        uint32_t propertyCount;
        vkEnumerateInstanceLayerProperties(&propertyCount, nullptr);

        std::vector<VkLayerProperties> properties(propertyCount);
        vkEnumerateInstanceLayerProperties(&propertyCount, properties.data());

        for (const char* layer : validationLayers)
        {
            bool layerSupported = false;
            for (const auto& property : properties)
            {
                if (strcmp(property.layerName, layer) == 0)
                {
                    layerSupported = true;
                    break;
                }
            }

            if (!layerSupported)
                return false;

        }

        return true;
    }

    void Vulkan::PickPhysicalDevice()
    {
        uint32_t physicalDeviceCount = 0;
        vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCount, nullptr);

        if (physicalDeviceCount == 0)
            throw std::runtime_error("Failed to find GPU's with Vulkan support!");

        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCount, physicalDevices.data());

        // TODO: Make device pick process using device score based on its features
        for (const auto& physicalDevice : physicalDevices)
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

    bool Vulkan::IsDeviceSuitable(VkPhysicalDevice device)
    {
        // VkPhysicalDeviceProperties deviceProperties;
        // vkGetPhysicalDeviceProperties(device, &deviceProperties);

        // VkPhysicalDeviceFeatures deviceFeatures;
        // vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        return true;
    }

}
