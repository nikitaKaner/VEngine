#pragma once

#include "Window.hpp"

#include <string>

namespace VEngine {

    class Application
    {
    public:
        Application();
        ~Application();

        void Run();
    private:
        Window* m_Window;
    };

}
