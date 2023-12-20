#include "Application.hpp"

namespace VEngine {

    const int WIDTH = 800;
    const int HEIGHT = 600;

    Application::Application()
    {
        m_Window = new Window(WIDTH, HEIGHT, "Vulkan Engine");
    }

    Application::~Application()
    {
        delete m_Window;
    }

    void Application::Run()
    {
        while (!m_Window->ShouldClose())
        {
            m_Window->OnUpdate();
        }
    }

}
