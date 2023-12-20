#pragma once

#include <GLFW/glfw3.h>

#include "Device.hpp"
#include "Instance.hpp"
#include "Surface.hpp"

namespace VEngine {

    class Renderer
    {
    public:
        Renderer(GLFWwindow* const glfwWindow);
        ~Renderer();

    private:
        void Init();
        void Cleanup();
    private:
        Instance* m_Instance;

        Surface* m_Surface;
        Device* m_Device;

        /* Injected dependepcies */
        GLFWwindow* const m_GlfwWindow;
    };

}
