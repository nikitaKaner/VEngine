#include "Instance.hpp"

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

namespace VEngine {

#ifdef VENGINE_DEBUG
    #define ENABLE_VALIDATION_LAYERS true
#else
    #define ENABLE_VALIDATION_LAYERS false
#endif

    Instance::Instance()
    {
        Init();
    }

    Instance::~Instance()
    {
        Cleanup();
    }

    void Instance::Init()
    {
        CreateVulkanInstance();
    }

    void Instance::Cleanup()
    {
        vkDestroyInstance(m_Instance, nullptr);
    }

    void Instance::CreateVulkanInstance()
    {
        /* Vulkan Application Info */
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "VEngine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Vulkan Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        /* Vulkan CreateInstance Info */
        VkInstanceCreateInfo instanceCreateInfo{};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo = &appInfo;
    
        /* Instance Extensions */
        uint32_t glfwExtensionCount;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        if (!IsExtensionsSupported({glfwExtensions, glfwExtensions + glfwExtensionCount}))
            throw std::runtime_error("Some of required instance extensions is not supported!");

        instanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
        instanceCreateInfo.ppEnabledExtensionNames = glfwExtensions;

        /* Validation Layers */
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        if (ENABLE_VALIDATION_LAYERS)
        {
            if (!IsValidationLayersSupported(validationLayers))
                throw std::runtime_error("Some of requested validation layers are not available!");

            instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else 
        {
            instanceCreateInfo.enabledLayerCount = 0;
        }

        if (vkCreateInstance(&instanceCreateInfo, nullptr, &m_Instance) != VK_SUCCESS)
            throw std::runtime_error("Failed to create Vulkan Instance!");
    }

    bool Instance::IsValidationLayersSupported(const std::vector<const char*>& validationLayers)
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
                if(strcmp(property.layerName, layer) == 0)
                    layerSupported = true;
            }

            if (!layerSupported)
                return false;
        }

        return true;
    }

    bool Instance::IsExtensionsSupported(std::vector<const char*> extensions)
    {
        uint32_t propertyCount;
        vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, nullptr);

        std::vector<VkExtensionProperties> properties(propertyCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, properties.data());

        for (const auto* extension : extensions)
        {
            bool extensionSupported = false;

            for (const auto& property : properties)
            {
                if (std::strcmp(property.extensionName, extension) == 0)
                {
                    extensionSupported = true;
                    break;
                }
            }

            if (!extensionSupported)
                return false;
        }

        return true;
    }

}
