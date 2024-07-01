#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>
#include "AppState.h"

class Application {
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

    double deltaTime = 0.0, fps = 0.0, time = 0.0;
    GLFWwindow* window = nullptr;
    Application();
    ~Application();
    static Application* instance;
public:
    AppState::AppState state = AppState::RUNNING;
    static Application* getInstance();
    void run();
};

#endif //APPLICATION_H


