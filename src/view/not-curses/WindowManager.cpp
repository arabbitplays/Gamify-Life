//
// Created by oschdi on 08.10.25.
//

#include "../../../include/view/not_curses/WindowManager.hpp"

#include "NotCursesCell.hpp"
#include "NotCursesCell.hpp"
#include "NotCursesCell.hpp"
#include "NotCursesCell.hpp"
#include "SizeErrorWindow.hpp"
#include "../../../include/view/not_curses/NotCursesCell.hpp"

WindowManager::WindowManager(const PlaneHandle& main_plane) {
    size_error_window = std::make_shared<SizeErrorWindow>(main_plane);
}

void WindowManager::addWindow(const WindowHandle &window) {
    windows.push_back(window);
}

void WindowManager::updateWindows(const glm::ivec2 screen_extent) const {
    if (!screenExtentIsBigEnough(screen_extent)) {
        hideAll();
        size_error_window->show();
        size_error_window->draw();
    } else {
        showAll();
        size_error_window->hide();
    }

    for (auto& window : windows) {
        glm::ivec2 new_pos, new_size;

        switch (window->getAlignment()) {
            case TOP_LEFT:
                new_size = glm::ivec2(ceil(screen_extent.x / 2.0), ceil(screen_extent.y / 2.0));
                new_pos = glm::ivec2(0, 0);
                break;
            case TOP_RIGHT:
                new_size = glm::ivec2(floor(screen_extent.x / 2.0), ceil(screen_extent.y / 2.0));
                new_pos = glm::ivec2(screen_extent.x - new_size.x, 0);
                break;
            case BOTTOM_LEFT:
                new_size = glm::ivec2(ceil(screen_extent.x / 2.0), floor(screen_extent.y / 2.0));
                new_pos = glm::ivec2(0, screen_extent.y - new_size.y);
                break;
            case BOTTOM_RIGHT:
                new_size = glm::ivec2(floor(screen_extent.x / 2.0), floor(screen_extent.y / 2.0));
                new_pos = glm::ivec2(screen_extent.x - new_size.x, screen_extent.y - new_size.y);
                break;
            default:
                new_pos = glm::ivec2(0);
                new_size = screen_extent;
        }

        window->move(new_pos);
        window->resize(new_size);
    }
}

void WindowManager::hideAll() const {
    for (auto& window : windows) {
        window->hide();
    }
}

void WindowManager::showAll() const {
    for (auto& window : windows) {
        window->show();
    }
}

bool WindowManager::screenExtentIsBigEnough(const glm::ivec2 screen_extent) const {
    auto min_screen_extent = glm::ivec2(0);
    for (auto& window : windows) {
        min_screen_extent += window->getMinExtent();
    }
    return min_screen_extent.x <= screen_extent.x && min_screen_extent.y <= screen_extent.y;
}