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
    virtual ~NotCursesWindow() = default;

    virtual void draw() const;

    [[nodiscard]] WindowAlignment getAlignment() const;
    void move(glm::ivec2 pos) const;
    void resize(glm::ivec2 new_size) const;

    void hide();
    void show();

    [[nodiscard]] glm::ivec2 getMinExtent() const;
    [[nodiscard]] bool isHidden() const;

protected:
    static PlaneHandle createPlane(const PlaneHandle & parent_plane, const glm::ivec2 extent);

    static constexpr uint32_t LEFT_MARGIN = 2;

    PlaneHandle parent_plane;
    PlaneHandle plane;

    glm::ivec2 min_extent;
    WindowAlignment alignment;
    bool hidden = false;
};


#endif //GAMIFY_LIFE_WINDOW_HPP