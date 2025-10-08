//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_WINDOW_HPP
#define GAMIFY_LIFE_WINDOW_HPP
#include <memory>
#include <glm/vec2.hpp>

#include "../NotCursesInstance.hpp"

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

    virtual void draw() const;

    WindowAlignment getAlignment() const;
    void move(glm::ivec2 pos) const;
    void resize(glm::ivec2 new_size) const;

    void hide();
    void show();

    glm::ivec2 getMinExtent() const;

protected:
    static PlaneHandle createPlane(const PlaneHandle & parent_plane, const glm::ivec2 extent);

    PlaneHandle parent_plane;
    PlaneHandle plane;

    glm::ivec2 min_extent;
    WindowAlignment alignment;
    bool hidden = false;
};


#endif //GAMIFY_LIFE_WINDOW_HPP