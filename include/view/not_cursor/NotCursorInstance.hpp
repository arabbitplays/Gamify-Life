//
// Created by oschdi on 06.10.25.
//

#ifndef GAMIFY_LIFE_NOTCURSORINSTANCE_HPP
#define GAMIFY_LIFE_NOTCURSORINSTANCE_HPP

#include <memory>
#include <notcurses/notcurses.h>

#include "NotCursorPlane.hpp"

class NotCursorInstance {
public:
    NotCursorInstance();

    void render();
    std::shared_ptr<NotCursorPlane> getStdPlane();
    void destroy();

    notcurses* getHandle() { return handle; }
private:
    notcurses* handle;
};


#endif //GAMIFY_LIFE_NOTCURSORINSTANCE_HPP