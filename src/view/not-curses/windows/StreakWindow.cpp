//
// Created by oschdi on 11.10.25.
//

#include "view/not_curses/windows/StreakWindow.hpp"

StreakWindow::StreakWindow(const std::shared_ptr<ProfileController> &profile_controller,
    const PlaneHandle &parent_plane) : BorderWindow("Streaks", parent_plane, glm::ivec2(10, 10), BOTTOM_LEFT), profile_controller(profile_controller) {
    setMargin(glm::ivec2(2, 1));
    streak_matrix = std::make_shared<StreakMatrix>();
}

void StreakWindow::draw() {
    BorderWindow::draw();

    std::vector<StreakHandle> streaks = profile_controller->getStreaks();
    streak_matrix->clear();
    for (const auto& streak : streaks) {
        streak_matrix->addStreak(streak);
    }

    streak_matrix->drawToPlane(content_plane, glm::ivec2(0), content_plane->getExtent());
}
