#pragma once

#include <string>

#include "Vulkan/Vulkan.hpp"

namespace VEngine {

    class Window
    {
    public:
        Window(int width, int height, const std::string& name);
        ~Window();

        bool ShouldClose() { return glfwWindowShouldClose(m_Window); }
        void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

        void Init();
        void OnUpdate();
    private:
        const int m_Width;
        const int m_Height;
        const std::string m_Name;

        GLFWwindow* m_Window;
        Vulkan::Vulkan* m_Vulkan;
    };

}
