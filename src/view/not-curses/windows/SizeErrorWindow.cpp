//
// Created by oschdi on 08.10.25.
//

#include "../../../../include/view/not_curses/windows/SizeErrorWindow.hpp"

void SizeErrorWindow::draw() const {
    border_plane->erase();
    border_plane->resize(parent_plane->getExtent());
    border_plane->writeText(glm::ivec2(0), "Window too small!", ERROR);
}
