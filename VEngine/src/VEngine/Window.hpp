#pragma once

#include <GLFW/glfw3.h>

#include <string>

#include "VEngine/Renderer/Renderer.hpp"

namespace VEngine {

    class Window
    {
    public:
        Window(int width, int height, const std::string& name);
        ~Window();

        bool ShouldClose() { return glfwWindowShouldClose(m_Window); }

        GLFWwindow* GetGlfwWindow() const { return m_Window; }

        void OnUpdate();
    private:
        void Init();
    private:
        const int m_Width;
        const int m_Height;
        const std::string& m_Name;

        GLFWwindow* m_Window;
        Renderer* m_Renderer;
    };

}
