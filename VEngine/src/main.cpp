#include "VEngine/Application.hpp"

int main()
{
    VEngine::Application* app = new VEngine::Application();
    app->Run();
    delete app;
}
