#include <iostream>
#include <memory>

#include "controller/TaskController.hpp"
#include "model/Profile.hpp"
#include "view/IFrontend.hpp"
#include "view/not_curses/NotCursesFrontend.hpp"

int main(int argc, char *argv[]) {
    auto app_controller = std::make_shared<AppController>();
    FrontendHandle frontend = std::make_shared<NotCursesFrontend>();
    try {
        frontend->init(app_controller);
        frontend->run();
    } catch (const std::exception& e) {
        fprintf(stderr, "%s", e.what());
        frontend->stop();
    }

    frontend->stop();

    return 0;
}
