#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application/Application.h"
#include "Application/AppState.h"

int main() {
    Application* app = Application::getInstance();
    if(app->state == AppState::FAILED) return -1;
    app->run();
    return 0;
}