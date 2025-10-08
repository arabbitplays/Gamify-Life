//
// Created by oschdi on 09.10.25.
//

#include "../../../../include/view/not_curses/windows/BorderWindow.hpp"

BorderWindow::BorderWindow(const std::string &name, const PlaneHandle &parent_plane, const glm::ivec2 min_extent,
                           const WindowAlignment alignment) : NotCursesWindow(parent_plane, min_extent, alignment), name(name) {
}

void BorderWindow::draw() const {
    NotCursesWindow::draw();
    plane->writeText(glm::ivec2(NAME_OFFSET, 0), LEFT_NAME_SEPARATOR + name + RIGHT_NAME_SEPARATOR);
}

