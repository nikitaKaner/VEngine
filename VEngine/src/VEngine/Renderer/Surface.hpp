#pragma once

#include <GLFW/glfw3.h>

#include "Instance.hpp"

namespace VEngine {

    class Surface
    {
    public:
        Surface(Instance* const instance, GLFWwindow* const glfwWindow);
        ~Surface();

        VkSurfaceKHR* const GetVulkanSurface() { return &m_Surface; } 
    private:
        void Init();
        void Cleanup();

        void CreateSurface();
    private:
        VkSurfaceKHR m_Surface;

        /* Injected dependencies */
        Instance* const m_Instance;
        GLFWwindow* const m_GlfwWindow;
    };

}
