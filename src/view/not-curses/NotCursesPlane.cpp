//
// Created by oschdi on 06.10.25.
//

#include "../../../include/view/not_curses/NotCursesPlane.hpp"

constexpr uint32_t BOX_FLAGS_NO_SIDES = NCBOXMASK_TOP | NCBOXMASK_RIGHT | NCBOXMASK_BOTTOM | NCBOXMASK_LEFT;

NotCursesPlane::NotCursesPlane(ncplane *handle) : handle(handle) {
}

NotCursesPlane::NotCursesPlane(ncplane *std_plane, glm::ivec2 extent) {
    ncplane_options opts = {
        .y = 2, .x = 20,        // position
        .rows = static_cast<uint32_t>(extent.y), .cols = static_cast<uint32_t>(extent.y),
    };

    handle = ncplane_create(std_plane, &opts);
}

void NotCursesPlane::setForegroundColor(const uint color_index) const {
    ncplane_set_fg_palindex(handle, color_index);
}

void NotCursesPlane::setBackgroundColor(const uint color_index) const {
    ncplane_set_bg_palindex(handle, color_index);
}

void NotCursesPlane::drawCell(const CellHandle &cell) {
    loadCell(cell);
    ncplane_putc_yx(handle, cell->pos.y, cell->pos.x, cell->getNcHandle());
}

void NotCursesPlane::drawHorizontalLine(const CellHandle &cell, uint32_t length) {
    loadCell(cell);
    setCursorPos(cell->pos);
    ncplane_hline(handle, cell->getNcHandle(), length);
}

void NotCursesPlane::drawVerticalLine(const CellHandle &cell, uint32_t length) {
    loadCell(cell);
    setCursorPos(cell->pos);
    ncplane_vline(handle, cell->getNcHandle(), length);
}

void NotCursesPlane::drawBox(const CellHandle &cell, glm::ivec2 extent) {
    setCursorPos(cell->pos);
    ncplane_rounded_box(handle, cell->getNcHandle()->stylemask, cell->getNcHandle()->channels, extent.y, extent.x, 0);
}

void NotCursesPlane::setCursorPos(glm::ivec2 pos) {
    ncplane_cursor_move_yx(handle, pos.y, pos.x);
}

void NotCursesPlane::loadCell(const CellHandle& cell) {
    nccell_load(handle, cell->getNcHandle(), cell->character);

}
