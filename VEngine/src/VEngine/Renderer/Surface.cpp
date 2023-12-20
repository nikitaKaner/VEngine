#include "Surface.hpp"

#include <stdexcept>

namespace VEngine {

    Surface::Surface(Instance* const instance, GLFWwindow* const glfwWindow)
        : m_Instance(instance), m_GlfwWindow(glfwWindow)
    {
        Init();
    }

    Surface::~Surface()
    {
        Cleanup();
    }

    void Surface::Init()
    {
        CreateSurface();
    }

    void Surface::Cleanup()
    {
        vkDestroySurfaceKHR(m_Instance->GetVulkanInstance(), m_Surface, nullptr);
    }

    void Surface::CreateSurface()
    {
        if (glfwCreateWindowSurface(m_Instance->GetVulkanInstance(), m_GlfwWindow, nullptr, &m_Surface) != VK_SUCCESS)
            throw std::runtime_error("Failed to create window surface!");
    }

}
