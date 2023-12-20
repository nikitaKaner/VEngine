#include "Renderer.hpp"

#include <iostream>

namespace VEngine {

    Renderer::Renderer(GLFWwindow* const glfwWindow)
        : m_GlfwWindow(glfwWindow)
    {
        Init();
    }

    Renderer::~Renderer()
    {
        Cleanup();
    }

    void Renderer::Init()
    {
        m_Instance = new Instance();
        m_Surface = new Surface(m_Instance, m_GlfwWindow);
        m_Device = new Device(m_Instance, m_Surface->GetVulkanSurface());
    }

    void Renderer::Cleanup()
    {
        delete m_Device;

        /* instance should be deleted lastly */
        delete m_Surface;
        delete m_Instance;
    }

}
