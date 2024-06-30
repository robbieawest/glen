#include <iostream>
#include <list>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application/Application.h"
#include "Application/AppState.h"
#include "Utils/MiscHelper.tpp"

int main() {
    Application* app = Application::getInstance();
    if(app->state == AppState::FAILED) return -1;
    //app->run();
    std::cout << helper::format("Sample format {}, hello {}", {"string", "world"});

    return 0;
}
