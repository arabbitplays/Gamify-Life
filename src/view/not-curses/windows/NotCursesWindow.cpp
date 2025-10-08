//
// Created by oschdi on 08.10.25.
//

#include "../../../../include/view/not_curses/windows/NotCursesWindow.hpp"

#include "NotCursesCell.hpp"

NotCursesWindow::NotCursesWindow(const PlaneHandle &parent_plane, const glm::ivec2 min_extent, const WindowAlignment alignment)
    : parent_plane(parent_plane), min_extent(min_extent), alignment(alignment) {
    plane = createPlane(parent_plane, min_extent);
}

void NotCursesWindow::draw() const {
    if (hidden)
        return;
    auto cell = std::make_shared<NotCursesCell>();
    plane->erase();
    plane->drawPerimeter(cell);
}

WindowAlignment NotCursesWindow::getAlignment() const {
    return alignment;
}

void NotCursesWindow::move(const glm::ivec2 pos) const {
    plane->move(pos);
}

void NotCursesWindow::resize(const glm::ivec2 new_size) const {
    plane->resize(new_size);
}

void NotCursesWindow::hide() {
    plane->erase();
    hidden = true;
}

void NotCursesWindow::show() {
    //plane->reparent(parent_plane);
    hidden = false;
}

glm::ivec2 NotCursesWindow::getMinExtent() const {
    return min_extent;
}

PlaneHandle NotCursesWindow::createPlane(const PlaneHandle &parent_plane, const glm::ivec2 extent) {
    return std::make_shared<NotCursesPlane>(parent_plane, extent);
}
