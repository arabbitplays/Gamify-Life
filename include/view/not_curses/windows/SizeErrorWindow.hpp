//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_SIZEERRORWINDOW_HPP
#define GAMIFY_LIFE_SIZEERRORWINDOW_HPP
#include "NotCursesWindow.hpp"


class SizeErrorWindow : public NotCursesWindow {
public:
    SizeErrorWindow(const PlaneHandle& parent_plane) : NotCursesWindow(parent_plane, glm::ivec2(1, 1), TOP_LEFT) {}
    void draw() const override;
};


#endif //GAMIFY_LIFE_SIZEERRORWINDOW_HPP