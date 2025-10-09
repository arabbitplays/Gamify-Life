//
// Created by oschdi on 06.10.25.
//

#include "view/not_curses/NotCursesPlane.hpp"

struct BoxCells {
    CellHandle tl, tr, bl, br;
    CellHandle vl, hl;
};

constexpr uint32_t BOX_FLAGS_NO_SIDES = NCBOXMASK_TOP | NCBOXMASK_RIGHT | NCBOXMASK_BOTTOM | NCBOXMASK_LEFT;

NotCursesPlane::NotCursesPlane(ncplane *handle) : handle(handle) {
}

NotCursesPlane::NotCursesPlane(const PlaneHandle& parent_plane, glm::ivec2 extent) {
    const ncplane_options opts = {
        .y = 0, .x = 0,
        .rows = static_cast<uint32_t>(extent.y), .cols = static_cast<uint32_t>(extent.x),
    };

    handle = ncplane_create(parent_plane->getNcHandle(), &opts);
    setForegroundColor(DEFAULT);
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
    ncplane_set_fg_alpha(handle, NCALPHA_OPAQUE);
}

void NotCursesPlane::setBackgroundColor(const uint color_index) const {
    ncplane_set_bg_palindex(handle, color_index);
}

void NotCursesPlane::drawCell(const CellHandle &cell, glm::ivec2 pos) const {
    setCursorPos(pos);
    ncplane_putc(handle, cell->getNcHandle());
}

void NotCursesPlane::writeText(const glm::ivec2 pos, const std::string &text, int32_t color, int32_t style_bits) const {
    setCursorPos(pos);
    addStyles(style_bits);
    setForegroundColor(color);
    ncplane_putstr(handle, text.c_str());
    removeAllStyles();
    setForegroundColor(DEFAULT);
}

void NotCursesPlane::drawHorizontalLine(const CellHandle &cell, glm::ivec2 pos, uint32_t length) const {
    glm::ivec2 curr_pos = pos;
    for (uint32_t i = 0; i < length; i++) {
        drawCell(cell, curr_pos);
        curr_pos.x++;
    }
    setCursorPos(curr_pos);
}

void NotCursesPlane::drawVerticalLine(const CellHandle &cell, glm::ivec2 pos, uint32_t length) const {
    glm::ivec2 curr_pos = pos;
    for (uint32_t i = 0; i < length; i++) {
        drawCell(cell, curr_pos);
        curr_pos.y++;
    }
    setCursorPos(curr_pos);
}

void NotCursesPlane::drawBox(const glm::ivec2 pos, const glm::ivec2 extent, const int32_t color, const int32_t style_bits) const {
    assert(extent.x >= 2 && extent.y >= 2);
    CellHandle styling_cell = std::make_shared<NotCursesCell>();
    styling_cell->setForegroundColor(color);

    BoxCells cells = loadRoundedBoxCells(styling_cell);

    drawCell(cells.tl, pos + glm::ivec2(0, 0));
    drawCell(cells.tr, pos + glm::ivec2(extent.x - 1, 0));
    drawCell(cells.bl, pos + glm::ivec2(0, extent.y - 1));
    drawCell(cells.br, pos + glm::ivec2(extent.x - 1, extent.y - 1));

    drawVerticalLine(cells.vl, pos + glm::ivec2(0, 1), extent.y - 2);
    drawVerticalLine(cells.vl, pos + glm::ivec2(extent.x - 1, 1), extent.y - 2);

    drawHorizontalLine(cells.hl, pos + glm::ivec2(1, 0), extent.x - 2);
    drawHorizontalLine(cells.hl, pos + glm::ivec2(1, extent.y - 1), extent.x - 2);
}

void NotCursesPlane::drawPerimeter(const int32_t color, const int32_t style_bits) const {
    glm::ivec2 extent = getExtent();
    drawBox(glm::ivec2(0), glm::ivec2(extent.x, extent.y), color, style_bits);
}

glm::ivec2 NotCursesPlane::getExtent() const {
    uint32_t width, height;
    ncplane_dim_yx(handle, &height, &width);
    return {width, height};
}

void NotCursesPlane::setCursorPos(glm::ivec2 pos) const {
    ncplane_cursor_move_yx(handle, pos.y, pos.x);
}

void NotCursesPlane::addStyles(const int32_t style_bits) const {
    if (style_bits & BOLD)
        ncplane_on_styles(handle, NCSTYLE_BOLD);
    if (style_bits & ITALIC)
        ncplane_on_styles(handle, NCSTYLE_ITALIC);
    if (style_bits & STRUCK)
        ncplane_on_styles(handle, NCSTYLE_STRUCK);
    if (style_bits & UNDERLINE)
        ncplane_on_styles(handle, NCSTYLE_UNDERLINE);
}

void NotCursesPlane::removeAllStyles() const {
    ncplane_off_styles(handle, NCSTYLE_MASK);
}

void NotCursesPlane::loadCell(const CellHandle& cell) const {
    nccell_load(handle, cell->getNcHandle(), cell->character);

}

NotCursesPlane::BoxCells NotCursesPlane::loadRoundedBoxCells(const CellHandle &styling_cell) const {
    BoxCells result;
    result.tl = std::make_shared<NotCursesCell>(styling_cell->getNcHandle()->stylemask, styling_cell->getNcHandle()->channels);
    result.tl->character = "╭";
    loadCell(result.tl);
    result.tr = std::make_shared<NotCursesCell>(styling_cell->getNcHandle()->stylemask, styling_cell->getNcHandle()->channels);
    result.tr->character = "╮";
    loadCell(result.tr);
    result.bl = std::make_shared<NotCursesCell>(styling_cell->getNcHandle()->stylemask, styling_cell->getNcHandle()->channels);
    result.bl->character = "╰";
    loadCell(result.bl);
    result.br = std::make_shared<NotCursesCell>(styling_cell->getNcHandle()->stylemask, styling_cell->getNcHandle()->channels);
    result.br->character = "╯";
    loadCell(result.br);

    result.hl = std::make_shared<NotCursesCell>(styling_cell->getNcHandle()->stylemask, styling_cell->getNcHandle()->channels);
    result.hl->character = "─";
    loadCell(result.hl);
    result.vl = std::make_shared<NotCursesCell>(styling_cell->getNcHandle()->stylemask, styling_cell->getNcHandle()->channels);
    result.vl->character = "│";
    loadCell(result.vl);

    return result;
}
