//
// Created by oschdi on 06.10.25.
//

#include "../../../include/view/not_curses/NotCursesFrontend.hpp"

void NotCursesFrontend::init() {
    instance = std::make_shared<NotCursesInstance>();
    main_plane = instance->getStdPlane();

    main_plane->test();
    instance->render();
}

void NotCursesFrontend::run() {
    while (!stopped) {
        handleInput();
        instance->render();
    }
}

void NotCursesFrontend::handleInput() {
    ncinput ni;
    notcurses_get(instance->getHandle(), nullptr, &ni);

    // Check if the event was a keypress and if the key was 'q'
    if (ni.evtype == NCTYPE_PRESS && ni.id == 'q') {
        stopped = true;
    }
}

void NotCursesFrontend::stop() {
    instance->destroy();
}
