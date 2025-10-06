//
// Created by oschdi on 06.10.25.
//

#include "../../../include/view/not_cursor/NotCursorFrontend.hpp"

void NotCursorFrontend::init() {
    instance = std::make_shared<NotCursorInstance>();
    main_plane = instance->getStdPlane();
    main_plane->test();
}

void NotCursorFrontend::render() {
    instance->render();
    ncinput ni;
    while (true) {
        notcurses_get(instance->getHandle(), nullptr, &ni);

        // Check if the event was a keypress and if the key was 'q'
        if (ni.evtype == NCTYPE_PRESS && ni.id == 'q') {
            break; // Exit the loop
        }
    }
}

void NotCursorFrontend::stop() {
    instance->destroy();
}
