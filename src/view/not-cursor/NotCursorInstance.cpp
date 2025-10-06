//
// Created by oschdi on 06.10.25.
//

#include "../../../include/view/not_cursor/NotCursorInstance.hpp"

#include <stdexcept>

NotCursorInstance::NotCursorInstance() {
    if(!setlocale(LC_ALL, "")){
        throw std::runtime_error("Setting locale failed!");
    }

    notcurses_options opts{};
    handle = notcurses_init(&opts, nullptr);
    if (!handle) {
        throw std::runtime_error("Failed to initialize Notcurses\n");
    }
}

void NotCursorInstance::render() {
    notcurses_render(handle);
}

std::shared_ptr<NotCursorPlane> NotCursorInstance::getStdPlane() {
    ncplane* std_plane = notcurses_stdplane(handle);
    return std::make_shared<NotCursorPlane>(std_plane);
}

void NotCursorInstance::destroy() {
    notcurses_stop(handle);
}
