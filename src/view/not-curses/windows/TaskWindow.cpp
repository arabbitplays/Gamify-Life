//
// Created by oschdi on 08.10.25.
//

#include "../../../../include/view/not_curses/windows/TaskWindow.hpp"

#include <cmath>
#include <vector>

#include "view/not_curses/widgets/Table.hpp"
#include "view/not_curses/widgets/WidgetUtil.hpp"

TaskWindow::TaskWindow(const std::shared_ptr<TaskController> &task_controller,
            const std::shared_ptr<ProfileController> &profile_controller, const PlaneHandle &parent_plane)
            : BorderWindow(TASK_WINDOW_NAME, parent_plane, glm::ivec2(10, 10), TOP_RIGHT),
            task_controller(task_controller), profile_controller(profile_controller) {

    setMargin(glm::ivec2(2, 1));
    tasks_table = std::make_shared<SelectionTable>(2);
}

void TaskWindow::draw() {
    BorderWindow::draw();

    tasks_table->clear();
    WidgetUtil::fillTableWithTaskList(tasks_table, task_controller->getAvailableTasks());

    if (tasks_table->isEmpty()) {
        active = false;
        content_plane->writeText(glm::ivec2(0), "No more tasks for today! :)", GOLD, BOLD);
    } else {
        tasks_table->setActive(active);
        glm::ivec2 content_size = content_plane->getExtent();
        glm::ivec2 table_size = glm::ivec2(content_size.x, 20);
        tasks_table->drawToPlane(content_plane, glm::ivec2(0), table_size);
    }

    drawControlTips({"i - insert", "j - \u2193", "k - \u2191"});
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
    if (input.evtype == NCTYPE_PRESS && input.id == 'j') {
        tasks_table->moveSelectionDown();
    }

    if (input.evtype == NCTYPE_PRESS && input.id == 'k') {
        tasks_table->moveSelectionUp();
    }

    if (input.evtype == NCTYPE_PRESS && input.id == NCKEY_ENTER) {
        profile_controller->addDoneTaskToday(tasks_table->getSelectedKey());
        active = false;
    }

    if (input.evtype == NCTYPE_PRESS && input.id == NCKEY_ESC) {
        active = false;
    }
}
