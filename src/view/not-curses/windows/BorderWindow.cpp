//
// Created by oschdi on 09.10.25.
//

#include "../../../../include/view/not_curses/windows/BorderWindow.hpp"

BorderWindow::BorderWindow(const std::string &name, const PlaneHandle &parent_plane, const glm::ivec2 min_extent,
                           const WindowAlignment alignment, Color border_color) : NotCursesWindow(parent_plane, min_extent, alignment), name(name), border_color(border_color) {
}

void BorderWindow::draw() {
    NotCursesWindow::draw();
    std::string space = " ";
    const int32_t border_color_idx = border_color;

    border_plane->drawPerimeter(border_color_idx);
    border_plane->writeText(glm::ivec2(NAME_OFFSET, 0), LEFT_NAME_SEPARATOR + space + name + space + RIGHT_NAME_SEPARATOR, border_color_idx);
    border_plane->writeText(glm::ivec2(NAME_OFFSET + 2, 0), name, DEFAULT, BOLD);
}
