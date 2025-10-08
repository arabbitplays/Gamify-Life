//
// Created by oschdi on 06.10.25.
//

#include "../../../include/view/not_curses/NotCursesPlane.hpp"

constexpr uint32_t BOX_FLAGS_NO_SIDES = NCBOXMASK_TOP | NCBOXMASK_RIGHT | NCBOXMASK_BOTTOM | NCBOXMASK_LEFT;

NotCursesPlane::NotCursesPlane(ncplane *handle) : handle(handle) {
}

NotCursesPlane::NotCursesPlane(const PlaneHandle& parent_plane, glm::ivec2 extent) {
    const ncplane_options opts = {
        .y = 0, .x = 0,
        .rows = static_cast<uint32_t>(extent.y), .cols = static_cast<uint32_t>(extent.x),
    };

    handle = ncplane_create(parent_plane->getNcHandle(), &opts);
}

void NotCursesPlane::move(const glm::ivec2 pos) const {
    ncplane_move_yx(handle, pos.y, pos.x);
}

void NotCursesPlane::resize(const glm::ivec2 new_size) const {
    ncplane_resize_simple(handle, new_size.y, new_size.x);
}

void NotCursesPlane::erase() const {
    ncplane_erase(handle);
}

void NotCursesPlane::reparent(const PlaneHandle& new_parent) const {
    if (new_parent) {
        ncplane_reparent_family(handle, new_parent->getNcHandle());
    } else {
        // TODO use this for hiding if possible
        ncplane_reparent_family(handle, NULL);
    }
}

void NotCursesPlane::setForegroundColor(const uint color_index) const {
    ncplane_set_fg_palindex(handle, color_index);
}

void NotCursesPlane::setBackgroundColor(const uint color_index) const {
    ncplane_set_bg_palindex(handle, color_index);
}

void NotCursesPlane::drawCell(const CellHandle &cell) const {
    loadCell(cell);
    ncplane_putc_yx(handle, cell->pos.y, cell->pos.x, cell->getNcHandle());
}

void NotCursesPlane::writeText(const glm::ivec2 pos, const std::string &text) const {
    setCursorPos(pos);
    ncplane_putstr(handle, text.c_str());
}

void NotCursesPlane::drawHorizontalLine(const CellHandle &cell, uint32_t length) const {
    loadCell(cell);
    setCursorPos(cell->pos);
    ncplane_hline(handle, cell->getNcHandle(), length);
}

void NotCursesPlane::drawVerticalLine(const CellHandle &cell, uint32_t length) const {
    loadCell(cell);
    setCursorPos(cell->pos);
    ncplane_vline(handle, cell->getNcHandle(), length);
}

void NotCursesPlane::drawBox(const CellHandle &cell, glm::ivec2 extent) const {
    setCursorPos(cell->pos);
    ncplane_rounded_box(handle, cell->getNcHandle()->stylemask, cell->getNcHandle()->channels, cell->pos.y + extent.y - 1, cell->pos.x + extent.x - 1, 0);
}

void NotCursesPlane::drawPerimeter(const CellHandle &cell) const {
    setCursorPos(glm::ivec2(0));
    glm::ivec2 extent = getExtent();
    ncplane_rounded_box(handle, cell->getNcHandle()->stylemask, cell->getNcHandle()->channels, extent.y - 1, extent.x - 1, 0);
}

glm::ivec2 NotCursesPlane::getExtent() const {
    uint32_t width, height;
    ncplane_dim_yx(handle, &height, &width);
    return {width, height};
}

void NotCursesPlane::setCursorPos(glm::ivec2 pos) const {
    ncplane_cursor_move_yx(handle, pos.y, pos.x);
}

void NotCursesPlane::loadCell(const CellHandle& cell) const {
    nccell_load(handle, cell->getNcHandle(), cell->character);

}
