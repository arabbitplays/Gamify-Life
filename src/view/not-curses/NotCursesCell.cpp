//
// Created by oschdi on 07.10.25.
//

#include "../../../include/view/not_curses/NotCursesCell.hpp"

NotCursesCell::NotCursesCell() {
    handle = std::make_shared<nccell>();
}

void NotCursesCell::setForegroundColor(uint32_t color_index) {
    nccell_set_fg_palindex(handle.get(), color_index);
}

void NotCursesCell::setBackgroundColor(uint32_t color_index) {
    nccell_set_bg_palindex(handle.get(), color_index);
}

nccell * NotCursesCell::getNcHandle() {
    return handle.get();
}
