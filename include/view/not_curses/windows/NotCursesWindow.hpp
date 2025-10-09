//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_WINDOW_HPP
#define GAMIFY_LIFE_WINDOW_HPP
#include <memory>
#include <glm/vec2.hpp>

#include "view/not_curses/NotCursesPlane.hpp"


class NotCursesWindow;
typedef std::shared_ptr<NotCursesWindow> WindowHandle;

enum WindowAlignment {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
};

class NotCursesWindow {
public:
    NotCursesWindow(const PlaneHandle &parent_plane, glm::ivec2 min_extent, WindowAlignment alignment);
    virtual ~NotCursesWindow() = default;

    virtual void draw();
    virtual void handleInput([[maybe_unused]] ncinput input) {};

    [[nodiscard]] WindowAlignment getAlignment() const;
    void move(glm::ivec2 pos) const;
    void resize(glm::ivec2 new_size) const;

    void hide();
    void show();

    [[nodiscard]] glm::ivec2 getMinExtent() const;
    [[nodiscard]] bool isHidden() const;

protected:
    static PlaneHandle createPlane(const PlaneHandle & parent_plane, const glm::ivec2 extent);
    void setMargin(glm::ivec2 new_margin);

    PlaneHandle parent_plane;
    PlaneHandle border_plane;
    PlaneHandle content_plane;

    glm::ivec2 min_extent;
    glm::ivec2 margin{};
    WindowAlignment alignment;
    bool hidden = false;
};


#endif //GAMIFY_LIFE_WINDOW_HPP