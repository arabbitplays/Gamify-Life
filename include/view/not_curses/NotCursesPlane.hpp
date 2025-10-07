//
// Created by oschdi on 06.10.25.
//

#ifndef GAMIFY_LIFE_NOTCURSORPLANE_HPP
#define GAMIFY_LIFE_NOTCURSORPLANE_HPP
#include <memory>
#include <notcurses/notcurses.h>

#include "NotCursesCell.hpp"

class NotCursesPlane {
public:
    explicit NotCursesPlane(ncplane* handle);

    void test() {
        setForegroundColor(1);
        setBackgroundColor(2);

        ncplane_putstr(handle, "Moin Moin\n");

        CellHandle cell1 = std::make_shared<NotCursesCell>();
        cell1->setChar('X');
        cell1->pos = glm::ivec2(10, 10);
        drawCell(cell1);
        cell1->setChar('Y');
        cell1->pos = glm::ivec2(3, 0);
        drawCell(cell1);

        ncplane_set_fg_default(handle);
    }

    void setForegroundColor(uint32_t color_index) const;
    void setBackgroundColor(uint32_t color_index) const;
    void drawCell(const CellHandle& cell);

    ncplane* getNcHandle() { return handle; }

private:
    ncplane* handle;
};


#endif //GAMIFY_LIFE_NOTCURSORPLANE_HPP