#include <iostream>
#include <memory>

#include "Profile.hpp"
#include "controller/TaskController.hpp"
#include "view/IFrontend.hpp"
#include "view/not_curses/NotCursesFrontend.hpp"

int main(int argc, char *argv[]) {
    const auto profile = std::make_shared<Profile>("Oschdi");
    auto app_controller = std::make_shared<AppController>();
    app_controller->task_controller = std::make_shared<TaskController>();

    std::vector<TaskHandle> tasks = app_controller->task_controller->getAvailableTasks();
    profile->addDoneTaskToday(tasks.at(0));

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
