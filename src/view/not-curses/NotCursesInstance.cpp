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
    handle = notcurses_init(&opts, nullptr);
    if (!handle) {
        throw std::runtime_error("Failed to initialize Notcurses\n");
    }
}

void NotCursesInstance::render() {
    notcurses_render(handle);
}

std::shared_ptr<NotCursesPlane> NotCursesInstance::getStdPlane() {
    ncplane* std_plane = notcurses_stdplane(handle);
    return std::make_shared<NotCursesPlane>(std_plane);
}

void NotCursesInstance::destroy() {
    notcurses_stop(handle);
}
