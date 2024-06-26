#ifndef APPLICATION_H
#define APPLICATION_H

#include "AppState.h"

class Application {
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

    double deltaTime = 0.0, fps = 0.0, time = 0.0;
    GLFWwindow* window = nullptr;
public:
    AppState::AppState state = AppState::RUNNING;
    Application();
    void run();
    void loop();
};

#endif //APPLICATION_H


