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

template<typename T>
concept DerivedFromWindow = std::is_base_of_v<NotCursesWindow, T>;

class NotCursesFrontend : public IFrontend {
public:
    NotCursesFrontend() = default;

    void init(const std::shared_ptr<AppController>& app_controller) override;
    void run() override;

    void handleInput();

    void stop() override;

private:

    template<DerivedFromWindow T, typename... Args>
    std::shared_ptr<T> createWindow(Args&&... args) {
        std::shared_ptr<T> window = std::make_shared<T>(std::forward<Args>(args)...);
        windows.push_back(window);
        window_manager->addWindow(window);
        return window;
    }

    std::shared_ptr<NotCursesInstance> instance;
    PlaneHandle main_plane;

    std::shared_ptr<WindowManager> window_manager;

    std::vector<WindowHandle> windows;

    bool stopped = false;
};


#endif //GAMIFY_LIFE_NOTCURSORFRONTEND_HPP