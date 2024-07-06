#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "spdlog/spdlog.h"
#include "Application.h"
#include "AppState.h"
#include "Shader/Shader.h"
#include "Utils/GlenConstants.h"
#include "Error/GLError.h"

Application* Application::instance = nullptr;

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        getInstance()->state = AppState::HALTED;
    }
}

Application* Application::getInstance() {
    if(instance == nullptr)
        instance = new Application();
    return instance;
}

Application::Application() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", 0, 0);
    glfwMakeContextCurrent(window);
    if (window == nullptr)
    {
        spdlog::error("Could not initialize GLFW");
        glfwTerminate();
        state = AppState::FAILED;
        return;
    }
    spdlog::info("GLFW initialized without error");

    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        spdlog::error("Could not intialize GLEW");
        state = AppState::FAILED;
        return;
    }
    spdlog::info("GLEW initialized without error");

    glc(glViewport(0, 0, WIDTH, HEIGHT));
}

Application::~Application() {
    delete instance;
}


void Application::run() {

    const float vertices[12] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };
    const unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint varr;
    glc(glGenVertexArrays(1, &varr));
    glc(glBindVertexArray(varr));

    GLuint vbuf;
    glc(glGenBuffers(1, &vbuf));
    glc(glBindBuffer(GL_ARRAY_BUFFER, vbuf));
    glc(glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW));

    GLuint ebuf;
    glc(glGenBuffers(1, &ebuf));
    glc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuf));
    glc(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    glc(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));
    glc(glEnableVertexAttribArray(0));

    Shader shader = Shader::parse("shader.vert", "shader.frag");

    while (state == AppState::RUNNING) {
        const double currentTime = glfwGetTime();
        deltaTime = currentTime - time;
        time = currentTime;
        fps = 1.0 / deltaTime;

        shader.attach();
        glc(glBindVertexArray(varr));
        glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        glfwSwapBuffers(window);
        glfwPollEvents();
        if(glfwWindowShouldClose(window)) state = AppState::HALTED;
    }
    spdlog::info("Glen exited at state {}", toString(state));
}




