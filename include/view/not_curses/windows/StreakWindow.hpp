//
// Created by oschdi on 11.10.25.
//

#ifndef GAMIFY_LIFE_STREAKWINDOW_HPP
#define GAMIFY_LIFE_STREAKWINDOW_HPP
#include "BorderWindow.hpp"
#include "controller/ProfileController.hpp"
#include "view/not_curses/widgets/StreakMatrix.hpp"

class StreakWindow : public BorderWindow {
public:
    StreakWindow(const std::shared_ptr<ProfileController> &profile_controller, const PlaneHandle &parent_plane);

    void draw() override;

private:
    std::shared_ptr<ProfileController> profile_controller;
    StreakMatrixHandle streak_matrix;
};


#endif //GAMIFY_LIFE_STREAKWINDOW_HPP