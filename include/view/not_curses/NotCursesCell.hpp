#ifndef GAMIFY_LIFE_NOTCURSORCELL_HPP
#define GAMIFY_LIFE_NOTCURSORCELL_HPP
#include <memory>
#include <notcurses/notcurses.h>
#include <glm/glm.hpp>

enum StyleAttributes {
    NONE = 0,
    BOLD = 1 << 0,
    ITALIC = 1 << 1,
    UNDERLINE = 1 << 2,
    STRUCK = 1 << 3
};

enum Color {
    DEFAULT = 255,
    ERROR = 1,
    SELECTED = 2,
};

class NotCursesCell;
typedef std::shared_ptr<NotCursesCell> CellHandle;

class NotCursesCell {
public:
    NotCursesCell();
    NotCursesCell(uint16_t style_mask, uint64_t channels);

    void setForegroundColor(uint32_t color_index);
    void setBackgroundColor(uint32_t color_index);
    void addStyles(int32_t style_bits) const;

    nccell* getNcHandle() const;


    glm::ivec2 pos = glm::ivec2(0);
    const char * character = "\u0000"; // utf-8 encoded character
private:
    std::shared_ptr<nccell> handle{};
};


#endif //GAMIFY_LIFE_NOTCURSORCELL_HPP