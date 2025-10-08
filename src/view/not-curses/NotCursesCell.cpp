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

void NotCursesCell::addStyles(const int32_t style_bits) const {
    if (style_bits & BOLD)
        nccell_on_styles(handle.get(), NCSTYLE_BOLD);
    if (style_bits & ITALIC)
        nccell_on_styles(handle.get(), NCSTYLE_ITALIC);
    if (style_bits & STRUCK)
        nccell_on_styles(handle.get(), NCSTYLE_STRUCK);
    if (style_bits & UNDERLINE)
        nccell_on_styles(handle.get(), NCSTYLE_UNDERLINE);
}

nccell * NotCursesCell::getNcHandle() const {
    return handle.get();
}
