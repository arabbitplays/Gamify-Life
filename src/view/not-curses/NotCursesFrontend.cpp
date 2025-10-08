//
// Created by oschdi on 06.10.25.
//

#include "../../../include/view/not_curses/NotCursesFrontend.hpp"

#include "windows/TaskWindow.hpp"

void NotCursesFrontend::init(const std::shared_ptr<AppController>& app_controller) {
    instance = std::make_shared<NotCursesInstance>();
    main_plane = instance->getStdPlane();
    window_manager = std::make_shared<WindowManager>(main_plane);

    createWindow(glm::ivec2(10, 10), TOP_LEFT);
    auto window = std::make_shared<TaskWindow>(app_controller->task_controller, main_plane, TOP_RIGHT);
    windows.push_back(window);
    window_manager->addWindow(window);
    createWindow(glm::ivec2(10, 10), BOTTOM_LEFT);
    createWindow(glm::ivec2(10, 10), BOTTOM_RIGHT);


    instance->render();
}

void NotCursesFrontend::run() {
    while (!stopped) {
        window_manager->updateWindows(main_plane->getExtent());
        for (const auto& window : windows) {
            window->draw();
        }

        handleInput();
        instance->render();
    }
}

void NotCursesFrontend::handleInput() {
    timespec delay = { .tv_sec = 0, .tv_nsec = 16 * 1000 * 1000 }; // ~60 FPS

    ncinput ni;
    notcurses_get(instance->getHandle(), &delay, &ni);

    // Check if the event was a keypress and if the key was 'q'
    if (ni.evtype == NCTYPE_PRESS && ni.id == 'q') {
        stopped = true;
    }

    if (ni.evtype == NCTYPE_PRESS && ni.id == 'a') {
        windows.at(0)->hide();
    }

    if (ni.evtype == NCTYPE_PRESS && ni.id == 'd') {
        windows.at(0)->show();
    }
}

void NotCursesFrontend::stop() {
    instance->destroy();
}

void NotCursesFrontend::createWindow(glm::ivec2 min_extent, WindowAlignment alignment) {
    auto window = std::make_shared<NotCursesWindow>(main_plane, min_extent, alignment);

    windows.push_back(window);
    window_manager->addWindow(window);
}
