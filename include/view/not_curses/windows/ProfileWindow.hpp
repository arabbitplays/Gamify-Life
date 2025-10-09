//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_PROFILEWINDOW_HPP
#define GAMIFY_LIFE_PROFILEWINDOW_HPP
#include "BorderWindow.hpp"
#include "controller/ProfileController.hpp"
#include "view/not_curses/widgets/SelectionTable.hpp"


class ProfileWindow : public BorderWindow {
public:
    ProfileWindow(const std::shared_ptr<ProfileController> &profile_controller, const PlaneHandle &parent_plane);
    void draw() override;

private:
    std::shared_ptr<ProfileController> profile_controller;

    SelectionTableHandle done_tasks_table;

};


#endif //GAMIFY_LIFE_PROFILEWINDOW_HPP