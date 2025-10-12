//
// Created by oschdi on 12.10.25.
//

#ifndef GAMIFY_LIFE_STATWINDOW_HPP
#define GAMIFY_LIFE_STATWINDOW_HPP
#include "BorderWindow.hpp"
#include "controller/ProfileController.hpp"
#include "view/not_curses/widgets/Histogram.hpp"


class StatWindow : public BorderWindow {
public:
    StatWindow(const std::shared_ptr<ProfileController>& profile_controller, const PlaneHandle& parent_plane);
    void draw() override;

private:
    std::shared_ptr<ProfileController> profile_controller;

    HistogramHandle total_score_histogram;
};


#endif //GAMIFY_LIFE_STATWINDOW_HPP