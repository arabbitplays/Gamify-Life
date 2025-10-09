//
// Created by oschdi on 06.10.25.
//

#ifndef GAMIFY_LIFE_NOTCURSORPLANE_HPP
#define GAMIFY_LIFE_NOTCURSORPLANE_HPP
#include <memory>
#include <notcurses/notcurses.h>

#include "NotCursesCell.hpp"

static constexpr auto HORIZONTAL_DOTTED_LINE_CHARACTER = "\u2504";

class NotCursesPlane;
typedef std::shared_ptr<NotCursesPlane> PlaneHandle;

class NotCursesPlane : public std::enable_shared_from_this<NotCursesPlane> {
public:
    explicit NotCursesPlane(ncplane* handle);
    NotCursesPlane(const PlaneHandle& parent_plane, glm::ivec2 extent);

    void move(glm::ivec2 pos) const;
    void resize(glm::ivec2 new_size) const;
    void erase() const;
    void reparent(const PlaneHandle& new_parent) const;

    void setForegroundColor(uint32_t color_index) const;
    void setBackgroundColor(uint32_t color_index) const;
    void drawCell(const CellHandle& cell, glm::ivec2 pos) const;
    void writeText(glm::ivec2 pos, const std::string &text, int32_t color = DEFAULT, int32_t style_bits = NONE) const;
    void drawHorizontalLine(const CellHandle& cell, glm::ivec2 pos, uint32_t length) const;
    void drawVerticalLine(const CellHandle& cell, glm::ivec2 pos, uint32_t length) const;
    void drawBox(glm::ivec2 pos, glm::ivec2 extent, int32_t color = DEFAULT, int32_t style_bits = NONE) const;
    void drawPerimeter(int32_t color = DEFAULT, int32_t style_bits = NONE) const;

    ncplane* getNcHandle() { return handle; }
    glm::ivec2 getExtent() const;
private:
    void setCursorPos(glm::ivec2 pos) const;
    void addStyles(int32_t style_bits) const;
    void removeAllStyles() const;

    void loadCell(const CellHandle &cell) const;

    struct BoxCells {
        CellHandle tl, tr, bl, br;
        CellHandle vl, hl;
    };

    BoxCells loadRoundedBoxCells(const CellHandle &styling_cell) const;

    ncplane* handle;
};


#endif //GAMIFY_LIFE_NOTCURSORPLANE_HPP