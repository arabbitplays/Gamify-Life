//
// Created by oschdi on 06.10.25.
//

#include "../../../include/view/not_curses/NotCursesInstance.hpp"

#include <stdexcept>

NotCursesInstance::NotCursesInstance() {
    if(!setlocale(LC_ALL, "")){
        throw std::runtime_error("Setting locale failed!");
    }

    notcurses_options opts{};
    setenv("NOTCURSES_LOGLEVEL", "trace", 1);
    handle = notcurses_init(&opts, NULL);
    if (!handle) {
        throw std::runtime_error("Failed to initialize Notcurses\n");
    }

    std_plane_handle = notcurses_stdplane(handle);
}

void NotCursesInstance::render() {
    notcurses_render(handle);
}

PlaneHandle NotCursesInstance::getStdPlane() {
    return std::make_shared<NotCursesPlane>(std_plane_handle);
}

void NotCursesInstance::destroy() {
    notcurses_stop(handle);
}
