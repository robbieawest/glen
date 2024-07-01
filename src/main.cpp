#include <iostream>

#include "Application/Application.h"
#include "Application/AppState.h"
#include "Utils/MiscHelper.h"
#include "Utils/LogType.h"


int main() {
    Application* app = Application::getInstance();
    if(app->state == AppState::FAILED) return -1;
    //app->run();
    std::cout << helper::format("Sample format {}, hello {}", {"string", "world"});
    helper::log(LogType::INFO, __func__, "tryinng this out {} hey!", {"bastard"});

    return 0;
}
