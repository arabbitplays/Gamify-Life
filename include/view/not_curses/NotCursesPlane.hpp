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

class NotCursesPlane {
public:
    explicit NotCursesPlane(ncplane* handle);
    NotCursesPlane(const PlaneHandle& parent_plane, glm::ivec2 extent);

    void test() {
        setForegroundColor(1);
        setBackgroundColor(2);

        setCursorPos(glm::ivec2(1, 1));
        ncplane_putstr(handle, "Moin Moin\n");

        CellHandle cell1 = std::make_shared<NotCursesCell>();
        cell1->character = "X";
        cell1->pos = glm::ivec2(3, 0);
        drawCell(cell1);
        cell1->character = HORIZONTAL_DOTTED_LINE_CHARACTER;
        cell1->pos = glm::ivec2(10, 10);
        drawHorizontalLine(cell1, 10);
        drawVerticalLine(cell1, 10);

        cell1->pos = glm::ivec2(15, 15);
        drawBox(cell1, glm::ivec2(2, 2));

        drawPerimeter(cell1);

        ncplane_set_fg_default(handle);
    }

    void move(glm::ivec2 pos) const;
    void resize(glm::ivec2 new_size) const;
    void erase() const;
    void reparent(const PlaneHandle& new_parent) const;

    void setForegroundColor(uint32_t color_index) const;
    void setBackgroundColor(uint32_t color_index) const;
    void drawCell(const CellHandle& cell) const;
    void writeText(glm::ivec2 pos, const std::string &text) const;
    void drawHorizontalLine(const CellHandle& cell, uint32_t length) const;
    void drawVerticalLine(const CellHandle& cell, uint32_t length) const;
    void drawBox(const CellHandle& cell, glm::ivec2 extent) const;
    void drawPerimeter(const CellHandle &cell) const;

    ncplane* getNcHandle() { return handle; }
    glm::ivec2 getExtent() const;
private:
    void setCursorPos(glm::ivec2 pos) const;

    void loadCell(const CellHandle &cell) const;

    ncplane* handle;
};


#endif //GAMIFY_LIFE_NOTCURSORPLANE_HPP