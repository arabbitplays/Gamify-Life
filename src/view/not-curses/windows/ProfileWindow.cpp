//
// Created by oschdi on 09.10.25.
//

#include "view/not_curses/windows/ProfileWindow.hpp"

#include "view/not_curses/widgets/DateUtil.hpp"
#include "view/not_curses/widgets/Table.hpp"
#include "view/not_curses/widgets/WidgetUtil.hpp"

ProfileWindow::ProfileWindow(const std::shared_ptr<ProfileController> &profile_controller, const PlaneHandle &parent_plane)
    : BorderWindow("Profile", parent_plane, glm::ivec2(10, 10), TOP_LEFT), profile_controller(profile_controller) {

    setMargin(glm::ivec2(2, 1));
    done_tasks_table = std::make_shared<SelectionTable>(2);
    displayed_date = Date::createToday();
}

void ProfileWindow::draw() {
    name = "Profile: " + profile_controller->getName();

    BorderWindow::draw();
    uint32_t displayed_total_score = std::floor(profile_controller->getTotalScoreAtDate(displayed_date));

    content_plane->writeText(glm::ivec2(0, 0), DateUtil::getWeekdayAsString(displayed_date) + " " + DateUtil::getDateAsString(displayed_date));
    content_plane->writeText(glm::ivec2(0, 2), "Total Score: " + std::to_string(displayed_total_score), GOLD, BOLD);

    done_tasks_table->clear();
    WidgetUtil::fillTableWithTaskList(done_tasks_table, profile_controller->getTasksDoneAtDate(displayed_date));
    glm::ivec2 content_size = content_plane->getExtent();
    glm::ivec2 table_size = glm::ivec2(content_size.x, 20);
    done_tasks_table->drawToPlane(content_plane, glm::ivec2(0, 3), table_size);
}

void ProfileWindow::handleInput(ncinput input) {
    BorderWindow::handleInput(input);

    if (input.evtype == NCTYPE_PRESS && input.id == 'h') {
        displayed_date = displayed_date.createPrev();
    }

    if (input.evtype == NCTYPE_PRESS && input.id == 'l') {
        displayed_date = displayed_date.createNext();
    }
}
