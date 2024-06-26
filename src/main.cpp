#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include "AppState.h"

int main() {
    Application app;
    if(app.state == AppState::FAILED) return -1;
    app.run();
    return 0;
}