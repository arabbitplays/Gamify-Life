//
// Created by oschdi on 06.10.25.
//

#ifndef GAMIFY_LIFE_NOTCURSORPLANE_HPP
#define GAMIFY_LIFE_NOTCURSORPLANE_HPP
#include <memory>
#include <notcurses/notcurses.h>

class NotCursorPlane {
public:
    explicit NotCursorPlane(ncplane* handle);

    void test() {
        ncplane_set_fg_rgb(handle, 0x00FFFF); // cyan
        ncplane_putstr(handle, "Moin Moin\n");
        ncplane_set_fg_default(handle);
    }
    ncplane* getHandle() { return handle; }

private:
    ncplane* handle;
};


#endif //GAMIFY_LIFE_NOTCURSORPLANE_HPP