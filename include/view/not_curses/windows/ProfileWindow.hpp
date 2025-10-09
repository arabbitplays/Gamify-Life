//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_PROFILEWINDOW_HPP
#define GAMIFY_LIFE_PROFILEWINDOW_HPP
#include "BorderWindow.hpp"
#include "controller/ProfileController.hpp"


class ProfileWindow : public BorderWindow {
public:
    ProfileWindow(const std::shared_ptr<ProfileController> &profile_controller, const PlaneHandle &parent_plane)
    : BorderWindow("Profile", parent_plane, glm::ivec2(10, 10), TOP_LEFT), profile_controller(profile_controller) {
        setMargin(glm::ivec2(2, 1));
    }
    void draw() override;

private:
    std::shared_ptr<ProfileController> profile_controller;
};


#endif //GAMIFY_LIFE_PROFILEWINDOW_HPP