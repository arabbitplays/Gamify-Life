//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_WINDOW_HPP
#define GAMIFY_LIFE_WINDOW_HPP
#include <memory>

class NotCursesWindow;
typedef std::shared_ptr<NotCursesWindow> WindowHandle;

class NotCursesWindow {
public:
    NotCursesWindow() = default;
};


#endif //GAMIFY_LIFE_WINDOW_HPP