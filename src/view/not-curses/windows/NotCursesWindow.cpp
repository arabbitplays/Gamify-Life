//
// Created by oschdi on 08.10.25.
//

#include "view/not_curses/windows/NotCursesWindow.hpp"

NotCursesWindow::NotCursesWindow(const PlaneHandle &parent_plane, const glm::ivec2 min_extent, const WindowAlignment alignment)
    : parent_plane(parent_plane), min_extent(min_extent), alignment(alignment) {
    border_plane = createPlane(parent_plane, min_extent);
    content_plane = createPlane(border_plane, min_extent - glm::ivec2(2, 2));
    content_plane->move(glm::ivec2(1, 1));
}

void NotCursesWindow::draw() {
    border_plane->erase();
    content_plane->erase();
}

WindowAlignment NotCursesWindow::getAlignment() const {
    return alignment;
}

void NotCursesWindow::move(const glm::ivec2 pos) const {
    border_plane->move(pos);
}

void NotCursesWindow::resize(const glm::ivec2 new_size) const {
    border_plane->resize(new_size);
    content_plane->resize(new_size - glm::ivec2(2, 2) - 2 * margin);
}

void NotCursesWindow::hide() {
    border_plane->erase();
    content_plane->erase();
    hidden = true;
}

void NotCursesWindow::show() {
    //plane->reparent(parent_plane);
    hidden = false;
}

glm::ivec2 NotCursesWindow::getMinExtent() const {
    return min_extent;
}

bool NotCursesWindow::isHidden() const {
    return hidden;
}

PlaneHandle NotCursesWindow::createPlane(const PlaneHandle &parent_plane, const glm::ivec2 extent) {
    return std::make_shared<NotCursesPlane>(parent_plane, extent);
}

void NotCursesWindow::setMargin(glm::ivec2 new_margin) {
    margin = new_margin;
    content_plane->move(glm::ivec2(1, 1) + margin);
}

void NotCursesWindow::drawControlTips(const std::vector<std::string> &tips) const {
    if (tips.empty())
        return;

    uint32_t longest_tipp_len = tips.at(0).size();
    for (uint32_t i = 1; i < tips.size(); i++) {
        longest_tipp_len = std::max(longest_tipp_len, static_cast<uint32_t>(tips.at(i).size()));
    }

    const glm::ivec2 bottom_right_pos = content_plane->getExtent();
    for (uint32_t i = 0; i < tips.size(); i++) {
        content_plane->writeText(bottom_right_pos - glm::ivec2(longest_tipp_len, tips.size() - i), tips.at(i));
    }
}
