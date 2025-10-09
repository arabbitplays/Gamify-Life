//
// Created by oschdi on 09.10.25.
//

#include "view/not_curses/windows/ProfileWindow.hpp"

#include "view/not_curses/widgets/Table.hpp"
#include "view/not_curses/widgets/WidgetUtil.hpp"

void ProfileWindow::draw() {
    name = "Profile: " + profile_controller->getName();

    BorderWindow::draw();
    uint32_t displayed_total_score = std::floor(profile_controller->getTotalScoreToday());
    content_plane->writeText(glm::ivec2(0, 0), "Total Score: " + std::to_string(displayed_total_score), GOLD, BOLD);

    std::shared_ptr<Table> done_tasks_table = WidgetUtil::convertTaskListToTable(profile_controller->getTasksDoneToday());
    glm::ivec2 content_size = content_plane->getExtent();
    glm::ivec2 table_size = glm::ivec2(content_size.x, 20);
    done_tasks_table->drawToPlane(content_plane, glm::ivec2(0, 2), table_size);
}
