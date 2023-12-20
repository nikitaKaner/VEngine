#include "Window.hpp"

#include <stdexcept>

namespace VEngine {

    Window::Window(int width, int height, const std::string& name)
        : m_Width(width), m_Height(height), m_Name(name)
    {
        Init();
    }

    Window::~Window()
    {
        delete m_Renderer;

        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::Init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), nullptr, nullptr);
        m_Renderer = new Renderer((GLFWwindow* const)GetGlfwWindow());
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
    }

}
