//
// Created by oschdi on 08.10.25.
//

#include "../../../../include/view/not_curses/windows/TaskWindow.hpp"

#include <cmath>
#include <vector>

#include "view/not_curses/widgets/Table.hpp"
#include "view/not_curses/widgets/WidgetUtil.hpp"

void TaskWindow::draw() {
    BorderWindow::draw();
    uint32_t col_distance = 20;

    std::shared_ptr<Table> task_table = WidgetUtil::convertTaskListToTable(task_controller->getAvailableTasks());
    glm::ivec2 content_size = content_plane->getExtent();
    glm::ivec2 table_size = glm::ivec2(content_size.x, 20);
    task_table->drawToPlane(content_plane, glm::ivec2(0), table_size);
}

void TaskWindow::handleInput(ncinput input) {
    BorderWindow::handleInput(input);

    if (active) {
        handleActiveInput(input);
    } else {
        if (input.evtype == NCTYPE_PRESS && input.id == 'i') {
            active = true;
        }
    }
}

void TaskWindow::handleActiveInput(ncinput input) {

}
