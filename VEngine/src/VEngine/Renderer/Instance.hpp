#pragma once

#include <GLFW/glfw3.h>

#include <vector>

namespace VEngine {

    class Instance
    {
    public:
        Instance();
        ~Instance();

        inline const VkInstance& GetVulkanInstance() const { return m_Instance; }
    private:
        void Init();
        void Cleanup();

        void CreateVulkanInstance();

        bool IsValidationLayersSupported(const std::vector<const char*>& validationLayers);
        bool IsExtensionsSupported(std::vector<const char*> extensions);
    private:
        VkInstance m_Instance;
    };

}
