#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application.h"

int main() {
    Application app;
    if(!app.validSession) return -1;
    app.run();
    return 0;
}