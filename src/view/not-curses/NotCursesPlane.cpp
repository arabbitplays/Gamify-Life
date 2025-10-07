//
// Created by oschdi on 06.10.25.
//

#include "../../../include/view/not_curses/NotCursesPlane.hpp"

NotCursesPlane::NotCursesPlane(ncplane *handle) : handle(handle) {
}

void NotCursesPlane::setForegroundColor(const uint color_index) const {
    ncplane_set_fg_palindex(handle, color_index);
}

void NotCursesPlane::setBackgroundColor(const uint color_index) const {
    ncplane_set_bg_palindex(handle, color_index);
}

void NotCursesPlane::drawCell(const CellHandle &cell) {
    ncplane_putc_yx(handle, cell->pos.y, cell->pos.x, cell->getNcHandle());
}