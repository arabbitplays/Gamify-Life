//
// Created by oschdi on 06.10.25.
//

#ifndef GAMIFY_LIFE_NOTCURSORINSTANCE_HPP
#define GAMIFY_LIFE_NOTCURSORINSTANCE_HPP

#include <memory>
#include <notcurses/notcurses.h>

#include "NotCursesPlane.hpp"

class NotCursesInstance {
public:
    NotCursesInstance();

    void render();

    PlaneHandle createPlane(glm::ivec2 extent);
    PlaneHandle getStdPlane();

    void destroy();

    notcurses* getHandle() { return handle; }
private:
    ncplane* std_plane_handle;
    notcurses* handle;
};


#endif //GAMIFY_LIFE_NOTCURSORINSTANCE_HPP