//
// Created by oschdi on 12.10.25.
//

#include "view/not_curses/windows/StatWindow.hpp"

#include "view/not_curses/widgets/WidgetUtil.hpp"

StatWindow::StatWindow(const std::shared_ptr<ProfileController>& profile_controller, const PlaneHandle& parent_plane)
        : BorderWindow("Stats", parent_plane, glm::ivec2(16, 10), BOTTOM_RIGHT, STATS_WINDOW),
        profile_controller(profile_controller) {

        setMargin(glm::ivec2(2, 1));
        total_score_histogram = std::make_shared<Histogram>();
}

void StatWindow::draw() {
        BorderWindow::draw();

        glm::ivec2 histogram_size = content_plane->getExtent();

        total_score_histogram->clear();
        WidgetUtil::fillHistogramWithProfile(total_score_histogram, profile_controller, histogram_size);
        total_score_histogram->drawToPlane(content_plane, glm::ivec2(0, 0), histogram_size);

}
