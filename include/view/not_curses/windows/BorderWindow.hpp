//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_BORDERWINDOW_HPP
#define GAMIFY_LIFE_BORDERWINDOW_HPP
#include "NotCursesWindow.hpp"

class BorderWindow : public NotCursesWindow {
public:
    BorderWindow(const std::string& name, const PlaneHandle &parent_plane, glm::ivec2 min_extent, WindowAlignment alignment);
    void draw() override;

protected:
    std::string name;
    bool active = false;

private:
    static constexpr uint32_t NAME_OFFSET = 5;
    static constexpr char* RIGHT_NAME_SEPARATOR = "╭";
    static constexpr char* LEFT_NAME_SEPARATOR = "╮";
};


#endif //GAMIFY_LIFE_BORDERWINDOW_HPP