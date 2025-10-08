//
// Created by oschdi on 06.10.25.
//

#ifndef GAMIFY_LIFE_NOTCURSORFRONTEND_HPP
#define GAMIFY_LIFE_NOTCURSORFRONTEND_HPP
#include <vector>

#include "NotCursesInstance.hpp"
#include "windows/NotCursesWindow.hpp"
#include "WindowManager.hpp"
#include "view/IFrontend.hpp"


class NotCursesFrontend : public IFrontend {
public:
    NotCursesFrontend() = default;

    void init(const std::shared_ptr<AppController>& app_controller) override;
    void run() override;

    void handleInput();

    void stop() override;

private:
    void createWindow(glm::ivec2 min_extent, WindowAlignment alignment);

    std::shared_ptr<NotCursesInstance> instance;
    PlaneHandle main_plane;

    std::shared_ptr<WindowManager> window_manager;

    std::vector<WindowHandle> windows;

    bool stopped = false;
};


#endif //GAMIFY_LIFE_NOTCURSORFRONTEND_HPP