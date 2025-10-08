#ifndef GAMIFY_LIFE_NOTCURSORCELL_HPP
#define GAMIFY_LIFE_NOTCURSORCELL_HPP
#include <memory>
#include <notcurses/notcurses.h>
#include <glm/glm.hpp>

class NotCursesCell;
typedef std::shared_ptr<NotCursesCell> CellHandle;

class NotCursesCell {
public:
    NotCursesCell();

    void setForegroundColor(uint32_t color_index);
    void setBackgroundColor(uint32_t color_index);

    nccell* getNcHandle();

    glm::ivec2 pos = glm::ivec2(0);
    const char * character = "\u0000"; // utf-8 encoded character
private:
    std::shared_ptr<nccell> handle{};
};


#endif //GAMIFY_LIFE_NOTCURSORCELL_HPP