//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_WINDOWMANAGER_HPP
#define GAMIFY_LIFE_WINDOWMANAGER_HPP
#include <vector>

#include "windows/NotCursesWindow.hpp"


class WindowManager {
public:
    explicit WindowManager(const PlaneHandle& main_plane);

    void addWindow(const WindowHandle& window);

    void updateWindows(glm::ivec2 screen_extent) const;

private:
    bool screenExtentIsBigEnough(const glm::ivec2 screen_extent) const;

    void hideAll() const;
    void showAll() const;

    std::vector<WindowHandle> windows;
    WindowHandle size_error_window;
};


#endif //GAMIFY_LIFE_WINDOWMANAGER_HPP