#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "spdlog/spdlog.h"

#include "Application.h"
#include "GlenConstants.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

Application::Application() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", 0, 0);
    glfwMakeContextCurrent(window);
    if (window == nullptr)
    {
        spdlog::error("Could not initialize GLFW");
        glfwTerminate();
        validSession = false;
        return;
    }
    spdlog::info("GLFW initialized without error");

    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        spdlog::error("Could not intialize GLEW");
        validSession = false;
        return;
    }
    spdlog::info("GLEW initialized without error");

    glViewport(0, 0, WIDTH, HEIGHT);
}

void Application::run() {

}


